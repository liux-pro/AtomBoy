#include <cstdlib>
#include <unordered_map>
#include <SDL_keycode.h>
#include <SDL_events.h>
#include "ArduinoCompatible.h"

U8G2_SDL_128X64::U8G2_SDL_128X64() : U8G2() {
    u8g2_SetupBuffer_SDL_128x64(&u8g2, U8G2_R0);
}

void U8G2_SDL_128X64::printf(int x, int y, const char *format, ...) {
    char buffer[128];  //缓冲
    va_list args;
    va_start(args, format);
    vsnprintf(buffer, sizeof(buffer), format, args);  // 使用 vsnprintf 将格式化的字符串写入缓冲区
    va_end(args);

    u8g2_DrawUTF8(&u8g2, x, y, buffer);  // 将缓冲区的内容传递给 u8g2_DrawStr 函数进行显示
}