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

#define Velocity_selected 1
#define Velocity_acc_selected 2
#define Velocity_dec_selected 3
#define Vel_play_cue 4
#define Vel_Rec_cue 5
#define Vel_Mod_cue 6
#define Vel_Del_cue 7
#define Position_selected 8
#define Position_vel_selected 9
#define Position_acc_selected 10
#define Position_dec_selected 11
#define Position_set_home 12
#define Torque_selected 13
#define Torque_rise_selected 14
#define Torque_fall_selected 15

extern int menu_indicator;

extern bool drive_enable_st;

extern bool FLAG_SET_HOME;
extern int counter_2s;

extern bool FLAG_SHORT_CUT;

extern bool FLAG_UPDATE;

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
