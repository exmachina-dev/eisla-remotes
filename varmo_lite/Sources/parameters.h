/*
 * parameters.h
 *
 *  Created on: 2016-08-01
 *      Author: Adrian
 */

#include "stdint.h"

#ifndef SOURCES_PARAMETERS_H_
#define SOURCES_PARAMETERS_H_

#ifdef __cplusplus
extern "C" {
#endif

extern int a;
extern struct velocity{
	float velocity;
	float velocity_real;
	float max;
	float min;
	uint16_t acceleration;
	uint16_t decceleration;
}vel;


extern struct position{
	float  position;
	float position_real;
	float max;
	float min;
	uint16_t velocity;
	uint16_t acceleration;
	uint16_t decceleration;
}pos;

extern struct torque{
	float torque;
	float torque_real;
	float max;
	float min;
	uint16_t torque_rise;
	uint16_t torque_fall;
}tor;

void parameters_init(void);
float convert(float,float,float);

#ifdef __cplusplus
}  /* extern "C" */
#endif


#endif /* SOURCES_PARAMETER_H_ */
