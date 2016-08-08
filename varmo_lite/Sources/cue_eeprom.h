/*
 * cue_eeprom.h
 *
 *  Created on: 2016-07-01
 *      Author: Adrian
 */

#include "stdint.h"
#include <stdio.h>
#include <string.h>
#include <stdarg.h>

#include "IFsh1.h"
#include "IntFlashLdd1.h"
#include "KSDK1.h"
#include "CS1.h"

#ifndef SOURCES_CUE_EEPROM_H_
#define SOURCES_CUE_EEPROM_H_

#ifdef __cplusplus
extern "C" {
#endif

struct data_eeprom_struc {
  byte data;
  byte cue_num;
  float pos;
  float pos_speed;
  float acc;
  float dec;
};

uint8_t get_cue_slot_free();
uint8_t get_cue_save(uint8_t *);
void erase_cue_eeprom(uint8_t , uint8_t *);
uint8_t get_cue_status(uint8_t );
void write_cue_eeprom(uint8_t , float , float , float , float );
void reading_cue_eeprom(uint8_t * , uint8_t , float *, float *, float *, float *);


#ifdef __cplusplus
}  /* extern "C" */
#endif

#endif /* SOURCES_CUE_EEPROM_H_ */
