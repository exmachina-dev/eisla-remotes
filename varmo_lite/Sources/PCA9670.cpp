#include "I2C0.h"
#include "LED_STATUS_1.h"
#include "WAIT1.h"
#include "LED_STATUS_1.h"
#include "BitIoLdd2.h"
#include "LCD_CTR.h"
#include "BitIoLdd6.h"
#include "LCD_EN.h"
#include "BitIoLdd7.h"

#define PCA9670_ADDR 0x20

#ifdef __cplusplus
extern "C" {
#endif

void PCA9670_Init() {
	#ifdef I2C0_SetMode
	if(!I2C0_GetMode()) {
		I2C0_SetMode(True);
	}
	#endif
	LCD_EN_SetVal();
	I2C0_SelectSlave(PCA9670_ADDR);
	I2C0_SendChar(0x00); //Put on IO to low voltage
	LCD_EN_ClrVal();
	LCD_EN_SetVal();
}

void PCA9670_SendByte(byte data, uint16_t delay_ms){
	I2C0_SendChar(data);
	WAIT1_Waitms(delay_ms);
	LCD_EN_ClrVal();
	LCD_EN_SetVal();
}

#ifdef __cplusplus
}  /* extern "C" */
#endif
