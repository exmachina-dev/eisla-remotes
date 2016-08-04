/*
 * send.cpp
 *
 *  Created on: 2016-08-04
 *      Author: Adrian
 */

#include "send.h"

#ifdef __cplusplus
extern "C" {
#endif

bool FLAG_SEND;

void send_fct(int flag){
	switch (flag){
		case Velocity_selected:

			break;
		case Velocity_acc_selected:
			vel.acceleration = convert(encoder, 0, 9999);
			//print_float_at(vel.acceleration,0,1,2, 0);
			break;
		case Velocity_dec_selected:
			vel.deceleration = convert(encoder, 0, 9999);
			//print_float_at(vel.deceleration,0,1,2, 0);
			break;
		case Position_selected:

			break;
		case Position_vel_selected:
			pos.velocity = convert(encoder, 0, 9999);
			//print_float_at(pos.velocity,0,1,2, 0);
			break;
		case Position_acc_selected:
			pos.acceleration = convert(encoder, 0, 9999);
			//print_float_at(pos.acceleration,0,1,2, 0);
			break;
		case Position_dec_selected:
			pos.deceleration = convert(encoder, 0, 9999);
			//print_float_at(pos.deceleration,0,1,2, 0);
			break;
		case Torque_selected:

			break;
		case Torque_rise_selected:
			tor.torque_rise = convert(encoder, 0, 9999);
			//print_float_at(tor.torque_rise,0,1,2, 0);
			break;
		case Torque_fall_selected:
			tor.torque_fall = convert(encoder, 0, 9999);
			//print_float_at(tor.torque_fall,0,1,2, 0);
			break;
	}
}


#ifdef __cplusplus
}  /* extern "C" */
#endif



