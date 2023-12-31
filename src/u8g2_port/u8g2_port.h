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
#include <cstdio>

class U8G2_SH1106_128X64_RENESAS_F_4W_HW_SPI : public U8G2 {
public:
    U8G2_SH1106_128X64_RENESAS_F_4W_HW_SPI();
    void printf(int x, int y, const char *format, ...);
};
#endif
