#include "custom_wake_word.h"
#include "audio_service.h"
#include "system_info.h"
#include "assets.h"
#include "settings.h"

#include <esp_log.h>
#include <esp_mn_iface.h>
#include <esp_mn_models.h>
#include <esp_mn_speech_commands.h>
#include <cJSON.h>
#include <algorithm>
#include <atomic>
#include <string>
#include <vector>


#define TAG "CustomWakeWord"

// Lana: "<command>|<prob>" of the last detection, sent to the server with the wake detect (protocol.cc)
std::string g_lana_wake_detail;
// Lana 2.2.5: true while the server says a story/song is playing (push {"type":"lana","action":"media","on":..}).
// Only then are the "dừng lại" stop commands acted on (and wake detection runs during Speaking at all).
std::atomic<bool> g_lana_media_on{false};
#define LANA_STOP_TEXT "Dừng lại"
#define LANA_STOP_MIN_PROB 0.18f


CustomWakeWord::CustomWakeWord()
    : wake_word_pcm_(), wake_word_opus_() {
}

CustomWakeWord::~CustomWakeWord() {
#ifdef LANA_WAKE_AFE
    if (afe_data_ != nullptr) {
        afe_iface_->destroy(afe_data_);
        afe_data_ = nullptr;
    }
#endif
    if (multinet_model_data_ != nullptr && multinet_ != nullptr) {
        multinet_->destroy(multinet_model_data_);
        multinet_model_data_ = nullptr;
    }

    if (wake_word_encode_task_stack_ != nullptr) {
        heap_caps_free(wake_word_encode_task_stack_);
    }

    if (wake_word_encode_task_buffer_ != nullptr) {
        heap_caps_free(wake_word_encode_task_buffer_);
    }

    if (models_ != nullptr) {
        esp_srmodel_deinit(models_);
    }
}

void CustomWakeWord::ParseWakenetModelConfig() {
    // Read index.json
    auto& assets = Assets::GetInstance();
    void* ptr = nullptr;
    size_t size = 0;
    if (!assets.GetAssetData("index.json", ptr, size)) {
        ESP_LOGE(TAG, "Failed to read index.json");
        return;
    }
    cJSON* root = cJSON_ParseWithLength(static_cast<char*>(ptr), size);
    if (root == nullptr) {
        ESP_LOGE(TAG, "Failed to parse index.json");
        return;
    }
    cJSON* multinet_model = cJSON_GetObjectItem(root, "multinet_model");
    if (cJSON_IsObject(multinet_model)) {
        cJSON* language = cJSON_GetObjectItem(multinet_model, "language");
        cJSON* duration = cJSON_GetObjectItem(multinet_model, "duration");
        cJSON* threshold = cJSON_GetObjectItem(multinet_model, "threshold");
        cJSON* commands = cJSON_GetObjectItem(multinet_model, "commands");
        if (cJSON_IsString(language)) {
            language_ = language->valuestring;
        }
        if (cJSON_IsNumber(duration)) {
            duration_ = duration->valueint;
        }
        if (cJSON_IsNumber(threshold)) {
            threshold_ = threshold->valuedouble;
        }
        if (cJSON_IsArray(commands)) {
            for (int i = 0; i < cJSON_GetArraySize(commands); i++) {
                cJSON* command = cJSON_GetArrayItem(commands, i);
                if (cJSON_IsObject(command)) {
                    cJSON* command_name = cJSON_GetObjectItem(command, "command");
                    cJSON* text = cJSON_GetObjectItem(command, "text");
                    cJSON* action = cJSON_GetObjectItem(command, "action");
                    if (cJSON_IsString(command_name) && cJSON_IsString(text) && cJSON_IsString(action)) {
                        commands_.push_back({command_name->valuestring, text->valuestring, action->valuestring});
                        ESP_LOGI(TAG, "Command: %s, Text: %s, Action: %s", command_name->valuestring, text->valuestring, action->valuestring);
                    }
                }
            }
        }
    }
    cJSON_Delete(root);
}


