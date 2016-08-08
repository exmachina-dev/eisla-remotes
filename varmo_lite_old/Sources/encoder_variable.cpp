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

int counter_100ms;


float encoder;

#ifdef __cplusplus
}  /* extern "C" */
#endif




