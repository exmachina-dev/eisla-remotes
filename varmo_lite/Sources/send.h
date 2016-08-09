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


void send_fct(int);
void Send_Control_Mode(int);

void control_mode_processing(char*);

#ifdef __cplusplus
}  /* extern "C" */
#endif

#endif /* SOURCES_SEND_H_ */
