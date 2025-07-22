/*
 * @brief	uart.c
 *
 * 	Created on: Apr 23, 2025
 * 	Updated on: Jul 18, 2025
 * 		Improved program flow
 * 		Improved logical flow
 * 		Fixed bug
 * 		Adding DMA feature
 *
 * 		Author: dobao
 */

#include "uart.h"

/*
 * -----------------------------------------------------------
 * Private Helpers
 * -----------------------------------------------------------
 */
/* Base-Address Lookup */
static inline volatile uartRegOffset_t* uartBase(UART_Name_t uartName){
	switch(uartName){
		case my_UART1: return UART1_REG;
		case my_UART2: return UART2_REG;
		case my_UART6: return UART6_REG;
		default: return NULL;
	}
}



/* Enable GPIOs' Clock */
static inline General_Status_t enableGpioClock(GPIO_PortName_t port){
	switch(port){
		case my_GPIOA: my_RCC_GPIOA_CLK_ENABLE(); return OK;
		case my_GPIOB: my_RCC_GPIOB_CLK_ENABLE(); return OK;
		case my_GPIOC: my_RCC_GPIOC_CLK_ENABLE(); return OK;
		case my_GPIOD: my_RCC_GPIOD_CLK_ENABLE(); return OK;
		case my_GPIOE: my_RCC_GPIOE_CLK_ENABLE(); return OK;
		case my_GPIOH: my_RCC_GPIOH_CLK_ENABLE(); return OK;
		default: return INVALID_PORT;
	}
}

/* Enable UARTs' Clock */
static inline UART_Status_t enableUartClock(UART_Name_t uartName){
	switch(uartName){
		case my_UART1: my_RCC_USART1_CLK_ENABLE(); return UART_OK;
		case my_UART2: my_RCC_USART2_CLK_ENABLE(); return UART_OK;
		case my_UART6: my_RCC_USART6_CLK_ENABLE(); return UART_OK;
		default: return UART_NOT_OK;
	}
}



/*
 * @brief	Helper function to write bit to a specific uart's register
 *
 * @param	bitPosition
 * @param	uartName
 * @param	regName
 * @param	value
 */
UART_Status_t writeUART(uint8_t bitPosition, UART_Name_t uartName, UART_RegName_t regName, uint32_t value){
	volatile uartRegOffset_t* UARTx = uartBase(uartName);
	if(UARTx == NULL) {return INVALID_UART; }

	volatile uint32_t* reg = NULL;
	switch(regName){
		case UART_SR: reg = &UARTx -> UART_SR; break;
		case UART_DR: reg = &UARTx -> UART_DR; break;
		case UART_BRR: reg = &UARTx -> UART_BRR; break;
		case UART_CR1: reg = &UARTx -> UART_CR1; break;
		case UART_CR2: reg = &UARTx -> UART_CR2; break;
		case UART_CR3: reg = &UARTx -> UART_CR3; break;
		case UART_GTPR: reg = &UARTx -> UART_GTPR; break;
		default: return INVALID_REG;
	}

	/*
	 * Auto detect bitWidth based on the "value" length
	 * This method is only applicable for those registers that has reset value = 0x00
	 */
	uint8_t bitWidth = 1;
	uint32_t temp = value;
	while(temp > 0){
		temp >>= 1;
		bitWidth++;
	}

	//Prevent overflow
	if(bitPosition + bitWidth > 32) return UART_NOT_OK;

	//Mask off the old bit and OR with new value
	uint32_t mask = ((1U << bitWidth) - 1U) << bitPosition;
	uint32_t shiftedValue = (value << bitPosition) & mask;
	*reg = (*reg & ~mask) | shiftedValue;

	return UART_OK;
}



/*
 * @brief
 *
 * @param
 * @param
 * @param
 */
