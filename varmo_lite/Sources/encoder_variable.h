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

extern bool FLAG_SENS;
extern bool FLAG_SENS_1;
extern bool FLAG_SENS_2;
extern bool FLAG_STOP;

extern int counter_100ms;


extern float encoder;
extern float old_encoder;

extern int resolution;

#ifdef __cplusplus
}  /* extern "C" */
#endif


#endif /* SOURCES_ENCODER_VARIABLE_H_ */
