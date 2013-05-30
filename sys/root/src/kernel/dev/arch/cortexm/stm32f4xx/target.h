/******************** (C) COPYRIGHT 2013 IJINUS ********************************
* File Name          : target.h
* Author             : Yoann TREGUIER
* Version            : Drivers demo
* Date               : 2013/05/24
* Description        : Target dependant definitions
*******************************************************************************/
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __TARGET_H
#define __TARGET_H

/* Includes ------------------------------------------------------------------*/
#include "kernel/dev/arch/cortexm/stm32f4xx/driverlib/stm32f4xx.h"

/* Exported define -----------------------------------------------------------*/
/* Exported types ------------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Exported variables --------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/
/* Drivers configuration -----------------------------------------------------*/
/*******************************************************************************
* GPIO
*******************************************************************************/
//#define _GPIO_I2CIO_SUPPORT
#define _GPIO_DEFAULT_SPEED   GPIO_Speed_50MHz

typedef enum
{
  GPIO_ID_TXD3,
  GPIO_ID_RXD3,

  GPIO_ID_LED1,
  GPIO_ID_LED2,
  GPIO_ID_LED3,
  GPIO_ID_LED4,

  GPIO_ID_WKUP,

  GPIO_NB
} _GPIO_LIST;

#define GPIO_TXD3  (&Gpio_Descriptor[GPIO_ID_TXD3])
#define GPIO_RXD3  (&Gpio_Descriptor[GPIO_ID_RXD3])

#define GPIO_LED1  (&Gpio_Descriptor[GPIO_ID_LED1])
#define GPIO_LED2  (&Gpio_Descriptor[GPIO_ID_LED2])
#define GPIO_LED3  (&Gpio_Descriptor[GPIO_ID_LED3])
#define GPIO_LED4  (&Gpio_Descriptor[GPIO_ID_LED4])

#define GPIO_WKUP   (&Gpio_Descriptor[GPIO_ID_WKUP])

/*******************************************************************************
* UART
*******************************************************************************/
//#define _UART_OS_SUPPORT

typedef enum
{
  UART_ID_3,
  UART_NB
} _UART_LIST;

#define UART_3  (&Uart_Descriptor[UART_ID_3])


#endif /* __TARGET_H */

/******************* (C) COPYRIGHT 2013 IJINUS ****************END OF FILE*****/