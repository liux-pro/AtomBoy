#include "hal_data.h"
#include "button.h"
#include "utils.h"
#include "config.h"

#define delay(ms) R_BSP_SoftwareDelay(ms, BSP_DELAY_UNITS_MILLISECONDS)


uint16_t keyStatus = 0;
uint16_t keyLastStatus = 0xFFFF;



uint16_t *keyScan() {

    bsp_io_level_t temp;
    R_IOPORT_PinRead(&g_ioport_ctrl, PIN_KEY_A, &temp);
    if ((temp == BSP_IO_LEVEL_LOW) && checkBit(KEY_A, &keyLastStatus)) {
        setBit(KEY_A, &keyStatus, true);
    }
    setBit(KEY_A, &keyLastStatus, temp);


    R_IOPORT_PinRead(&g_ioport_ctrl, PIN_KEY_B, &temp);
    if ((temp == BSP_IO_LEVEL_LOW) && checkBit(KEY_B, &keyLastStatus)) {
        setBit(KEY_B, &keyStatus, true);
    }
    setBit(KEY_B, &keyLastStatus, temp);
    return &keyStatus;
}

void keyClear(uint16_t mask) {
    setBit(mask, &keyStatus, false);
}

bool keyCheck(uint16_t mask) {
    bool bit = checkBit(mask, &keyStatus);
    keyClear(mask);
    return bit;
}

bool keyPeek(uint16_t mask) {
    return checkBit(mask, &keyStatus);
}

void keyWaitAnyKey() {
    keyClear(KEY_ANY);
    while (true) {
        delay(10);
        keyScan();
        if (keyCheck(KEY_ANY)) {
            break;
        }
    };
}