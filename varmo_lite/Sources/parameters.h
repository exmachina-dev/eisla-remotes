/*
 * parameters.h
 *
 *  Created on: 2016-08-01
 *      Author: Adrian
 */

#include "stdint.h"
//#include "display.h"

#ifndef SOURCES_PARAMETERS_H_
#define SOURCES_PARAMETERS_H_

#ifdef __cplusplus
extern "C" {
#endif

#define Velocity_selected 1
#define Velocity_acc_selected 2
#define Velocity_dec_selected 3
#define Position_selected 4
#define Position_vel_selected 5
#define Position_acc_selected 6
#define Position_dec_selected 7
#define Torque_selected 8
#define Torque_rise_selected 9
#define Torque_fall_selected 10

extern int menu_indicator;

extern struct velocity{
	float velocity;
	float velocity_real;
	float max;
	float min;
	uint16_t acceleration;
	uint16_t deceleration;
}vel;


extern struct position{
	float  position;
	float position_real;
	float max;
	float min;
	float velocity;
	float velocity_real;
	uint16_t acceleration;
	uint16_t deceleration;
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
