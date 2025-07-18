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
#define DMA2_BASE_ADDR		0x40026400U
#define DMA1_BASE_ADDR		0x40026000U

#define FLASH_BASE_ADDR		  0x40023C00U
#define RCC_BASE_ADDR		  0x40023800U
#define CRC_BASE_ADDR		  0x40023000U
#define EXTI_BASE_ADDR		  0x40013C00U
#define ADC1_BASE_ADDR		  0x40012000U
#define ADC1_COMMON_BASE_ADDR 0x40012300U

#define GPIOH_BASE_ADDR	0x40021C00U
#define GPIOE_BASE_ADDR	0x40021000U
#define GPIOD_BASE_ADDR	0x40020C00U
#define GPIOC_BASE_ADDR	0x40020800U
#define GPIOB_BASE_ADDR	0x40020400U
#define GPIOA_BASE_ADDR	0x40020000U

#define UART1_BASE_ADDR	0x40011000U
#define UART2_BASE_ADDR	0x40004400U
#define UART6_BASE_ADDR	0x40011400U

#define TIM1_BASE_ADDR	0x40010000U
#define TIM2_BASE_ADDR	0x40000000U
#define	TIM3_BASE_ADDR	0x40000400U
#define TIM4_BASE_ADDR	0x40000800U
#define TIM5_BASE_ADDR	0x40000C00U
#define TIM9_BASE_ADDR	0x40014000U
#define TIM10_BASE_ADDR	0x40014400U
#define TIM11_BASE_ADDR	0x40014800U

#define NVIC_BASE_ADDR 	0xE000E100U
#define VTOR_BASE_ADDR 0xE000ED08UL


/*
 * ----------------------------------------------------
 * Peripheral Register Address Offsets
 * ----------------------------------------------------
 */
typedef struct{
	volatile uint32_t MODER;
	volatile uint32_t OTYPER;
	volatile uint32_t OSPEEDR;
	volatile uint32_t PUPDR;
	volatile uint32_t IDR;
	volatile uint32_t ODR;
	volatile uint32_t BSRR;
	volatile uint32_t LCKR;
	volatile uint32_t AFRL;
	volatile uint32_t AFRH;
}gpioRegOffset_t;


typedef struct{
	volatile uint32_t UART_SR;
	volatile uint32_t UART_DR;
	volatile uint32_t UART_BRR;
	volatile uint32_t UART_CR1;
	volatile uint32_t UART_CR2;
	volatile uint32_t UART_CR3;
	volatile uint32_t UART_GTPR;
}uartRegOffset_t;


typedef struct{
	volatile uint32_t TIM_CR1;
	volatile uint32_t TIM_CR2;
	volatile uint32_t TIM_SMCR;
	volatile uint32_t TIM_DIER;

	volatile uint32_t TIM_SR;
	volatile uint32_t TIM_EGR;
	volatile uint32_t TIM_CCMR1;
	volatile uint32_t TIM_CCMR2;

	volatile uint32_t TIM_CCER;
	volatile uint32_t TIM_CNT;
	volatile uint32_t TIM_PSC;
	volatile uint32_t TIM_ARR;

	volatile uint32_t TIM_RCR;
	volatile uint32_t TIM_CCR1;
	volatile uint32_t TIM_CCR2;
	volatile uint32_t TIM_CCR3;

	volatile uint32_t TIM_CCR4;
	volatile uint32_t TIM_BDTR;
	volatile uint32_t TIM_DCR;
	volatile uint32_t TIM_DMAR;

	union{
		volatile uint32_t TIM2_OR;
		volatile uint32_t TIM5_OR;
		volatile uint32_t TIM11_OR;
	};
}timerRegOffset_t;


