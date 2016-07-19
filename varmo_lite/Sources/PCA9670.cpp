#include "I2C0.h"
#include "LED_STATUS_1.h"
#include "WAIT1.h"

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

	I2C0_SelectSlave(PCA9670_ADDR);
	I2C0_SendChar(0x00); //Put on IO to low voltage

	//LED_STATUS_1_SetVal();
/*	byte ret;
	ret = I2C0_SendChar(0x30);
	WAIT1_Waitms(10);
	ret = I2C0_SendChar(0x30);
	WAIT1_Waitms(20);
	ret = I2C0_SendChar(0x30);
	WAIT1_Waitms(20);
	ret = I2C0_SendChar(0x38);
	WAIT1_Waitms(20);
	ret = I2C0_SendChar(0x04);
	WAIT1_Waitms(20);
	ret = I2C0_SendChar(0x01);
	WAIT1_Waitms(20);
	ret = I2C0_SendChar(0x04);
	WAIT1_Waitms(20);
	ret = I2C0_SendChar(0x0F);
*/
	//LED_STATUS_1_SetVal();
}

#ifdef __cplusplus
}  /* extern "C" */
#endif