int16_t readUART(uint8_t bitPosition, UART_Name_t uartName, UART_RegName_t regName){
	volatile uartRegOffset_t* UARTx = uartBase(uartName);
	if(UARTx == NULL) return -1;

	volatile uint32_t* reg = NULL;
	switch(regName){
		case UART_SR: reg = &UARTx -> UART_SR; break;
		case UART_DR: reg = &UARTx -> UART_DR; break;
		case UART_BRR: reg = &UARTx -> UART_BRR; break;
		case UART_CR1: reg = &UARTx -> UART_CR1; break;
		case UART_CR2: reg = &UARTx -> UART_CR2; break;
		case UART_CR3: reg = &UARTx -> UART_CR3; break;
		case UART_GTPR: reg = &UARTx -> UART_GTPR; break;
		default: return -1;
	}

	if(regName == UART_DR){
		return (int16_t)(*reg & 0x1FF); //Return full 9 bits
	}

	else {
		if((*reg >> bitPosition) & 0x1){
			return 1;
		} else{
			return 0;
		}
	}
}

/*
 * ------------------------------------------------------------
 * Public API
 * ------------------------------------------------------------
 */

/*
 * @brief	Set up DMA2-Stream2-Channel4 to move incoming UART1 RX bytes into a user-supplier buffer
 *
 * @param	rxBuffer	Pointer to the receive buffer (must be word-aligned if required by ur DMA)
 * 						Its size must be programmed into NDTR before each reception.
 *
 * @routine:
 * 		1. Enable DMA mode for reception in UART1 (UART_CR3)
 * 		2. Enable DMA2 peripheral clock
 * 		3. Programs DMA2 Stream 2 registers:
 * 			PAR 	<- &UART1.DR (feed DR address)
 * 			M0AR	<- rxBuffer	 (destination in RAM)
 * 			NDTR	<- sizeof(buffer)	(number of bytes to receive)
 * 			CR		<- channel 4 | 8bit | MINC | CIRC | TCIE | EN
 * 		4. Enable the NVIC interrupt for DMA2_Stream2
 */
void UART1_DMA_Receiver_Init(char *rxBuffer, uint32_t bufferSize){
	writeUART(6, my_UART1, UART_CR3, SET); //Enable DMA for reception
	/*
	 * According to DMA2 request mapping
	 * 		Choose Stream 2, channel 4 for UART1_RX
	 */
	my_RCC_DMA2_CLK_ENABLE(); //Enabling clock for DMA2

	/* Assign the address of sender which is UART_DR*/
	writeDMA2(0, DMA_S2CR, RESET); //Disable stream before configuring

	writeDMA2(0, DMA_S2PAR, (uint32_t)UART1_GET_REG(UART_DR)); //Write sender address to DMA_S2PAR
	writeDMA2(0, DMA_S2M0AR, (uint32_t)rxBuffer); //Write receiver address to DMA_S2M0AR
	writeDMA2(0, DMA_S2NDTR, bufferSize); //Let DMA knows the size of the transfered package

	writeDMA2(25, DMA_S2CR, 0b100); //Select channel 4
	writeDMA2(11, DMA_S2CR, 0b00); //Set data size is 8-bit
	writeDMA2(8, DMA_S2CR, SET); //Enable circular mode

	if(bufferSize > 1){
		writeDMA2(10, DMA_S2CR, SET); //Set memory increment mode
	} else writeDMA2(10, DMA_S2CR, RESET); //No memory increment mode

	writeDMA2(4, DMA_S2CR, SET); //Enable transfer complete interrupt
	writeDMA2(0, DMA_S2CR, SET); //Enable Stream 2

	NVIC_enableIRQ(DMA2_S2);
}


