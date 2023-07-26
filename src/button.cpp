#include "hal_data.h"
#include "button.h"
#include "utils.h"
#include "config.h"
#include "fps/fps.h"
#include "sleep.h"

#define delay(ms) R_BSP_SoftwareDelay(ms, BSP_DELAY_UNITS_MILLISECONDS)


uint16_t keyStatus = 0;  // bit 1 代表有按下事件
uint16_t keyLastStatus = 0xFFFF; //保存按键实际状态
/**
 * 判断powerkey是长按还是短按
 * 长按500ms重启
 * 短按待机
 * @param pinKey
 */
static void powerKey(bsp_io_port_pin_t pinKey) {
    bsp_io_level_t temp;
    R_IOPORT_PinRead(&g_ioport_ctrl, pinKey, &temp);
    if (temp == BSP_IO_LEVEL_LOW) {
            uint64_t keyTime = fps_get_ms();
            while (true) {
                bsp_io_level_t powerKeyStatus;
                R_IOPORT_PinRead(&g_ioport_ctrl, pinKey, &powerKeyStatus);
                if (powerKeyStatus == BSP_IO_LEVEL_HIGH) {
                    break;
                }
            }
            keyTime = fps_get_ms() - keyTime;
            if (keyTime>500){
                NVIC_SystemReset();
            } else{
                goSleep();
            }
    }
}

/**
 * 按键扫描
 * @param pinKey
 * @param key
 */
static void oneKey(bsp_io_port_pin_t pinKey, uint16_t key) {
    bsp_io_level_t temp;
    R_IOPORT_PinRead(&g_ioport_ctrl, pinKey, &temp);
    if ((temp == BSP_IO_LEVEL_LOW) && checkBit(key, &keyLastStatus)) {
        setBit(key, &keyStatus, true);
    }
    setBit(key, &keyLastStatus, temp);
}

uint16_t keyScan() {
    powerKey(PIN_KEY_POWER);
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
    return keyLastStatus;
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