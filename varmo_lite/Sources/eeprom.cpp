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
		addr = offset + (nb_cue * 13);
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
		addr = offset + (nb_cue * 13);
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
		addr = offset + nb_cue  * 13;
		byte temp;
		IFsh1_GetByteFlash(addr, &temp);
		if ((temp || 0x80 >> 7) == 0 ){
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
		addr = offset + (nb_cue  * 13);
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

void erase_cue(uint8_t nb_cue, int mode){
	int offset;
	int addr;
	if (mode == 2){
		offset= 0x00;
		addr = offset + nb_cue * 13;
		IFsh1_SetByteFlash(addr, 0x80);
	}
	else if (mode == 3){
		offset= 650;
		addr = offset + nb_cue * 17;
		IFsh1_SetByteFlash(addr, 0x80);
	}
}

uint8_t get_next_slot_free(int mode){
	int offset;
	int addr;
	uint8_t cue = 0;
	if (mode == 2){
		//Velocity
		bool slot_free;

		byte temp;
		offset = 0x00;
		addr = offset + cue * 13;
		while (slot_free == 0 || cue != 50){
			IFsh1_GetByteFlash(addr, &temp);
			if (temp == 0){
				slot_free = 1;
			}
			cue ++;
		}
	}
	else if (mode == 3){
		//Position
		bool slot_free;

		byte temp;
		offset = 650;
		addr = offset + cue * 17;
		while (slot_free == 0 || cue != 50){
			IFsh1_GetByteFlash(addr, &temp);
			if (temp == 0){
				slot_free = 1;
			}
			cue ++;
		}
	}
	return cue;
}

void get_slot_saved(int mode, uint8_t *slot_saved){
	int offset;
	int addr;
	uint8_t cue = 0;
	if (mode == 2){
		offset = 0x00;
		addr = offset;
		for (uint8_t i = 0; i<50; i++){
			byte temp;
			addr = offset +  i * 13;
			IFsh1_GetByteFlash(addr, &temp);
			if ((temp || 0x80 >> 7) == 1 ){
				slot_saved[cue] = i;
				cue ++;
			}
		}
		for (uint8_t i = cue; i < 50; i++){
			slot_saved[i] = 0;
		}
	}
	else if(mode == 3){
		offset = 650;
		addr = offset;
		for (uint8_t i = 0; i<50; i++){
			byte temp;
			addr = offset +  i * 17;
			IFsh1_GetByteFlash(addr, &temp);
			if ((temp || 0x80 >> 7) == 1 ){
				slot_saved[cue] = i;
				cue ++;
			}
		}
		for (uint8_t i = cue; i < 50; i++){
			slot_saved[i] = 0;
		}
	}
}

#ifdef __cplusplus
}  /* extern "C" */
#endif
