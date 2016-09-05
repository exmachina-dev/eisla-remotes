/*
 * send.h
 *
 *  Created on: 2016-08-04
 *      Author: Adrian
 */
#include "WAIT1.h"
#include "parameters.h"
#include "encoder_variable.h"
#include "protocol.h"

#ifndef SOURCES_SEND_H_
#define SOURCES_SEND_H_

#ifdef __cplusplus
extern "C" {
#endif

extern bool FLAG_SEND;

extern bool FLAG_CONTROL_MODE_CONFIRM;
extern bool FLAG_ENTER_CONTROL_MODE;
extern bool FLAG_UPDATE_MENU;
extern bool FLAG_SEND_STOP;
extern bool FLAG_SEND_VEL;
extern bool FLAG_COM_TIME_OUT;


void get_update_drive_en(void);
void get_update_value(int);
void send_fct(int);
void Send_Control_Mode(int);

void velocity_processing(char*);
void velocity_ref_processing(char*);
void acceleration_processing(char*);
void deceleration_processing(char*);

void torque_processing(char*);
void torque_ref_processing(char*);
void torque_rise_processing(char*);
void torque_fall_processing(char*);

void position_ref_processing(char*);
void position_processing(char*);

void control_mode_processing(char*);

void set_drive_enable(void);
void clear_drive_enable(void);

void drive_enable_processing(char*);

void send_stop(void);
void send_velocity_cue(void);
void send_position_cue(void);

#ifdef __cplusplus
}  /* extern "C" */
#endif

#endif /* SOURCES_SEND_H_ */
