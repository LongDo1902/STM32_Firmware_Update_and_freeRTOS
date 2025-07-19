/*
 * UART.h
 *
 *  Created on: July 18, 2025
 *      Author: dobao
 */

#ifndef INC_UART_H_
#define INC_UART_H_
#include <stdio.h>
#include <math.h>

#include "stm32PeripheralAddr.h"
#include "timer.h"
#include "rcc.h"
#include "gpioWriteRead.h"
#include "dma.h"

typedef enum{
	UART_SR,
	UART_DR,
	UART_BRR,
	UART_CR1,
	UART_CR2,
	UART_CR3,
	UART_GTPR
}UART_RegName_t;

typedef enum{
	my_UART1,
	my_UART2,
	my_UART6
}UART_Name_t;

typedef enum{
	PARITY_NONE,
	PARITY_EVEN,
	PARITY_ODD
}UART_Parity_t;

typedef enum{
	_8B_WORDLENGTH,
	_9B_WORDLENGTH
}UART_WordLength_t;

typedef enum{
	UART_OK,
	UART_NOT_OK,
	INVALID_UART,
	INVALID_REG
}UART_Status_t;

typedef enum{
	INVALID_PORT
}General_Status_t;

typedef enum{
	DISABLE_DMA,
	ENABLE_DMA
}Enable_DMA_t;

/*
 * Function Declaration
 */
void UART_Init(GPIO_Pin_t TXPin,
			   GPIO_Pin_t RXPin,
			   GPIO_PortName_t portName,
			   UART_Name_t uartName,
			   uint32_t baudRate,
			   UART_Parity_t parity,
			   UART_WordLength_t wordLength,
			   Enable_DMA_t enableDMA);

void my_UART_Transmit(UART_Name_t UARTx, uint8_t inputData);

int16_t my_UART_Receive(UART_Name_t uartName);

void UART1_DMA_Init(uint16_t bufferSize);

#endif /* INC_UART_H_ */
