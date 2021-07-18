//
// Created by yao on 2021/7/15.
//

#include "u8g2.h"
#include "main.h"


static void delay_us(uint32_t us)
{
    __IO uint32_t currentTicks = SysTick->VAL;
    /* Number of ticks per millisecond */
    const uint32_t tickPerMs = SysTick->LOAD + 1;
    /* Number of ticks to count */
    const uint32_t nbTicks = ((us - ((us > 0) ? 1 : 0)) * tickPerMs) / 1000;
    /* Number of elapsed ticks */
    uint32_t elapsedTicks = 0;
    __IO uint32_t oldTicks = currentTicks;
    do {
        currentTicks = SysTick->VAL;
        elapsedTicks += (oldTicks < currentTicks) ? tickPerMs + oldTicks - currentTicks :
                        oldTicks - currentTicks;
        oldTicks = currentTicks;
    } while (nbTicks > elapsedTicks);
}
UART_HandleTypeDef huart1;

uint8_t u8x8_gpio_and_delay_hal(u8x8_t *u8x8, uint8_t msg, uint8_t arg_int, void *arg_ptr) {
    switch (msg) {
        case U8X8_MSG_DELAY_NANO:			// delay arg_int * 1 nano second
            __NOP();
            __NOP();
            __NOP();
            __NOP();
            __NOP();

            break;
        case U8X8_MSG_DELAY_100NANO:        // delay arg_int * 100 nano seconds
            delay_us(arg_int);
            break;
        case U8X8_MSG_DELAY_10MICRO: // delay arg_int * 10 micro seconds
            delay_us(10*arg_int);
            break;
        case U8X8_MSG_DELAY_MILLI: // delay arg_int * 1 milli second
            HAL_Delay(arg_int);
            break;
        case U8X8_MSG_DELAY_I2C: // arg_int is the I2C speed in 100KHz, e.g. 4 = 400 KHz
            delay_us((5+arg_int-1)/arg_int);
            break;                    // arg_int=1: delay by 5us, arg_int = 4: delay by 1.25us
#if defined(U8G2_SCK_GPIO_Port) && defined(U8G2_SCK_Pin)
        case U8X8_MSG_GPIO_SPI_CLOCK:
//            HAL_UART_Transmit(&huart1,(uint8_t*)"clk",3,HAL_MAX_DELAY);
            HAL_GPIO_WritePin(U8G2_SCK_GPIO_Port,U8G2_SCK_Pin,arg_int==0?GPIO_PIN_RESET:GPIO_PIN_SET);
            break;
#endif
#if defined(U8G2_MOSI_GPIO_Port) && defined(U8G2_MOSI_Pin)
        case U8X8_MSG_GPIO_SPI_DATA:
            HAL_GPIO_WritePin(U8G2_MOSI_GPIO_Port,U8G2_MOSI_Pin,arg_int==0?GPIO_PIN_RESET:GPIO_PIN_SET);
            break;
#endif
#if defined(U8G2_CS_GPIO_Port) && defined(U8G2_CS_Pin)
        case U8X8_MSG_GPIO_CS:				// CS (chip select) pin: Output level in arg_int
            HAL_GPIO_WritePin(U8G2_CS_GPIO_Port,U8G2_CS_Pin,arg_int==0?GPIO_PIN_RESET:GPIO_PIN_SET);
            break;
#endif
#if defined(U8G2_RESET_GPIO_Port) && defined(U8G2_RESET_Pin)
        case U8X8_MSG_GPIO_RESET:			// Reset pin: Output level in arg_int
            HAL_GPIO_WritePin(U8G2_RESET_GPIO_Port,U8G2_RESET_Pin,arg_int);
            break;
#endif
#if defined(U8G2_DC_GPIO_Port) && defined(U8G2_DC_Pin)
        case U8X8_MSG_GPIO_DC:				// DC (data/cmd, A0, register select) pin: Output level in arg_int
            HAL_GPIO_WritePin(U8G2_DC_GPIO_Port,U8G2_DC_Pin,arg_int);
            break;
#endif
#if defined(U8G2_SCL_GPIO_Port) && defined(U8G2_SCL_Pin)
        case U8X8_MSG_GPIO_I2C_CLOCK: // arg_int=0: Output low at I2C clock pin
            HAL_GPIO_WritePin(U8G2_SCL_GPIO_Port,U8G2_SCL_Pin,arg_int);
            break;                    // arg_int=1: Input dir with pullup high for I2C clock pin
#endif
#if defined(U8G2_SDA_GPIO_Port) && defined(U8G2_SDA_Pin)
        case U8X8_MSG_GPIO_I2C_DATA:  // arg_int=0: Output low at I2C data pin
            HAL_GPIO_WritePin(U8G2_SDA_GPIO_Port,U8G2_SDA_Pin,arg_int);
            break;                    // arg_int=1: Input dir with pullup high for I2C data pin
#endif

        case U8X8_MSG_GPIO_MENU_SELECT:
#if defined(U8G2_SELECT_GPIO_Port) && defined(U8G2_SELECT_Pin)
            u8x8_SetGPIOResult(u8x8, HAL_GPIO_ReadPin(U8G2_SELECT_GPIO_Port,U8G2_SELECT_Pin));
#else
            u8x8_SetGPIOResult(u8x8, /* get menu select pin state */ 0);
#endif
            break;
        case U8X8_MSG_GPIO_MENU_NEXT:
#if defined(U8G2_NEXT_GPIO_Port) && defined(U8G2_NEXT_Pin)
            u8x8_SetGPIOResult(u8x8, HAL_GPIO_ReadPin(U8G2_NEXT_GPIO_Port,U8G2_NEXT_Pin));
#else
            u8x8_SetGPIOResult(u8x8, /* get menu select pin state */ 0);
#endif
            break;
        case U8X8_MSG_GPIO_MENU_PREV:
#if defined(U8G2_PREV_GPIO_Port) && defined(U8G2_PREV_Pin)
            u8x8_SetGPIOResult(u8x8, HAL_GPIO_ReadPin(U8G2_PREV_GPIO_Port,U8G2_PREV_Pin));
#else
            u8x8_SetGPIOResult(u8x8, /* get menu select pin state */ 0);
#endif
            break;
        case U8X8_MSG_GPIO_MENU_HOME:
#if defined(U8G2_MENU_GPIO_Port) && defined(U8G2_MENU_Pin)
            u8x8_SetGPIOResult(u8x8, HAL_GPIO_ReadPin(U8G2_MENU_GPIO_Port,U8G2_MENU_Pin));
#else
            u8x8_SetGPIOResult(u8x8, /* get menu select pin state */ 0);
#endif
            break;
        case U8X8_MSG_GPIO_AND_DELAY_INIT:	// called once during init phase of u8g2/u8x8
            break;							// can be used to setup pins
        default:
            u8x8_SetGPIOResult(u8x8, 1); // default return value
            break;
    }
    return 1;
}
