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
uint8_t counter_2s = 0;
uint8_t counter_1s = 0;
uint8_t counter_update = 0;
uint8_t counter_update_menu = 0;
uint8_t counter_send_stop = 0;
uint8_t counter_vel_inst = 0;

bool FLAG_SHORT_CUT = 0;
bool FLAG_UPDATE_SETTING = 1;
bool FLAG_SETTING_SELECTED = 0;
bool FLAG_UPDATE_SETTING_SELECTED = 0;
bool FLAG_UPDATE_VALUE = 0;
bool FLAG_REC_SHORT_CUT = 0;

bool FLAG_UPDATE = 0;
bool FLAG_VEL_INST = 0;
uint8_t CONTROL_MODE = 0;

float last_value_send = 0;

uint8_t OLD_ENC_A = 1;

struct velocity vel;
struct position pos;
struct torque tor;


void parameters_init(void){
	vel.control_mode = 2;
	vel.velocity_ref = 0;
	vel.velocity = 0;
	vel.acceleration = 0;
	vel.deceleration = 0;

	pos.control_mode = 3;
	pos.position_ref = 0;
	pos.position = 0;
	pos.velocity_ref = 0;
	pos.acceleration = 0;
	pos.deceleration = 0;

	tor.control_mode = 1;
	tor.torque_ref = 0;
	tor.torque = 0;
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
