#pragma once
#include "hal_data.h"
#include "u8g2_port.h"

extern U8G2_SH1106_128X64_RENESAS_F_4W_HW_SPI u8g2;
#define displayHeight  64
#define displayWidth  128

void setup();
void loop();