typedef struct{
	volatile uint32_t RCC_CR;			//0x00 (RCC Clock Control Reg)
	volatile uint32_t RCC_PLL_CFGR;		//0x04 (RCC PLL Config Reg)
	volatile uint32_t RCC_CFGR;			//0x08 (RCC Clock Config Reg)
	volatile uint32_t RCC_CIR;			//0x0C (RCC Clock Interrupt Reg)

	volatile uint32_t RCC_AHB1_RSTR;	//0x10 (RCC AHB1 Reset Reg)
	volatile uint32_t RCC_AHB2_RSTR;	//0x14 (RCC AHB2 Reset Reg)

	volatile uint32_t RESERVED0;
	volatile uint32_t RESERVED1;

	volatile uint32_t RCC_APB1_RSTR;	//0x20 (RCC APB1 Reset Reg)
	volatile uint32_t RCC_APB2_RSTR;	//0x24 (RCC APB2 Reset Reg)

	volatile uint32_t RESERVED2;
	volatile uint32_t RESERVED3;

	volatile uint32_t RCC_AHB1_ENR;		//0x30 (RCC AHB1 Clock Enable)
	volatile uint32_t RCC_AHB2_ENR;		//0x34 (RCC AHB2 Clock Enable)

	volatile uint32_t RESERVED4;
	volatile uint32_t RESERVED5;

	volatile uint32_t RCC_APB1_ENR;		//0x40 (RCC APB1 Clock Enable)
	volatile uint32_t RCC_APB2_ENR;		//0x44 (RCC APB2 Clock Enable)

	volatile uint32_t RESERVED6;
	volatile uint32_t RESERVED7;

	volatile uint32_t RCC_AHB1_LP_ENR;	//0x50 (RCC AHB1 Low Power Mode Enable)
	volatile uint32_t RCC_AHB2_LP_ENR;	//0x54 (RCC AHB2 Low Power Mode Enable)

	volatile uint32_t RESERVED8;
	volatile uint32_t RESERVED9;

	volatile uint32_t RCC_APB1_LP_ENR;	//0x60 (RCC APB1 Low Power Mode Enable)
	volatile uint32_t RCC_APB2_LP_ENR;	//0x64 (RCC APB2 Low Power Mode Enable)

	volatile uint32_t RESERVED10;
	volatile uint32_t RESERVED11;

	volatile uint32_t RCC_BDCR;			//0x70 (RCC Backup Domain Control Reg)
	volatile uint32_t RCC_CSR;			//0x74 (RCC Clock Control & Status Reg)

	volatile uint32_t RESERVED12;
	volatile uint32_t RESERVED13;

	volatile uint32_t RCC_SSCGR;		//0x80 (RCC Spread Spectrum Clock Generation Reg)
	volatile uint32_t RCC_PLL_I2S_CFGR;	//0x84 (RCC PLLI2S Config Reg)

	volatile uint32_t RESERVED14;

	volatile uint32_t RCC_DCK_CFGR;		//0x8C (RCC Dedicated Clocks Config Reg)
}rccRegOffset_t;


typedef struct{
	volatile uint32_t ADC_SR;
	volatile uint32_t ADC_CR1;
	volatile uint32_t ADC_CR2;

	volatile uint32_t ADC_SMPR1;
	volatile uint32_t ADC_SMPR2;

	volatile uint32_t ADC_JOFR1;
	volatile uint32_t ADC_JOFR2;
	volatile uint32_t ADC_JOFR3;
	volatile uint32_t ADC_JOFR4;

	volatile uint32_t ADC_HTR;
	volatile uint32_t ADC_LTR;

	volatile uint32_t ADC_SQR1;
	volatile uint32_t ADC_SQR2;
	volatile uint32_t ADC_SQR3;

	volatile uint32_t ADC_JSQR;

	volatile uint32_t ADC_JDR1;
	volatile uint32_t ADC_JDR2;
	volatile uint32_t ADC_JDR3;
	volatile uint32_t ADC_JDR4;

	volatile uint32_t ADC_DR;
}adcRegOffset_t;


typedef struct{
	volatile uint32_t ADC_CSR;
	volatile uint32_t ADC_CCR;
	volatile uint32_t ADC_CDR;
}adcCommonRegOffset_t;


