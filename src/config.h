#include "hal_data.h"


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

// 控制屏幕,蜂鸣器用的ldo的enable引脚
#define PIN_DEVICE_ON    R_IOPORT_PinWrite(&g_ioport_ctrl, BSP_IO_PORT_00_PIN_00, BSP_IO_LEVEL_HIGH);
#define PIN_DEVICE_OFF   R_IOPORT_PinWrite(&g_ioport_ctrl, BSP_IO_PORT_00_PIN_00, BSP_IO_LEVEL_LOW);



/////////
#define PIN_KEY_POWER   BSP_IO_PORT_04_PIN_01
#define PIN_KEY_A       BSP_IO_PORT_03_PIN_02
#define PIN_KEY_A_UP    BSP_IO_PORT_02_PIN_08
#define PIN_KEY_A_DOWN  BSP_IO_PORT_03_PIN_01
#define PIN_KEY_A_LEFT  BSP_IO_PORT_02_PIN_06
#define PIN_KEY_A_RIGHT BSP_IO_PORT_02_PIN_07
#define PIN_KEY_B       BSP_IO_PORT_09_PIN_14
#define PIN_KEY_B_UP    BSP_IO_PORT_04_PIN_07
#define PIN_KEY_B_DOWN  BSP_IO_PORT_04_PIN_09
#define PIN_KEY_B_LEFT  BSP_IO_PORT_09_PIN_15
#define PIN_KEY_B_RIGHT BSP_IO_PORT_04_PIN_08
