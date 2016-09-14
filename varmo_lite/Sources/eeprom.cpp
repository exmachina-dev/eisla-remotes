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
	long unsigned int offset;
	long unsigned int addr;
	data_save data;

	if (mode == 2){
		//Velocity

		addr = velocity_offset + (nb_cue * 13);
		byte temp;
		IFsh1_GetByteFlash(addr, &temp);
		if ((temp || 0x80 >> 7) == 1 ){
			//Data Ok
			addr += 1;
			IFsh1_GetLongFlash(addr, &data.Todword);
			vel.velocity_ref = data.Tofloat;

			addr += 4;
			IFsh1_GetLongFlash(addr, &data.Todword);
			vel.acceleration = data.Tofloat;

			addr += 4;
			IFsh1_GetLongFlash(addr, &data.Todword);
			vel.deceleration = data.Tofloat;
		}

	}
	else if (mode == 3){
		//Position
		addr = position_offset + (nb_cue * 17);
		byte temp;
		IFsh1_GetByteFlash(addr, &temp);
		if ((temp || 0x80 >> 7) == 1 ){
			//Data Ok
			addr += 1;
			IFsh1_GetLongFlash(addr, &data.Todword);
			pos.position_ref = data.Tofloat;

			addr += 4;
			IFsh1_GetLongFlash(addr, &data.Todword);
			pos.velocity_ref = data.Tofloat;

			addr += 4;
			IFsh1_GetLongFlash(addr, &data.Todword);
			pos.acceleration = data.Tofloat;

			addr += 4;
			IFsh1_GetLongFlash(addr, &data.Todword);
			pos.deceleration = data.Tofloat;
		}
	}

}

void write_cue(uint8_t nb_cue, int mode){
	long unsigned int offset;
	long unsigned int addr;
	data_save data;
	if (mode == 2){
		//Velocity
		addr = velocity_offset + nb_cue  * 13;
		byte temp = 0x80;
		byte ERR;
		ERR = IFsh1_SetByteFlash(addr, temp);

		addr += 1;
		if ( FLAG_REC_SHORT_CUT == 1){
			data.Tofloat = old_encoder * resolution;
		}
		else{
			data.Tofloat= vel.velocity_ref;
		}
		ERR = IFsh1_SetLongFlash(addr, data.Todword);

		addr += 4;
		data.Tofloat = vel.acceleration;
		ERR = IFsh1_SetLongFlash(addr, data.Todword);

		addr += 4;
		data.Tofloat = vel.deceleration;
		ERR = IFsh1_SetLongFlash(addr, data.Todword);
		addr += 4;
	}
	else if (mode == 3){
		//Position

		addr = position_offset + nb_cue  * 17;
		byte temp = 0x80;
		byte ERR;
		ERR = IFsh1_SetByteFlash(addr, temp);
		addr += 1;
		if (FLAG_REC_SHORT_CUT == 1){
			data.Tofloat = old_encoder * resolution;
		}
		else{
			data.Tofloat = pos.position_ref;
		}
		IFsh1_SetLongFlash(addr, data.Todword);

		addr += 4;
		data.Tofloat = pos.velocity_ref;
		IFsh1_SetLongFlash(addr, data.Todword);

		addr += 4;
		data.Tofloat = pos.acceleration ;
		IFsh1_SetLongFlash(addr, data.Todword);

		addr += 4;
		data.Tofloat = pos.deceleration;
		IFsh1_SetLongFlash(addr, data.Todword);
	}
}

void erase_cue(uint8_t nb_cue, int mode){
	int offset;
	int addr;
	if (mode == 2){
		//nb_cue = cue_saved[cue] - 1;
		addr = velocity_offset + nb_cue * 13;
		IFsh1_SetByteFlash(addr, 0x00);
	}
	else if (mode == 3){
		addr = position_offset + nb_cue * 17;
		IFsh1_SetByteFlash(addr, 0x00);
	}
}

uint8_t get_next_slot_free(int mode){
	long unsigned int offset;
	long unsigned int addr;

	uint8_t cue = 0;
	if (mode == 2){
		//Velocity
		bool slot_free;
		byte temp;
		addr = velocity_offset + cue * 13;
		while (slot_free == 0 && cue < 50){
			IFsh1_GetByteFlash(addr, &temp);
			if (temp != 0x80){
				slot_free = 1;
			}
			else{
				cue ++;
				addr = velocity_offset + cue * 13;
			}
		}
	}
	else if (mode == 3){
		//Position
		bool slot_free;
		byte temp;
		addr = position_offset + cue * 17;
		while (slot_free == 0 && cue < 50){
			IFsh1_GetByteFlash(addr, &temp);
			if (temp != 0x80){
				slot_free = 1;
			}
			else{
				cue ++;
				addr = position_offset + cue * 17;
			}
		}
	}
	return cue;
}

uint8_t get_slot_saved(int mode, uint8_t *slot_saved){
	long unsigned int offset;
	long unsigned int addr;

	uint8_t cue = 0;
	uint8_t nb_cue = 0;
	if (mode == 2){
		addr = velocity_offset;
		for (uint8_t i = 0; i<50; i++){
			byte temp;
			addr = velocity_offset +  i * 13;
			IFsh1_GetByteFlash(addr, &temp);
			if (temp  == 0X80 ){
				slot_saved[cue] = i+1;
				nb_cue ++;
				cue ++;
			}
		}
		for (uint8_t i = cue; i < 50; i++){
			slot_saved[i] = 0;
		}
	}
	else if(mode == 3){
		addr = position_offset;
		for (uint8_t i = 0; i<50; i++){
			byte temp;
			addr = position_offset +  i * 17;
			IFsh1_GetByteFlash(addr, &temp);
			if (temp  == 0X80 ){
				slot_saved[cue] = i+1;
				nb_cue ++;
				cue ++;
			}
		}
		for (uint8_t i = cue; i < 50; i++){
			slot_saved[i] = 0;
		}
	}
	return nb_cue;
}

void get_cues_saved_values(int mode, cue_parameter* value_array,uint8_t *cue_saved, uint8_t size){
	for (uint8_t i = 0; i<size; i++){
		value_array[i] = get_cue_values(mode, cue_saved[i]-1);
	}
}

cue_parameter get_cue_values(int mode, uint8_t nb_cue){
	long unsigned int offset;
	long unsigned int addr;
	cue_parameter cue;
	data_save data;
	if (mode == 2){
		byte temp;
		addr = velocity_offset +  nb_cue * 13;
		IFsh1_GetByteFlash(addr, &temp);
		if (temp  == 0X80 ){
			cue.data = 1;
			addr += 1;
			IFsh1_GetLongFlash(addr, &data.Todword);
			cue.velocity = data.Tofloat;
		}
		else{
			cue.data = 0;
		}
	}
	else if(mode == 3){
		byte temp;
		addr = position_offset +  nb_cue * 17;
		IFsh1_GetByteFlash(addr, &temp);
		if (temp  == 0X80 ){
			cue.data = 1;
			addr += 1;
			IFsh1_GetLongFlash(addr, &data.Todword);
			cue.position = data.Tofloat;
			addr += 4;
			IFsh1_GetLongFlash(addr, &data.Todword);
			cue.velocity = data.Tofloat;
		}
		else{
			cue.data = 0;
		}
	}
	return cue;

}
#ifdef __cplusplus
}  /* extern "C" */
#endif
