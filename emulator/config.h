#include "SDL_scancode.h"

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
#define PIN_KEY_POWER   SDL_SCANCODE_SPACE
#define PIN_KEY_A       SDL_SCANCODE_Q
#define PIN_KEY_A_UP    SDL_SCANCODE_W
#define PIN_KEY_A_DOWN  SDL_SCANCODE_S
#define PIN_KEY_A_LEFT  SDL_SCANCODE_A
#define PIN_KEY_A_RIGHT SDL_SCANCODE_D
#define PIN_KEY_B       SDL_SCANCODE_E
#define PIN_KEY_B_UP    SDL_SCANCODE_UP
#define PIN_KEY_B_DOWN  SDL_SCANCODE_DOWN
#define PIN_KEY_B_LEFT  SDL_SCANCODE_LEFT
#define PIN_KEY_B_RIGHT SDL_SCANCODE_RIGHT

#define KEY_POWER      ((uint16_t)(1 << 0))
#define KEY_A          ((uint16_t)(1 << 1))
#define KEY_A_UP       ((uint16_t)(1 << 2))
#define KEY_A_DOWN     ((uint16_t)(1 << 3))
#define KEY_A_LEFT     ((uint16_t)(1 << 4))
#define KEY_A_RIGHT    ((uint16_t)(1 << 5))
#define KEY_B          ((uint16_t)(1 << 6))
#define KEY_B_UP       ((uint16_t)(1 << 7))
#define KEY_B_DOWN     ((uint16_t)(1 << 8))
#define KEY_B_LEFT     ((uint16_t)(1 << 9))
#define KEY_B_RIGHT    ((uint16_t)(1 << 10))
#define KEY_ANY        ((uint16_t)(0xFFFFFFFF))
