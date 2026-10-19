/*******************************************************************************
* Lana: Be Vietnam Pro Medium 12px, 1bpp, Latin + full Vietnamese (lv_font_conv 1.5.2); line_height trimmed 20->18 to keep the stock 128x64 OLED layout.
 * Size: 12 px
 * Bpp: 1
 * Opts: --font /usr/share/fonts/truetype/sand-box/google/Be Vietnam Pro/BeVietnamPro-Medium.ttf -r 0x20-0x7E -r 0xA0-0x17F -r 0x1A0-0x1B0 -r 0x300-0x303 -r 0x309 -r 0x323 -r 0x1EA0-0x1EF9 -r 0x2010-0x2027 -r 0x2030-0x203A -r 0x20AB -r 0x20AC -r 0x2122 --size 12 --bpp 1 --format lvgl --lv-include lvgl.h --no-compress --force-fast-kern-format -o main/fonts/font_lana_vi_12_1.c
 ******************************************************************************/

#ifdef LV_LVGL_H_INCLUDE_SIMPLE
#include "lvgl.h"
#else
#include "lvgl.h"
#endif

#ifndef FONT_LANA_VI_14_1
#define FONT_LANA_VI_14_1 1
#endif

#if FONT_LANA_VI_14_1

/*-----------------
 *    BITMAPS
 *----------------*/

