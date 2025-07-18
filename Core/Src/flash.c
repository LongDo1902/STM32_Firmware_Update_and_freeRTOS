/*
 * flash.c
 *
 *  Created on: July 18, 2025
 *      Author: dobao
 */


#include "flash.h"

/*
 * @brief	Initialize a lookup table for readFlash() and writeFlash() to access any Flash register generically via an enum index
 * 			instead osf hard-coding addresses each time
 *
 * @note	'const keeps the table in Flash'; registers themselve stay 'volatile' because the hardware can change them anytime
 */
static volatile uint32_t* const flashRegLookupTable[FLASH_REG_COUNT] = {
		[FLASH_ACR] 	= FLASH_GET_REG(FLASH_ACR),
		[FLASH_KEYR] 	= FLASH_GET_REG(FLASH_KEYR),
		[FLASH_OPTKEYR]	= FLASH_GET_REG(FLASH_OPTKEYR),
		[FLASH_SR]		= FLASH_GET_REG(FLASH_SR),
		[FLASH_CR]		= FLASH_GET_REG(FLASH_CR),
		[FLASH_OPTCR]	= FLASH_GET_REG(FLASH_OPTCR)
};



/*
 * @brief	A lookup table of **valid-bit masks** for every FLASH register
 * 			The array is indexed by 'FLASH_REG_COUNT'
 */
static const uint32_t FLASH_VALID_BIT[FLASH_REG_COUNT] = {
		[FLASH_ACR] = ~((0xFu << 4) | 0xFFFFE000u), //These bits are reserved
		[FLASH_KEYR] = 0xFFFFFFFFu,
		[FLASH_OPTKEYR] = 0xFFFFFFFFu,
		[FLASH_SR] = ~((0x3u << 2) | (0x7Fu << 9) | 0x7FFFu << 17),
		[FLASH_CR] = ~((1u << 7) | (0x3Fu << 10) | (0x7Fu << 17) | (0x1Fu << 26)),
		[FLASH_OPTCR] = ~((1u << 4) | (0x7F << 24)),
};



/*
 * @brief	Check if a specific bit position in a Flash reg is valid (not reserved)
 *
 * @param	bitPosition		Bit index (0-31) to check within the given Flash reg
 * @param	mode			Enum value representing flash register being access
 *
 * @retval	true			Bit is valid
 * 			false			Bit is reserved or inputs are out of range
 */
static inline bool isValidFlashBit(uint8_t bitPosition, Flash_RegName_t mode){
	return ((mode < FLASH_REG_COUNT && bitPosition < 32) && (FLASH_VALID_BIT[mode] >> bitPosition) & 0x01);
}



/*
 * @brief	Safely write a value to a bit-field inside one of the Flash reg
 *
 * The helper:
 * 		Rejects invalid bit position / reserved bits
 * 		Calculates how many bits are needed to store @p value
 *
 * @param	bitPosition		The starting bit position (0-31) to write the value
 * @param	mode			Which Flash register to access (see Flash_Name_t)
 * @param	value			New value to write into the field.
 */
void writeFlash(uint8_t bitPosition, Flash_RegName_t mode, uint32_t value){
	/*
	 * Basic checks
	 */
	if(bitPosition > 31) return;
	if(!isValidFlashBit(bitPosition, mode)) return;
	if(flashRegLookupTable[mode] == NULL)  return;

	volatile uint32_t* reg = flashRegLookupTable[mode];

	/*
	 * Automatically determine bitWidth based on value
	 */
	uint8_t bitWidth = 1;
	uint32_t temp = value;

	while(temp > 0){
		temp >>= 1;
		bitWidth++;
	}

	/*
	 * Special case:
	 * 		FLASH_OPTCR powers up with a certain bits already set.
	 * 		Its two unlock-key bytes (bit range 0-7 and 8-15)
	 * 		must be written separate 8-bit chunk; otherwise the preset
	 * 		'1's will be untouched after the write.
	 */
	if(mode == FLASH_OPTCR){
		if(bitPosition == 8 || bitWidth == 16) bitWidth = 8;
	}

	if(value >= (1U << bitWidth)) return;
	if(bitWidth >= 32) return;
	if((bitWidth + bitPosition) > 32) return;

	/*
	 * Build mask, merge new bits and update the register
	 */
	uint32_t mask = ((1U << bitWidth) - 1U) << bitPosition;
	uint32_t shiftedVal = (value << bitPosition) & mask;
	*reg = (*reg & ~mask) | shiftedVal;
}

