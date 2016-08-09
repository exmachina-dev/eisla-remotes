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

bool FLAG_SEND = 0;
bool FLAG_CONTROL_MODE_CONFIRM = 0;
uint8_t CONTROL_MODE = 0;

void Send_Control_Mode(int control){
	serial_send_block(2,2, Set, Control_Mode);
	serial_send_int(control);
	serial_send_end();
}

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
			serial_send_block(4,2, Set, Velocity_ref);
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

void get_update_value(int mode){
	if (mode == 1){
		//Torque
		serial_send_block(0,2, Get, Torque);
		serial_send_end();

		serial_send_block(0,2, Get, Torque_rise);
		serial_send_end();

		serial_send_block(0,2, Get, Torque_fall);
		serial_send_end();

		serial_send_block(0,2, Get, Torque_ref);
		serial_send_end();

	}
	else if(mode == 2){
		//Velocity
		serial_send_block(0,2, Get, Velocity);
		serial_send_end();

		serial_send_block(0,2, Get, Acceleration);
		serial_send_end();

		serial_send_block(0,2, Get, Deceleration);
		serial_send_end();

		serial_send_block(0,2, Get, Velocity_ref);
		serial_send_end();

	}
	else if(mode == 3){
		//Position

	}
}

void velocity_processing(char* value){
	convert_to_send temp;
	for (int i = 0; i < sizeof(value)/sizeof(value[0]); i++){
		temp.toBytes[3-i] = value[i];
	}
	vel.velocity = temp.toFloat;
	pos.velocity = temp.toFloat;
}

void velocity_ref_processing(char* value){
	convert_to_send temp;
	for (int i = 0; i < sizeof(value)/sizeof(value[0]); i++){
		temp.toBytes[3-i] = value[i];
	}
	vel.velocity_ref = temp.toFloat;
}

void acceleration_processing(char* value){
	convert_to_send temp;
	for (int i = 0; i < sizeof(value)/sizeof(value[0]); i++){
		temp.toBytes[3-i] = value[i];
	}
	vel.acceleration = temp.toFloat;
	pos.acceleration = temp.toFloat;
}

void deceleration_processing(char* value){
	convert_to_send temp;
	for (int i = 0; i < sizeof(value)/sizeof(value[0]); i++){
		temp.toBytes[3-i] = value[i];
	}
	vel.deceleration = temp.toFloat;
	pos.deceleration = temp.toFloat;
}

void torque_processing(char* value){
	convert_to_send temp;
	for (int i = 0; i < sizeof(value)/sizeof(value[0]); i++){
		temp.toBytes[3-i] = value[i];
	}
	tor.torque = temp.toFloat;
}

void torque_rise_processing(char* value){
	convert_to_send temp;
	for (int i = 0; i < sizeof(value)/sizeof(value[0]); i++){
		temp.toBytes[3-i] = value[i];
	}
	tor.torque_rise = temp.toFloat;
}

void torque_fall_processing(char* value){
	convert_to_send temp;
	for (int i = 0; i < sizeof(value)/sizeof(value[0]); i++){
		temp.toBytes[3-i] = value[i];
	}
	tor.torque_fall = temp.toFloat;
}

void control_mode_processing(char* value){
		convert_to_send temp;
		FLAG_CONTROL_MODE_CONFIRM = 1;
		for (int i = 0; i < sizeof(value)/sizeof(value[0]); i++){
			temp.toBytes[3-i] = value[i];
		}
		if (temp.toInt.int0 == 1){
			//Torque
			CONTROL_MODE = 1;
		}
		else if (temp.toInt.int0 == 2){
			//Velocity
			CONTROL_MODE = 2;
		}
		else if (temp.toInt.int0 == 3){
			//Position
			CONTROL_MODE = 3;
		}
		else{
			CONTROL_MODE = 0;
		}
}

#ifdef __cplusplus
}  /* extern "C" */
#endif