/*Store the image of the glyphs*/
static LV_ATTRIBUTE_LARGE_CONST const uint8_t glyph_bitmap[] = {
    /* U+0020 " " */
    0x0,

    /* U+0021 "!" */
    0xfe, 0xc0,

    /* U+0022 "\"" */
    0xb6, 0x80,

    /* U+0023 "#" */
    0x12, 0x36, 0x36, 0xff, 0x24, 0x24, 0xfe, 0x6c,
    0x48, 0x48,

    /* U+0024 "$" */
    0x8, 0x39, 0xba, 0x54, 0x87, 0x83, 0x85, 0x4a,
    0xfc, 0xf0, 0x40,

    /* U+0025 "%" */
    0x62, 0x4b, 0x25, 0xc, 0x80, 0x80, 0x40, 0x4c,
    0x29, 0x34, 0x91, 0x80,

    /* U+0026 "&" */
    0x30, 0x48, 0x48, 0x48, 0x70, 0x72, 0x9a, 0x8e,
    0x8c, 0x7a,

    /* U+0027 "'" */
    0xe0,

    /* U+0028 "(" */
    0x13, 0x44, 0x88, 0x88, 0x88, 0x46, 0x31,

    /* U+0029 ")" */
    0x8c, 0x22, 0x11, 0x11, 0x11, 0x26, 0xc8,

    /* U+002A "*" */
    0x25, 0x7e, 0xe5, 0x0,

    /* U+002B "+" */
    0x21, 0x3e, 0x42, 0x0,

    /* U+002C "," */
    0x36,

    /* U+002D "-" */
    0xf0,

    /* U+002E "." */
    0xc0,

    /* U+002F "/" */
    0xc, 0x20, 0x86, 0x10, 0x41, 0xc, 0x20, 0x86,
    0x10, 0x40,

    /* U+0030 "0" */
    0x38, 0x8a, 0xc, 0x18, 0x30, 0x60, 0xc1, 0x44,
    0x70,

    /* U+0031 "1" */
    0x3c, 0x92, 0x49, 0x24,

    /* U+0032 "2" */
    0x7b, 0x3c, 0x41, 0xc, 0x21, 0x8c, 0x63, 0xf0,

    /* U+0033 "3" */
    0x7b, 0x38, 0x41, 0x38, 0x30, 0x61, 0xcd, 0xe0,

    /* U+0034 "4" */
    0xc, 0xc, 0x1c, 0x14, 0x24, 0x64, 0x44, 0xff,
    0x4, 0x4,

    /* U+0035 "5" */
    0x7d, 0xc, 0x3e, 0xcc, 0x10, 0x61, 0xc9, 0xe0,

    /* U+0036 "6" */
    0x39, 0x84, 0x20, 0xfb, 0x38, 0x61, 0x4c, 0xe0,

    /* U+0037 "7" */
    0xfc, 0x30, 0x86, 0x10, 0x42, 0x8, 0x20, 0x80,

    /* U+0038 "8" */
    0x7b, 0x38, 0x63, 0x7b, 0x38, 0x61, 0xcd, 0xe0,

    /* U+0039 "9" */
    0x73, 0x28, 0x61, 0xcd, 0xf0, 0x42, 0x1b, 0xc0,

    /* U+003A ":" */
    0xc6,

    /* U+003B ";" */
    0xc7, 0x0,

    /* U+003C "<" */
    0x1b, 0xb0, 0xc1, 0x80,

    /* U+003D "=" */
    0xfc, 0x0, 0x3f,

    /* U+003E ">" */
    0xc3, 0x86, 0x6c, 0x0,

    /* U+003F "?" */
    0x7b, 0x38, 0x41, 0x18, 0xc2, 0x0, 0x20, 0x80,

    /* U+0040 "@" */
    0x1f, 0x4, 0x11, 0x1, 0x47, 0x99, 0x93, 0x22,
    0x64, 0x4c, 0xc9, 0x4e, 0xc4, 0x10, 0x7e, 0x0,

    /* U+0041 "A" */
    0x1c, 0x1c, 0x14, 0x34, 0x36, 0x26, 0x22, 0x7f,
    0x43, 0x41,

    /* U+0042 "B" */
    0xf9, 0x1a, 0x14, 0x28, 0xdf, 0x21, 0xc1, 0x83,
    0xf8,

    /* U+0043 "C" */
    0x3c, 0x46, 0xc2, 0x80, 0x80, 0x80, 0x80, 0xc2,
    0x46, 0x3c,

    /* U+0044 "D" */
    0xf9, 0x1a, 0x14, 0x18, 0x30, 0x60, 0xc2, 0x8d,
    0xf0,

    /* U+0045 "E" */
    0xfc, 0x21, 0x8, 0x7e, 0x10, 0x87, 0xc0,

    /* U+0046 "F" */
    0xfe, 0x8, 0x20, 0x83, 0xe8, 0x20, 0x82, 0x0,

    /* U+0047 "G" */
    0x3e, 0x63, 0x41, 0x80, 0x80, 0x8f, 0x81, 0xc1,
    0x62, 0x3c,

    /* U+0048 "H" */
    0x83, 0x6, 0xc, 0x18, 0x3f, 0xe0, 0xc1, 0x83,
    0x4,

    /* U+0049 "I" */
    0xff, 0xc0,

    /* U+004A "J" */
    0x11, 0x11, 0x11, 0x11, 0x3e,

    /* U+004B "K" */
    0x8d, 0x32, 0x45, 0x8e, 0x1c, 0x2c, 0x4c, 0x89,
    0x18,

    /* U+004C "L" */
    0x84, 0x21, 0x8, 0x42, 0x10, 0x87, 0xc0,

    /* U+004D "M" */
    0xc3, 0xc3, 0xe7, 0xa7, 0xa5, 0xbd, 0x99, 0x99,
    0x81, 0x81,

    /* U+004E "N" */
    0x83, 0x87, 0x8f, 0x1b, 0x33, 0x63, 0xc7, 0x87,
    0x4,

    /* U+004F "O" */
    0x3e, 0x31, 0x90, 0x50, 0x18, 0xc, 0x6, 0x2,
    0x82, 0x63, 0x1f, 0x0,

    /* U+0050 "P" */
    0xfa, 0x38, 0x61, 0x86, 0x3f, 0xa0, 0x82, 0x0,

    /* U+0051 "Q" */
    0x3e, 0x31, 0x90, 0x50, 0x18, 0xc, 0x6, 0x12,
    0x8f, 0x63, 0xf, 0xc0,

    /* U+0052 "R" */
    0xfa, 0x38, 0x61, 0x8f, 0xe9, 0xa2, 0x8e, 0x10,

    /* U+0053 "S" */
    0x3c, 0x8d, 0xb, 0x7, 0xc3, 0xc0, 0xa1, 0x62,
    0x78,

    /* U+0054 "T" */
    0xfe, 0x20, 0x40, 0x81, 0x2, 0x4, 0x8, 0x10,
    0x20,

    /* U+0055 "U" */
    0x83, 0x6, 0xc, 0x18, 0x30, 0x60, 0xc1, 0x44,
    0x70,

    /* U+0056 "V" */
    0xc1, 0x43, 0x63, 0x62, 0x26, 0x26, 0x34, 0x14,
    0x1c, 0x18,

    /* U+0057 "W" */
    0x46, 0x34, 0x63, 0x46, 0x26, 0x72, 0x6d, 0x62,
    0x96, 0x29, 0x43, 0x9c, 0x39, 0xc1, 0x8c,

    /* U+0058 "X" */
    0xc7, 0x89, 0xb1, 0x43, 0x87, 0xa, 0x36, 0xc5,
    0x8c,

    /* U+0059 "Y" */
    0xc6, 0x89, 0xb1, 0x42, 0x82, 0x4, 0x8, 0x10,
    0x20,

    /* U+005A "Z" */
    0xfe, 0xc, 0x30, 0x41, 0x86, 0x8, 0x30, 0xc1,
    0xfc,

    /* U+005B "[" */
    0xf2, 0x49, 0x24, 0x92, 0x4e,

    /* U+005C "\\" */
    0xc1, 0x4, 0x18, 0x20, 0x82, 0x4, 0x10, 0x41,
    0x82, 0x8,

    /* U+005D "]" */
    0xe4, 0x92, 0x49, 0x24, 0x9e,

    /* U+005E "^" */
    0x22, 0x80,

    /* U+005F "_" */
    0xfc,

    /* U+0060 "`" */
    0x48,

    /* U+0061 "a" */
    0x77, 0x38, 0x61, 0x87, 0x37, 0x40,

    /* U+0062 "b" */
    0x82, 0x8, 0x2e, 0xce, 0x18, 0x61, 0xce, 0xe0,

    /* U+0063 "c" */
    0x7b, 0x28, 0x20, 0x83, 0x27, 0x80,

    /* U+0064 "d" */
    0x4, 0x10, 0x5f, 0xce, 0x18, 0x61, 0xcd, 0xf0,

    /* U+0065 "e" */
    0x7b, 0x38, 0x7f, 0x83, 0x37, 0x80,

    /* U+0066 "f" */
    0x34, 0x4f, 0x44, 0x44, 0x44,

    /* U+0067 "g" */
    0x77, 0x38, 0x61, 0x87, 0x37, 0xc1, 0xcd, 0xe0,

    /* U+0068 "h" */
    0x84, 0x21, 0xe8, 0xc6, 0x31, 0x8c, 0x40,

    /* U+0069 "i" */
    0xdf, 0xc0,

    /* U+006A "j" */
    0x24, 0x12, 0x49, 0x24, 0x9c,

    /* U+006B "k" */
    0x84, 0x21, 0x3b, 0x73, 0x94, 0xb4, 0xc0,

    /* U+006C "l" */
    0xff, 0xc0,

    /* U+006D "m" */
    0xf7, 0x44, 0x62, 0x31, 0x18, 0x8c, 0x46, 0x22,

    /* U+006E "n" */
    0xf4, 0x63, 0x18, 0xc6, 0x20,

    /* U+006F "o" */
    0x7b, 0x38, 0x61, 0x87, 0x37, 0x80,

    /* U+0070 "p" */
    0xfb, 0x38, 0x61, 0x87, 0x3f, 0xa0, 0x82, 0x0,

    /* U+0071 "q" */
    0x77, 0x38, 0x61, 0x87, 0x37, 0xc1, 0x4, 0x10,

    /* U+0072 "r" */
    0xfa, 0x49, 0x20,

    /* U+0073 "s" */
    0x74, 0x70, 0xe0, 0xc5, 0xc0,

    /* U+0074 "t" */
    0x44, 0xf4, 0x44, 0x44, 0x30,

    /* U+0075 "u" */
    0x8c, 0x63, 0x18, 0xcd, 0xe0,

    /* U+0076 "v" */
    0x44, 0x89, 0xb1, 0x42, 0x87, 0x4, 0x0,

    /* U+0077 "w" */
    0x4c, 0x53, 0x34, 0xe9, 0xaa, 0x3b, 0x8c, 0xe3,
    0x30,

    /* U+0078 "x" */
    0x45, 0xb3, 0x8c, 0x39, 0xb4, 0x40,

    /* U+0079 "y" */
    0xc7, 0x34, 0x92, 0x78, 0xc3, 0xc, 0x23, 0x0,

    /* U+007A "z" */
    0xf8, 0xcc, 0x46, 0x63, 0xe0,

    /* U+007B "{" */
    0x19, 0x8, 0x42, 0x13, 0x4, 0x21, 0x8, 0x41,
    0x80,

    /* U+007C "|" */
    0xff, 0xff,

    /* U+007D "}" */
    0xc1, 0x8, 0x42, 0x10, 0x64, 0x21, 0x8, 0x4c,
    0x0,

    /* U+007E "~" */
    0xdb,

    /* U+00A0 " " */
    0x0,

    /* U+00A1 "¡" */
    0xdf, 0xc0,

    /* U+00A2 "¢" */
    0x10, 0xe5, 0xe5, 0x92, 0x45, 0xce, 0x10,

    /* U+00A3 "£" */
    0x3d, 0x84, 0x10, 0x43, 0xe2, 0x8, 0x63, 0xf0,

    /* U+00A4 "¤" */
    0x1, 0xf6, 0xd1, 0x45, 0xb7, 0xc0,

    /* U+00A5 "¥" */
    0xc6, 0x89, 0x13, 0x62, 0x8f, 0x84, 0x3e, 0x10,
    0x20,

    /* U+00A6 "¦" */
    0xfe, 0x7e,

    /* U+00A7 "§" */
    0x3c, 0x8d, 0xa, 0x3, 0x89, 0xe0, 0xc1, 0x7e,
    0x38, 0xe, 0x14, 0x67, 0x80,

    /* U+00A8 "¨" */
    0x99,

    /* U+00A9 "©" */
    0x3e, 0x31, 0xb7, 0x74, 0x5a, 0xd, 0x17, 0x76,
    0xc6, 0x3e, 0x0,

    /* U+00AA "ª" */
    0x63, 0xff,

    /* U+00AB "«" */
    0x12, 0x64, 0xc8, 0x64, 0x12,

    /* U+00AC "¬" */
    0xfc, 0x10, 0x40,

    /* U+00AD "­" */
    0xf0,

    /* U+00AE "®" */
    0x75, 0x6b, 0x17, 0x0,

    /* U+00AF "¯" */
    0xf0,

    /* U+00B0 "°" */
    0x69, 0x99, 0x60,

    /* U+00B1 "±" */
    0x21, 0x3e, 0x42, 0x3, 0xe0,

    /* U+00B2 "²" */
    0x69, 0x36, 0xf0,

    /* U+00B3 "³" */
    0x7d, 0x29, 0x70,

    /* U+00B4 "´" */
    0x60,

    /* U+00B5 "µ" */
    0x8a, 0x28, 0xa2, 0x8a, 0x6f, 0xe0, 0x82, 0x0,

    /* U+00B6 "¶" */
    0x7f, 0xdf, 0x7d, 0x34, 0x51, 0x45, 0x14,

    /* U+00B7 "·" */
    0xc0,

    /* U+00B8 "¸" */
    0x47, 0x80,

    /* U+00B9 "¹" */
    0x75, 0x40,

    /* U+00BA "º" */
    0x69, 0x96,

    /* U+00BB "»" */
    0x4c, 0x36, 0x1b, 0x36, 0x4c,

    /* U+00BC "¼" */
    0x41, 0x8, 0x61, 0x8, 0x22, 0x0, 0xcc, 0x11,
    0x84, 0x50, 0x8f, 0x20, 0x40,

    /* U+00BD "½" */
    0x43, 0x8, 0x41, 0x18, 0x22, 0x0, 0x8c, 0x12,
    0x84, 0x10, 0x84, 0x21, 0xe0,

    /* U+00BE "¾" */
    0xe1, 0x8, 0x62, 0x88, 0x72, 0x0, 0x4c, 0x11,
    0x86, 0x50, 0x8f, 0x20, 0x40,

    /* U+00BF "¿" */
    0x10, 0x40, 0x4, 0x31, 0x88, 0x21, 0xcd, 0xe0,

    /* U+00C0 "À" */
    0x10, 0x8, 0x0, 0x1c, 0x1c, 0x14, 0x34, 0x36,
    0x26, 0x22, 0x7f, 0x43, 0x41,

    /* U+00C1 "Á" */
    0x4, 0x8, 0x0, 0x1c, 0x1c, 0x14, 0x34, 0x36,
    0x26, 0x22, 0x7f, 0x43, 0x41,

    /* U+00C2 "Â" */
    0x8, 0x14, 0x36, 0x1c, 0x1c, 0x14, 0x34, 0x36,
    0x26, 0x22, 0x7f, 0x43, 0x41,

    /* U+00C3 "Ã" */
    0x1c, 0x2c, 0x0, 0x1c, 0x1c, 0x14, 0x34, 0x36,
    0x26, 0x22, 0x7f, 0x43, 0x41,

    /* U+00C4 "Ä" */
    0x24, 0x24, 0x18, 0x3c, 0x3c, 0x34, 0x64, 0x66,
    0x66, 0x7e, 0xc3, 0xc3,

    /* U+00C5 "Å" */
    0x10, 0x50, 0xa0, 0x81, 0x7, 0xa, 0x14, 0x6c,
    0xd9, 0x17, 0xfc, 0x70, 0x40,

    /* U+00C6 "Æ" */
    0xf, 0xe3, 0x80, 0x70, 0xa, 0x3, 0x40, 0x4f,
    0x99, 0x3, 0xe0, 0xc4, 0x10, 0xfc,

    /* U+00C7 "Ç" */
    0x3c, 0x63, 0x41, 0x80, 0x80, 0x80, 0x80, 0xc1,
    0x63, 0x3e, 0x1c, 0x4, 0x18,

    /* U+00C8 "È" */
    0x41, 0x1, 0xf8, 0x42, 0x10, 0xfc, 0x21, 0xf,
    0x80,

    /* U+00C9 "É" */
    0x11, 0x1, 0xf8, 0x42, 0x10, 0xfc, 0x21, 0xf,
    0x80,

    /* U+00CA "Ê" */
    0x22, 0x97, 0xf8, 0x42, 0x10, 0xfc, 0x21, 0xf,
    0x80,

    /* U+00CB "Ë" */
    0x49, 0x2f, 0xe0, 0x82, 0x8, 0x3e, 0x82, 0x8,
    0x3f,

    /* U+00CC "Ì" */
    0x91, 0x55, 0x55, 0x40,

    /* U+00CD "Í" */
    0x62, 0xaa, 0xaa, 0x80,

    /* U+00CE "Î" */
    0x56, 0xa4, 0x92, 0x49, 0x24,

    /* U+00CF "Ï" */
    0xdd, 0x22, 0x22, 0x22, 0x22, 0x22,

    /* U+00D0 "Ð" */
    0x7c, 0x46, 0x42, 0x41, 0x41, 0xf1, 0x41, 0x42,
    0x46, 0x7c,

    /* U+00D1 "Ñ" */
    0x34, 0xb0, 0x4, 0x1c, 0x3c, 0x78, 0xd9, 0x9b,
    0x1e, 0x3c, 0x38, 0x20,

    /* U+00D2 "Ò" */
    0x10, 0x4, 0x0, 0x7, 0xc6, 0x32, 0xa, 0x3,
    0x1, 0x80, 0xc0, 0x50, 0x4c, 0x63, 0xe0,

    /* U+00D3 "Ó" */
    0x4, 0x6, 0x0, 0x7, 0xc6, 0x32, 0xa, 0x3,
    0x1, 0x80, 0xc0, 0x50, 0x4c, 0x63, 0xe0,

    /* U+00D4 "Ô" */
    0x8, 0xa, 0x0, 0x7, 0xc6, 0x32, 0xa, 0x3,
    0x1, 0x80, 0xc0, 0x50, 0x4c, 0x63, 0xe0,

    /* U+00D5 "Õ" */
    0x1a, 0x16, 0x0, 0x7, 0xc6, 0x32, 0xa, 0x3,
    0x1, 0x80, 0xc0, 0x50, 0x4c, 0x63, 0xe0,

    /* U+00D6 "Ö" */
    0x14, 0xa, 0x0, 0x7, 0xc6, 0x32, 0xa, 0x3,
    0x1, 0x80, 0xc0, 0x50, 0x4c, 0x63, 0xe0,

    /* U+00D7 "×" */
    0xdb, 0x9c, 0xb0,

    /* U+00D8 "Ø" */
    0x1f, 0x31, 0x91, 0xf0, 0x98, 0xcc, 0xc6, 0x43,
    0xe2, 0x63, 0x3e, 0x0,

    /* U+00D9 "Ù" */
    0x20, 0x60, 0x4, 0x18, 0x30, 0x60, 0xc1, 0x83,
    0x6, 0xa, 0x23, 0x80,

    /* U+00DA "Ú" */
    0x8, 0x30, 0x4, 0x18, 0x30, 0x60, 0xc1, 0x83,
    0x6, 0xa, 0x23, 0x80,

    /* U+00DB "Û" */
    0x38, 0x51, 0x14, 0x18, 0x30, 0x60, 0xc1, 0x83,
    0x6, 0xa, 0x23, 0x80,

    /* U+00DC "Ü" */
    0x28, 0x50, 0x6, 0x1c, 0x38, 0x70, 0xe1, 0xc3,
    0x87, 0xb, 0x23, 0x80,

    /* U+00DD "Ý" */
    0x8, 0x20, 0x6, 0x34, 0x4d, 0x8a, 0x14, 0x10,
    0x20, 0x40, 0x81, 0x0,

    /* U+00DE "Þ" */
    0x82, 0xf, 0xa3, 0x86, 0x18, 0xfe, 0x82, 0x0,

    /* U+00DF "ß" */
    0x7b, 0x38, 0x61, 0xba, 0x38, 0x61, 0x8e, 0xe0,

    /* U+00E0 "à" */
    0x60, 0x80, 0x1d, 0xce, 0x18, 0x61, 0xcd, 0xd0,

    /* U+00E1 "á" */
    0x18, 0x40, 0x1d, 0xce, 0x18, 0x61, 0xcd, 0xd0,

    /* U+00E2 "â" */
    0x31, 0xa0, 0x1d, 0xce, 0x18, 0x61, 0xcd, 0xd0,

    /* U+00E3 "ã" */
    0x69, 0x60, 0x1d, 0xce, 0x18, 0x61, 0xcd, 0xd0,

    /* U+00E4 "ä" */
    0x49, 0x20, 0x1d, 0xce, 0x18, 0x61, 0xcd, 0xd0,

    /* U+00E5 "å" */
    0x38, 0xa3, 0x80, 0x7f, 0x38, 0x61, 0x87, 0x37,
    0x40,

    /* U+00E6 "æ" */
    0x73, 0xb3, 0x10, 0xc5, 0xff, 0x8c, 0x23, 0x37,
    0x78,

    /* U+00E7 "ç" */
    0x7b, 0x38, 0x20, 0x8d, 0xe2, 0xc, 0x18, 0xc0,

    /* U+00E8 "è" */
    0x60, 0xc0, 0x1e, 0xce, 0x1f, 0xe0, 0xcd, 0xe0,

    /* U+00E9 "é" */
    0x18, 0x40, 0x1e, 0xce, 0x1f, 0xe0, 0xcd, 0xe0,

    /* U+00EA "ê" */
    0x31, 0xa0, 0x1e, 0xce, 0x1f, 0xe0, 0xcd, 0xe0,

    /* U+00EB "ë" */
    0x49, 0x20, 0x1e, 0xce, 0x1f, 0xe0, 0xcd, 0xe0,

    /* U+00EC "ì" */
    0x91, 0x55, 0x50,

    /* U+00ED "í" */
    0x62, 0xaa, 0xa0,

    /* U+00EE "î" */
    0x54, 0x24, 0x92, 0x48,

    /* U+00EF "ï" */
    0xdd, 0x2, 0x22, 0x22, 0x22,

    /* U+00F0 "ð" */
    0xd1, 0xc7, 0x6, 0x7b, 0x38, 0x61, 0x87, 0x27,
    0x80,

    /* U+00F1 "ñ" */
    0x75, 0x81, 0xe8, 0xc6, 0x31, 0x8c, 0x40,

    /* U+00F2 "ò" */
    0x60, 0x80, 0x1e, 0xce, 0x18, 0x61, 0xcd, 0xe0,

    /* U+00F3 "ó" */
    0x18, 0x40, 0x1e, 0xce, 0x18, 0x61, 0xcd, 0xe0,

    /* U+00F4 "ô" */
    0x31, 0xe0, 0x1e, 0xce, 0x18, 0x61, 0xcd, 0xe0,

    /* U+00F5 "õ" */
    0x69, 0x60, 0x1e, 0xce, 0x18, 0x61, 0xcd, 0xe0,

    /* U+00F6 "ö" */
    0x49, 0x20, 0x1e, 0xce, 0x18, 0x61, 0xcd, 0xe0,

    /* U+00F7 "÷" */
    0x21, 0x1, 0xf0, 0x10, 0x80,

    /* U+00F8 "ø" */
    0x5, 0xe5, 0xe5, 0xb6, 0x9c, 0x9e, 0x80,

    /* U+00F9 "ù" */
    0x41, 0x1, 0x18, 0xc6, 0x31, 0x9b, 0xc0,

    /* U+00FA "ú" */
    0x11, 0x1, 0x18, 0xc6, 0x31, 0x9b, 0xc0,

    /* U+00FB "û" */
    0x62, 0x81, 0x18, 0xc6, 0x31, 0x9b, 0xc0,

    /* U+00FC "ü" */
    0x52, 0x81, 0x18, 0xc6, 0x31, 0x9b, 0xc0,

    /* U+00FD "ý" */
    0x18, 0x40, 0x31, 0xcd, 0x24, 0x9e, 0x30, 0xc3,
    0x8, 0xc0,

    /* U+00FE "þ" */
    0x82, 0x8, 0x2e, 0xce, 0x18, 0x61, 0xcf, 0xe8,
    0x20, 0x80,

    /* U+00FF "ÿ" */
    0x49, 0x20, 0x21, 0xcd, 0x24, 0x9a, 0x70, 0xc3,
    0x18, 0xc0,

    /* U+0100 "Ā" */
    0x3c, 0x0, 0x18, 0x18, 0x3c, 0x3c, 0x24, 0x66,
    0x66, 0x7e, 0xc3, 0xc3,

    /* U+0101 "ā" */
    0x78, 0x7, 0x73, 0x86, 0x18, 0x73, 0x74,

    /* U+0102 "Ă" */
    0x20, 0x14, 0x1c, 0x1c, 0x1c, 0x14, 0x34, 0x36,
    0x26, 0x22, 0x7f, 0x43, 0x41,

    /* U+0103 "ă" */
    0x48, 0xe0, 0x1d, 0xce, 0x18, 0x61, 0xcd, 0xd0,

    /* U+0104 "Ą" */
    0x18, 0x38, 0x38, 0x2c, 0x6c, 0x64, 0x46, 0xfe,
    0xc2, 0x82, 0x3, 0x2, 0x3,

    /* U+0105 "ą" */
    0x77, 0x38, 0x61, 0x87, 0x37, 0xc1, 0x8, 0x10,

    /* U+0106 "Ć" */
    0x8, 0x8, 0x0, 0x3c, 0x46, 0xc2, 0x80, 0x80,
    0x80, 0x80, 0xc2, 0x46, 0x3c,

    /* U+0107 "ć" */
    0x10, 0x40, 0x1e, 0xca, 0x8, 0x20, 0xc9, 0xe0,

    /* U+010A "Ċ" */
    0x8, 0x8, 0x0, 0x3c, 0x42, 0x43, 0x80, 0x80,
    0x80, 0x80, 0x43, 0x42, 0x3c,

    /* U+010B "ċ" */
    0x10, 0x40, 0x1e, 0x4e, 0x8, 0x20, 0x4d, 0xe0,

    /* U+010C "Č" */
    0x2c, 0x18, 0x10, 0x3c, 0x46, 0xc2, 0x80, 0x80,
    0x80, 0x80, 0xc2, 0x46, 0x3c,

    /* U+010D "č" */
    0x58, 0xc0, 0x1e, 0xce, 0x8, 0x23, 0xc9, 0xe0,

    /* U+010E "Ď" */
    0x48, 0xe0, 0x87, 0xc8, 0xd0, 0xa0, 0xc1, 0x83,
    0x6, 0x14, 0x6f, 0x80,

    /* U+010F "ď" */
    0x5, 0x5, 0x5, 0x7c, 0xcc, 0x84, 0x84, 0x84,
    0xcc, 0x7c,

    /* U+0110 "Đ" */
    0x7c, 0x46, 0x42, 0x41, 0x41, 0xf1, 0x41, 0x42,
    0x46, 0x7c,

    /* U+0111 "đ" */
    0x4, 0x3c, 0x13, 0xec, 0xd0, 0xa1, 0x42, 0xcc,
    0xf8,

    /* U+0112 "Ē" */
    0x78, 0xf, 0xe0, 0x82, 0x8, 0x3e, 0x82, 0x8,
    0x3f,

    /* U+0113 "ē" */
    0x78, 0x7, 0xb3, 0x87, 0xf8, 0x33, 0x78,

    /* U+0116 "Ė" */
    0x21, 0x1, 0xf8, 0x42, 0x10, 0xf4, 0x21, 0xf,
    0x80,

    /* U+0117 "ė" */
    0x10, 0x40, 0x1e, 0xce, 0x1f, 0xe0, 0xcd, 0xe0,

    /* U+0118 "Ę" */
    0xfe, 0x8, 0x20, 0x83, 0xe8, 0x20, 0x83, 0xf0,
    0x82, 0xc,

    /* U+0119 "ę" */
    0x79, 0x28, 0x61, 0xfe, 0x4, 0xce, 0x20, 0xc0,

    /* U+011A "Ě" */
    0x5a, 0x89, 0xf8, 0x42, 0x10, 0xfc, 0x21, 0xf,
    0x80,

    /* U+011B "ě" */
    0x48, 0xc0, 0x1e, 0xce, 0x1f, 0xe0, 0xcd, 0xe0,

    /* U+011E "Ğ" */
    0x24, 0x1c, 0x0, 0x3e, 0x63, 0x41, 0x80, 0x80,
    0x8f, 0x81, 0xc1, 0x62, 0x3c,

    /* U+011F "ğ" */
    0x48, 0xe0, 0x1d, 0xce, 0x18, 0x61, 0xcd, 0xf0,
    0x73, 0x78,

    /* U+0120 "Ġ" */
    0x8, 0x8, 0x0, 0x3e, 0x63, 0x41, 0x80, 0x80,
    0x8f, 0x81, 0xc1, 0x62, 0x3c,

    /* U+0121 "ġ" */
    0x10, 0x40, 0x1d, 0xce, 0x18, 0x61, 0xcd, 0xf0,
    0x73, 0x78,

    /* U+0126 "Ħ" */
    0x41, 0x20, 0xbf, 0xe8, 0x24, 0x13, 0xf9, 0x4,
    0x82, 0x41, 0x20, 0x80,

    /* U+0127 "ħ" */
    0x43, 0xc4, 0x1e, 0x45, 0x14, 0x51, 0x45, 0x10,

    /* U+0128 "Ĩ" */
    0xfc, 0x24, 0x92, 0x49, 0x24,

    /* U+0129 "ĩ" */
    0xfc, 0x24, 0x92, 0x48,

    /* U+012A "Ī" */
    0xf0, 0x44, 0x44, 0x44, 0x44, 0x44,

    /* U+012B "ī" */
    0xf0, 0x44, 0x44, 0x44, 0x40,

    /* U+012E "Į" */
    0x55, 0x55, 0x56, 0x40,

    /* U+012F "į" */
    0xdf, 0xf8,

    /* U+0130 "İ" */
    0xdf, 0xf8,

    /* U+0131 "ı" */
    0xfe,

    /* U+0139 "Ĺ" */
    0x42, 0x0, 0x20, 0x82, 0x8, 0x20, 0x82, 0x8,
    0x20, 0xfc,

    /* U+013A "ĺ" */
    0x62, 0xaa, 0xaa, 0x80,

    /* U+013D "Ľ" */
    0xa1, 0x41, 0x2, 0x4, 0x8, 0x10, 0x20, 0x40,
    0x81, 0x2, 0x7, 0xe0,

    /* U+013E "ľ" */
    0xbb, 0xa8, 0x88, 0x88, 0x88,

    /* U+0141 "Ł" */
    0x40, 0x81, 0x2, 0x47, 0x98, 0x10, 0x20, 0x40,
    0xfc,

    /* U+0142 "ł" */
    0x44, 0x45, 0x7c, 0x44, 0x44,

    /* U+0143 "Ń" */
    0x8, 0x20, 0x4, 0x1c, 0x3c, 0x78, 0xd9, 0x9b,
    0x1e, 0x3c, 0x38, 0x20,

    /* U+0144 "ń" */
    0x11, 0x1, 0xe8, 0xc6, 0x31, 0x8c, 0x40,

    /* U+0147 "Ň" */
    0x44, 0x50, 0x44, 0x1c, 0x3c, 0x78, 0xd9, 0x9b,
    0x1e, 0x3c, 0x38, 0x20,

    /* U+0148 "ň" */
    0x53, 0x81, 0xe8, 0xc6, 0x31, 0x8c, 0x40,

    /* U+014C "Ō" */
    0x3c, 0x0, 0xf, 0x8c, 0x64, 0x14, 0x6, 0x3,
    0x1, 0x80, 0xa0, 0x98, 0xc7, 0xc0,

    /* U+014D "ō" */
    0x78, 0x7, 0xb3, 0x86, 0x18, 0x73, 0x78,

    /* U+0150 "Ő" */
    0x1a, 0xb, 0x0, 0x7, 0xc6, 0x32, 0xa, 0x3,
    0x1, 0x80, 0xc0, 0x50, 0x4c, 0x63, 0xe0,

    /* U+0151 "ő" */
    0x29, 0xa0, 0x1e, 0xce, 0x18, 0x61, 0xcd, 0xe0,

    /* U+0152 "Œ" */
    0x3f, 0xec, 0x81, 0x10, 0x42, 0x8, 0x41, 0xf,
    0xa1, 0x2, 0x20, 0x64, 0x7, 0xfc,

    /* U+0153 "œ" */
    0x7b, 0xd9, 0xce, 0x10, 0xc3, 0xf8, 0x41, 0x9c,
    0xde, 0xf0,

    /* U+0154 "Ŕ" */
    0x30, 0x80, 0x3e, 0x8e, 0x18, 0x63, 0xfa, 0x68,
    0xa3, 0x84,

    /* U+0155 "ŕ" */
    0x68, 0x7d, 0x24, 0x90,

    /* U+0158 "Ř" */
    0x99, 0xc6, 0x3e, 0x8e, 0x18, 0x63, 0xfa, 0x68,
    0xa3, 0x84,

    /* U+0159 "ř" */
    0xb8, 0x7d, 0x24, 0x90,

    /* U+015A "Ś" */
    0xc, 0x10, 0x1, 0xe4, 0x68, 0x58, 0x3e, 0x1e,
    0x5, 0xb, 0x13, 0xc0,

    /* U+015B "ś" */
    0x11, 0x80, 0xe8, 0xe1, 0xc1, 0x8b, 0x80,

    /* U+015E "Ş" */
    0x3c, 0x8d, 0xb, 0x7, 0xc3, 0xc0, 0xa1, 0x62,
    0x78, 0x60, 0x41, 0x80,

    /* U+015F "ş" */
    0x74, 0x70, 0x78, 0xfc, 0x8e, 0x13, 0x80,

    /* U+0160 "Š" */
    0x2c, 0x30, 0xf2, 0x34, 0x2c, 0x1f, 0xf, 0x2,
    0x85, 0x89, 0xe0,

    /* U+0161 "š" */
    0x53, 0x80, 0xf8, 0x61, 0xc1, 0x8b, 0x80,

    /* U+0162 "Ţ" */
    0xfe, 0x20, 0x40, 0x81, 0x2, 0x4, 0x8, 0x10,
    0x20, 0x40, 0xc1, 0x80,

    /* U+0163 "ţ" */
    0x42, 0x3c, 0x84, 0x21, 0x8, 0x73, 0x84, 0xe0,

    /* U+0164 "Ť" */
    0x28, 0x50, 0x47, 0xf1, 0x2, 0x4, 0x8, 0x10,
    0x20, 0x40, 0x81, 0x0,

    /* U+0165 "ť" */
    0x18, 0x94, 0x8f, 0x21, 0x8, 0x42, 0xc,

    /* U+0166 "Ŧ" */
    0xfe, 0x20, 0x40, 0x81, 0x1f, 0x84, 0x8, 0x10,
    0x20,

    /* U+0167 "ŧ" */
    0x44, 0xf4, 0xe4, 0x44, 0x30,

    /* U+0168 "Ũ" */
    0x74, 0xb0, 0x4, 0x18, 0x30, 0x60, 0xc1, 0x83,
    0x6, 0xa, 0x23, 0x80,

    /* U+0169 "ũ" */
    0x75, 0x81, 0x18, 0xc6, 0x31, 0x9b, 0xc0,

    /* U+016A "Ū" */
    0x78, 0x2, 0xc, 0x18, 0x30, 0x60, 0xc1, 0x83,
    0x5, 0x11, 0xc0,

    /* U+016B "ū" */
    0x78, 0x23, 0x18, 0xc6, 0x33, 0x78,

    /* U+016E "Ů" */
    0x38, 0x50, 0xe0, 0x8, 0x30, 0x60, 0xc1, 0x83,
    0x6, 0xc, 0x14, 0x47, 0x0,

    /* U+016F "ů" */
    0x72, 0x9c, 0x8, 0xc6, 0x31, 0x8c, 0xde,

    /* U+0170 "Ű" */
    0x34, 0x58, 0x4, 0x18, 0x30, 0x60, 0xc1, 0x83,
    0x6, 0xa, 0x23, 0x80,

    /* U+0171 "ű" */
    0x7a, 0x81, 0x18, 0xc6, 0x31, 0x9b, 0xc0,

    /* U+0172 "Ų" */
    0x83, 0x6, 0xc, 0x18, 0x30, 0x60, 0xc1, 0xc6,
    0xf8, 0x61, 0x81, 0x80,

    /* U+0173 "ų" */
    0x8c, 0x63, 0x18, 0xcd, 0xe1, 0x10, 0x40,

    /* U+0174 "Ŵ" */
    0x6, 0x0, 0x60, 0x9, 0xc, 0x63, 0x46, 0x24,
    0x62, 0x4f, 0x66, 0xf6, 0x29, 0x42, 0x94, 0x39,
    0x43, 0x9c, 0x30, 0x80,

    /* U+0175 "ŵ" */
    0xc, 0x2, 0x80, 0x1, 0x31, 0x4c, 0xd3, 0xa6,
    0xa8, 0xee, 0x33, 0x8c, 0xc0,

    /* U+0176 "Ŷ" */
    0x10, 0x53, 0x1a, 0x26, 0xc5, 0xa, 0x8, 0x10,
    0x20, 0x40, 0x80,

    /* U+0177 "ŷ" */
    0x31, 0xa0, 0x31, 0xcd, 0x24, 0x9e, 0x30, 0xc3,
    0x8, 0xc0,

    /* U+0178 "Ÿ" */
    0x34, 0x34, 0xc3, 0x62, 0x26, 0x34, 0x14, 0x18,
    0x8, 0x8, 0x8, 0x8,

    /* U+0179 "Ź" */
    0x8, 0x20, 0x7, 0xf0, 0x61, 0x82, 0xc, 0x30,
    0x41, 0x86, 0xf, 0xe0,

    /* U+017A "ź" */
    0x11, 0x1, 0xf1, 0x98, 0x8c, 0xc7, 0xc0,

    /* U+017B "Ż" */
    0x10, 0x20, 0x7, 0xf0, 0x61, 0x86, 0xc, 0x30,
    0x61, 0x87, 0xf, 0xe0,

    /* U+017C "ż" */
    0x21, 0x1, 0xf1, 0x98, 0x8c, 0xc7, 0xc0,

    /* U+017D "Ž" */
    0x4c, 0x50, 0x47, 0xf0, 0x61, 0x82, 0xc, 0x30,
    0x41, 0x86, 0xf, 0xe0,

    /* U+017E "ž" */
    0x53, 0x1, 0xf1, 0x98, 0x8c, 0xc7, 0xc0,

    /* U+01A0 "Ơ" */
    0x1, 0x1f, 0x98, 0xc8, 0x38, 0xc, 0x6, 0x3,
    0x1, 0x41, 0x31, 0x8f, 0x80,

    /* U+01A1 "ơ" */
    0x4, 0x17, 0xb3, 0x86, 0x18, 0x72, 0x78,

    /* U+01AF "Ư" */
    0x1, 0x83, 0x82, 0x82, 0x82, 0x82, 0x82, 0x82,
    0x82, 0x44, 0x38,

    /* U+01B0 "ư" */
    0x2, 0x6, 0x3c, 0x48, 0x91, 0x22, 0x4c, 0x78,

    /* U+0300 "̀" */
    0xd0,

    /* U+0301 "́" */
    0x58,

    /* U+0302 "̂" */
    0x65,

    /* U+0303 "̃" */
    0xdb,

    /* U+0309 "̉" */
    0xe5, 0x0,

    /* U+0323 "̣" */
    0xc0,

    /* U+1EA0 "Ạ" */
    0x10, 0x70, 0xa1, 0x42, 0x8d, 0x9b, 0x3e, 0xc7,
    0x84, 0x0, 0x81, 0x0,

    /* U+1EA1 "ạ" */
    0x77, 0x38, 0x61, 0x87, 0x37, 0xc0, 0x10, 0x40,

    /* U+1EA2 "Ả" */
    0x38, 0x28, 0x10, 0x0, 0x38, 0x38, 0x28, 0x2c,
    0x6c, 0x64, 0x44, 0xfe, 0xc2, 0x82,

    /* U+1EA3 "ả" */
    0x30, 0xa1, 0x0, 0x77, 0x38, 0x61, 0x87, 0x37,
    0x40,

    /* U+1EA4 "Ấ" */
    0x1, 0x2, 0x1c, 0x0, 0x1c, 0x1c, 0x14, 0x34,
    0x36, 0x26, 0x22, 0x7f, 0x43, 0x41,

    /* U+1EA5 "ấ" */
    0x4, 0x8, 0xc2, 0x40, 0xe, 0xb3, 0x42, 0x85,
    0xb, 0x33, 0xa0,

    /* U+1EA6 "Ầ" */
    0x6, 0x2, 0x1c, 0x0, 0x1c, 0x1c, 0x14, 0x34,
    0x36, 0x26, 0x22, 0x7f, 0x43, 0x41,

    /* U+1EA7 "ầ" */
    0x8, 0x13, 0x12, 0x1, 0xdc, 0xe1, 0x86, 0x1c,
    0xdd,

    /* U+1EA8 "Ẩ" */
    0xe, 0x2, 0x14, 0x28, 0x0, 0x38, 0x38, 0x28,
    0x2c, 0x6c, 0x64, 0x44, 0xfe, 0xc2, 0x82,

    /* U+1EA9 "ẩ" */
    0xc, 0x8, 0xc3, 0x40, 0xe, 0xb3, 0x42, 0x85,
    0xb, 0x33, 0xa0,

    /* U+1EAA "Ẫ" */
    0x1c, 0x2c, 0x8, 0x14, 0x0, 0x1c, 0x1c, 0x14,
    0x34, 0x36, 0x26, 0x22, 0x7f, 0x43, 0x41,

    /* U+1EAB "ẫ" */
    0x69, 0x63, 0x1a, 0x1, 0xdc, 0xe1, 0x86, 0x1c,
    0xdd,

    /* U+1EAC "Ậ" */
    0x10, 0x50, 0xa0, 0x83, 0x85, 0xa, 0x14, 0x6c,
    0xd9, 0xf6, 0x3c, 0x20, 0x4, 0x8,

    /* U+1EAD "ậ" */
    0x10, 0xa4, 0x1d, 0xce, 0x18, 0x61, 0xcd, 0xf0,
    0x4, 0x10,

    /* U+1EAE "Ắ" */
    0x4, 0x8, 0x0, 0x14, 0x1c, 0x1c, 0x1c, 0x14,
    0x34, 0x36, 0x26, 0x22, 0x7f, 0x43, 0x41,

    /* U+1EAF "ắ" */
    0x18, 0x44, 0x8e, 0x1, 0xdc, 0xe1, 0x86, 0x1c,
    0xdd,

    /* U+1EB0 "Ằ" */
    0x10, 0x8, 0x0, 0x14, 0x1c, 0x1c, 0x1c, 0x14,
    0x34, 0x36, 0x26, 0x22, 0x7f, 0x43, 0x41,

    /* U+1EB1 "ằ" */
    0x60, 0x84, 0x8e, 0x1, 0xdc, 0xe1, 0x86, 0x1c,
    0xdd,

    /* U+1EB2 "Ẳ" */
    0x18, 0x28, 0x18, 0x10, 0x28, 0x38, 0x38, 0x38,
    0x28, 0x2c, 0x6c, 0x64, 0x44, 0xfe, 0xc2, 0x82,

    /* U+1EB3 "ẳ" */
    0x30, 0x61, 0x12, 0x38, 0x7, 0x73, 0x86, 0x18,
    0x73, 0x74,

    /* U+1EB4 "Ẵ" */
    0x1c, 0x2c, 0x0, 0x14, 0x1c, 0x1c, 0x1c, 0x14,
    0x34, 0x36, 0x26, 0x22, 0x7f, 0x43, 0x41,

    /* U+1EB5 "ẵ" */
    0x69, 0x64, 0x8e, 0x1, 0xdc, 0xe1, 0x86, 0x1c,
    0xdd,

    /* U+1EB6 "Ặ" */
    0x28, 0x50, 0x60, 0x83, 0x85, 0xa, 0x14, 0x6c,
    0xd9, 0xf6, 0x3c, 0x20, 0x4, 0x8,

    /* U+1EB7 "ặ" */
    0x28, 0xe0, 0x1d, 0xce, 0x18, 0x61, 0xcd, 0xf0,
    0x4, 0x10,

    /* U+1EB8 "Ẹ" */
    0xfc, 0x21, 0x8, 0x7e, 0x10, 0x87, 0xc0, 0x42,
    0x0,

    /* U+1EB9 "ẹ" */
    0x7b, 0x38, 0x7f, 0x83, 0x37, 0x80, 0x10, 0x40,

    /* U+1EBA "Ẻ" */
    0x31, 0x43, 0x0, 0xfe, 0x8, 0x20, 0x83, 0xe8,
    0x20, 0x83, 0xf0,

    /* U+1EBB "ẻ" */
    0x39, 0x61, 0x0, 0x7b, 0x38, 0x7f, 0x83, 0x37,
    0x80,

    /* U+1EBC "Ẽ" */
    0x6b, 0x81, 0xf8, 0x42, 0x10, 0xfc, 0x21, 0xf,
    0x80,

    /* U+1EBD "ẽ" */
    0x69, 0x60, 0x1e, 0xce, 0x1f, 0xe0, 0xcd, 0xe0,

    /* U+1EBE "Ế" */
    0x4, 0x27, 0x0, 0xfa, 0x8, 0x20, 0x83, 0xe8,
    0x20, 0x83, 0xe0,

    /* U+1EBF "ế" */
    0x6, 0x8, 0xc2, 0x40, 0xf, 0x33, 0x42, 0xfd,
    0x3, 0x33, 0xc0,

    /* U+1EC0 "Ề" */
    0x18, 0x5c, 0xf, 0xc2, 0x10, 0x87, 0xe1, 0x8,
    0x7c,

    /* U+1EC1 "ề" */
    0x8, 0x13, 0x12, 0x1, 0xec, 0xe1, 0xfe, 0xc,
    0xde,

    /* U+1EC2 "Ể" */
    0xc, 0x8, 0xa2, 0x80, 0x1f, 0xa0, 0x40, 0x81,
    0x3, 0xe4, 0x8, 0x10, 0x3f, 0x0,

    /* U+1EC3 "ể" */
    0xc, 0x8, 0xc3, 0x40, 0xf, 0x33, 0x42, 0xfd,
    0x3, 0x33, 0xc0,

    /* U+1EC4 "Ễ" */
    0x6b, 0x88, 0xa0, 0x7e, 0x10, 0x84, 0x3f, 0x8,
    0x43, 0xe0,

    /* U+1EC5 "ễ" */
    0x69, 0x63, 0x1a, 0x1, 0xec, 0xe1, 0xfe, 0xc,
    0xde,

    /* U+1EC6 "Ệ" */
    0x22, 0x95, 0xf8, 0x42, 0x10, 0xfc, 0x21, 0xf,
    0x80, 0x84,

    /* U+1EC7 "ệ" */
    0x11, 0xa0, 0x1e, 0xce, 0x1f, 0xe0, 0xcd, 0xe0,
    0x4, 0x10,

    /* U+1EC8 "Ỉ" */
    0x75, 0x4, 0x92, 0x49, 0x24, 0x80,

    /* U+1EC9 "ỉ" */
    0x75, 0x4, 0x92, 0x49, 0x0,

    /* U+1ECA "Ị" */
    0xff, 0xd8,

    /* U+1ECB "ị" */
    0xdf, 0xd8,

    /* U+1ECC "Ọ" */
    0x3e, 0x31, 0x90, 0x50, 0x18, 0xc, 0x6, 0x2,
    0x82, 0x63, 0x1f, 0x0, 0x1, 0x0, 0x80,

    /* U+1ECD "ọ" */
    0x7b, 0x38, 0x61, 0x87, 0x37, 0x80, 0x10, 0x40,

    /* U+1ECE "Ỏ" */
    0x1c, 0xa, 0x2, 0x0, 0x3, 0xe3, 0x19, 0x5,
    0x1, 0x80, 0xc0, 0x60, 0x28, 0x26, 0x31, 0xf0,

    /* U+1ECF "ỏ" */
    0x31, 0xe1, 0x0, 0x7b, 0x38, 0x61, 0x87, 0x37,
    0x80,

    /* U+1ED0 "Ố" */
    0x1, 0x1, 0x87, 0x6, 0xc0, 0x1, 0xf1, 0x8c,
    0x82, 0x80, 0xc0, 0x60, 0x30, 0x14, 0x13, 0x18,
    0xf8,

    /* U+1ED1 "ố" */
    0x4, 0x8, 0xc2, 0x40, 0xf, 0x33, 0x42, 0x85,
    0xb, 0x33, 0xc0,

    /* U+1ED2 "Ồ" */
    0x6, 0x1, 0x87, 0x6, 0xc0, 0x1, 0xf1, 0x8c,
    0x82, 0x80, 0xc0, 0x60, 0x30, 0x14, 0x13, 0x18,
    0xf8,

    /* U+1ED3 "ồ" */
    0x8, 0x13, 0x12, 0x1, 0xec, 0xe1, 0x86, 0x1c,
    0xde,

    /* U+1ED4 "Ổ" */
    0x3, 0x0, 0x82, 0x82, 0x80, 0x1, 0xf1, 0x8c,
    0x82, 0x80, 0xc0, 0x60, 0x30, 0x14, 0x13, 0x18,
    0xf8,

    /* U+1ED5 "ổ" */
    0xc, 0x30, 0x4c, 0x58, 0x7, 0xb3, 0x86, 0x18,
    0x73, 0x78,

    /* U+1ED6 "Ỗ" */
    0x1a, 0x16, 0x2, 0x2, 0x80, 0x1, 0xf1, 0x8c,
    0x82, 0x80, 0xc0, 0x60, 0x30, 0x14, 0x13, 0x18,
    0xf8,

    /* U+1ED7 "ỗ" */
    0x69, 0x63, 0x16, 0x1, 0xec, 0xe1, 0x86, 0x1c,
    0xde,

    /* U+1ED8 "Ộ" */
    0x8, 0xa, 0x0, 0x7, 0xc6, 0x32, 0xa, 0x3,
    0x1, 0x80, 0xc0, 0x50, 0x4c, 0x63, 0xe0, 0x0,
    0x20, 0x10,

    /* U+1ED9 "ộ" */
    0x10, 0xa4, 0x1e, 0xce, 0x18, 0x61, 0xcd, 0xe0,
    0x4, 0x10,

    /* U+1EDA "Ớ" */
    0xc, 0x4, 0x0, 0x47, 0xe6, 0x32, 0xe, 0x3,
    0x1, 0x80, 0xc0, 0x50, 0x4c, 0x63, 0xe0,

    /* U+1EDB "ớ" */
    0x18, 0x40, 0x5e, 0xce, 0x18, 0x61, 0xc9, 0xe0,

    /* U+1EDC "Ờ" */
    0x10, 0xc, 0x0, 0x47, 0xe6, 0x32, 0xe, 0x3,
    0x1, 0x80, 0xc0, 0x50, 0x4c, 0x63, 0xe0,

    /* U+1EDD "ờ" */
    0x60, 0x80, 0x5e, 0xce, 0x18, 0x61, 0xc9, 0xe0,

    /* U+1EDE "Ở" */
    0x18, 0xa, 0x2, 0x0, 0x23, 0xf3, 0x19, 0x7,
    0x1, 0x80, 0xc0, 0x60, 0x28, 0x26, 0x31, 0xf0,

    /* U+1EDF "ở" */
    0x31, 0x61, 0x1, 0x7b, 0x38, 0x61, 0x87, 0x27,
    0x80,

    /* U+1EE0 "Ỡ" */
    0x34, 0x16, 0x0, 0x47, 0xe6, 0x32, 0xe, 0x3,
    0x1, 0x80, 0xc0, 0x50, 0x4c, 0x63, 0xe0,

    /* U+1EE1 "ỡ" */
    0x69, 0x60, 0x5e, 0xce, 0x18, 0x61, 0xc9, 0xe0,

    /* U+1EE2 "Ợ" */
    0x1, 0x1f, 0x98, 0xc8, 0x38, 0xc, 0x6, 0x3,
    0x1, 0x41, 0x31, 0x8f, 0x80, 0x0, 0x80, 0x40,

    /* U+1EE3 "ợ" */
    0x4, 0x17, 0xb3, 0x86, 0x18, 0x72, 0x78, 0x1,
    0x4,

    /* U+1EE4 "Ụ" */
    0x83, 0x6, 0xc, 0x18, 0x30, 0x60, 0xc1, 0x44,
    0x70, 0x0, 0x81, 0x0,

    /* U+1EE5 "ụ" */
    0x8c, 0x63, 0x18, 0xcd, 0xe0, 0x21, 0x0,

    /* U+1EE6 "Ủ" */
    0x38, 0x50, 0x40, 0x8, 0x30, 0x60, 0xc1, 0x83,
    0x6, 0xc, 0x14, 0x47, 0x0,

    /* U+1EE7 "ủ" */
    0x72, 0x88, 0x8, 0xc6, 0x31, 0x8c, 0xde,

    /* U+1EE8 "Ứ" */
    0x8, 0x18, 0x1, 0x83, 0x82, 0x82, 0x82, 0x82,
    0x82, 0x82, 0x82, 0x44, 0x38,

    /* U+1EE9 "ứ" */
    0x10, 0x40, 0xc, 0x78, 0x91, 0x22, 0x44, 0x98,
    0xf0,

    /* U+1EEA "Ừ" */
    0x20, 0x10, 0x1, 0x83, 0x82, 0x82, 0x82, 0x82,
    0x82, 0x82, 0x82, 0x44, 0x38,

    /* U+1EEB "ừ" */
    0x40, 0xc0, 0xc, 0x78, 0x91, 0x22, 0x44, 0x98,
    0xf0,

    /* U+1EEC "Ử" */
    0x38, 0x28, 0x18, 0x1, 0x83, 0x82, 0x82, 0x82,
    0x82, 0x82, 0x82, 0x82, 0x44, 0x38,

    /* U+1EED "ử" */
    0x70, 0xa0, 0x80, 0x18, 0xf1, 0x22, 0x44, 0x89,
    0x31, 0xe0,

    /* U+1EEE "Ữ" */
    0x34, 0x5c, 0x1, 0x83, 0x82, 0x82, 0x82, 0x82,
    0x82, 0x82, 0x82, 0x44, 0x38,

    /* U+1EEF "ữ" */
    0x71, 0x60, 0xc, 0x78, 0x91, 0x22, 0x44, 0x98,
    0xf0,

    /* U+1EF0 "Ự" */
    0x1, 0x83, 0x82, 0x82, 0x82, 0x82, 0x82, 0x82,
    0x82, 0x44, 0x38, 0x0, 0x10, 0x10,

    /* U+1EF1 "ự" */
    0x2, 0x6, 0x3c, 0x48, 0x91, 0x22, 0x4c, 0x78,
    0x0, 0x81, 0x0,

    /* U+1EF2 "Ỳ" */
    0x20, 0x20, 0x6, 0x34, 0x4d, 0x8a, 0x14, 0x10,
    0x20, 0x40, 0x81, 0x0,

    /* U+1EF3 "ỳ" */
    0x20, 0x80, 0x31, 0xcd, 0x24, 0x9e, 0x30, 0xc3,
    0x8, 0xc0,

    /* U+1EF4 "Ỵ" */
    0xc6, 0x89, 0xb1, 0x42, 0x82, 0x4, 0x8, 0x10,
    0x20, 0x0, 0x81, 0x0,

    /* U+1EF5 "ỵ" */
    0xcb, 0x24, 0x92, 0x70, 0xc3, 0x8, 0x23, 0x20,
    0x80,

    /* U+1EF6 "Ỷ" */
    0x18, 0x10, 0x6, 0x14, 0x6c, 0x8b, 0x14, 0x18,
    0x20, 0x40, 0x81, 0x0,

    /* U+1EF7 "ỷ" */
    0x30, 0x40, 0x31, 0xcd, 0x24, 0x9e, 0x30, 0xc3,
    0x8, 0xc0,

    /* U+1EF8 "Ỹ" */
    0x38, 0x70, 0x6, 0x34, 0x4d, 0x8a, 0x14, 0x10,
    0x20, 0x40, 0x81, 0x0,

    /* U+1EF9 "ỹ" */
    0x69, 0x60, 0x31, 0xcd, 0x24, 0x9e, 0x30, 0xc3,
    0x8, 0xc0,

    /* U+2013 "–" */
    0xf8,

    /* U+2014 "—" */
    0xff,

    /* U+2018 "‘" */
    0x6c,

    /* U+2019 "’" */
    0xfa,

    /* U+201A "‚" */
    0x36,

    /* U+201C "“" */
    0x5a, 0xf0,

    /* U+201D "”" */
    0xff, 0xaa,

    /* U+201E "„" */
    0xf, 0x5a,

    /* U+2020 "†" */
    0x20, 0x8f, 0xc8, 0x20, 0x82, 0x0,

    /* U+2021 "‡" */
    0x20, 0x8f, 0xc8, 0xfc, 0x82, 0x0,

    /* U+2022 "•" */
    0x6f, 0xf6,

    /* U+2026 "…" */
    0x93, 0x24,

    /* U+2030 "‰" */
    0x62, 0x4, 0xb0, 0x25, 0x0, 0xc8, 0x0, 0x80,
    0x4, 0x0, 0x4c, 0xe2, 0x95, 0x34, 0xa9, 0x19,
    0xc0,

    /* U+2039 "‹" */
    0x13, 0x30, 0x41, 0x0,

    /* U+203A "›" */
    0x41, 0x86, 0x64, 0x0,

    /* U+20AB "₫" */
    0x8, 0x77, 0xa6, 0x8a, 0x67, 0x80, 0xfc,

    /* U+20AC "€" */
    0xf, 0x18, 0x30, 0x20, 0xfe, 0xfe, 0x20, 0x30,
    0x18, 0xf,

    /* U+2122 "™" */
    0xe9, 0x4f, 0x4f, 0x49
};


