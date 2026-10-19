// Lana robot: ESP32-S3-WROOM-1 N16R8 purple "Xiaozhi" board (xiaozhi.vn "mach-tim").
// Wiring = bread-compact-wifi: INMP441 WS4/SCK5/SD6, MAX98357A DIN7/BCLK15/LRC16,
// SSD1306 128x64 SDA41/SCL42, Wake button 47, BOOT0, LED 48.
// The xiaozhi.vn wiring sheet puts Vol-/Vol+ on 39/40, but this robot (vendor fw "mach-tim-wartank")
// uses 39/40/43/44 for the tank motors, so those are motor outputs here.
#ifndef _BOARD_CONFIG_H_
#define _BOARD_CONFIG_H_

#include <driver/gpio.h>

#define AUDIO_INPUT_SAMPLE_RATE  16000
#define AUDIO_OUTPUT_SAMPLE_RATE 24000

// 如果使用 Duplex I2S 模式，请注释下面一行
#define AUDIO_I2S_METHOD_SIMPLEX

#ifdef AUDIO_I2S_METHOD_SIMPLEX

#define AUDIO_I2S_MIC_GPIO_WS   GPIO_NUM_4
#define AUDIO_I2S_MIC_GPIO_SCK  GPIO_NUM_5
#define AUDIO_I2S_MIC_GPIO_DIN  GPIO_NUM_6
#define AUDIO_I2S_SPK_GPIO_DOUT GPIO_NUM_7
#define AUDIO_I2S_SPK_GPIO_BCLK GPIO_NUM_15
#define AUDIO_I2S_SPK_GPIO_LRCK GPIO_NUM_16

#else

#define AUDIO_I2S_GPIO_WS GPIO_NUM_4
#define AUDIO_I2S_GPIO_BCLK GPIO_NUM_5
#define AUDIO_I2S_GPIO_DIN  GPIO_NUM_6
#define AUDIO_I2S_GPIO_DOUT GPIO_NUM_7

#endif


#define BUILTIN_LED_GPIO        GPIO_NUM_48
#define BOOT_BUTTON_GPIO        GPIO_NUM_0
#define TOUCH_BUTTON_GPIO       GPIO_NUM_47   // "Wake" button (hold to talk)

// Lana War Tank (vendor board mach-tim-wartank): L298 motor driver, no volume buttons.
// GPIO43/44 are UART0 TX/RX, so the console is on USB-Serial-JTAG.
#define TANK_A_IN1_GPIO GPIO_NUM_39
#define TANK_A_IN2_GPIO GPIO_NUM_40
#define TANK_B_IN1_GPIO GPIO_NUM_43
#define TANK_B_IN2_GPIO GPIO_NUM_44
#define TANK_PWM_HZ     1000

#define DISPLAY_SDA_PIN GPIO_NUM_41
#define DISPLAY_SCL_PIN GPIO_NUM_42
#define DISPLAY_WIDTH   128

#if CONFIG_OLED_SSD1306_128X32
#define DISPLAY_HEIGHT  32
#elif CONFIG_OLED_SSD1306_128X64
#define DISPLAY_HEIGHT  64
#elif CONFIG_OLED_SH1106_128X64
#define DISPLAY_HEIGHT  64
#define SH1106
#else
#error "未选择 OLED 屏幕类型"
#endif

#define DISPLAY_MIRROR_X true
#define DISPLAY_MIRROR_Y true



#endif // _BOARD_CONFIG_H_
