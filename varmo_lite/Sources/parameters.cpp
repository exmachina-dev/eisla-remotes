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

int menu_indicator;

struct velocity vel;
struct position pos;
struct torque tor;


void parameters_init(void){
	vel.velocity_ref = 0;
	vel.velocity = -2000;
	vel.velocity_maximun = 100;
	vel.velocity_minimun = -100;
	vel.acceleration = 0;
	vel.deceleration = 0;

	pos.position_ref = 0;
	pos.position = -2;
	pos.position_maximun = 9999;
	pos.position_minimun = -9999;
	pos.velocity = 0;
	pos.acceleration = 0;
	pos.deceleration = 0;

	tor.torque_ref = 0;
	tor.torque = -2;
	tor.torque_maximun = 9999;
	tor.torque_minimun = -9999;
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
