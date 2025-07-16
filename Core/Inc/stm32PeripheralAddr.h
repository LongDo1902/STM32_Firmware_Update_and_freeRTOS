/*
 * stm32PeripheralAddr.h
 *
 *  Created on: Jul 16, 2025
 *      Author: dobao
 */

#ifndef INC_STM32PERIPHERALADDR_H_
#define INC_STM32PERIPHERALADDR_H_

#include <stdint.h>
#include <stdio.h>

/*
 * ----------------------------------------------------
 * Peripheral's Base Address Declarations
 * ----------------------------------------------------
 */
#define DMA2_BASE_ADDR		0x50000000U
#define DMA1_BASE_ADDR		0x40026400U

#define FLASH_BASE_ADDR		0x40023C00U
#define RCC_BASE_ADDR		0x40023800U
#define CRC_BASE_ADDR		0x40023000U
#define EXTI_BASE_ADDR		0x40013C00U
#define ADC1_BASE_ADDR		0x40012000U

#define GPIOH_BASE_ADDR		0x40023000U
#define GPIOE_BASE_ADDR		0x40021000U
#define GPIOD_BASE_ADDR		0x40020C00U
#define GPIOC_BASE_ADDR		0x40020800U
#define GPIOB_BASE_ADDR		0x40020400U
#define GPIOA_BASE_ADDR		0x40020000U

#define UART1_BASE_ADDR		0x40011000U
#define UART2_BASE_ADDR		0x40004400U
#define UART6_BASE_ADDR		0x40011400U

#define TIM1_BASE_ADDR		0x40010000U
#define TIM2_BASE_ADDR		0x40000000U
#define	TIM3_BASE_ADDR		0x40000400U
#define TIM4_BASE_ADDR		0x40000800U
#define TIM5_BASE_ADDR		0x40000C00U
#define TIM9_BASE_ADDR		0x40014000U
#define TIM10_BASE_ADDR		0x40014400U
#define TIM11_BASE_ADDR		0x40014800U

s



#endif /* INC_STM32PERIPHERALADDR_H_ */