bool CustomWakeWord::Initialize(AudioCodec* codec, srmodel_list_t* models_list) {
    codec_ = codec;
    commands_.clear();

    if (models_list == nullptr) {
        language_ = "cn";
        models_ = esp_srmodel_init("model");
#ifdef CONFIG_CUSTOM_WAKE_WORD
        threshold_ = CONFIG_CUSTOM_WAKE_WORD_THRESHOLD / 100.0f;
        // Several wake phrases may be given separated by ';' (display texts likewise)
        {
            auto split = [](const std::string& s) {
                std::vector<std::string> out;
                size_t start = 0;
                while (start <= s.size()) {
                    size_t end = s.find(';', start);
                    if (end == std::string::npos) end = s.size();
                    std::string item = s.substr(start, end - start);
                    while (!item.empty() && item.front() == ' ') item.erase(item.begin());
                    while (!item.empty() && item.back() == ' ') item.pop_back();
                    if (!item.empty()) out.push_back(item);
                    start = end + 1;
                }
                return out;
            };
            auto words = split(CONFIG_CUSTOM_WAKE_WORD);
            auto texts = split(CONFIG_CUSTOM_WAKE_WORD_DISPLAY);
            for (size_t i = 0; i < words.size(); i++) {
                std::string text = texts.empty() ? words[i] : texts[std::min(i, texts.size() - 1)];
                commands_.push_back({words[i], text, "wake"});
            }
        }
#endif
    } else {
        models_ = models_list;
        ParseWakenetModelConfig();
    }
#ifdef LANA_WAKE_AFE
    // 2.2.5: "dừng lại" (+ southern "yừng lại", "dừng lại đi") as pinyin approximations; action "stop" is ignored
    // unless media is playing, so the TV saying it while idle does nothing.
    for (const char* w : {"deng lai", "dong lai", "yong lai", "deng lai di", "dong lai di"}) {
        commands_.push_back({w, LANA_STOP_TEXT, "stop"});
    }
#endif

    if (models_ == nullptr || models_->num == -1) {
        ESP_LOGE(TAG, "Failed to initialize wakenet model");
        return false;
    }

    // 初始化 multinet (命令词识别)
    mn_name_ = esp_srmodel_filter(models_, ESP_MN_PREFIX, language_.c_str());
    if (mn_name_ == nullptr) {
        ESP_LOGW(TAG, "Language '%s' multinet not found, falling back to any multinet model", language_.c_str());
        mn_name_ = esp_srmodel_filter(models_, ESP_MN_PREFIX, NULL);
    }
    if (mn_name_ == nullptr) {
        ESP_LOGE(TAG, "Failed to initialize multinet, mn_name is nullptr");
        ESP_LOGI(TAG, "Please refer to https://pcn7cs20v8cr.feishu.cn/wiki/CpQjwQsCJiQSWSkYEvrcxcbVnwh to add custom wake word");
        return false;
    }

    multinet_ = esp_mn_handle_from_name(mn_name_);
#ifdef LANA_WAKE_AFE
    // longer window: resets now happen in silence (see DetectionTask), the timeout is only a fallback
    if (duration_ < 6000) duration_ = 6000;
#endif
    multinet_model_data_ = multinet_->create(mn_name_, duration_);
    multinet_->set_det_threshold(multinet_model_data_, threshold_);
    esp_mn_commands_clear();
    for (int i = 0; i < commands_.size(); i++) {
        esp_mn_commands_add(i + 1, commands_[i].command.c_str());
    }
    esp_mn_commands_update();
    
    multinet_->print_active_speech_commands(multinet_model_data_);
    ESP_LOGI(TAG, "MultiNet %s: %d commands, threshold %.2f, duration %d ms", mn_name_, (int)commands_.size(), threshold_, duration_);

#ifdef LANA_WAKE_AFE
    {
        // crash guard: if the AFE path did not survive 20 s twice in a row, fall back to direct MultiNet
        int afe_fail = 0;
        {
            Settings st("lana", true);
            afe_fail = st.GetInt("afe_fail", 0);
            if (afe_fail < 2) st.SetInt("afe_fail", afe_fail + 1);
        }
        std::string input_format(codec_->input_channels(), 'M');
        afe_config_t* cfg = afe_fail >= 2 ? nullptr
            : afe_config_init(input_format.c_str(), models_, AFE_TYPE_SR, AFE_MODE_HIGH_PERF);
        if (afe_fail >= 2) ESP_LOGW(TAG, "AFE front end disabled by crash guard (lana/afe_fail=%d)", afe_fail);
        if (cfg != nullptr) {
            cfg->wakenet_init = false;
            cfg->aec_init = false;
            cfg->se_init = false;
            cfg->ns_init = false;              // NS tends to smear consonants for ASR; AGC + VAD only
            cfg->vad_init = true;
            cfg->vad_mode = VAD_MODE_2;
            cfg->vad_model_name = nullptr;     // WebRTC VAD
            cfg->vad_min_noise_ms = 400;
            cfg->agc_init = true;
            cfg->agc_mode = AFE_AGC_MODE_WEBRTC;
            cfg->agc_compression_gain_db = 9;  // 2.2.3: was 12; INMP441 at 1-3 m is quiet, but +12 dB woke on TV/background
            cfg->agc_target_level_dbfs = 3;
            cfg->afe_linear_gain = 1.0f;
            cfg->afe_perferred_core = 1;
            cfg->afe_perferred_priority = 5;
            cfg->memory_alloc_mode = AFE_MEMORY_ALLOC_MORE_PSRAM;
            afe_iface_ = esp_afe_handle_from_config(cfg);
            afe_data_ = afe_iface_ ? afe_iface_->create_from_config(cfg) : nullptr;
            afe_config_free(cfg);
        }
        if (afe_data_ == nullptr) {
            ESP_LOGW(TAG, "AFE front end unavailable, feeding MultiNet directly");
        } else {
            ESP_LOGI(TAG, "AFE front end on: feed %d fetch %d mn %d", afe_iface_->get_feed_chunksize(afe_data_),
                     afe_iface_->get_fetch_chunksize(afe_data_), multinet_->get_samp_chunksize(multinet_model_data_));
            xTaskCreatePinnedToCore([](void* arg) {
                static_cast<CustomWakeWord*>(arg)->DetectionTask();
                vTaskDelete(NULL);
            }, "lana_wake", 4096 * 2, this, 5, nullptr, 1);
        }
    }
#endif
    return true;
}

