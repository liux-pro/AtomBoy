#include "hal_data.h"
#include "button.h"
#include "utils.h"
#include "config.h"

#define delay(ms) R_BSP_SoftwareDelay(ms, BSP_DELAY_UNITS_MILLISECONDS)


uint16_t keyStatus = 0;
uint16_t keyLastStatus = 0xFFFF;


static void oneKey(bsp_io_port_pin_t pinKey,uint16_t key){
    bsp_io_level_t temp;
    R_IOPORT_PinRead(&g_ioport_ctrl, pinKey, &temp);
    if ((temp == BSP_IO_LEVEL_LOW) && checkBit(key, &keyLastStatus)) {
        setBit(key, &keyStatus, true);
    }
    setBit(key, &keyLastStatus, temp);
}

uint16_t *keyScan() {
    oneKey(PIN_KEY_POWER, KEY_POWER);
    oneKey(PIN_KEY_A, KEY_A);
    oneKey(PIN_KEY_A_UP, KEY_A_UP);
    oneKey(PIN_KEY_A_DOWN, KEY_A_DOWN);
    oneKey(PIN_KEY_A_LEFT, KEY_A_LEFT);
    oneKey(PIN_KEY_A_RIGHT, KEY_A_RIGHT);
    oneKey(PIN_KEY_B, KEY_B);
    oneKey(PIN_KEY_B_UP, KEY_B_UP);
    oneKey(PIN_KEY_B_DOWN, KEY_B_DOWN);
    oneKey(PIN_KEY_B_LEFT, KEY_B_LEFT);
    oneKey(PIN_KEY_B_RIGHT, KEY_B_RIGHT);
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