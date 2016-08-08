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
			vel.velocity_ref = convert(encoder, vel.velocity_minimum, vel.velocity_maximum);
			serial_send_block(4, 2, Set, Velocity_ref);
			serial_send_float(vel.velocity_ref);
			serial_send_end();
			break;
		case Velocity_acc_selected:
			vel.acceleration = convert(encoder, 0, 9999);
			serial_send_block(4,2, Set, Acceleration);
			serial_send_float(vel.acceleration);
			serial_send_end();
			break;
		case Velocity_dec_selected:
			vel.deceleration = convert(encoder, 0, 9999);

			serial_send_block(4,2, Set, Deceleration);
			serial_send_float(vel.deceleration);
			serial_send_end();
			break;
		case Position_selected:
			pos.position_ref = convert(encoder, pos.position_minimum, pos.position_maximum);
			serial_send_block(4, 2, Set, Position_ref);
			serial_send_float(pos.position_ref);
			serial_send_end();
			break;
		case Position_vel_selected:
			pos.velocity_ref = convert(encoder, 0, 9999);
			serial_send_block(4,2, Set, Velocity);
			serial_send_float(pos.velocity_ref);
			serial_send_end();
			break;
		case Position_acc_selected:
			pos.acceleration = convert(encoder, 0, 9999);
			serial_send_block(4,2, Set, Acceleration);
			serial_send_float(pos.acceleration);
			serial_send_end();
			break;
		case Position_dec_selected:
			pos.deceleration = convert(encoder, 0, 9999);
			serial_send_block(4,2, Set, Deceleration);
			serial_send_float(pos.deceleration);
			serial_send_end();
			break;
		case Torque_selected:
			tor.torque_ref = convert(encoder, tor.torque_minimum, tor.torque_maximum);
			serial_send_block(4,2, Set, Torque_ref);
			serial_send_float(tor.torque_ref);
			serial_send_end();
			break;
		case Torque_rise_selected:
			tor.torque_rise = convert(encoder, 0, 9999);
			serial_send_block(4, 2, Set, Torque_rise);
			serial_send_float(tor.torque_rise);
			serial_send_end();
			break;
		case Torque_fall_selected:
			tor.torque_fall = convert(encoder, 0, 9999);
			serial_send_block(4, 2, Set, Torque_fall);
			serial_send_float(tor.torque_fall);
			serial_send_end();
			break;
	}
}


#ifdef __cplusplus
}  /* extern "C" */
#endif