/*---------------------
 *  GLYPH DESCRIPTION
 *--------------------*/

static const lv_font_fmt_txt_glyph_dsc_t glyph_dsc[] = {
    {.bitmap_index = 0, .adv_w = 0, .box_w = 0, .box_h = 0, .ofs_x = 0, .ofs_y = 0} /* id = 0 reserved */,
    {.bitmap_index = 0, .adv_w = 44, .box_w = 1, .box_h = 1, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1, .adv_w = 58, .box_w = 1, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 3, .adv_w = 66, .box_w = 3, .box_h = 3, .ofs_x = 1, .ofs_y = 7},
    {.bitmap_index = 5, .adv_w = 157, .box_w = 8, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 15, .adv_w = 124, .box_w = 7, .box_h = 12, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 26, .adv_w = 164, .box_w = 9, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 38, .adv_w = 144, .box_w = 8, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 48, .adv_w = 37, .box_w = 1, .box_h = 3, .ofs_x = 1, .ofs_y = 7},
    {.bitmap_index = 49, .adv_w = 85, .box_w = 4, .box_h = 14, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 56, .adv_w = 85, .box_w = 4, .box_h = 14, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 63, .adv_w = 96, .box_w = 5, .box_h = 5, .ofs_x = 0, .ofs_y = 5},
    {.bitmap_index = 67, .adv_w = 120, .box_w = 5, .box_h = 5, .ofs_x = 1, .ofs_y = 2},
    {.bitmap_index = 71, .adv_w = 61, .box_w = 2, .box_h = 4, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 72, .adv_w = 117, .box_w = 4, .box_h = 1, .ofs_x = 1, .ofs_y = 4},
    {.bitmap_index = 73, .adv_w = 58, .box_w = 1, .box_h = 2, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 74, .adv_w = 99, .box_w = 6, .box_h = 13, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 84, .adv_w = 131, .box_w = 7, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 93, .adv_w = 77, .box_w = 3, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 97, .adv_w = 126, .box_w = 6, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 105, .adv_w = 128, .box_w = 6, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 113, .adv_w = 137, .box_w = 8, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 123, .adv_w = 128, .box_w = 6, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 131, .adv_w = 132, .box_w = 6, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 139, .adv_w = 114, .box_w = 6, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 147, .adv_w = 124, .box_w = 6, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 155, .adv_w = 132, .box_w = 6, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 163, .adv_w = 58, .box_w = 1, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 164, .adv_w = 61, .box_w = 1, .box_h = 9, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 166, .adv_w = 108, .box_w = 5, .box_h = 6, .ofs_x = 1, .ofs_y = 1},
    {.bitmap_index = 170, .adv_w = 141, .box_w = 6, .box_h = 4, .ofs_x = 1, .ofs_y = 2},
    {.bitmap_index = 173, .adv_w = 108, .box_w = 5, .box_h = 6, .ofs_x = 1, .ofs_y = 1},
    {.bitmap_index = 177, .adv_w = 113, .box_w = 6, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 185, .adv_w = 194, .box_w = 11, .box_h = 11, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 201, .adv_w = 143, .box_w = 8, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 211, .adv_w = 132, .box_w = 7, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 220, .adv_w = 149, .box_w = 8, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 230, .adv_w = 141, .box_w = 7, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 239, .adv_w = 120, .box_w = 5, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 246, .adv_w = 122, .box_w = 6, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 254, .adv_w = 151, .box_w = 8, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 264, .adv_w = 138, .box_w = 7, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 273, .adv_w = 52, .box_w = 1, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 275, .adv_w = 91, .box_w = 4, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 280, .adv_w = 133, .box_w = 7, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 289, .adv_w = 121, .box_w = 5, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 296, .adv_w = 166, .box_w = 8, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 306, .adv_w = 142, .box_w = 7, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 315, .adv_w = 159, .box_w = 9, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 327, .adv_w = 126, .box_w = 6, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 335, .adv_w = 158, .box_w = 9, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 347, .adv_w = 131, .box_w = 6, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 355, .adv_w = 124, .box_w = 7, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 364, .adv_w = 127, .box_w = 7, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 373, .adv_w = 140, .box_w = 7, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 382, .adv_w = 138, .box_w = 8, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 392, .adv_w = 196, .box_w = 12, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 407, .adv_w = 141, .box_w = 7, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 416, .adv_w = 131, .box_w = 7, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 425, .adv_w = 127, .box_w = 7, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 434, .adv_w = 91, .box_w = 3, .box_h = 13, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 439, .adv_w = 96, .box_w = 6, .box_h = 13, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 449, .adv_w = 91, .box_w = 3, .box_h = 13, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 454, .adv_w = 111, .box_w = 5, .box_h = 2, .ofs_x = 1, .ofs_y = 7},
    {.bitmap_index = 456, .adv_w = 137, .box_w = 6, .box_h = 1, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 457, .adv_w = 44, .box_w = 3, .box_h = 2, .ofs_x = 0, .ofs_y = 8},
    {.bitmap_index = 458, .adv_w = 124, .box_w = 6, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 464, .adv_w = 126, .box_w = 6, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 472, .adv_w = 119, .box_w = 6, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 478, .adv_w = 126, .box_w = 6, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 486, .adv_w = 116, .box_w = 6, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 492, .adv_w = 76, .box_w = 4, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 497, .adv_w = 124, .box_w = 6, .box_h = 10, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 505, .adv_w = 113, .box_w = 5, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 512, .adv_w = 53, .box_w = 1, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 514, .adv_w = 54, .box_w = 3, .box_h = 13, .ofs_x = -1, .ofs_y = -3},
    {.bitmap_index = 519, .adv_w = 109, .box_w = 5, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 526, .adv_w = 51, .box_w = 1, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 528, .adv_w = 172, .box_w = 9, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 536, .adv_w = 112, .box_w = 5, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 541, .adv_w = 124, .box_w = 6, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 547, .adv_w = 126, .box_w = 6, .box_h = 10, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 555, .adv_w = 126, .box_w = 6, .box_h = 10, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 563, .adv_w = 78, .box_w = 3, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 566, .adv_w = 99, .box_w = 5, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 571, .adv_w = 83, .box_w = 4, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 576, .adv_w = 110, .box_w = 5, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 581, .adv_w = 112, .box_w = 7, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 588, .adv_w = 168, .box_w = 10, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 597, .adv_w = 110, .box_w = 6, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 603, .adv_w = 113, .box_w = 6, .box_h = 10, .ofs_x = 0, .ofs_y = -3},
    {.bitmap_index = 611, .adv_w = 98, .box_w = 5, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 616, .adv_w = 85, .box_w = 5, .box_h = 13, .ofs_x = 0, .ofs_y = -3},
    {.bitmap_index = 625, .adv_w = 80, .box_w = 1, .box_h = 16, .ofs_x = 2, .ofs_y = -3},
    {.bitmap_index = 627, .adv_w = 85, .box_w = 5, .box_h = 13, .ofs_x = 0, .ofs_y = -3},
    {.bitmap_index = 636, .adv_w = 91, .box_w = 4, .box_h = 2, .ofs_x = 1, .ofs_y = 4},
    {.bitmap_index = 637, .adv_w = 44, .box_w = 1, .box_h = 1, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 638, .adv_w = 58, .box_w = 1, .box_h = 10, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 640, .adv_w = 119, .box_w = 6, .box_h = 9, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 647, .adv_w = 120, .box_w = 6, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 655, .adv_w = 119, .box_w = 6, .box_h = 8, .ofs_x = 0, .ofs_y = 1},
    {.bitmap_index = 661, .adv_w = 131, .box_w = 7, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 670, .adv_w = 80, .box_w = 1, .box_h = 15, .ofs_x = 2, .ofs_y = -3},
    {.bitmap_index = 672, .adv_w = 134, .box_w = 7, .box_h = 14, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 685, .adv_w = 63, .box_w = 4, .box_h = 2, .ofs_x = 1, .ofs_y = 8},
    {.bitmap_index = 686, .adv_w = 157, .box_w = 9, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 697, .adv_w = 81, .box_w = 4, .box_h = 4, .ofs_x = 1, .ofs_y = 5},
    {.bitmap_index = 699, .adv_w = 130, .box_w = 8, .box_h = 5, .ofs_x = 0, .ofs_y = 2},
    {.bitmap_index = 704, .adv_w = 126, .box_w = 6, .box_h = 3, .ofs_x = 1, .ofs_y = 4},
    {.bitmap_index = 707, .adv_w = 115, .box_w = 4, .box_h = 1, .ofs_x = 1, .ofs_y = 4},
    {.bitmap_index = 708, .adv_w = 83, .box_w = 5, .box_h = 5, .ofs_x = 1, .ofs_y = 5},
    {.bitmap_index = 712, .adv_w = 68, .box_w = 4, .box_h = 1, .ofs_x = 1, .ofs_y = 8},
    {.bitmap_index = 713, .adv_w = 91, .box_w = 4, .box_h = 5, .ofs_x = 1, .ofs_y = 5},
    {.bitmap_index = 716, .adv_w = 126, .box_w = 5, .box_h = 7, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 721, .adv_w = 85, .box_w = 4, .box_h = 5, .ofs_x = 1, .ofs_y = 5},
    {.bitmap_index = 724, .adv_w = 87, .box_w = 4, .box_h = 5, .ofs_x = 0, .ofs_y = 5},
    {.bitmap_index = 727, .adv_w = 44, .box_w = 2, .box_h = 2, .ofs_x = 0, .ofs_y = 8},
    {.bitmap_index = 728, .adv_w = 118, .box_w = 6, .box_h = 10, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 736, .adv_w = 101, .box_w = 6, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 743, .adv_w = 52, .box_w = 1, .box_h = 2, .ofs_x = 1, .ofs_y = 4},
    {.bitmap_index = 744, .adv_w = 46, .box_w = 3, .box_h = 3, .ofs_x = 0, .ofs_y = -3},
    {.bitmap_index = 746, .adv_w = 62, .box_w = 2, .box_h = 5, .ofs_x = 0, .ofs_y = 5},
    {.bitmap_index = 748, .adv_w = 88, .box_w = 4, .box_h = 4, .ofs_x = 1, .ofs_y = 5},
    {.bitmap_index = 750, .adv_w = 130, .box_w = 8, .box_h = 5, .ofs_x = 0, .ofs_y = 2},
    {.bitmap_index = 755, .adv_w = 152, .box_w = 11, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 768, .adv_w = 154, .box_w = 11, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 781, .adv_w = 155, .box_w = 11, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 794, .adv_w = 113, .box_w = 6, .box_h = 10, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 802, .adv_w = 143, .box_w = 8, .box_h = 13, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 815, .adv_w = 143, .box_w = 8, .box_h = 13, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 828, .adv_w = 143, .box_w = 8, .box_h = 13, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 841, .adv_w = 143, .box_w = 8, .box_h = 13, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 854, .adv_w = 143, .box_w = 8, .box_h = 12, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 866, .adv_w = 143, .box_w = 7, .box_h = 14, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 879, .adv_w = 197, .box_w = 11, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 893, .adv_w = 149, .box_w = 8, .box_h = 13, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 906, .adv_w = 122, .box_w = 5, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 915, .adv_w = 122, .box_w = 5, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 924, .adv_w = 122, .box_w = 5, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 933, .adv_w = 122, .box_w = 6, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 942, .adv_w = 55, .box_w = 2, .box_h = 13, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 946, .adv_w = 55, .box_w = 2, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 950, .adv_w = 55, .box_w = 3, .box_h = 13, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 955, .adv_w = 55, .box_w = 4, .box_h = 12, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 961, .adv_w = 151, .box_w = 8, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 971, .adv_w = 145, .box_w = 7, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 983, .adv_w = 159, .box_w = 9, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 998, .adv_w = 159, .box_w = 9, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1013, .adv_w = 159, .box_w = 9, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1028, .adv_w = 159, .box_w = 9, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1043, .adv_w = 159, .box_w = 9, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1058, .adv_w = 114, .box_w = 5, .box_h = 4, .ofs_x = 1, .ofs_y = 2},
    {.bitmap_index = 1061, .adv_w = 159, .box_w = 9, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1073, .adv_w = 143, .box_w = 7, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1085, .adv_w = 143, .box_w = 7, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1097, .adv_w = 143, .box_w = 7, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1109, .adv_w = 143, .box_w = 7, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1121, .adv_w = 131, .box_w = 7, .box_h = 13, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1133, .adv_w = 126, .box_w = 6, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1141, .adv_w = 132, .box_w = 6, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1149, .adv_w = 126, .box_w = 6, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1157, .adv_w = 126, .box_w = 6, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1165, .adv_w = 126, .box_w = 6, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1173, .adv_w = 126, .box_w = 6, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1181, .adv_w = 126, .box_w = 6, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1189, .adv_w = 126, .box_w = 6, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1198, .adv_w = 185, .box_w = 10, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1207, .adv_w = 120, .box_w = 6, .box_h = 10, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 1215, .adv_w = 118, .box_w = 6, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1223, .adv_w = 118, .box_w = 6, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1231, .adv_w = 118, .box_w = 6, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1239, .adv_w = 118, .box_w = 6, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1247, .adv_w = 55, .box_w = 2, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1250, .adv_w = 55, .box_w = 2, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1253, .adv_w = 55, .box_w = 3, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1257, .adv_w = 55, .box_w = 4, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1262, .adv_w = 124, .box_w = 6, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1271, .adv_w = 116, .box_w = 5, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1278, .adv_w = 126, .box_w = 6, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1286, .adv_w = 126, .box_w = 6, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1294, .adv_w = 126, .box_w = 6, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1302, .adv_w = 126, .box_w = 6, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1310, .adv_w = 126, .box_w = 6, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1318, .adv_w = 131, .box_w = 5, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1323, .adv_w = 124, .box_w = 6, .box_h = 9, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 1330, .adv_w = 114, .box_w = 5, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1337, .adv_w = 114, .box_w = 5, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1344, .adv_w = 114, .box_w = 5, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1351, .adv_w = 114, .box_w = 5, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1358, .adv_w = 113, .box_w = 6, .box_h = 13, .ofs_x = 0, .ofs_y = -3},
    {.bitmap_index = 1368, .adv_w = 126, .box_w = 6, .box_h = 13, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 1378, .adv_w = 113, .box_w = 6, .box_h = 13, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 1388, .adv_w = 143, .box_w = 8, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1400, .adv_w = 126, .box_w = 6, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1407, .adv_w = 143, .box_w = 8, .box_h = 13, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1420, .adv_w = 126, .box_w = 6, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1428, .adv_w = 143, .box_w = 8, .box_h = 13, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 1441, .adv_w = 126, .box_w = 6, .box_h = 10, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 1449, .adv_w = 149, .box_w = 8, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1462, .adv_w = 120, .box_w = 6, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1470, .adv_w = 149, .box_w = 8, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1483, .adv_w = 120, .box_w = 6, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1491, .adv_w = 149, .box_w = 8, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1504, .adv_w = 120, .box_w = 6, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1512, .adv_w = 143, .box_w = 7, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1524, .adv_w = 138, .box_w = 8, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1534, .adv_w = 151, .box_w = 8, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1544, .adv_w = 128, .box_w = 7, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1553, .adv_w = 122, .box_w = 6, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1562, .adv_w = 118, .box_w = 6, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1569, .adv_w = 122, .box_w = 5, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1578, .adv_w = 118, .box_w = 6, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1586, .adv_w = 122, .box_w = 6, .box_h = 13, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 1596, .adv_w = 118, .box_w = 6, .box_h = 10, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 1604, .adv_w = 122, .box_w = 5, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1613, .adv_w = 118, .box_w = 6, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1621, .adv_w = 151, .box_w = 8, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1634, .adv_w = 127, .box_w = 6, .box_h = 13, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 1644, .adv_w = 151, .box_w = 8, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1657, .adv_w = 127, .box_w = 6, .box_h = 13, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 1667, .adv_w = 149, .box_w = 9, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1679, .adv_w = 120, .box_w = 6, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1687, .adv_w = 55, .box_w = 3, .box_h = 13, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1692, .adv_w = 55, .box_w = 3, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1696, .adv_w = 55, .box_w = 4, .box_h = 12, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1702, .adv_w = 55, .box_w = 4, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1707, .adv_w = 55, .box_w = 2, .box_h = 13, .ofs_x = 0, .ofs_y = -3},
    {.bitmap_index = 1711, .adv_w = 55, .box_w = 1, .box_h = 13, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 1713, .adv_w = 55, .box_w = 1, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1715, .adv_w = 55, .box_w = 1, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1716, .adv_w = 122, .box_w = 6, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1726, .adv_w = 54, .box_w = 2, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1730, .adv_w = 122, .box_w = 7, .box_h = 13, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1742, .adv_w = 65, .box_w = 4, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1747, .adv_w = 125, .box_w = 7, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1756, .adv_w = 80, .box_w = 4, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1761, .adv_w = 145, .box_w = 7, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1773, .adv_w = 116, .box_w = 5, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1780, .adv_w = 145, .box_w = 7, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1792, .adv_w = 116, .box_w = 5, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1799, .adv_w = 159, .box_w = 9, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1813, .adv_w = 126, .box_w = 6, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1820, .adv_w = 159, .box_w = 9, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1835, .adv_w = 126, .box_w = 6, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1843, .adv_w = 195, .box_w = 11, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1857, .adv_w = 196, .box_w = 11, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1867, .adv_w = 133, .box_w = 6, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1877, .adv_w = 83, .box_w = 3, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1881, .adv_w = 133, .box_w = 6, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1891, .adv_w = 83, .box_w = 3, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1895, .adv_w = 124, .box_w = 7, .box_h = 13, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1907, .adv_w = 101, .box_w = 5, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1914, .adv_w = 124, .box_w = 7, .box_h = 13, .ofs_x = 0, .ofs_y = -3},
    {.bitmap_index = 1926, .adv_w = 101, .box_w = 5, .box_h = 10, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 1933, .adv_w = 124, .box_w = 7, .box_h = 12, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1944, .adv_w = 101, .box_w = 5, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1951, .adv_w = 127, .box_w = 7, .box_h = 13, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 1963, .adv_w = 83, .box_w = 5, .box_h = 12, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 1971, .adv_w = 127, .box_w = 7, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1983, .adv_w = 79, .box_w = 5, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1990, .adv_w = 127, .box_w = 7, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1999, .adv_w = 83, .box_w = 4, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 2004, .adv_w = 143, .box_w = 7, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 2016, .adv_w = 114, .box_w = 5, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 2023, .adv_w = 143, .box_w = 7, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 2034, .adv_w = 114, .box_w = 5, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 2040, .adv_w = 143, .box_w = 7, .box_h = 14, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 2053, .adv_w = 114, .box_w = 5, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 2060, .adv_w = 143, .box_w = 7, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 2072, .adv_w = 114, .box_w = 5, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 2079, .adv_w = 143, .box_w = 7, .box_h = 13, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 2091, .adv_w = 114, .box_w = 5, .box_h = 10, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 2098, .adv_w = 191, .box_w = 12, .box_h = 13, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 2118, .adv_w = 168, .box_w = 10, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 2131, .adv_w = 131, .box_w = 7, .box_h = 12, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 2142, .adv_w = 113, .box_w = 6, .box_h = 13, .ofs_x = 0, .ofs_y = -3},
    {.bitmap_index = 2152, .adv_w = 131, .box_w = 8, .box_h = 12, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 2164, .adv_w = 127, .box_w = 7, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 2176, .adv_w = 98, .box_w = 5, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 2183, .adv_w = 127, .box_w = 7, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 2195, .adv_w = 98, .box_w = 5, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 2202, .adv_w = 127, .box_w = 7, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 2214, .adv_w = 98, .box_w = 5, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 2221, .adv_w = 159, .box_w = 9, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 2234, .adv_w = 125, .box_w = 6, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 2241, .adv_w = 143, .box_w = 8, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 2252, .adv_w = 112, .box_w = 7, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 2260, .adv_w = 0, .box_w = 2, .box_h = 2, .ofs_x = 0, .ofs_y = 8},
    {.bitmap_index = 2261, .adv_w = 0, .box_w = 3, .box_h = 2, .ofs_x = 0, .ofs_y = 8},
    {.bitmap_index = 2262, .adv_w = 0, .box_w = 4, .box_h = 2, .ofs_x = 0, .ofs_y = 8},
    {.bitmap_index = 2263, .adv_w = 0, .box_w = 4, .box_h = 2, .ofs_x = 0, .ofs_y = 8},
    {.bitmap_index = 2264, .adv_w = 0, .box_w = 3, .box_h = 3, .ofs_x = 0, .ofs_y = 8},
    {.bitmap_index = 2266, .adv_w = 0, .box_w = 1, .box_h = 2, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 2267, .adv_w = 143, .box_w = 7, .box_h = 13, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 2279, .adv_w = 126, .box_w = 6, .box_h = 10, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 2287, .adv_w = 143, .box_w = 8, .box_h = 14, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 2301, .adv_w = 126, .box_w = 6, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 2310, .adv_w = 143, .box_w = 8, .box_h = 14, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 2324, .adv_w = 126, .box_w = 7, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 2335, .adv_w = 143, .box_w = 8, .box_h = 14, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 2349, .adv_w = 126, .box_w = 6, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 2358, .adv_w = 143, .box_w = 8, .box_h = 15, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 2373, .adv_w = 126, .box_w = 7, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 2384, .adv_w = 143, .box_w = 8, .box_h = 15, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 2399, .adv_w = 126, .box_w = 6, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 2408, .adv_w = 143, .box_w = 7, .box_h = 16, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 2422, .adv_w = 126, .box_w = 6, .box_h = 13, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 2432, .adv_w = 143, .box_w = 8, .box_h = 15, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 2447, .adv_w = 126, .box_w = 6, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 2456, .adv_w = 143, .box_w = 8, .box_h = 15, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 2471, .adv_w = 126, .box_w = 6, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 2480, .adv_w = 143, .box_w = 8, .box_h = 16, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 2496, .adv_w = 126, .box_w = 6, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 2506, .adv_w = 143, .box_w = 8, .box_h = 15, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 2521, .adv_w = 126, .box_w = 6, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 2530, .adv_w = 143, .box_w = 7, .box_h = 16, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 2544, .adv_w = 126, .box_w = 6, .box_h = 13, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 2554, .adv_w = 122, .box_w = 5, .box_h = 13, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 2563, .adv_w = 118, .box_w = 6, .box_h = 10, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 2571, .adv_w = 122, .box_w = 6, .box_h = 14, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 2582, .adv_w = 118, .box_w = 6, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 2591, .adv_w = 122, .box_w = 5, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 2600, .adv_w = 118, .box_w = 6, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 2608, .adv_w = 122, .box_w = 6, .box_h = 14, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 2619, .adv_w = 118, .box_w = 7, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 2630, .adv_w = 122, .box_w = 5, .box_h = 14, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 2639, .adv_w = 118, .box_w = 6, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 2648, .adv_w = 122, .box_w = 7, .box_h = 15, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 2662, .adv_w = 118, .box_w = 7, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 2673, .adv_w = 122, .box_w = 5, .box_h = 15, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 2683, .adv_w = 118, .box_w = 6, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 2692, .adv_w = 122, .box_w = 5, .box_h = 16, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 2702, .adv_w = 118, .box_w = 6, .box_h = 13, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 2712, .adv_w = 55, .box_w = 3, .box_h = 14, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 2718, .adv_w = 55, .box_w = 3, .box_h = 11, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 2723, .adv_w = 55, .box_w = 1, .box_h = 13, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 2725, .adv_w = 55, .box_w = 1, .box_h = 13, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 2727, .adv_w = 159, .box_w = 9, .box_h = 13, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 2742, .adv_w = 126, .box_w = 6, .box_h = 10, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 2750, .adv_w = 159, .box_w = 9, .box_h = 14, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 2766, .adv_w = 126, .box_w = 6, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 2775, .adv_w = 159, .box_w = 9, .box_h = 15, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 2792, .adv_w = 126, .box_w = 7, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 2803, .adv_w = 159, .box_w = 9, .box_h = 15, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 2820, .adv_w = 126, .box_w = 6, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 2829, .adv_w = 159, .box_w = 9, .box_h = 15, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 2846, .adv_w = 126, .box_w = 6, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 2856, .adv_w = 159, .box_w = 9, .box_h = 15, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 2873, .adv_w = 126, .box_w = 6, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 2882, .adv_w = 159, .box_w = 9, .box_h = 16, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 2900, .adv_w = 126, .box_w = 6, .box_h = 13, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 2910, .adv_w = 159, .box_w = 9, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 2925, .adv_w = 126, .box_w = 6, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 2933, .adv_w = 159, .box_w = 9, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 2948, .adv_w = 126, .box_w = 6, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 2956, .adv_w = 159, .box_w = 9, .box_h = 14, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 2972, .adv_w = 126, .box_w = 6, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 2981, .adv_w = 159, .box_w = 9, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 2996, .adv_w = 125, .box_w = 6, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 3004, .adv_w = 159, .box_w = 9, .box_h = 14, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 3020, .adv_w = 126, .box_w = 6, .box_h = 12, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 3029, .adv_w = 143, .box_w = 7, .box_h = 13, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 3041, .adv_w = 114, .box_w = 5, .box_h = 10, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 3048, .adv_w = 143, .box_w = 7, .box_h = 14, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 3061, .adv_w = 114, .box_w = 5, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 3068, .adv_w = 143, .box_w = 8, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 3081, .adv_w = 114, .box_w = 7, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 3090, .adv_w = 143, .box_w = 8, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 3103, .adv_w = 114, .box_w = 7, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 3112, .adv_w = 143, .box_w = 8, .box_h = 14, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 3126, .adv_w = 114, .box_w = 7, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 3136, .adv_w = 143, .box_w = 8, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 3149, .adv_w = 114, .box_w = 7, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 3158, .adv_w = 143, .box_w = 8, .box_h = 14, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 3172, .adv_w = 114, .box_w = 7, .box_h = 12, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 3183, .adv_w = 131, .box_w = 7, .box_h = 13, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 3195, .adv_w = 113, .box_w = 6, .box_h = 13, .ofs_x = 0, .ofs_y = -3},
    {.bitmap_index = 3205, .adv_w = 131, .box_w = 7, .box_h = 13, .ofs_x = 0, .ofs_y = -3},
    {.bitmap_index = 3217, .adv_w = 113, .box_w = 6, .box_h = 11, .ofs_x = 0, .ofs_y = -4},
    {.bitmap_index = 3226, .adv_w = 131, .box_w = 7, .box_h = 13, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 3238, .adv_w = 113, .box_w = 6, .box_h = 13, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 3248, .adv_w = 131, .box_w = 7, .box_h = 13, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 3260, .adv_w = 113, .box_w = 6, .box_h = 13, .ofs_x = 0, .ofs_y = -3},
    {.bitmap_index = 3270, .adv_w = 132, .box_w = 5, .box_h = 1, .ofs_x = 1, .ofs_y = 4},
    {.bitmap_index = 3271, .adv_w = 167, .box_w = 8, .box_h = 1, .ofs_x = 1, .ofs_y = 4},
    {.bitmap_index = 3272, .adv_w = 54, .box_w = 2, .box_h = 4, .ofs_x = 1, .ofs_y = 6},
    {.bitmap_index = 3273, .adv_w = 43, .box_w = 2, .box_h = 4, .ofs_x = 1, .ofs_y = 6},
    {.bitmap_index = 3274, .adv_w = 57, .box_w = 2, .box_h = 4, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 3275, .adv_w = 76, .box_w = 4, .box_h = 4, .ofs_x = 0, .ofs_y = 6},
    {.bitmap_index = 3277, .adv_w = 81, .box_w = 4, .box_h = 4, .ofs_x = 1, .ofs_y = 6},
    {.bitmap_index = 3279, .adv_w = 98, .box_w = 4, .box_h = 4, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 3281, .adv_w = 133, .box_w = 6, .box_h = 7, .ofs_x = 1, .ofs_y = 3},
    {.bitmap_index = 3287, .adv_w = 133, .box_w = 6, .box_h = 7, .ofs_x = 1, .ofs_y = 3},
    {.bitmap_index = 3293, .adv_w = 107, .box_w = 4, .box_h = 4, .ofs_x = 1, .ofs_y = 3},
    {.bitmap_index = 3295, .adv_w = 148, .box_w = 7, .box_h = 2, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 3297, .adv_w = 237, .box_w = 13, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 3314, .adv_w = 80, .box_w = 5, .box_h = 5, .ofs_x = 0, .ofs_y = 2},
    {.bitmap_index = 3318, .adv_w = 80, .box_w = 5, .box_h = 5, .ofs_x = 0, .ofs_y = 2},
    {.bitmap_index = 3322, .adv_w = 116, .box_w = 6, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 3329, .adv_w = 137, .box_w = 8, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 3339, .adv_w = 162, .box_w = 8, .box_h = 4, .ofs_x = 1, .ofs_y = 5}
};

