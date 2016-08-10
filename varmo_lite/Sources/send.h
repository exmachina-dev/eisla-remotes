/*
 * send.h
 *
 *  Created on: 2016-08-04
 *      Author: Adrian
 */
#include "parameters.h"
#include "encoder_variable.h"
#include "protocol.h"

#ifndef SOURCES_SEND_H_
#define SOURCES_SEND_H_

#ifdef __cplusplus
extern "C" {
#endif

extern bool FLAG_SEND;
extern uint8_t CONTROL_MODE;
extern bool FLAG_CONTROL_MODE_CONFIRM;
extern bool FLAG_UPDATE;

void get_update_value(int);
void send_fct(int);
void Send_Control_Mode(int);

void velocity_processing(char*);
void velocity_ref_processing(char*);
void acceleration_processing(char*);
void deceleration_processing(char*);

void torque_processing(char*);
void torque_rise_processing(char*);
void torque_fall_processing(char*);

void control_mode_processing(char*);

void set_drive_enable(void);
void clear_drive_enable(void);

void drive_enable_processing(char*);

#ifdef __cplusplus
}  /* extern "C" */
#endif

#endif /* SOURCES_SEND_H_ */
