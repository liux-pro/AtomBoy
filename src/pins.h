#include "hal_data.h"

#define PIN_DC_HIGH R_IOPORT_PinWrite(&g_ioport_ctrl, BSP_IO_PORT_05_PIN_00, BSP_IO_LEVEL_HIGH)
#define PIN_DC_LOW  R_IOPORT_PinWrite(&g_ioport_ctrl, BSP_IO_PORT_05_PIN_00, BSP_IO_LEVEL_LOW)

#define PIN_RST_HIGH R_IOPORT_PinWrite(&g_ioport_ctrl, BSP_IO_PORT_01_PIN_00, BSP_IO_LEVEL_HIGH)
#define PIN_RST_LOW  R_IOPORT_PinWrite(&g_ioport_ctrl, BSP_IO_PORT_01_PIN_00, BSP_IO_LEVEL_LOW)

#define PIN_MOSI_HIGH R_IOPORT_PinWrite(&g_ioport_ctrl, BSP_IO_PORT_01_PIN_01, BSP_IO_LEVEL_HIGH)
#define PIN_MOSI_LOW  R_IOPORT_PinWrite(&g_ioport_ctrl, BSP_IO_PORT_01_PIN_01, BSP_IO_LEVEL_LOW)

#define PIN_CLK_HIGH R_IOPORT_PinWrite(&g_ioport_ctrl, BSP_IO_PORT_01_PIN_02, BSP_IO_LEVEL_HIGH)
#define PIN_CLK_LOW  R_IOPORT_PinWrite(&g_ioport_ctrl, BSP_IO_PORT_01_PIN_02, BSP_IO_LEVEL_LOW)