typedef struct{
	volatile uint32_t DMA_LISR;
	volatile uint32_t DMA_HISR;
	volatile uint32_t DMA_LIFCR;
	volatile uint32_t DMA_HIFCR;

	volatile uint32_t DMA_S0CR;
	volatile uint32_t DMA_S0NDTR;
	volatile uint32_t DMA_S0PAR;
	volatile uint32_t DMA_S0M0AR;
	volatile uint32_t DMA_S0M1AR;
	volatile uint32_t DMA_S0FCR;

	volatile uint32_t DMA_S1CR;
	volatile uint32_t DMA_S1NDTR;
	volatile uint32_t DMA_S1PAR;
	volatile uint32_t DMA_S1M0AR;
	volatile uint32_t DMA_S1M1AR;
	volatile uint32_t DMA_S1FCR;

	volatile uint32_t DMA_S2CR;
	volatile uint32_t DMA_S2NDTR;
	volatile uint32_t DMA_S2PAR;
	volatile uint32_t DMA_S2M0AR;
	volatile uint32_t DMA_S2M1AR;
	volatile uint32_t DMA_S2FCR;

	volatile uint32_t DMA_S3CR;
	volatile uint32_t DMA_S3NDTR;
	volatile uint32_t DMA_S3PAR;
	volatile uint32_t DMA_S3M0AR;
	volatile uint32_t DMA_S3M1AR;
	volatile uint32_t DMA_S3FCR;

	volatile uint32_t DMA_S4CR;
	volatile uint32_t DMA_S4NDTR;
	volatile uint32_t DMA_S4PAR;
	volatile uint32_t DMA_S4M0AR;
	volatile uint32_t DMA_S4M1AR;
	volatile uint32_t DMA_S4FCR;

	volatile uint32_t DMA_S5CR;
	volatile uint32_t DMA_S5NDTR;
	volatile uint32_t DMA_S5PAR;
	volatile uint32_t DMA_S5M0AR;
	volatile uint32_t DMA_S5M1AR;
	volatile uint32_t DMA_S5FCR;

	volatile uint32_t DMA_S6CR;
	volatile uint32_t DMA_S6NDTR;
	volatile uint32_t DMA_S6PAR;
	volatile uint32_t DMA_S6M0AR;
	volatile uint32_t DMA_S6M1AR;
	volatile uint32_t DMA_S6FCR;

	volatile uint32_t DMA_S7CR;
	volatile uint32_t DMA_S7NDTR;
	volatile uint32_t DMA_S7PAR;
	volatile uint32_t DMA_S7M0AR;
	volatile uint32_t DMA_S7M1AR;
	volatile uint32_t DMA_S7FCR;
}dmaRegOffset_t;

typedef struct{
	volatile uint32_t FLASH_ACR;
	volatile uint32_t FLASH_KEYR;
	volatile uint32_t FLASH_OPTKEYR;
	volatile uint32_t FLASH_SR;
	volatile uint32_t FLASH_CR;
	volatile uint32_t FLASH_OPTCR;
}flashRegOffset_t;

typedef struct{
	volatile uint32_t IMR; 		//0x00 (Interrupt Mask Reg)
	volatile uint32_t EMR; 		//0x04 (Event Mask Reg)
	volatile uint32_t RTSR;		//0x08 (Rising Trigger Selection Reg)
	volatile uint32_t FTSR;		//0x0C (Falling Trigger Selection Reg)
	volatile uint32_t SWIER; 	//0x10 (Software Interrupt Event Reg)
	volatile uint32_t PR;		//0x14 (Pending Reg)
}extiRegOffset_t;

typedef struct{
	volatile uint32_t _ISER[8];		//0xE000E100 (Interrupt Set Enable Reg)
	uint32_t RESERVED0[24]; 		//Reserved gap (0xE000E120 to 0xE000E17F)
	volatile uint32_t _ICER[8]; 	//0xE000E180 (Interrupt Clear-Enable Reg)
	uint32_t RESERVED1[24];
	volatile uint32_t _ISPR[8]; 	//0xE000E200 (Interrupt Set Pending Reg)
	uint32_t RESERVED2[24];
	volatile uint32_t _ICPR[8]; 	//0xE000E280 (Interrupt Clear-Pending Reg)
	uint32_t RESERVED3[24];
	volatile uint32_t _IABR[8]; 	//0xE000E300 (Interrupt Active Bit Reg)
	uint32_t RESERVED4[56];
	volatile uint8_t _IPR[240]; 	//0xE000E400 (Interrupt Priority Reg 1 byte each)
}NVIC_t;

/*
 * ----------------------------------------------------
 * Peripheral Register Address Offsets
 * ----------------------------------------------------
 */
#define GPIOA_REG ((volatile gpioRegOffset_t*)GPIOA_BASE_ADDR)
#define GPIOB_REG ((volatile gpioRegOffset_t*)GPIOB_BASE_ADDR)
#define GPIOC_REG ((volatile gpioRegOffset_t*)GPIOC_BASE_ADDR)
#define GPIOD_REG ((volatile gpioRegOffset_t*)GPIOD_BASE_ADDR)
#define GPIOE_REG ((volatile gpioRegOffset_t*)GPIOE_BASE_ADDR)
#define GPIOH_REG ((volatile gpioRegOffset_t*)GPIOH_BASE_ADDR)

