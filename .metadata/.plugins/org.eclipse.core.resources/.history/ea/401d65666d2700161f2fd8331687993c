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
/* MODULE main */

#include "LED_STATUS_1.h"
#include "LED_STATUS_2.h"
#include "LED_STATUS_3.h"
#include "LED_STATUS_4.h"

#ifdef __cplusplus
extern "C" {
#endif

void led_init(int i){
	if (i%4 == 0){
		LED_STATUS_1_PutVal(1);
		LED_STATUS_2_PutVal(0);
		LED_STATUS_3_PutVal(0);
		LED_STATUS_4_PutVal(0);
	}
	else if (i%4 == 1){
		LED_STATUS_1_PutVal(0);
		LED_STATUS_2_PutVal(1);
		LED_STATUS_3_PutVal(0);
		LED_STATUS_4_PutVal(0);
	}
	else if (i%4 == 2){
		LED_STATUS_1_PutVal(0);
		LED_STATUS_2_PutVal(0);
		LED_STATUS_3_PutVal(1);
		LED_STATUS_4_PutVal(0);
	}
	else if (i%4 == 3){
		LED_STATUS_1_PutVal(0);
		LED_STATUS_2_PutVal(0);
		LED_STATUS_3_PutVal(0);
		LED_STATUS_4_PutVal(1);
	}
}