/*---------------------
 *  CHARACTER MAPPING
 *--------------------*/

static const uint8_t glyph_id_ofs_list_2[] = {
    0, 1, 2, 3, 4, 5, 6, 7,
    8, 9, 0, 0, 10, 11, 12, 13,
    14, 15, 0, 0, 16, 17, 18, 19,
    0, 0, 0, 0, 20, 21, 22, 23,
    24, 25, 0, 0, 26, 27, 28, 29,
    0, 0, 0, 0, 0, 0, 0, 30,
    31, 0, 0, 32, 33, 0, 0, 34,
    35, 36, 37, 0, 0, 38, 39, 0,
    0, 0, 40, 41, 0, 0, 42, 43,
    44, 45, 46, 47, 0, 0, 48, 49,
    50, 51, 0, 0, 52, 53, 54, 55,
    56, 57, 58, 59, 60, 61, 62, 63,
    64, 65
};

static const uint16_t unicode_list_4[] = {
    0x0, 0x1, 0xf, 0x10, 0x160, 0x161, 0x162, 0x163,
    0x169, 0x183
};

static const uint16_t unicode_list_6[] = {
    0x0, 0x1, 0x5, 0x6, 0x7, 0x9, 0xa, 0xb,
    0xd, 0xe, 0xf, 0x13, 0x1d, 0x26, 0x27, 0x98,
    0x99, 0x10f
};

