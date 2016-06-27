/*
 * protocol.cpp
 *
 *  Created on: 2016-06-27
 *      Author: Adrian
 */

#include "protocol.h"

#ifdef __cplusplus
extern "C" {
#endif

protocol_setting define_protocol_setting(){
	protocol_setting setting;
	setting.PROTOCOL= (char*) "ExmEisla";
	setting.SERIAL_NUMBER = (char*) "0716VARMO0001";
	setting.DELIMITATOR = ':';
	setting.END = (char*) "\r\n";
	return setting;
}

void serial_send_block(protocol_setting setting, char* data1, char* data2)
{
	serial_send_string(setting.PROTOCOL);
	serial_send_string(setting.SERIAL_NUMBER);
	serial_send_string(data1);
	serial_send_char(setting.DELIMITATOR);
	serial_send_string(data2);
	serial_send_string(setting.END);
}

void serial_send_string(char* string){
	int nb_character = sizeof(string)/sizeof(string[0]);

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
	AS1_SendChar(character);
}
#ifdef __cplusplus
}  /* extern "C" */
#endif


