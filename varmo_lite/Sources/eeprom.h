/*
 * eeprom.h
 *
 *  Created on: 2016-08-18
 *      Author: Adrian
 */

#include "IFsh1.h"

#include "stdint.h"
#include "parameters.h"

#ifndef SOURCES_EEPROM_H_
#define SOURCES_EEPROM_H_

#ifdef __cplusplus
extern "C" {
#endif

#define velocity_offset 0x1FC00
#define position_offset 0X00

typedef union {
	float Tofloat;
	dword Todword;
}data_save;

void load_cue(uint8_t, int);
void write_cue(uint8_t, int);

void erase_cue(uint8_t, int);

uint8_t get_next_slot_free(int);

uint8_t get_slot_saved(int, uint8_t *);

#ifdef __cplusplus
}  /* extern "C" */
#endif

#endif /* SOURCES_EEPROM_H_ */
