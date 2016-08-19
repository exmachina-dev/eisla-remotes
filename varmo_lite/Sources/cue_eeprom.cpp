/*
 * cue_eeprom.cpp
 *
 *  Created on: 2016-07-01
 *      Author: Adrian
 */

#include "cue_eeprom.h"

#include "stdint.h"
#include <stdio.h>
#include <string.h>
#include <stdarg.h>

#include "IFsh1.h"
#include "IntFlashLdd1.h"
#include "KSDK1.h"
#include "CS1.h"

#ifdef __cplusplus
extern "C" {
#endif

uint8_t get_cue_slot_free() {
  short eeAddress;
  uint8_t j = 0;
  bool slot_free = 0;
  for (uint8_t i = 0; i < 50; i++) {
    eeAddress = (i) * 18;
    uint8_t *temp;
    //IFsh1_GetByteFlash(eeAddress, temp);
    if (*temp != 1 && slot_free == 0) {
      j = i;
      slot_free = 1;
    }
  }
  if (slot_free == 0){
    j = 50;
  }
  return j;
}

uint8_t get_cue_save(uint8_t * cue) {
  short eeAddress;
  uint8_t j = 0;
  for (uint8_t i = 0; i < 50; i++) {
    eeAddress = (i) * 18;
    uint8_t *temp;
   // IFsh1_GetByteFlash(eeAddress, temp);

    if (*temp == 1) {
      cue[j] = i + 1;
      j++;
    }
  }
  for (uint8_t i = j; i < 50; i++) {
    cue[i] = 0;
  }
  return j;
}

void erase_cue_eeprom(uint8_t cue, uint8_t *cue_save){
  int eeAddress = 18 * (cue_save[cue]-1);
  /*lcd.setCursor(0,13);
  lcd.print(eeAddress);*/
  //EEPROM.write(eeAddress, 0);
}

byte get_cue_status(uint8_t cue) {
  int eeAddress = 0;   //Location we want the data to be put.
/*
  MyObject writing;

  eeAddress = sizeof(writing) * (cue);
  return EEPROM.read(eeAddress);*/
}

void write_cue_eeprom(uint8_t cue, float pos, float speed, float acceleration, float decceleration) {
  int eeAddress = 0;   //Location we want the data to be put.

  data_eeprom_struc writing;

  eeAddress = sizeof(writing) * (cue);

  uint8_t *temp;
 // IFsh1_GetByteFlash(eeAddress, temp);


  if (*temp != 1)  {
    writing.data = 1;
    writing.cue_num = cue;
    writing.pos = pos;
    writing.pos_speed = speed;
    writing.acc = acceleration;
    writing.dec = decceleration;
  }
  else if (*temp == 1) {
    writing.data = 1;
    writing.cue_num = cue;
    writing.pos = pos;
    writing.pos_speed = speed;
    writing.acc = acceleration;
    writing.dec = decceleration;
  }
  //EEPROM.put(eeAddress, writing);
}

void reading_cue_eeprom(uint8_t * cue_save, uint8_t cue_pos, float *pos, float *speed, float *acceleration, float *decceleration) {
  int eeAddress = 0; //Move address to the next byte after float 'f'.

  data_eeprom_struc reading; //Variable to store custom object read from EEPROM.
  uint8_t cue = cue_save[cue_pos];
  eeAddress = sizeof(reading) * (cue - 1);


  //EEPROM.get(eeAddress, reading);

  if (reading.data == 1 ) {
    *pos = reading.pos;
    *speed = reading.pos_speed;
    *acceleration = reading.acc;
    *decceleration = reading.dec;
  }
}

#ifdef __cplusplus
}  /* extern "C" */
#endif