/*Collect the unicode lists and glyph_id offsets*/
static const lv_font_fmt_txt_cmap_t cmaps[] =
{
    {
        .range_start = 32, .range_length = 95, .glyph_id_start = 1,
        .unicode_list = NULL, .glyph_id_ofs_list = NULL, .list_length = 0, .type = LV_FONT_FMT_TXT_CMAP_FORMAT0_TINY
    },
    {
        .range_start = 160, .range_length = 104, .glyph_id_start = 96,
        .unicode_list = NULL, .glyph_id_ofs_list = NULL, .list_length = 0, .type = LV_FONT_FMT_TXT_CMAP_FORMAT0_TINY
    },
    {
        .range_start = 266, .range_length = 98, .glyph_id_start = 200,
        .unicode_list = NULL, .glyph_id_ofs_list = glyph_id_ofs_list_2, .list_length = 98, .type = LV_FONT_FMT_TXT_CMAP_FORMAT0_FULL
    },
    {
        .range_start = 366, .range_length = 17, .glyph_id_start = 266,
        .unicode_list = NULL, .glyph_id_ofs_list = NULL, .list_length = 0, .type = LV_FONT_FMT_TXT_CMAP_FORMAT0_TINY
    },
    {
        .range_start = 416, .range_length = 388, .glyph_id_start = 283,
        .unicode_list = unicode_list_4, .glyph_id_ofs_list = NULL, .list_length = 10, .type = LV_FONT_FMT_TXT_CMAP_SPARSE_TINY
    },
    {
        .range_start = 7840, .range_length = 90, .glyph_id_start = 293,
        .unicode_list = NULL, .glyph_id_ofs_list = NULL, .list_length = 0, .type = LV_FONT_FMT_TXT_CMAP_FORMAT0_TINY
    },
    {
        .range_start = 8211, .range_length = 272, .glyph_id_start = 383,
        .unicode_list = unicode_list_6, .glyph_id_ofs_list = NULL, .list_length = 18, .type = LV_FONT_FMT_TXT_CMAP_SPARSE_TINY
    }
};

