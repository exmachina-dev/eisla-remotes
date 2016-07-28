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

int convert_encoder(float encoder,float min, float max){
	if (encoder >= max){
		encoder = max;
	}
	else if (encoder <= min){
		encoder = min;
	}
	return encoder;
}

#ifdef __cplusplus
}  /* extern "C" */
#endif




