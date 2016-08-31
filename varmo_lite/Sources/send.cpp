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
bool FLAG_UPDATE_MENU = 0;
bool FLAG_SEND_STOP = 0;
bool FLAG_COM_TIME_OUT = 0;

void Send_Control_Mode(int control){
	serial_send_block(4,2, Set, Control_Mode);
	serial_send_int(control);
	serial_send_end();
}

void send_fct(int flag){
	switch (flag){
		case Velocity_selected:
			encoder = convert(encoder, -9999, 9999);
			serial_send_block(4, 2, Set, Velocity_ref);
			serial_send_float(encoder);
			serial_send_end();
			break;

		case Velocity_acc_selected:
			if(encoder != 0){
				vel.acceleration = convert(encoder, 0, 9999);
				serial_send_block(4,2, Set, Acceleration);
				serial_send_float(vel.acceleration);
				serial_send_end();
			}
			break;

		case Velocity_dec_selected:
			if(encoder != 0){
				vel.deceleration = convert(encoder, 0, 9999);
				serial_send_block(4,2, Set, Deceleration);
				serial_send_float(vel.deceleration);
				serial_send_end();
			}
			break;

		case Position_selected:
			encoder = convert(encoder, -9999, 9999);
			if(encoder == 0){
				serial_send_block(1, 2, Set, Go_Home);
				serial_send_char(protocol_setting.DELIMITATOR);
				serial_send_char(1);
				serial_send_end();
			}
			else {
				serial_send_block(4, 2, Set, Position_ref);
				serial_send_float(encoder);
				serial_send_end();
			}
			serial_send_block(1, 2, Set, Pos_go);
			serial_send_char(protocol_setting.DELIMITATOR);
			serial_send_char(1);
			serial_send_end();

			break;

		case Position_vel_selected:
			pos.velocity_ref = convert(encoder, 0, 9999);
			serial_send_block(4,2, Set, Velocity_ref);
			serial_send_float(pos.velocity_ref);
			serial_send_end();
			break;

		case Position_acc_selected:
			if(encoder != 0){
				pos.acceleration = convert(encoder, 0, 9999);
				serial_send_block(4,2, Set, Acceleration);
				serial_send_float(pos.acceleration);
				serial_send_end();
			}
			break;

		case Position_dec_selected:
			if (encoder != 0){
				pos.deceleration = convert(encoder, 0, 9999);
				serial_send_block(4,2, Set, Deceleration);
				serial_send_float(pos.deceleration);
				serial_send_end();
			}
			break;

		case Position_set_home :
			serial_send_block(1,2, Set, Set_Home);
			serial_send_char(protocol_setting.DELIMITATOR);
			serial_send_char(1);
			serial_send_end();
			break;

		case Torque_selected:
			encoder = convert(encoder, -9999, 9999);
			serial_send_block(4,2, Set, Torque_ref);
			serial_send_float(encoder);
			serial_send_end();
			break;

		case Torque_rise_selected:
			if(encoder != 0){
				tor.torque_rise = convert(encoder, 0, 9999);
				serial_send_block(4, 2, Set, Torque_rise);
				serial_send_float(tor.torque_rise);
				serial_send_end();
			}
			break;

		case Torque_fall_selected:
			if(encoder != 0){
				tor.torque_fall = convert(encoder, 0, 9999);
				serial_send_block(4, 2, Set, Torque_fall);
				serial_send_float(tor.torque_fall);
				serial_send_end();
			}
			break;
	}
}

void get_update_drive_en(){
	serial_send_block(0,2, Get, Drive_Enable);
	serial_send_end();
}

void get_update_value(int mode){
	if (mode == 1){
		//Torque
		serial_send_block(0,2, Get, Torque);
		serial_send_end();
		if (FLAG_UPDATE_MENU == 0){
			serial_send_block(0,2, Get, Torque_rise);
			serial_send_end();

			serial_send_block(0,2, Get, Torque_fall);
			serial_send_end();

			serial_send_block(0,2, Get, Torque_ref);
			serial_send_end();
		}

	}
	else if(mode == 2){
		//Velocity
		serial_send_block(0,2, Get, Velocity);
		serial_send_end();
		if (FLAG_UPDATE_MENU == 0){
			serial_send_block(0,2, Get, Acceleration);
			serial_send_end();

			serial_send_block(0,2, Get, Deceleration);
			serial_send_end();

			serial_send_block(0,2, Get, Velocity_ref);
			serial_send_end();
		}

	}
	else if(mode == 3){
		//Position
		serial_send_block(0,2, Get, Position);
		serial_send_end();
		serial_send_block(0,2, Get, Velocity);
		serial_send_end();

		if (FLAG_UPDATE_MENU == 0){
			serial_send_block(0,2, Get, Velocity_ref);
			serial_send_end();

			serial_send_block(0,2, Get, Acceleration);
			serial_send_end();

			serial_send_block(0,2, Get, Deceleration);
			serial_send_end();
		}
	}
}

