/*
 * parameters.cpp
 *
 *  Created on: 2016-08-01
 *      Author: Adrian
 */

#include "parameters.h"


#ifdef __cplusplus
extern "C" {
#endif

bool FLAG_REC = 0;

int menu_indicator;
int old_menu_indicator;
bool drive_enable_st;

bool FLAG_SET_HOME = 0;
int counter_2s = 0;
int counter_1s = 0;
bool FLAG_SHORT_CUT = 0;
bool FLAG_UPDATE_SETTING = 0;
bool FLAG_SETTING_SELECTED = 0;
bool FLAG_UPDATE_SETTING_SELECTED = 0;
bool FLAG_UPDATE_VALUE = 0;

bool FLAG_UPDATE = 0;
uint8_t CONTROL_MODE = 0;
struct velocity vel;
struct position pos;
struct torque tor;


void parameters_init(void){
	vel.control_mode = 2;
	vel.velocity_ref = 0;
	vel.velocity = 0;
	vel.velocity_maximum = 9999;
	vel.velocity_minimum = -9999;
	vel.acceleration = 0;
	vel.deceleration = 0;

	pos.control_mode = 3;
	pos.position_ref = 0;
	pos.position = 0;
	pos.position_maximum = 9999;
	pos.position_minimum = -9999;
	pos.velocity_ref = 0;
	pos.acceleration = 0;
	pos.deceleration = 0;

	tor.control_mode = 1;
	tor.torque_ref = 0;
	tor.torque = 0;
	tor.torque_maximum = 9999;
	tor.torque_minimum = -9999;
	tor.torque_rise = 0;
	tor.torque_fall = 0;
}

float convert(float encoder,float min, float max){
	if (encoder >= max){
		encoder = max;
	}
	else if (encoder <= min){
		encoder = min;
	}
	return encoder;
}






#ifdef __cplusplus
}  /* extern "C" */
#endif