/*-----------------
 *    KERNING
 *----------------*/


/*Map glyph_ids to kern left classes*/
static const uint8_t kern_left_class_mapping[] =
{
    0, 0, 0, 1, 2, 3, 4, 0,
    1, 0, 4, 0, 0, 5, 0, 5,
    6, 7, 0, 8, 9, 10, 11, 12,
    13, 14, 15, 0, 0, 0, 0, 16,
    0, 0, 17, 9, 18, 4, 19, 20,
    0, 21, 21, 22, 23, 24, 21, 21,
    4, 25, 0, 26, 3, 27, 22, 28,
    28, 29, 30, 31, 0, 32, 0, 0,
    0, 0, 33, 34, 35, 21, 34, 36,
    37, 38, 39, 40, 41, 21, 38, 38,
    34, 34, 42, 43, 44, 45, 46, 47,
    47, 48, 49, 50, 0, 0, 0, 0,
    0, 0, 0, 3, 0, 30, 0, 3,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 51, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    17, 17, 17, 17, 17, 17, 19, 4,
    19, 19, 19, 19, 21, 21, 21, 21,
    4, 21, 4, 4, 4, 4, 4, 0,
    4, 22, 22, 22, 22, 30, 0, 9,
    33, 33, 33, 33, 33, 33, 34, 52,
    34, 34, 34, 34, 39, 39, 39, 39,
    53, 38, 34, 34, 34, 34, 34, 0,
    0, 46, 46, 46, 46, 49, 34, 49,
    17, 33, 17, 33, 17, 33, 4, 52,
    4, 52, 4, 52, 4, 0, 4, 53,
    19, 34, 19, 34, 19, 34, 19, 34,
    0, 37, 0, 37, 0, 38, 21, 39,
    21, 39, 21, 39, 21, 39, 24, 21,
    24, 0, 24, 0, 21, 38, 21, 38,
    4, 0, 4, 0, 19, 34, 26, 43,
    26, 43, 3, 44, 3, 44, 3, 44,
    27, 51, 27, 51, 27, 51, 22, 46,
    22, 46, 22, 46, 22, 46, 22, 46,
    28, 47, 30, 49, 30, 31, 50, 31,
    50, 31, 50, 4, 54, 55, 56, 0,
    0, 0, 0, 0, 0, 17, 33, 17,
    33, 17, 33, 17, 33, 17, 33, 17,
    33, 17, 33, 17, 33, 17, 33, 17,
    33, 17, 33, 17, 33, 19, 34, 19,
    34, 19, 34, 19, 34, 19, 34, 19,
    34, 19, 34, 19, 34, 21, 39, 21,
    39, 4, 34, 4, 34, 4, 34, 4,
    34, 4, 34, 4, 34, 4, 34, 4,
    54, 4, 54, 4, 54, 4, 54, 4,
    54, 22, 46, 22, 46, 55, 56, 55,
    56, 55, 56, 55, 56, 55, 56, 30,
    49, 30, 49, 30, 49, 30, 49, 0,
    0, 0, 57, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0
};

