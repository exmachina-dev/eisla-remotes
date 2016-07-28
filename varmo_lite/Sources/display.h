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

#include <string.h>
#include <stdio.h>
#include <stdarg.h>

#ifndef SOURCES_DISPLAY_H_
#define SOURCES_DISPLAY_H_

/* MODULE main */

#include "LED_STATUS_1.h"
#include "LED_STATUS_2.h"
#include "LED_STATUS_3.h"
#include "LED_STATUS_4.h"

#include "menu.h"


#ifdef __cplusplus
extern "C" {
#endif

int vspfunc(char *, ...);

void print_float_at(float, int,bool, int, int);
void print_int_at(int, bool, int, int);

void led_init(int);
void load_char(void);
menu menu_init(void);

int refresh(int);

void velocity_fct(void);
void acceleration_fct(void);
void deceleration_fct(void);

void pos_velocity_fct(void);
void pos_acceleration_fct(void);
void pos_deceleration_fct(void);

void torque_fct(void);
void torque_rise_fct(void);
void torque_fall_fct(void);

void back_fct(void);



#ifdef __cplusplus
}  /* extern "C" */
#endif

#endif /* SOURCES_DISPLAY_H_ */