#define UART1_REG ((volatile uartRegOffset_t*)UART1_BASE_ADDR)
#define UART2_REG ((volatile uartRegOffset_t*)UART2_BASE_ADDR)
#define UART6_REG ((volatile uartRegOffset_t*)UART6_BASE_ADDR)

#define TIM1_REG 	((volatile timerRegOffset_t*)TIM1_BASE_ADDR)
#define TIM2_REG 	((volatile timerRegOffset_t*)TIM2_BASE_ADDR)
#define TIM3_REG 	((volatile timerRegOffset_t*)TIM3_BASE_ADDR)
#define TIM4_REG 	((volatile timerRegOffset_t*)TIM4_BASE_ADDR)
#define TIM5_REG 	((volatile timerRegOffset_t*)TIM5_BASE_ADDR)
#define TIM9_REG 	((volatile timerRegOffset_t*)TIM9_BASE_ADDR)
#define TIM10_REG 	((volatile timerRegOffset_t*)TIM10_BASE_ADDR)
#define TIM11_REG 	((volatile timerRegOffset_t*)TIM11_BASE_ADDR)

#define DMA2_REG	((volatile dmaRegOffset_t*)DMA2_BASE_ADDR)
#define DMA1_REG	((volatile dmaRegOffset_t*)DMA1_BASE_ADDR)

#define FLASH_REG		((volatile flashRegOffset_t*)FLASH_BASE_ADDR)
#define RCC_REG 		((volatile rccRegOffset_t*)RCC_BASE_ADDR)
#define ADC1_REG		((volatile adcRegOffset_t*)ADC1_BASE_ADDR)
#define ADC1_COMMON_REG	((volatile adcCommonRegOffset_t*)ADC1_COMMON_BASE_ADDR)
#define	EXTI_REG		((volatile extiRegOffset_t*)EXTI_BASE_ADDR)
#define NVIC_REG		((volatile NVIC_t*)NVIC_BASE_ADDR)

/*
 * ----------------------------------------------------
 *
 * ----------------------------------------------------
 */
#define GPIOA_GET_REG(regOffset) (&(GPIOA_REG -> regOffset))
#define GPIOB_GET_REG(regOffset) (&(GPIOB_REG -> regOffset))
#define GPIOC_GET_REG(regOffset) (&(GPIOC_REG -> regOffset))
#define GPIOD_GET_REG(regOffset) (&(GPIOD_REG -> regOffset))
#define GPIOE_GET_REG(regOffset) (&(GPIOE_REG -> regOffset))
#define GPIOH_GET_REG(regOffset) (&(GPIOH_REG -> regOffset))

#define UART1_GET_REG(regOffset) (&(UART1_REG -> regOffset))
#define UART2_GET_REG(regOffset) (&(UART2_REG -> regOffset))
#define UART6_GET_REG(regOffset) (&(UART6_REG -> regOffset))

#define TIM1_GET_REG(regOffset)  (&(TIM1_REG -> regOffset))
#define TIM2_GET_REG(regOffset)  (&(TIM2_REG -> regOffset))
#define TIM3_GET_REG(regOffset)  (&(TIM3_REG -> regOffset))
#define TIM4_GET_REG(regOffset)  (&(TIM4_REG -> regOffset))
#define TIM5_GET_REG(regOffset)  (&(TIM5_REG -> regOffset))
#define TIM9_GET_REG(regOffset)  (&(TIM9_REG -> regOffset))
#define TIM10_GET_REG(regOffset) (&(TIM10_REG -> regOffset))
#define TIM11_GET_REG(regOffset) (&(TIM11_REG -> regOffset))

#define DMA2_GET_REG(regOffset) (&(DMA2_REG -> regOffset))
#define DMA1_GET_REG(regOffset) (&(DMA1_REG -> regOffset))

#define FLASH_GET_REG(regOffset)		(&(FLASH_REG -> regOffset))
#define RCC_GET_REG(regOffset)			(&(RCC_REG -> regOffset))
#define ADC1_GET_REG(regOffset) 		(&(ADC1_REG -> regOffset))
#define ADC1_COMMON_GET_REG(regOffset) 	(&(ADC1_COMMON_REG -> regOffset))

#endif /* INC_STM32PERIPHERALADDR_H_ */