/*Map glyph_ids to kern right classes*/
static const uint8_t kern_right_class_mapping[] =
{
    0, 0, 1, 2, 3, 4, 5, 0,
    6, 5, 7, 8, 0, 9, 0, 9,
    10, 11, 12, 13, 14, 15, 16, 17,
    18, 19, 20, 0, 0, 0, 0, 21,
    22, 0, 23, 24, 5, 25, 24, 24,
    5, 24, 24, 26, 24, 24, 24, 24,
    5, 24, 5, 24, 4, 27, 28, 29,
    29, 30, 31, 32, 0, 33, 0, 0,
    0, 0, 17, 24, 17, 17, 17, 34,
    17, 24, 35, 36, 24, 24, 37, 37,
    17, 37, 17, 38, 39, 40, 41, 42,
    42, 43, 44, 45, 0, 0, 46, 0,
    0, 0, 0, 4, 0, 31, 0, 4,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 41, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    23, 23, 23, 23, 23, 23, 23, 5,
    24, 24, 24, 24, 24, 24, 24, 24,
    0, 24, 5, 5, 5, 5, 5, 0,
    5, 28, 28, 28, 28, 31, 24, 24,
    17, 17, 17, 17, 17, 17, 47, 17,
    17, 17, 17, 17, 48, 35, 35, 35,
    17, 35, 17, 17, 17, 17, 17, 0,
    0, 41, 41, 41, 41, 44, 24, 44,
    23, 17, 23, 17, 23, 17, 5, 17,
    5, 17, 5, 17, 25, 17, 0, 17,
    24, 17, 24, 17, 24, 17, 24, 17,
    5, 17, 5, 17, 0, 0, 24, 49,
    24, 35, 24, 35, 24, 35, 24, 24,
    24, 24, 0, 0, 24, 35, 24, 35,
    5, 0, 5, 0, 5, 17, 24, 38,
    24, 38, 4, 39, 4, 39, 4, 39,
    27, 40, 27, 40, 27, 40, 28, 41,
    28, 41, 28, 41, 28, 41, 28, 41,
    29, 42, 31, 44, 31, 50, 45, 50,
    45, 50, 45, 5, 17, 28, 41, 0,
    0, 0, 0, 0, 0, 23, 17, 23,
    17, 23, 17, 23, 17, 23, 17, 23,
    17, 23, 17, 23, 17, 23, 17, 23,
    17, 23, 17, 23, 17, 24, 17, 24,
    17, 24, 17, 24, 17, 24, 17, 24,
    17, 24, 17, 24, 17, 24, 35, 24,
    35, 5, 17, 5, 17, 5, 17, 5,
    17, 5, 17, 5, 17, 5, 17, 5,
    17, 5, 17, 5, 17, 5, 17, 5,
    17, 28, 41, 28, 41, 28, 41, 28,
    41, 28, 41, 28, 41, 28, 41, 31,
    44, 31, 44, 31, 44, 31, 44, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0
};

