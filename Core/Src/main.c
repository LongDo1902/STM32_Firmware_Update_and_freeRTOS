/*
 * main.c
 *
 *  Created on: Jul 16, 2025
 *      Author: dobao
 */

#include "stm32PeripheralAddr.h"
#include "rcc.h"
#include "timer.h"
#include "exti.h"
#include "led.h"

int main(void){
	RCC_init();
	initTimer(my_TIM1); //100MHz, 1 tick per 0.001s
	ledBlueInit();

	while(1){
		ledControl(LED_BLUE, ON);
		delay(1000);
		ledControl(LED_BLUE, OFF);
		delay(1000);
	}
}