#ifdef LANA_WAKE_AFE
void CustomWakeWord::DetectionTask() {
    const int mn_chunk = multinet_->get_samp_chunksize(multinet_model_data_);
    mn_buf_.reserve(mn_chunk * 4);
    int64_t fetched_ms = 0;
    bool marked_ok = false;
    while (true) {
        if (!marked_ok && fetched_ms >= 20000) {
            Settings st("lana", true);
            st.SetInt("afe_fail", 0);
            marked_ok = true;
            ESP_LOGI(TAG, "AFE front end stable");
        }
        if (!running_) {
            vTaskDelay(pdMS_TO_TICKS(30));
            continue;
        }
        auto res = afe_iface_->fetch_with_delay(afe_data_, pdMS_TO_TICKS(200));
        if (need_reset_) {
            need_reset_ = false;
            mn_buf_.clear();
            multinet_->clean(multinet_model_data_);
            silence_ms_ = 0;
            cleaned_in_silence_ = true;
        }
        if (res == nullptr || res->ret_value == ESP_FAIL || !running_) {
            continue;
        }
        int n = res->data_size / sizeof(int16_t);
        int frame_ms = n * 1000 / 16000;
        fetched_ms += frame_ms;
        if (res->vad_state == VAD_SILENCE) {
            silence_ms_ += frame_ms;
            if (silence_ms_ >= 600 && !cleaned_in_silence_) {
                multinet_->clean(multinet_model_data_);   // fresh decoder for the next utterance
                cleaned_in_silence_ = true;
            }
        } else {
            silence_ms_ = 0;
            cleaned_in_silence_ = false;
        }
        StoreWakeWordData(std::vector<int16_t>(res->data, res->data + n));
        mn_buf_.insert(mn_buf_.end(), res->data, res->data + n);
        size_t off = 0;
        while (mn_buf_.size() - off >= (size_t)mn_chunk && running_) {
            DetectChunk(mn_buf_.data() + off);
            off += mn_chunk;
        }
        mn_buf_.erase(mn_buf_.begin(), mn_buf_.begin() + off);
    }
}
#endif

void CustomWakeWord::OnWakeWordDetected(std::function<void(const std::string& wake_word)> callback) {
    wake_word_detected_callback_ = callback;
}

void CustomWakeWord::Start() {
#ifdef LANA_WAKE_AFE
    need_reset_ = true;
#endif
    running_ = true;
}

void CustomWakeWord::Stop() {
    running_ = false;
#ifdef LANA_WAKE_AFE
    if (afe_data_ != nullptr) {
        afe_iface_->reset_buffer(afe_data_);
    }
    need_reset_ = true;
#endif
}

void CustomWakeWord::Feed(const std::vector<int16_t>& data) {
    if (multinet_model_data_ == nullptr || !running_) {
        return;
    }
#ifdef LANA_WAKE_AFE
    if (afe_data_ != nullptr) {
        afe_iface_->feed(afe_data_, data.data());
        return;
    }
#endif

    // If input channels is 2, we need to fetch the left channel data
    if (codec_->input_channels() == 2) {
        auto mono_data = std::vector<int16_t>(data.size() / 2);
        for (size_t i = 0, j = 0; i < mono_data.size(); ++i, j += 2) {
            mono_data[i] = data[j];
        }

        StoreWakeWordData(mono_data);
        DetectChunk(mono_data.data());
    } else {
        StoreWakeWordData(data);
        DetectChunk(const_cast<int16_t*>(data.data()));
    }
}

