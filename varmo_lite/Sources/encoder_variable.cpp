/*
 * encoder.cpp
 *
 *  Created on: 2016-07-05
 *      Author: Adrian
 */

#include "encoder_variable.h"

#ifdef __cplusplus
extern "C" {
#endif

bool FLAG_PUSH_SHORT;
bool FLAG_PUSH_LONG;
bool FLAG_ENCODER;
bool FLAG_DEBOUNCE;

bool FLAG_SENS;
bool FLAG_SENS_1;
bool FLAG_SENS_2;
bool FLAG_STOP = 0;

int counter_100ms;


float encoder;
float old_encoder;

int resolution = 100;

#ifdef __cplusplus
}  /* extern "C" */
#endif




