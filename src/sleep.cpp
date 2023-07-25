#include "sleep.h"
#include "hal_data.h"
#include "Arduino.h"

void goSleep() {
    PIN_DEVICE_OFF; //关闭oled和蜂鸣器的ldo
    PIN_DC_LOW;
    PIN_RST_LOW;
    R_SPI_Close(&g_spi0_ctrl);
    R_LPM_Open(&g_lpm0_ctrl, &g_lpm0_cfg);
    R_LPM_LowPowerModeEnter(&g_lpm0_ctrl);

    //醒来
    PIN_DEVICE_ON;
    R_LPM_Close(&g_lpm0_ctrl);
    u8g2.begin();
}