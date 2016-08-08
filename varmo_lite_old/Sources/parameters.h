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
	int control_mode;
	float velocity_ref;
	float velocity;
	float velocity_maximum;
	float velocity_minimum;
	float acceleration;
	float deceleration;
}vel;


extern struct position{
	int control_mode;
	float position_ref;
	float position;
	float position_maximum;
	float position_minimum;
	float velocity_ref;
	float velocity;
	float acceleration;
	float deceleration;
}pos;

extern struct torque{
	int control_mode;
	float torque_ref;
	float torque;
	float torque_maximum;
	float torque_minimum;
	float torque_rise;
	float torque_fall;
}tor;

void parameters_init(void);
float convert(float,float,float);




#ifdef __cplusplus
}  /* extern "C" */
#endif


#endif /* SOURCES_PARAMETER_H_ */
