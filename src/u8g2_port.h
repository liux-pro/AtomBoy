#pragma once

#include <u8g2.h>
#include <u8x8.h>
#include "hal_data.h"
#include "config.h"

#ifdef __cplusplus
extern "C" {
#endif

uint8_t u8x8_byte_renesas_hw_spi(u8x8_t *u8x8, uint8_t msg, uint8_t arg_int, void *arg_ptr);

uint8_t u8x8_gpio_and_delay(u8x8_t *u8x8, uint8_t msg, uint8_t arg_int, void *arg_ptr);


#ifdef __cplusplus
}
#endif


#ifdef __cplusplus

#include "U8g2lib.h"
#include "Print.h"

class U8G2_SSD1603_128X64_RENESAS_F_4W_HW_SPI : public U8G2, public Print {
public:
    U8G2_SSD1603_128X64_RENESAS_F_4W_HW_SPI() : U8G2() {
        u8g2_Setup_ssd1306_128x64_noname_f(&u8g2,U8G2_R0,u8x8_byte_renesas_hw_spi,u8x8_gpio_and_delay);
    }
    size_t write(const uint8_t *buffer, size_t size) override {
        return 1;
    }
    size_t write(uint8_t) override {
        return 1;
    }
    void printf(int x, int y, const char *format, ...) {
        char buffer[128];  //缓冲
        va_list args;
        va_start(args, format);
        vsnprintf(buffer, sizeof(buffer), format, args);  // 使用 vsnprintf 将格式化的字符串写入缓冲区
        va_end(args);

        u8g2_DrawUTF8(&u8g2, x, y, buffer);  // 将缓冲区的内容传递给 u8g2_DrawStr 函数进行显示
    }
};



#endif
