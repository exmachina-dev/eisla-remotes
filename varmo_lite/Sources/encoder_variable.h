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

extern bool FLAG_PUSH_SHORT;
extern bool FLAG_PUSH_LONG;
extern bool FLAG_ENCODER;
extern bool FLAG_DEBOUNCE;
extern int counter_100ms;


extern float encoder;


#ifdef __cplusplus
}  /* extern "C" */
#endif


#endif /* SOURCES_ENCODER_VARIABLE_H_ */
