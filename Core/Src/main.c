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

int main(void){
	RCC_init();
	initTimer(my_TIM1); //100MHz, 1 tick per 0.001s
	ledBlueInit();
	ledRedInit();
	UART_Init(my_GPIO_PIN_6, my_GPIO_PIN_7, my_GPIOB, my_UART1, 9600, PARITY_ODD, _9B_WORDLENGTH);

	while(1){
//		my_UART_Transmit(my_UART1, 'a');
//		delay(200);

//		ledControl(LED_BLUE, ON);
//		delay(200);
//		ledControl(LED_BLUE, OFF);z
//		delay(200);

		if(my_UART_Receive(my_UART1) == 'b'){
			ledControl(LED_RED, ON);
			delay(100);
			ledControl(LED_RED, OFF);
		}
	}
}

