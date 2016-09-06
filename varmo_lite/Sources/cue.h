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
#include "parameters.h"
#include "send.h"
#include "eeprom.h"

#ifndef SOURCES_CUE_EEPROM_H_
#define SOURCES_CUE_EEPROM_H_

#ifdef __cplusplus
extern "C" {
#endif

#define cue_max 50

extern uint8_t cue_saved[50];
extern uint8_t cue_saved_size;
extern cue_parameter cue_value_saved[50];

extern bool FLAG_CUE_MODE;
extern bool FLAG_CUE_SELECTED;
extern bool FLAG_UPDATE_CUE;


void select_cue(uint8_t, uint8_t);

#ifdef __cplusplus
}  /* extern "C" */
#endif

#endif /* SOURCES_CUE_EEPROM_H_ */
