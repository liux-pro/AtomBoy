#include "hal_data.h"
#include "button.h"
#include "utils.h"


uint8_t keyStatus = 0;
uint8_t keyLastStatus = 0xff;
//R_IOPORT_PinWrite(&g_ioport_ctrl, BSP_IO_PORT_01_PIN_04, BSP_IO_LEVEL_HIGH);


int flag = 1;


void g_timer0_1ms_callback(timer_callback_args_t *p_args) {
    if (TIMER_EVENT_CREST == p_args->event) {


    }
}


uint8_t *keyScan() {

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

void keyClear(uint8_t mask) {
    setBit(mask, &keyStatus, false);
}

void keyClear() {
    setBit(0xFF, &keyStatus, false);
}

bool keyCheck(uint8_t mask) {
    return checkBit(mask, &keyStatus);
}
