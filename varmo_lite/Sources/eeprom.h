/*
 * eeprom.h
 *
 *  Created on: 2016-08-18
 *      Author: Adrian
 */

#include "IFsh1.h"

#include "stdint.h"
#include "parameters.h"
#include "encoder_variable.h"


#ifndef SOURCES_EEPROM_H_
#define SOURCES_EEPROM_H_

#ifdef __cplusplus
extern "C" {
#endif

#define velocity_offset 0x3F000
#define position_offset 0X3F2BC

typedef union {
	float Tofloat;
	dword Todword;
}data_save;

typedef struct cue_parameter{
	bool data;
	float velocity;
	float position;
}cue_parameter;

void load_cue(uint8_t, int);
void write_cue(uint8_t, int);

void erase_cue(uint8_t, int);

uint8_t get_next_slot_free(int);

uint8_t get_slot_saved(int, uint8_t *);

cue_parameter get_cue_values(int, uint8_t);

void get_cues_saved_values(int, cue_parameter*, uint8_t *, uint8_t );

#ifdef __cplusplus
}  /* extern "C" */
#endif

#endif /* SOURCES_EEPROM_H_ */