void UART1_DMA_Transmitter_Init(char* txBuffer){
	writeUART(7, my_UART1, UART_CR3, SET); //Enable DMA for transmission
	/*
	 * According to DMA2 request mapping
	 * 		Choose Stream 7, channel 4 for UART1_TX
	 */
	my_RCC_DMA2_CLK_ENABLE(); //Enabling clock for DMA2

	writeDMA2(0, DMA_S7CR, RESET); //Disable stream before configuring

	/* Assign the address of sender which is UART_DR*/
	writeDMA2(0, DMA_S7PAR, (uint32_t)UART1_GET_REG(UART_DR)); //Write sender address to DMA_S7PAR
	writeDMA2(0, DMA_S7M0AR, (uint32_t)txBuffer); //Write receiver address to DMA_S7M0AR
	writeDMA2(0, DMA_S7NDTR, sizeof(txBuffer)); //Let DMA knows the size of the transfered package

	writeDMA2(25, DMA_S7CR, 0b100); //Select channel 4
	writeDMA2(7, DMA_S7CR, 0b01); //Data transfer direction: memory to peripheral
	writeDMA2(11, DMA_S7CR, 0b00); //Set data size is 8-bit
	writeDMA2(10, DMA_S7CR, SET); //Set memory increment mode
	writeDMA2(8, DMA_S7CR, SET); //Enable circular mode
	writeDMA2(4, DMA_S7CR, SET); //Enable transfer complete interrupt
	writeDMA2(0, DMA_S7CR, SET); //Enable Stream 7

	NVIC_enableIRQ(DMA2_S7);
}


/*
 * @brief	 High-level helper to configure UART peripheral and its GPIO pins.
 *
 * @param	TXPin		Logical GPIO pin used as UARTx_TX
 * @param	RXPin		Logical GPIO pin used as UARTx_RX
 * @param	portName	GPIO port hosting the pins (my_GPIOA)
 * @param	uartName	Target UART peripheral (my_UART1)
 * @param	baudRate	Desired baud rate in bit/s (e.g. 115200)
 * @param	parity		PARITY_NONE, PARITY_EVEN, OR PARITY_ODD
 * @param	wordLength	_8B_WORDLENGTH or _9B_WORDLENGTH
 *
 * @note	The function assumes SYSCLK_FREQ_100M is set to the current peripheral clock speed.
 * 			Update this constant if the clock tree is changed
 */
void UART_Init(GPIO_Pin_t TXPin,
			   GPIO_Pin_t RXPin,
			   GPIO_PortName_t portName,
			   UART_Name_t uartName,
			   uint32_t baudRate,
			   UART_Parity_t parity,
			   UART_WordLength_t wordLength){
	/* Clock */
	enableUartClock(uartName);
	enableGpioClock(portName);

	/*
	 * Set TX/RXpin of a specific port to MODER mode and set its state to 0x02 (Alternate function mode)
	 */
	writePin(TXPin, portName, MODER, AF_MODE);
	writePin(RXPin, portName, MODER, AF_MODE);

	writePin(TXPin, portName, (TXPin <= 7U) ? AFRL : AFRH, AF7);
	writePin(RXPin, portName, (RXPin <= 7U) ? AFRL : AFRH, AF7);

	/*
	 * CONFIG UART
	 *
	 * Config baud rate
	 * baud = fclk / (8*(2-OVER8)*UARTDIV)
	 *
	 * APB2 supports System Clock upto 100MHz
	 */
	volatile uartRegOffset_t* huart = uartBase(uartName);
	if(huart == NULL) {return;}

	long int f_clk = SYSCLK_FREQ_100M; //Note: Remember to change this when you change clock speed in RCC
	char over8 = 0; //16x oversampling
	float uartDiv = (float)f_clk / (8.0f * (2 - over8) * (float)baudRate);

	int divMantissa = (int)uartDiv; //Extract the integer part
	float divFraction = uartDiv - divMantissa; //Extract the fraction part
	int convert_divFraction = (int)(roundf(divFraction * 16.0f)); //scale and store divFraction in 4 bits
	uint16_t fullBRR = (divMantissa << 4) | (convert_divFraction & 0xF);

	/* Write Calculated full values to BRR */
	writeUART(0, uartName, UART_BRR, fullBRR);

	/* Enable Tx and Rx */
	writeUART(2, uartName, UART_CR1, 1); //Receiver is enabled and begins searching for a start bit
	writeUART(3, uartName, UART_CR1, 1); //Transmitter enable

	/* Parity Configuration	 */
	if(parity == PARITY_NONE){
		writeUART(10, uartName, UART_CR1, 0); //PCE = 0
	}else{
		writeUART(10, uartName, UART_CR1, 1); //PCE = 1

		if(parity == PARITY_EVEN){
			writeUART(9, uartName, UART_CR1, 0); //PS = 0 for EVEN
		} else{
			writeUART(9, uartName, UART_CR1, 1); //PS = 1 for ODD
		}
	}

	/* Word Length */
	if (wordLength == _8B_WORDLENGTH){
		writeUART(12, uartName, UART_CR1, 0); //Set data frame size as 8 bits
	}else if (wordLength == _9B_WORDLENGTH) {
		writeUART(12, uartName, UART_CR1, 1); //Set data frame size as 9 bits
	}else{
		return;
	}

	writeUART(4, uartName, UART_CR1, SET); //Enable IDLE interrupt
	writeUART(13, uartName, UART_CR1, 1); //Enable UART
	NVIC_enableIRQ(UART1); //Position 37 in vector table
}



