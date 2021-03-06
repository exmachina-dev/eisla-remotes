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
#define Velocity_instant_selected 4
#define Vel_play_cue 5
#define Vel_Rec_cue 6
#define Vel_Mod_cue 7
#define Vel_Del_cue 8
#define Position_selected 9
#define Position_vel_selected 10
#define Position_acc_selected 11
#define Position_dec_selected 12
#define Position_set_home 13
#define Pos_play_cue 14
#define Pos_Rec_cue 15
#define Pos_Mod_cue 16
#define Pos_Del_cue 17
#define Torque_selected 18
#define Torque_rise_selected 19
#define Torque_fall_selected 20
#define Baud_rate_setting 21
#define Update_setting 22

extern bool FLAG_REC;

extern int menu_indicator;
extern int old_menu_indicator;

extern bool drive_enable_st;

extern bool FLAG_SET_HOME;
extern uint8_t counter_2s;
extern uint8_t counter_1s;
extern uint8_t counter_update;
extern uint8_t counter_update_menu;
extern uint8_t counter_send_stop;
extern uint8_t counter_vel_inst;


extern bool FLAG_SHORT_CUT;
extern bool FLAG_UPDATE_SETTING;
extern bool FLAG_SETTING_SELECTED;
extern bool FLAG_UPDATE_SETTING_SELECTED;
extern bool FLAG_UPDATE_VALUE;

extern bool FLAG_REC_SHORT_CUT;

extern bool FLAG_UPDATE;
extern bool FLAG_VEL_INST;
extern uint8_t CONTROL_MODE;

extern float last_value_send;

extern uint8_t OLD_ENC_A;

extern struct velocity{
	int control_mode;
	float velocity_ref;
	float velocity;
	float acceleration;
	float deceleration;
}vel;


extern struct position{
	int control_mode;
	float position_ref;
	float position;
	float velocity_ref;
	float velocity;
	float acceleration;
	float deceleration;
}pos;

extern struct torque{
	int control_mode;
	float torque_ref;
	float torque;
	float torque_rise;
	float torque_fall;
}tor;


void parameters_init(void);
float convert(float,float,float);




#ifdef __cplusplus
}  /* extern "C" */
#endif


#endif /* SOURCES_PARAMETER_H_ */
