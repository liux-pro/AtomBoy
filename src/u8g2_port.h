#pragma once
#include <u8g2.h>
#include <u8x8.h>
#include "hal_data.h"
#include "pins.h"

#ifdef __cplusplus
extern "C" {
#endif

uint8_t u8x8_byte_renesas_hw_spi(u8x8_t *u8x8, uint8_t msg, uint8_t arg_int, void *arg_ptr) ;
uint8_t u8x8_gpio_and_delay(u8x8_t *u8x8, uint8_t msg, uint8_t arg_int, void *arg_ptr);


#ifdef __cplusplus
}
#endif


#ifdef __cplusplus

#include "U8g2lib.h"

class U8G2_SSD1603_128X64_RENESAS_F_4W_HW_SPI : public U8G2 {
public:
    U8G2_SSD1603_128X64_RENESAS_F_4W_HW_SPI() : U8G2() {
        u8g2_Setup_ssd1306_128x64_noname_f(&u8g2,U8G2_R1,u8x8_byte_renesas_hw_spi,u8x8_gpio_and_delay);
    }
};


#endif
