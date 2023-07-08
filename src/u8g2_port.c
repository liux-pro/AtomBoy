#include "u8g2_port.h"

uint8_t u8x8_gpio_and_delay(u8x8_t *u8x8, uint8_t msg, uint8_t arg_int, void *arg_ptr)
{
  switch(msg)
  {
//    case U8X8_MSG_GPIO_AND_DELAY_INIT:  // called once during init phase of u8g2/u8x8
//      break;                            // can be used to setup pins
    case U8X8_MSG_DELAY_NANO:           // delay arg_int * 1 nano second
        for(int i=0;i<arg_int;i++)__NOP();
      break;
    case U8X8_MSG_DELAY_100NANO:        // delay arg_int * 100 nano seconds
        for(int i=0;i<arg_int*10;i++)__NOP();
      break;
    case U8X8_MSG_DELAY_10MICRO:        // delay arg_int * 10 micro seconds
        R_BSP_SoftwareDelay (arg_int*10, BSP_DELAY_UNITS_MICROSECONDS);
      break;
    case U8X8_MSG_DELAY_MILLI:          // delay arg_int * 1 milli second
        R_BSP_SoftwareDelay (arg_int, BSP_DELAY_UNITS_MILLISECONDS);
      break;
//    case U8X8_MSG_DELAY_I2C:                // arg_int is the I2C speed in 100KHz, e.g. 4 = 400 KHz
//      break;                            // arg_int=1: delay by 5us, arg_int = 4: delay by 1.25us
    case U8X8_MSG_GPIO_SPI_CLOCK:              // D0 or SPI clock pin: Output level in arg_int
        if(arg_int)PIN_CLK_HIGH;else PIN_CLK_LOW;
      break;
    case U8X8_MSG_GPIO_SPI_DATA:              // D1 or SPI data pin: Output level in arg_int
        if(arg_int)PIN_MOSI_HIGH;else PIN_MOSI_LOW;
      break;
//    case U8X8_MSG_GPIO_D2:              // D2 pin: Output level in arg_int
//      break;
//    case U8X8_MSG_GPIO_D3:              // D3 pin: Output level in arg_int
//      break;
//    case U8X8_MSG_GPIO_D4:              // D4 pin: Output level in arg_int
//      break;
//    case U8X8_MSG_GPIO_D5:              // D5 pin: Output level in arg_int
//      break;
//    case U8X8_MSG_GPIO_D6:              // D6 pin: Output level in arg_int
//      break;
//    case U8X8_MSG_GPIO_D7:              // D7 pin: Output level in arg_int
//      break;
//    case U8X8_MSG_GPIO_E:               // E/WR pin: Output level in arg_int
//      break;
//    case U8X8_MSG_GPIO_CS:              // CS (chip select) pin: Output level in arg_int
//      break;
    case U8X8_MSG_GPIO_DC:              // DC (data/cmd, A0, register select) pin: Output level in arg_int
        if(arg_int)PIN_DC_HIGH;else PIN_DC_LOW;
      break;
    case U8X8_MSG_GPIO_RESET:           // Reset pin: Output level in arg_int
        if(arg_int)PIN_RST_HIGH;else PIN_RST_LOW;
      break;
//    case U8X8_MSG_GPIO_CS1:             // CS1 (chip select) pin: Output level in arg_int
//      break;
//    case U8X8_MSG_GPIO_CS2:             // CS2 (chip select) pin: Output level in arg_int
//      break;
//    case U8X8_MSG_GPIO_I2C_CLOCK:       // arg_int=0: Output low at I2C clock pin
//      break;                            // arg_int=1: Input dir with pullup high for I2C clock pin
//    case U8X8_MSG_GPIO_I2C_DATA:            // arg_int=0: Output low at I2C data pin
//      break;                            // arg_int=1: Input dir with pullup high for I2C data pin
//    case U8X8_MSG_GPIO_MENU_SELECT:
//      break;
//    case U8X8_MSG_GPIO_MENU_NEXT:
//      break;
//    case U8X8_MSG_GPIO_MENU_PREV:
//      break;
//    case U8X8_MSG_GPIO_MENU_HOME:
//      break;
    default:
      break;
  }
  return 1;
}


volatile bool g_transfer_complete;

void spi_callback (spi_callback_args_t * p_args)
{
    if (SPI_EVENT_TRANSFER_COMPLETE == p_args->event)
    {
        g_transfer_complete = true;

    }
}

uint8_t u8x8_byte_renesas_hw_spi(u8x8_t *u8x8, uint8_t msg, uint8_t arg_int, void *arg_ptr) {
  switch(msg) {
    case U8X8_MSG_BYTE_SEND:
        g_transfer_complete=false;
        R_SPI_Write(&g_spi0_ctrl, arg_ptr, arg_int, SPI_BIT_WIDTH_8_BITS);
        while (false == g_transfer_complete);
      break;
    case U8X8_MSG_BYTE_INIT:
        R_SPI_Open(&g_spi0_ctrl, &g_spi0_cfg);
      break;
    case U8X8_MSG_BYTE_SET_DC:
      u8x8_gpio_SetDC(u8x8, arg_int);
      break;
    case U8X8_MSG_BYTE_START_TRANSFER:


      break;
    case U8X8_MSG_BYTE_END_TRANSFER:


      break;
    default:
      return 0;
  }
  return 1;
}
