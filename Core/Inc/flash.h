/*
 * flash.h
 *
 *  Created on: July 18, 2025
 *      Author: dobao
 */

#ifndef INC_FLASH_H_
#define INC_FLASH_H_

#include <stdio.h>
#include <stdbool.h>

#include "stm32PeripheralAddr.h"


typedef enum{
	FLASH_ACR,
	FLASH_KEYR,
	FLASH_OPTKEYR,
	FLASH_SR,
	FLASH_CR,
	FLASH_OPTCR,

	FLASH_REG_COUNT // == 6
}Flash_RegName_t;

/*
 * List of function declarations
 */
void writeFlash(uint8_t bitPosition, Flash_RegName_t mode, uint32_t value);


#endif /* INC_FLASH_H_ */
