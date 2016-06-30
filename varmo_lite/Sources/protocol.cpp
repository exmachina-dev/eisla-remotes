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

#include "LED_STATUS_1.h"
#include "BitIoLdd2.h"

#include "protocol.h"

#ifdef __cplusplus
extern "C" {
#endif

void serial_send_block(int n,...)
{
	int nb_element = n;
	va_list arg;
	va_start(arg, n);

	binaryRepr length;

	length.toInt.int0 = protocol_setting.length.toInt.int0;

	for (int i = 0; i < nb_element; i++){
		length.toInt.int0 += strlen(va_arg(arg, char*));
	}
	va_end(arg);

	//binaryRepr length_block = format_length(length);
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
			serial_send_string(va_arg(arg, char*));
		}
	}
	va_end(arg);

	serial_send_string(protocol_setting.END);
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
		LED_STATUS_1_SetVal();
	}
}

void test_protocol(){
	serial_send_block(2, (char*)Get, (char*)Velocity);
}

#ifdef __cplusplus
}  /* extern "C" */
#endif