/*
 * 	@brief	Send one byte over a selected UART port
 * 	@param 	Target peripheral: my_UART1, my_UART2, my_UART6.
 * 	@param	inputData: write any value/data to but only <= 1 byte
 *
 * 	Routine:
 * 		1. Waits for TXE = 1 (DR empty)
 * 		2. Writes the inputData to DR register
 * 		3. Wait for TC = 1 to ensure the byte has completely left the shift register.
 */
void my_UART_Transmit(UART_Name_t UARTx, uint8_t inputData){
	while((readUART(7, UARTx, UART_SR) & 1) == 0);
	writeUART(0, UARTx, UART_DR, inputData & 0x1FF);
	while((readUART(6, UARTx, UART_SR) & 1) == 0);
}



/*
 * @brief	Receives a character over the specified UART interface
 *
 * This function waits until data is available in the receive buffer (RXNE == 1)
 * Checks for a parity error (PE == 1), and if there is no error, returns the received byte
 * If a parity error occurs, it discards the corrupted data and return -1.
 */
int16_t my_UART_Receive(UART_Name_t uartName){
	volatile uartRegOffset_t* huart = uartBase(uartName);
	if(huart == NULL){return INVALID_UART;} //Invalid peripheral

	//Wait until the data is ready
	while(readUART(5, uartName, UART_SR) == 0); //Wait for RXNE == 1

	/*
	 * To clear the PE, FE, NE, or ORE flags, the following sequence must be respected:
	 * Read the SR register
	 * Read the DR register
	 *
	 * If skip DR read:
	 * 		The flag won't be cleared
	 * 		You may get stuck in your parity check loop
	 * 		Worst case: DR wont get new data, leading to data loss or lockup
	 */

	//Check parity error (bitPosition = 0)
	if(readUART(0, uartName, UART_SR) == 1){
		(void)readUART(0, uartName, UART_DR); //read and discard error
		return UART_NOT_OK; //There is parity error
	}

	//No error, return valid data
	int16_t data = readUART(0, uartName, UART_DR);
	return data;
}



/*
 * @brief	Send a zero-terminated ASCII string over the selected UART port
 *
 * @param	uartName	UART peripheral (example: my_UART1, my_UART2, and my_UART6)
 * @param	message		Pointer to a C-string that ends with '\0'
 *
 * @note!	The routine is blocking: it waits inside my_UART_Transmit()
 * 			until each byte has physically left the shift register.
 * 			For short status messages that is fine; for large logs consider
 * 			an IRQ or DMA-drivin Tx buffer so the CPU can do other work.
 */
void uartPrintLog(UART_Name_t uartName, char* message){
	int messageLength = strlen(message);
	for(short i = 0; i < messageLength; i++){
		my_UART_Transmit(uartName, message[i]);
	}
}













