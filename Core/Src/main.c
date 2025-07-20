/*
 * main.c
 *
 *  Created on: Jul 16, 2025
 *      Author: dobao
 */
#include <string.h>

#include "stm32PeripheralAddr.h"
#include "rcc.h"
#include "timer.h"
#include "exti.h"
#include "led.h"
#include "uart.h"
#include "dma.h"

//char message [60];
//uint8_t idx = 0;
//
//void USART1_IRQHandler(void){
//	message[idx++] = my_UART_Receive(my_UART1);
//
//	if(strstr(message, "\n")){
//		if(strstr(message, "red led on")){
//			ledControl(LED_RED, ON);
//			uartPrintLog(my_UART1, "RED LED IS ON\n");
//		}
//		else if(strstr(message, "red led off")){
//			ledControl(LED_RED, OFF);
//			uartPrintLog(my_UART1, "RED LED IS OFF\n");
//		}
//		else{
//			uartPrintLog(my_UART1, "COMMAND NOT FOUND!\n");
//		}
//		memset(message, 0, sizeof(message));
//		idx = 0;
//	}
//}


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
			  _9B_WORDLENGTH,
			  ENABLE_DMA);

	while(1){
		ledControl(LED_BLUE, ON);
		delay(100);
		ledControl(LED_BLUE, OFF);
		delay(100);
	}
}