/*Kern values between classes*/
static const int8_t kern_class_values[] =
{
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 6, 0, 0, 0, 0, -8, 0,
    0, 0, 0, 0, 0, 0, 8, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    -11, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 1,
    3, 0, 0, 0, 0, 0, 3, 0,
    0, 0, 0, 0, 0, 1, 1, 0,
    0, 0, -4, 0, 0, 0, -4, 0,
    -2, 0, -5, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, -1, -1,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, -2,
    0, 0, 0, 0, -8, 0, 0, -8,
    -12, 0, -4, -7, -9, 0, 0, 0,
    0, -8, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    -5, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 5, 0, 0, 0,
    0, 0, -18, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, -26, 0, 0, -8, -8,
    -9, 0, -9, 14, -6, 0, 0, 0,
    0, 0, 0, 0, 8, 0, 10, 0,
    11, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, -2, 0, 0,
    0, 0, -8, 0, 0, -8, -12, 0,
    -4, -7, -9, 0, 0, 0, 0, -8,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, -5, 0, 0, -1,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, -2, 0, 0, 0,
    0, -3, -2, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, -1, 0,
    0, 0, -7, 0, -6, -5, -8, 0,
    0, 0, 0, -10, 0, 0, 0, 0,
    0, 0, -3, -2, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, -3, 0,
    0, 0, 0, -7, 3, 0, 0, 0,
    -3, 3, 0, 0, -14, 0, -10, -8,
    -10, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, -3,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, -5,
    0, -4, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, -8, 0, 0, 0,
    0, -8, -8, 3, -3, -5, -15, 0,
    -10, 3, 0, 2, 0, 0, -13, 0,
    5, -19, 4, 0, 0, 0, 5, 0,
    0, 0, -8, 0, 0, -10, -10, 0,
    -10, -8, -8, -10, -8, 0, -10, -8,
    -8, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, -1, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 3, 0, 0,
    0, 0, -8, 0, 3, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 1, 0, 2, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, -8, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, -17,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, -8, -3, -4, -7, -8, 0, 0,
    0, 0, -7, 0, 0, 0, 0, 0,
    -3, 0, 0, -1, 0, 0, 0, 0,
    0, 0, -18, 0, -17, 0, -17, 0,
    0, -8, 0, 0, 0, 0, 0, -2,
    -3, -12, 0, -12, 0, 0, -2, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, -2, 0, 0, 0, 0,
    -8, 0, 0, -8, -12, 0, 0, -7,
    -9, 0, 0, 0, 0, -8, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, -2,
    -1, 0, 0, 0, 0, 0, -1, 0,
    0, 0, 0, 0, -2, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, -5, 0, 0, 0, 0, 0,
    -5, 0, -7, 0, -11, 0, -10, 0,
    0, 0, 0, 0, -16, 0, 0, -22,
    0, 0, 0, 0, 2, 0, 0, 0,
    0, 0, 0, -9, 0, 0, 0, 0,
    0, 0, -10, 0, -10, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 2, 6, 6, 0,
    0, 0, 3, 5, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, -3, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    -3, 0, 0, 0, 0, 0, 3, 0,
    5, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, -6,
    -12, 0, 0, 0, 0, 0, -12, 0,
    0, 0, -11, 0, -9, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, -8, -10, -11, 0, -13,
    0, 0, -7, 0, 0, 0, 0, 0,
    0, 0, -12, 0, 0, 0, 0, 0,
    -12, 0, 0, 0, -15, 0, -7, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    -31, 0, -22, 0, -29, 0, 0, 0,
    0, 0, 0, 0, 0, 0, -5, -14,
    0, -11, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    -4, 0, 0, 0, 0, 0, -14, 0,
    0, -18, -5, 0, 0, 0, 0, 0,
    0, 0, 0, -2, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, -1, 0,
    0, 0, 0, 0, 0, -2, -5, 0,
    0, 0, 0, 0, -5, 0, 0, 0,
    -9, 0, -10, -5, 0, 0, 0, 0,
    0, 0, 0, 0, -6, -5, -6, 0,
    -8, 0, 0, 0, 0, 0, 0, 0,
    0, 0, -10, -5, 0, -5, 0, 0,
    0, 0, 0, 0, 0, 0, 0, -4,
    -12, 0, 0, 0, -18, -11, -12, 0,
    0, 0, -20, 0, -18, 4, 0, 0,
    0, 0, -17, 0, -2, -25, 0, 0,
    0, 0, 2, 0, 0, 0, 0, 0,
    -12, -12, -2, 0, -17, -21, -17, -16,
    -17, 0, -17, 0, 5, 0, 0, 0,
    0, 0, -4, 0, 0, 0, 0, -23,
    -4, 0, 0, 0, -13, 0, -10, 0,
    0, 0, 0, 0, -17, 0, 1, -21,
    0, 0, 3, 0, 4, 0, 0, 0,
    0, 0, -6, 0, -10, 0, -8, 0,
    0, -4, 0, 0, -12, 9, 0, 0,
    0, 0, 0, 0, -7, 0, 0, 0,
    0, 0, -7, 0, 0, 0, -8, 0,
    -8, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    -6, 0, 0, -9, 0, 0, 0, 0,
    0, 0, 0, 0, 0, -5, -8, 0,
    0, 0, 0, -18, -8, 0, 0, 0,
    -20, 0, -20, 0, 0, -8, 0, 0,
    -17, 0, -1, -22, 2, 0, 4, 0,
    0, 0, 0, 0, -1, -2, -13, 0,
    0, 0, -17, -10, 0, 0, 0, 0,
    -17, -1, -1, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, -5, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, -26, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, -12, 0, -6, 0, -8, 0,
    0, -2, 0, 1, 0, 0, 0, -3,
    0, -4, 0, -3, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, -1, -6, 0, 0, 0, 0,
    -3, 0, 0, 0, -17, 0, -8, -8,
    -17, 0, 0, -1, 0, -3, 0, 0,
    0, -2, 0, -4, -6, -6, 0, 0,
    -2, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, -17, 0,
    0, 0, -17, 0, 0, 0, 0, -11,
    0, 0, 0, 0, 0, -4, 0, -5,
    0, 0, -4, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, -5, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 1, 0,
    0, 0, 0, 0, -7, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    -3, 0, 0, 0, 0, 0, 0, 0,
    1, 0, 0, 0, 0, 0, -13, 0,
    0, 0, 0, 5, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, -9, 0, 0, 0, 0,
    0, 0, 0, 0, -14, 0, 0, 0,
    -15, 0, 0, 0, 0, -2, 0, 0,
    0, -3, 0, -4, 0, -5, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, -3, 0,
    0, 0, 0, 0, 0, 0, 1, 0,
    0, 0, 0, 0, -6, 0, 0, 0,
    0, 5, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    -8, 0, 0, 0, 0, 0, -2, 0,
    0, 0, -5, 0, -4, 0, -14, 0,
    0, 0, 0, 0, 0, 0, -5, 0,
    0, 0, 0, 0, 0, 0, -5, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    -14, 0, 0, 0, 0, 3, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, -7, 0, 0, 0,
    0, 0, 0, 0, 1, -12, -8, 0,
    0, 0, -5, 0, 0, 2, 3, 0,
    0, 0, 0, 0, 0, 0, 6, 0,
    0, 0, -5, 3, 3, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, -2, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, -16, 0, 0, 0,
    0, 0, 0, 0, 0, -2, 0, -4,
    0, -5, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, -2, 0, 0, 0,
    0, 0, -2, 0, 0, 0, 0, 0,
    -3, 0, 0, 0, 0, 0, 0, 0,
    2, 0, 0, 0, 0, 0, -16, 0,
    0, -7, 0, 0, 0, 0, 0, -2,
    0, 0, 0, -2, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    -11, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 2, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, -4, -1, 0, 0,
    0, 0, -2, 0, 1, -9, 0, 0,
    0, 0, -11, 0, 0, 2, 0, 0,
    0, 0, -3, 3, 0, 6, 3, 0,
    -5, 0, -5, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, -6, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    -17, 0, 0, 0, -8, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, -3, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    -7, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, -3, 3,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, -2, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    -11, 0, 0, 0, 0, 5, 0, 0,
    0, 0, 0, 6, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    -2, 0, 0, 0, 0, 0, -2, 0,
    0, 0, 0, 0, -3, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, -16, 0, 0, -7, 0, 0,
    0, 0, 0, -2, 0, 0, 0, -5,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    -17, 0, 0, 0, -17, 0, 0, 0,
    0, -11, 0, 0, 0, 0, 0, -4,
    0, 0, 0, 0, -4, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 4,
    0, 0, 0, 0, 0, 0, 0, 0,
    3, 0, 0, 0, 0, 0, 0, 7,
    0, 0, 0, 0, 5, 0, 0, 0,
    0, 2, 7, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, -1, 4,
    7, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 1, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 1, 1, 0, 0, 13, 0, 0,
    0, 13, 7, 0, 0, 0, 0, 2,
    2, 0, 0, 0, 0, 10, 0, 0,
    0, 0, 0, 8, 7, 0, 12, 7,
    16, 12, 14, 12, 0, 0, 10, 12,
    0, 0, 0, 9, 0, 0, 0, 0,
    0, 9, 0, 10, 10, 0, 15, 16,
    0, 12, 12, 18, 17, 13, 0, 0,
    12, 0, 0, 0, 0, 6, 3, 0,
    0, 0, 0, 19, 0, 12, 9, 0,
    9, 7, 8, 0, 0, 8, 0, 11,
    13, 0, 8, 0, 4, 11, 7, 12,
    15, 13, 15, 0, 6, 13, 13, 8,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    -7, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, -5, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0
};


/*Collect the kern class' data in one place*/
static const lv_font_fmt_txt_kern_classes_t kern_classes =
{
    .class_pair_values   = kern_class_values,
    .left_class_mapping  = kern_left_class_mapping,
    .right_class_mapping = kern_right_class_mapping,
    .left_class_cnt      = 57,
    .right_class_cnt     = 50,
};

/*--------------------
 *  ALL CUSTOM DATA
 *--------------------*/

#if LV_VERSION_CHECK(8, 0, 0)
/*Store all the custom data of the font*/
static  lv_font_fmt_txt_glyph_cache_t cache;
static const lv_font_fmt_txt_dsc_t font_dsc = {
#else
static lv_font_fmt_txt_dsc_t font_dsc = {
#endif
    .glyph_bitmap = glyph_bitmap,
    .glyph_dsc = glyph_dsc,
    .cmaps = cmaps,
    .kern_dsc = &kern_classes,
    .kern_scale = 16,
    .cmap_num = 7,
    .bpp = 1,
    .kern_classes = 1,
    .bitmap_format = 0,
#if LV_VERSION_CHECK(8, 0, 0)
    .cache = &cache
#endif
};


/*-----------------
 *  PUBLIC FONT
 *----------------*/

/*Initialize a public general font descriptor*/
#if LV_VERSION_CHECK(8, 0, 0)
const lv_font_t font_lana_vi_12_1 = {
#else
lv_font_t font_lana_vi_12_1 = {
#endif
    .get_glyph_dsc = lv_font_get_glyph_dsc_fmt_txt,    /*Function pointer to get glyph's data*/
    .get_glyph_bitmap = lv_font_get_bitmap_fmt_txt,    /*Function pointer to get glyph's bitmap*/
    .line_height = 18,          /*The maximum line height required by the font*/
    .base_line = 4,             /*Baseline measured from the bottom of the line*/
#if !(LVGL_VERSION_MAJOR == 6 && LVGL_VERSION_MINOR == 0)
    .subpx = LV_FONT_SUBPX_NONE,
#endif
#if LV_VERSION_CHECK(7, 4, 0) || LVGL_VERSION_MAJOR >= 8
    .underline_position = -1,
    .underline_thickness = 1,
#endif
    .dsc = &font_dsc           /*The custom font data. Will be accessed by `get_glyph_bitmap/dsc` */
};



#endif /*#if FONT_LANA_VI_14_1*/