void send_stop(){
	serial_send_block(1,2, Set, Cancel);
	serial_send_char(protocol_setting.DELIMITATOR);
	serial_send_char(1);
	serial_send_end();
}

void send_velocity_cue(){
	serial_send_block(4, 2, Set, Velocity_ref);
	serial_send_float(vel.velocity_ref);
	serial_send_end();
	vel.acceleration = convert(encoder, 0, 9999);
	serial_send_block(4,2, Set, Acceleration);
	serial_send_float(vel.acceleration);
	serial_send_end();
	serial_send_block(4,2, Set, Deceleration);
	serial_send_float(vel.deceleration);
	serial_send_end();
}

void send_position_cue(){
	if(pos.position_ref == 0){
		serial_send_block(1, 2, Set, Go_Home);
		serial_send_char(protocol_setting.DELIMITATOR);
		serial_send_char(1);
		serial_send_end();
	}
	else {
		serial_send_block(4, 2, Set, Position_ref);
		serial_send_float(pos.position_ref);
		serial_send_end();
	}

	serial_send_block(4,2, Set, Velocity_ref);
	serial_send_float(pos.velocity_ref);
	serial_send_end();
	serial_send_block(4,2, Set, Acceleration);
	serial_send_float(pos.acceleration);
	serial_send_end();
	serial_send_block(4,2, Set, Deceleration);
	serial_send_float(pos.deceleration);
	serial_send_end();
	serial_send_block(1, 2, Set, Pos_go);
	serial_send_char(protocol_setting.DELIMITATOR);
	serial_send_char(1);
	serial_send_end();
}

void velocity_processing(char* value){
	convert_to_send temp;
	for (uint8_t i = 0; i < sizeof(value)/sizeof(value[0]); i++){
		temp.toBytes[i] = value[i];
	}
	vel.velocity = temp.toFloat;
	pos.velocity = temp.toFloat;
}

void velocity_ref_processing(char* value){
	convert_to_send temp;
	for (uint8_t i = 0; i < sizeof(value)/sizeof(value[0]); i++){
		temp.toBytes[i] = value[i];
	}
	vel.velocity_ref = temp.toFloat;
	pos.velocity_ref = temp.toFloat;
}

void acceleration_processing(char* value){
	convert_to_send temp;
	for (uint8_t i = 0; i < sizeof(value)/sizeof(value[0]); i++){
		temp.toBytes[i] = value[i];
	}
	vel.acceleration = temp.toFloat;
	pos.acceleration = temp.toFloat;
}

void deceleration_processing(char* value){
	convert_to_send temp;
	for (uint8_t i = 0; i < sizeof(value)/sizeof(value[0]); i++){
		temp.toBytes[i] = value[i];
	}
	vel.deceleration = temp.toFloat;
	pos.deceleration = temp.toFloat;
}

void torque_processing(char* value){
	convert_to_send temp;
	for (uint8_t i = 0; i < sizeof(value)/sizeof(value[0]); i++){
		temp.toBytes[i] = value[i];
	}
	tor.torque = temp.toFloat;
}

void torque_ref_processing(char* value){
	convert_to_send temp;
	for (uint8_t i = 0; i < sizeof(value)/sizeof(value[0]); i++){
		temp.toBytes[i] = value[i];
	}
	tor.torque_ref = temp.toFloat;
}

void torque_rise_processing(char* value){
	convert_to_send temp;
	for (uint8_t i = 0; i < sizeof(value)/sizeof(value[0]); i++){
		temp.toBytes[i] = value[i];
	}
	tor.torque_rise = temp.toFloat;
}

void torque_fall_processing(char* value){
	convert_to_send temp;
	for (uint8_t i = 0; i < sizeof(value)/sizeof(value[0]); i++){
		temp.toBytes[i] = value[i];
	}
	tor.torque_fall = temp.toFloat;
}

void position_ref_processing(char* value){
	convert_to_send temp;
	for (uint8_t i = 0; i < sizeof(value)/sizeof(value[0]); i++){
		temp.toBytes[i] = value[i];
	}
	pos.position_ref = temp.toFloat;
}

void position_processing(char* value){
	convert_to_send temp;
	for (int i = 0; i < sizeof(value)/sizeof(value[0]); i++){
		temp.toBytes[i] = value[i];
	}
	pos.position = temp.toFloat;
}

void control_mode_processing(char* value){
		convert_to_send temp;
		FLAG_CONTROL_MODE_CONFIRM = 1;
		for (uint8_t i = 0; i < sizeof(value)/sizeof(value[0]); i++){
			temp.toBytes[i] = value[i];
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

void drive_enable_processing(char* value){
	convert_bool_to_send temp;
	temp.toByte = value[0];
	drive_enable_st = temp.toBool;
}



#ifdef __cplusplus
}  /* extern "C" */
#endif



