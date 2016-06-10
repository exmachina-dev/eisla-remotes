/*
 * display.cpp
 *
 *  Created on: 2016-06-10
 *      Author: Adrian
 */

#include "display.h"

#ifdef __cplusplus
extern "C" {
#endif

void led_init(int counter){
	if ((counter%4) == 0){
		LED_STATUS_1_PutVal(1);
		LED_STATUS_2_PutVal(0);
		LED_STATUS_3_PutVal(0);
		LED_STATUS_4_PutVal(0);
	}
	else if ((counter%4) == 1){
		LED_STATUS_1_PutVal(0);
		LED_STATUS_2_PutVal(1);
		LED_STATUS_3_PutVal(0);
		LED_STATUS_4_PutVal(0);
	}
	else if ((counter%4) == 2){
		LED_STATUS_1_PutVal(0);
		LED_STATUS_2_PutVal(0);
		LED_STATUS_3_PutVal(1);
		LED_STATUS_4_PutVal(0);
	}
	else if ((counter%4) == 3){
		LED_STATUS_1_PutVal(0);
		LED_STATUS_2_PutVal(0);
		LED_STATUS_3_PutVal(0);
		LED_STATUS_4_PutVal(1);
	}
}

void menu_init(){

}

#ifdef __cplusplus
}  /* extern "C" */
#endif




