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

char in_buffer[127];
uint8_t cnt;
bool FLAG_MSG_RCV;
bool FLAG_MSG_ERR;
bool FLAG_MSG_OK;
char msg[100];
int nb_data;

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
		//LED_STATUS_2_SetVal();
	}
}

void serial_send_end(void){
	serial_send_string(protocol_setting.END);
}

void test_protocol(){
	/*
	serial_send_block(2, Get_OK, Velocity_ref);
	serial_send_block(2, Set_OK, Position_ref);
	*/
}

bool msg_parse(char* msg){
	  int offset = 22;
	  char chr = msg[offset];
	  char data1[50];
	  char data2[50];
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
		  //char temp1[50];
		  offset += i +1;
		  i = 0;
		  char chr = msg[offset];
		  while (chr != ':' && chr != '\r'){
			  data2[i] = chr;
			  i++;
			  chr = msg[offset + i];
		  }
		  data2[i] = '\0';
		  //data2 = temp1;
	  }
	  else {
		  //only one data
	  }
	  return FLAG_MSG_ERR = msg_processing(2, data1, data2);
	  //FLAG_MSG_OK = 0;

}

bool msg_processing(int n, ...){
	int nb_data = n;
	va_list arg;
	va_start(arg, n);
	char* data = va_arg(arg, char*);
/*
 	if (strcmp(data, Set_OK) == 0){
		return 0;
	}
 	else if (strcmp(data, Set_ERR) == 0){
 		return 1;
 	}
 	else if (strcmp(data, Get_OK) == 0){
		//return 0;
	}
 	else if (strcmp(data, Get_ERR) == 0){
 		return 1;
 	}
 	*/
	va_end(arg);
	return 0;
}

#ifdef __cplusplus
}  /* extern "C" */
#endif


