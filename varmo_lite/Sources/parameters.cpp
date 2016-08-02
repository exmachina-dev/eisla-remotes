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

struct velocity vel;
struct position pos;
struct torque tor;

void parameters_init(void){
	vel.velocity = 0;
	vel.max = 10;
	vel.min = -10;
	vel.acceleration = 500;
	vel.decceleration = 500;

	pos.position = 0;
	pos.max = 9999;
	pos.min = -9999;
	pos.velocity = 0;
	pos.acceleration = 500;
	pos.decceleration = 500;

	tor.torque = 0;
	tor.max = 9999;
	tor.min = -9999;
	tor.torque_rise = 500;
	tor.torque_fall = 500;
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
