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

void send_fct(int);

#ifdef __cplusplus
}  /* extern "C" */
#endif

#endif /* SOURCES_SEND_H_ */
