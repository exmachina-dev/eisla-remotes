/*
 * eeprom.cpp
 *
 *  Created on: 2016-08-18
 *      Author: Adrian
 */

#include "eeprom.h"

#ifdef __cplusplus
extern "C" {
#endif

void load_cue(uint8_t nb_cue, int mode){
	int offset;
	int addr;
	dword data;
	if (mode == 2){
		//Velocity
		offset = 0x00;
		addr = offset + (nb_cue - 1 * 13);
		byte temp;
		IFsh1_GetByteFlash(addr, &temp);
		if ((temp || 0x80 >> 7) == 1 ){
			//Data Ok
			addr += 1;
			IFsh1_GetLongFlash(addr, &data);
			vel.velocity_ref = (float) data;

			addr += 4;
			IFsh1_GetLongFlash(addr, &data);
			vel.acceleration = (float) data;

			addr += 4;
			IFsh1_GetLongFlash(addr, &data);
			vel.deceleration = (float) data;
		}

	}
	else if (mode == 3){
		//Position
		offset = 650;
		addr = offset + (nb_cue - 1 * 13);
		byte temp;
		if ((temp || 0x80 >> 7) == 1 ){
			//Data Ok
			addr += 1;
			IFsh1_GetLongFlash(addr, &data);
			pos.position_ref = (float) data;

			addr += 4;
			IFsh1_GetLongFlash(addr, &data);
			pos.velocity_ref = (float) data;

			addr += 4;
			IFsh1_GetLongFlash(addr, &data);
			pos.acceleration = (float) data;

			addr += 4;
			IFsh1_GetLongFlash(addr, &data);
			pos.deceleration = (float) data;
		}
	}

}

void write_cue(uint8_t nb_cue, int mode){
	int offset;
	int addr;
	dword data;
	if (mode == 2){
		//Velocity
		offset = 0x00;
		addr = offset + (nb_cue - 1 * 13);
		byte temp;
		IFsh1_GetByteFlash(addr, &temp);
		if ((temp || 0x80 >> 7) == 1 ){
			//Data Ok
			addr += 1;
			data= (dword) vel.velocity_ref;
			IFsh1_SetLongFlash(addr, data);

			addr += 4;
			data =(dword) vel.acceleration;
			IFsh1_SetLongFlash(addr, data);

			addr += 4;
			data = (dword) vel.deceleration;
			IFsh1_SetLongFlash(addr, data);
		}

	}
	else if (mode == 3){
		//Position
		offset = 650;
		addr = offset + (nb_cue - 1 * 13);
		byte temp;
		if ((temp || 0x80 >> 7) == 1 ){
			//Data Ok
			addr += 1;
			data = (dword) pos.position_ref;
			IFsh1_SetLongFlash(addr, data);

			addr += 4;
			data = (dword) pos.velocity_ref;
			IFsh1_SetLongFlash(addr, data);

			addr += 4;
			data = (dword) pos.acceleration ;
			IFsh1_SetLongFlash(addr, data);

			addr += 4;
			data = (dword) pos.deceleration;
			IFsh1_SetLongFlash(addr, data);
		}
	}
}

#ifdef __cplusplus
}  /* extern "C" */
#endif