void CustomWakeWord::DetectChunk(int16_t* chunk) {
    esp_mn_state_t mn_state = multinet_->detect(multinet_model_data_, chunk);
    if (mn_state == ESP_MN_STATE_DETECTING) {
        return;
    } else if (mn_state == ESP_MN_STATE_DETECTED) {
        esp_mn_results_t *mn_result = multinet_->get_results(multinet_model_data_);
        for (int i = 0; i < mn_result->num && running_; i++) {
            ESP_LOGI(TAG, "Custom wake word detected: command_id=%d, string=%s, prob=%f", 
                    mn_result->command_id[i], mn_result->string, mn_result->prob[i]);
            auto& command = commands_[mn_result->command_id[i] - 1];
            if (command.action == "stop" && (!g_lana_media_on.load() || mn_result->prob[i] < LANA_STOP_MIN_PROB)) {
                ESP_LOGI(TAG, "Stop phrase ignored (media %d, prob %.3f)", (int)g_lana_media_on.load(), mn_result->prob[i]);
                continue;
            }
            if (command.action == "wake" || command.action == "stop") {
                last_detected_wake_word_ = command.text;
                char detail[96];
                snprintf(detail, sizeof(detail), "%s|%.3f", command.command.c_str(), mn_result->prob[i]);
                g_lana_wake_detail = detail;
                running_ = false;
                
                if (wake_word_detected_callback_) {
                    wake_word_detected_callback_(last_detected_wake_word_);
                }
            }
        }
        multinet_->clean(multinet_model_data_);
    } else if (mn_state == ESP_MN_STATE_TIMEOUT) {
        ESP_LOGD(TAG, "Command word detection timeout, cleaning state");
        multinet_->clean(multinet_model_data_);
    }
}

size_t CustomWakeWord::GetFeedSize() {
    if (multinet_model_data_ == nullptr) {
        return 0;
    }
#ifdef LANA_WAKE_AFE
    if (afe_data_ != nullptr) {
        return afe_iface_->get_feed_chunksize(afe_data_);
    }
#endif
    return multinet_->get_samp_chunksize(multinet_model_data_);
}

void CustomWakeWord::StoreWakeWordData(const std::vector<int16_t>& data) {
    // store audio data to wake_word_pcm_
    wake_word_pcm_.push_back(data);
    // keep about 2 seconds of data, detect duration is 30ms (sample_rate == 16000, chunksize == 512)
    while (wake_word_pcm_.size() > 2000 / 30) {
        wake_word_pcm_.pop_front();
    }
}

void CustomWakeWord::EncodeWakeWordData() {
    const size_t stack_size = 4096 * 7;
    wake_word_opus_.clear();
    if (wake_word_encode_task_stack_ == nullptr) {
        wake_word_encode_task_stack_ = (StackType_t*)heap_caps_malloc(stack_size, MALLOC_CAP_SPIRAM);
        assert(wake_word_encode_task_stack_ != nullptr);
    }
    if (wake_word_encode_task_buffer_ == nullptr) {
        wake_word_encode_task_buffer_ = (StaticTask_t*)heap_caps_malloc(sizeof(StaticTask_t), MALLOC_CAP_INTERNAL);
        assert(wake_word_encode_task_buffer_ != nullptr);
    }

    wake_word_encode_task_ = xTaskCreateStatic([](void* arg) {
        auto this_ = (CustomWakeWord*)arg;
        {
            auto start_time = esp_timer_get_time();
            auto encoder = std::make_unique<OpusEncoderWrapper>(16000, 1, OPUS_FRAME_DURATION_MS);
            encoder->SetComplexity(0); // 0 is the fastest

            int packets = 0;
            for (auto& pcm: this_->wake_word_pcm_) {
                encoder->Encode(std::move(pcm), [this_](std::vector<uint8_t>&& opus) {
                    std::lock_guard<std::mutex> lock(this_->wake_word_mutex_);
                    this_->wake_word_opus_.emplace_back(std::move(opus));
                    this_->wake_word_cv_.notify_all();
                });
                packets++;
            }
            this_->wake_word_pcm_.clear();

            auto end_time = esp_timer_get_time();
            ESP_LOGI(TAG, "Encode wake word opus %d packets in %ld ms", packets, (long)((end_time - start_time) / 1000));

            std::lock_guard<std::mutex> lock(this_->wake_word_mutex_);
            this_->wake_word_opus_.push_back(std::vector<uint8_t>());
            this_->wake_word_cv_.notify_all();
        }
        vTaskDelete(NULL);
    }, "encode_wake_word", stack_size, this, 2, wake_word_encode_task_stack_, wake_word_encode_task_buffer_);
}

bool CustomWakeWord::GetWakeWordOpus(std::vector<uint8_t>& opus) {
    std::unique_lock<std::mutex> lock(wake_word_mutex_);
    wake_word_cv_.wait(lock, [this]() {
        return !wake_word_opus_.empty();
    });
    opus.swap(wake_word_opus_.front());
    wake_word_opus_.pop_front();
    return !opus.empty();
}
