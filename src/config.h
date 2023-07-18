#include "hal_data.h"

#define displayHeight  64
#define displayWidth  128

#define PIN_DC_HIGH R_IOPORT_PinWrite(&g_ioport_ctrl, BSP_IO_PORT_05_PIN_00, BSP_IO_LEVEL_HIGH)
#define PIN_DC_LOW  R_IOPORT_PinWrite(&g_ioport_ctrl, BSP_IO_PORT_05_PIN_00, BSP_IO_LEVEL_LOW)

#define PIN_RST_HIGH R_IOPORT_PinWrite(&g_ioport_ctrl, BSP_IO_PORT_01_PIN_11, BSP_IO_LEVEL_HIGH)
#define PIN_RST_LOW  R_IOPORT_PinWrite(&g_ioport_ctrl, BSP_IO_PORT_01_PIN_11, BSP_IO_LEVEL_LOW)

#define PIN_MOSI_HIGH R_IOPORT_PinWrite(&g_ioport_ctrl, BSP_IO_PORT_01_PIN_01, BSP_IO_LEVEL_HIGH)
#define PIN_MOSI_LOW  R_IOPORT_PinWrite(&g_ioport_ctrl, BSP_IO_PORT_01_PIN_01, BSP_IO_LEVEL_LOW)

#define PIN_CLK_HIGH R_IOPORT_PinWrite(&g_ioport_ctrl, BSP_IO_PORT_01_PIN_02, BSP_IO_LEVEL_HIGH)
#define PIN_CLK_LOW  R_IOPORT_PinWrite(&g_ioport_ctrl, BSP_IO_PORT_01_PIN_02, BSP_IO_LEVEL_LOW)

#define PIN_LED_ON R_IOPORT_PinWrite(&g_ioport_ctrl, BSP_IO_PORT_01_PIN_04, BSP_IO_LEVEL_HIGH)
#define PIN_LED_OFF  R_IOPORT_PinWrite(&g_ioport_ctrl, BSP_IO_PORT_01_PIN_04, BSP_IO_LEVEL_LOW)


/////////
#define PIN_KEY_A BSP_IO_PORT_00_PIN_00
#define PIN_KEY_B BSP_IO_PORT_00_PIN_01

#define KEY_POWER ((uint8_t)(1<<0))
#define KEY_UP ((uint8_t)(1<<1))
#define KEY_DOWN ((uint8_t)(1<<2))
#define KEY_LEFT ((uint8_t)(1<<3))
#define KEY_RIGHT ((uint8_t)(1<<4))
#define KEY_A ((uint8_t)(1<<5))
#define KEY_B ((uint8_t)(1<<6))
#define KEY_RESERVE ((uint8_t)(1<<7))
#define KEY_ANY 0xFFFF