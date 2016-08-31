/*
 * protocol.cpp
 *
 *  Created on: 2016-06-27
 *      Author: Adrian
 */

#include "stdint.h"
#include <stdio.h>
#include <string.h>
#include <stdarg.h>

#include "LED_STATUS_2.h"
#include "BitIoLdd3.h"

#include "protocol.h"

#ifdef __cplusplus
extern "C" {
#endif

char in_buffer[512];
uint8_t cnt;
bool FLAG_MSG_RCV;
bool FLAG_MSG_ERR;
bool FLAG_MSG_OK;
char msg[100];
int nb_data;
uint8_t mode[2] = {0, 1};

void serial_send_block(int nb_value_byte,int n,...)
{
	int nb_element = n;
	va_list arg;
	va_start(arg, n);

	binaryRepr length;

	length.toInt.int0 = protocol_setting.length.toInt.int0;

	for (int i = 0; i < nb_element; i++){
		length.toInt.int0 += strlen(va_arg(arg, char*));
	}
	if (nb_value_byte != 0){
		length.toInt.int0 += nb_value_byte + 1;
	}
	va_end(arg);

	serial_send_string(protocol_setting.PROTOCOL);

	serial_send_char((int)length.toUint_8.toUint_8_1);
	serial_send_char((int)length.toUint_8.toUint_8_0);
	serial_send_string(protocol_setting.SERIAL_NUMBER);

	va_start(arg, n);
	for (int j = 0; j < nb_element; j++){
		if (j == 0){
			char *temp =  va_arg(arg, char*);
			serial_send_string(temp);
		}
		else {
			serial_send_char(protocol_setting.DELIMITATOR);
			char *temp =  va_arg(arg, char*);
			serial_send_string(temp);
		}
	}
	va_end(arg);
}

void serial_send_float(float f){
	serial_send_char(protocol_setting.DELIMITATOR);
	convert_to_send temp;
	temp.toFloat = f;
	word i;
	AS1_SendBlock(temp.toBytes, (word) 4, &i);
}

void serial_send_int(int in){
	serial_send_char(protocol_setting.DELIMITATOR);
	convert_int_to_send temp;
	temp.toInt = in;
	word i;
	AS1_SendBlock(temp.toBytes, (word) 4, &i);
}

void serial_send_byte(byte b){
	serial_send_byte(protocol_setting.DELIMITATOR);
	AS1_SendChar((char)b);
}

void serial_send_string(char* string){
	int nb_character = strlen(string);

	if (nb_character == 1){
		serial_send_char(string[0]);
	}
	else if (nb_character == 0){
		//do nothing
	}
	else{
		for (int i = 0; i < nb_character; i++){
			serial_send_char(string[i]);
		}
	}
}

void serial_send_char(char character){
	byte err = AS1_SendChar(character);
	if (err != ERR_OK){
		LED_STATUS_2_SetVal();
	}
}

void serial_send_end(void){
	serial_send_string(protocol_setting.END);
}

bool msg_parse(char* msg, int size){
	  int offset = 22;
	  char chr = msg[offset];
	  char data1[50];
	  char data2[50];
	  char data3[50];
	  int i = 0;
	  while (chr != ':' && chr != '\r'){
		  data1[i] = chr;
		  i++;
		  chr = msg[offset + i];
	  }
	  data1[i] = '\0';
	  //data1 = temp;

	  if (chr == ':'){
		  //several data
		  offset += i +1;
		  i = 0;
		  chr = msg[offset];
		  while (chr != ':' && chr != '\r'){
			  data2[i] = chr;
			  i++;
			  chr = msg[offset + i];
		  }
		  data2[i] = '\0';
		  if (chr != '\r'){
			  offset += i +1;
			  i = 0;
			  chr = msg[offset];
			  while ((i+offset) != (size-2)){
				  data3[i] = chr;
				  i++;
				  chr = msg[offset + i];
			  }
		  }
		  if ((offset+i) == size-2){
			  //three data
			  return FLAG_MSG_ERR = msg_processing(2, data1, data2, data3);
		  }
		  else{
			  return FLAG_MSG_ERR = msg_processing(2, data1, data2);
		  }
		  //data2 = temp1;
	  }
	  else {
		  //only one data
		  return FLAG_MSG_ERR = msg_processing(2, data1);
	  }

	  //FLAG_MSG_OK = 0;

}

bool msg_processing(int n, ...){
	int nb_data = n;
	va_list arg;
	va_start(arg, n);

	char* data = va_arg(arg, char*);

 	if (strcmp(data, Set_OK) == 0){
 		data = va_arg(arg, char*);
 		if (strcmp(data,Control_Mode) == 0) {
 			data = va_arg(arg, char*);
 			control_mode_processing(data);
 			return 0;
 		}
 		else if (strcmp(data, Set_Home) == 0){
 			FLAG_SET_HOME = 1;
 			counter_2s = 0;
 			return 0;
 		}
 		else if (strcmp(data, Velocity_ref) == 0){
 			data = va_arg(arg, char*);
 			velocity_ref_processing(data);
 			if (menu_indicator == Position_vel_selected){
 				FLAG_SHORT_CUT = 1;
 			}
 			FLAG_UPDATE_VALUE = 1;
 			return 0;
 		}
 		else if (strcmp(data, Position_ref) == 0){
 			data = va_arg(arg, char*);
 			position_ref_processing(data);
 			FLAG_UPDATE_VALUE = 1;
 			return 0;
 		}
 		else if (strcmp(data, Torque_ref) == 0){
 			data = va_arg(arg, char*);
 			torque_ref_processing(data);
 			FLAG_UPDATE_VALUE = 1;
 			return 0;
 		}

	}
 	else if (strcmp(data, Set_ERR) == 0){
 		return 1;
 	}

 	else if (strcmp(data, Get_OK) == 0){
 		data = va_arg(arg, char*);
		if (strcmp(data,Velocity) == 0){
			data = va_arg(arg, char*);
			velocity_processing(data);
			return 0;
		}
		else if(strcmp(data,Velocity_ref) == 0){
			data = va_arg(arg, char*);
			velocity_ref_processing(data);
			return 0;
		}
		else if(strcmp(data,Acceleration) == 0){
			data = va_arg(arg, char*);
			acceleration_processing(data);
			return 0;
		}
		else if(strcmp(data,Deceleration) == 0){
			data = va_arg(arg, char*);
			deceleration_processing(data);
			return 0;
		}
		else if(strcmp(data,Torque) == 0){
			data = va_arg(arg, char*);
			torque_processing(data);
			return 0;
		}
		else if(strcmp(data,Torque_rise) == 0){
			data = va_arg(arg, char*);
			torque_rise_processing(data);
			return 0;
		}
		else if(strcmp(data,Torque_fall) == 0){
			data = va_arg(arg, char*);
			torque_fall_processing(data);
			return 0;
		}
		else if(strcmp(data, Position) == 0){
			data = va_arg(arg, char*);
			position_processing(data);
			return 0;
		}
		else if(strcmp(data,Drive_Enable) == 0){
			data =va_arg(arg, char*);
			drive_enable_processing(data);
			return 0;
		}
		//return 0;
	}
 	else if (strcmp(data, Get_ERR) == 0){
 		data = va_arg(arg, char*);
		if(strcmp(data,Drive_Enable) == 0){
			//clear_drive_enable();
			return 0;
		}
 		return 1;
 	}

	va_end(arg);
	return 0;
}

bool select_baud_rate(byte mode){
	AS1_SetBaudRateMode(mode);
}

#ifdef __cplusplus
}  /* extern "C" */
#endif


