#include "U8g2lib.h"
#include "u8g2_port.h"


U8G2_SH1106_128X64_RENESAS_F_4W_HW_SPI::U8G2_SH1106_128X64_RENESAS_F_4W_HW_SPI() : U8G2() {
    u8g2_Setup_sh1106_128x64_noname_f(&u8g2, U8G2_R0, u8x8_byte_renesas_hw_spi, u8x8_gpio_and_delay);
}


void U8G2_SH1106_128X64_RENESAS_F_4W_HW_SPI::printf(int x, int y, const char *format, ...) {
    char buffer[128];  //缓冲
    va_list args;
    va_start(args, format);
    vsnprintf(buffer, sizeof(buffer), format, args);  // 使用 vsnprintf 将格式化的字符串写入缓冲区
    va_end(args);

    u8g2_DrawUTF8(&u8g2, x, y, buffer);  // 将缓冲区的内容传递给 u8g2_DrawStr 函数进行显示
}