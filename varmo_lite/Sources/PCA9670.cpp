#include "I2C0.h"
#include "LED_STATUS_3.h"
#include "WAIT1.h"

#define PCA9670_ADDR 0x40

#ifdef __cplusplus
extern "C" {
#endif

void PCA9670_Init() {
	#ifdef I2C0_SetMode
	if(!I2C0_GetMode()) {
		I2C0_SetMode(True);
	}
	#endif

	// Software reset
	I2C0_SelectSlave(0x0);
	I2C0_SendChar(0x06);
	I2C0_SendStop();

	I2C0_SelectSlave(PCA9670_ADDR);
	I2C0_SendChar(0x00);
}

#ifdef __cplusplus
}  /* extern "C" */
#endif
