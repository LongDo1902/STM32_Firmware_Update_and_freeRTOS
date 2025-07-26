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
#include "adc.h"
//#include "flash.h"


float temperatureVal = 0;

char rxBuf[22032];
bool updateFirmware = false;
void DMA2_Stream2_IRQHandler(void){
	/* Clear all the flags */
	writeDMA2(21, DMA_LIFCR, SET); //Clear transfer completed interrupt flag of stream 2
	updateFirmware = true;
}

//static volatile bool rxIndicator = false;
//
//char rxMessage[25];
//int idx = 0;
//void USART1_IRQHandler(void){
//	if((readUART(5, my_UART1, UART_SR) & 1) == 1){
//		rxIndicator = true;
//	}
//
//	/*
//	 * @note	my_UART_Receive clears interrupt itself because:
//	 * 				In this function, it reads SR then DR
//	 */
//	rxMessage[idx++] = my_UART_Receive(my_UART1);
//
//	if(strstr(rxMessage, "\n")){
//		if(strstr(rxMessage, "orange led on")){
//			ledControl(LED_ORANGE, ON);
//			uartPrintLog(my_UART1, "--> ORANGE LED ON\n");
//		}
//		else if(strstr(rxMessage, "orange led off")){
//			ledControl(LED_ORANGE, OFF);
//			uartPrintLog(my_UART1, "--> ORANGE LED OFF\n");
//		}
//		else{
//			uartPrintLog(my_UART1, "--> COMMAND NOT FOUND\n");
//		}
//		memset(rxMessage, 0, sizeof rxMessage);
//		idx = 0;
//	}
//}


//static void uartPrintTemperature(UART_Name_t uartName, float temperatureVal, uint8_t decimals){
//	ledControl(LED_GREEN, ON);
//
//	uartPrintLog(uartName, "\n");
//	uartPrintLog(uartName, "STM32's Temperature: ");
//	uartPrintFloat(uartName, temperatureVal, decimals);
//	uartPrintLog(uartName, "*C");
//
//	ledControl(LED_GREEN, OFF);
//}


int main(void){
	RCC_init();
	initTimer(my_TIM1); //100MHz, 1 tick per 0.001s

	ledBlueInit();
	ledOrangeInit();
	ledRedInit();
	ledGreenInit();

	UART_Init(my_GPIO_PIN_6,
			  my_GPIO_PIN_7,
			  my_GPIOB,
			  my_UART1,
			  9600,
			  PARITY_ODD,
			  _9B_WORDLENGTH);

//	ADC_temperatureSensorInit();
	UART1_DMA_Receiver_Init(rxBuf, sizeof rxBuf);

	while(1){
		ledControl(LED_BLUE, ON);
		delay(100);
		ledControl(LED_BLUE, OFF);
		delay(100);

//		if(rxIndicator == true){
//			rxIndicator = false;
//			ledControl(LED_RED, ON);
//			delay(30);
//			ledControl(LED_RED, OFF);
//		}
//
		if(updateFirmware == true){
			__asm("cpsid i");
			firmwareUpdate(rxBuf, sizeof rxBuf);
		}
//
//		temperatureVal = temperatureSensorRead();
//		uartPrintTemperature(my_UART1, temperatureVal, 2);
	}
}



///*
// * @brief
// *
// * @retval	Number of characters were written into buf, plus the automatic \0. No truncation happened
// */
//static int convertFloatToString(char *destinationArray, uint8_t length, float val, uint8_t decimals){
//	if(decimals > 9) decimals = 9;
//	char fmt[] = "%.1f";
//	fmt[2] = '0' + decimals;
//	return snprintf(destinationArray, length, fmt, val);
//}
