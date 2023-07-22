#pragma once
#ifdef __cplusplus
#include "ArduinoCompatible.h"
extern U8G2_SSD1603_128X64_RENESAS_F_4W_HW_SPI u8g2;
extern "C"
{
#endif
#define displayHeight  64
#define displayWidth  128

void setup();
void loop();



#ifdef __cplusplus
}
#endif


