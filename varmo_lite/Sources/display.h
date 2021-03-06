/* ###################################################################
**     Filename    : display.c
**     Project     : varmo_lite
**     Processor   : MK20DX256VMC7
**     Version     : Driver 01.01
**     Compiler    : GNU C Compiler
**     Date/Time   : 2016-05-30, 15:08, # CodeGen: 0
**     Abstract    :
**         Main module.
**         This module contains user's application code.
**     Settings    :
**     Contents    :
**         No public methods
**
** ###################################################################*/
/*!
** @file main.c
** @version 01.01
** @brief
**         Main module.
**         This module contains user's application code.
*/
/*!
**  @addtogroup main_module main module documentation
**  @{
*/
#include "stdint.h"
#include "stdlib.h"
#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include <math.h>

#ifndef SOURCES_DISPLAY_H_
#define SOURCES_DISPLAY_H_

/* MODULE main */

#include "LED_STATUS_1.h"
#include "LED_STATUS_2.h"
#include "LED_STATUS_3.h"
#include "LED_STATUS_4.h"

#include "WAIT1.h"
#include "parameters.h"
#include "menu.h"
#include "encoder_variable.h"
#include "send.h"
#include "eeprom.h"
#include "cue.h"

#ifdef __cplusplus
extern "C" {
#endif

char buffer[80];
bool FLAG_MENU;
extern bool FLAG_SETTING;
extern bool FLAG_RESOLUTION;

int vspfunc(char *, ...);

void print_float_at(float, int,bool, int, int);
void print_int_at(int, bool, int, int);
void print_cue_array(uint8_t , uint8_t*, uint8_t);

void print_all_cue(uint8_t, uint8_t);

void led_init(int);
void load_char(void);
menu menu_init(void);

int refresh(int);
int select(int);
int back(int);

void refresh_fct(int);

void select_setting(int);

void controle_mode_display(int);

void control_mode_fct(void);

void update_icon_dir(bool, bool);
void update_icon_drive_enable(void);

void back_fct(void);

void velocity_fct(void);
void acceleration_fct(void);
void deceleration_fct(void);
void velocity_instant_fct(void);

void pos_position_fct(void);
void pos_velocity_fct(void);
void pos_acceleration_fct(void);
void pos_deceleration_fct(void);
void pos_set_home_fct(void);

void torque_fct(void);
void torque_rise_fct(void);
void torque_fall_fct(void);

void pos_play_cue_fct(void);
void pos_rec_cue_fct(void);
void pos_mod_cue_fct(void);
void pos_del_cue_fct(void);

void vel_play_cue_fct(void);
void vel_rec_cue_fct(void);
void vel_mod_cue_fct(void);
void vel_del_cue_fct(void);

void select_baud_rate_fct(void);
void select_update_menu_fct(void);

void short_cut_position_menu(void);

void display_resolution(void);
int get_cursor_resolution_position(void);
int get_resolution(void);

#ifdef __cplusplus
}  /* extern "C" */
#endif

#endif /* SOURCES_DISPLAY_H_ */

