#pragma once

#include "U8g2lib.h"
#include <cstdint>
#include <SDL_timer.h>
#include "iostream"
#include <cstdlib>

#define U8G2_SSD1603_128X64_RENESAS_F_4W_HW_SPI U8G2_SDL_128X64

// 使用SDL模拟 12864 oled


class U8G2_SDL_128X64 : public U8G2 {
public:
    U8G2_SDL_128X64();
    void printf(int x, int y, const char *format, ...);
};

#define delay(ms) SDL_Delay(ms)

