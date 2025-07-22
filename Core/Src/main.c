/*
 * main.c
 *
 *  Created on: Jul 16, 2025
 *      Author: dobao
 */
#include <string.h>
#include <stdbool.h>

#include "stm32PeripheralAddr.h"
#include "rcc.h"
#include "timer.h"
#include "exti.h"
#include "led.h"
#include "uart.h"
#include "dma.h"

char fifoBuf[14]; //Change this to fit your initial message length

void DMA2_Stream2_IRQHandler(void){
	if(readDMA2(21, DMA_LISR) == 1){ //Check if transfer is completed
		writeDMA2(21, DMA_LIFCR, SET); //Clear transfer completed interrupt flag of stream 2
		writeDMA2(20, DMA_LIFCR, SET); //Clear half transfer interrupt flag
		writeDMA2(19, DMA_LIFCR, SET); //Clear transfer error interrupt flag
		writeDMA2(18, DMA_LIFCR, SET); //Clear direct mode error interrupt flag
		writeDMA2(16, DMA_LIFCR, SET); //Clear FIFO error interrupt flag
	}

	if(strstr(fifoBuf, "\n")){
		/* Reset DMA to store a new buffer size */
		if(strstr(fifoBuf, "ORANGE LED ON")){
			ledControl(LED_ORANGE, ON);
		} else{
			ledControl(LED_ORANGE, OFF);
		}
		memset(fifoBuf, 0, sizeof(fifoBuf)); //Reset all elements in the buffer
	}
}

static volatile uint8_t uartIdleIndicator = 0;

void USART1_IRQHandler(void){
	if((readUART(4, my_UART1, UART_SR) & 1) == 1){
		/* Clear the interrupt flag by reading SR and then DR */
		readUART(0, my_UART1, UART_SR);
		readUART(0, my_UART1, UART_DR);

		uartIdleIndicator = 1;
	}
}


/*
 * This DMA is for sending temperature value to terminal
 */
void DMA2_Stream7_IRQHandler(void){

}


int main(void){
	HAL_Init();
	RCC_init();
	initTimer(my_TIM1); //100MHz, 1 tick per 0.001s

	ledBlueInit();
	ledOrangeInit();
	ledRedInit();

	UART_Init(my_GPIO_PIN_6,
			  my_GPIO_PIN_7,
			  my_GPIOB,
			  my_UART1,
			  9600,
			  PARITY_ODD,
			  _9B_WORDLENGTH);

	UART1_DMA_Receiver_Init(fifoBuf, 14);

	while(1){
		ledControl(LED_BLUE, ON);
		delay(100);
		ledControl(LED_BLUE, OFF);
		delay(100);

		if(uartIdleIndicator){
			uartIdleIndicator = 0;
			ledControl(LED_RED, ON);
			delay(30);
			ledControl(LED_RED, OFF);
		}
	}
}
