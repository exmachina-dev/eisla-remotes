/*
 * encoder.h
 *
 *  Created on: 2016-07-05
 *      Author: Adrian
 */


#ifndef SOURCES_ENCODER_VARIABLE_H_
#define SOURCES_ENCODER_VARIABLE_H_

#ifdef __cplusplus
extern "C" {
#endif

bool FLAG_PUSH_SHORT;
bool FLAG_PUSH_LONG;
bool FLAG_ENCODER;

int counter_100ms;

float encoder;

int convert_encoder(float,float,float);

#ifdef __cplusplus
}  /* extern "C" */
#endif


#endif /* SOURCES_ENCODER_VARIABLE_H_ */
