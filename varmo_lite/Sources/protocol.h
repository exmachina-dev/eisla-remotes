/*
 * protocol.h
 *
 *  Created on: 2016-06-27
 *      Author: Adrian
 */

#ifndef SOURCES_PROTOCOL_H_
#define SOURCES_PROTOCOL_H_

#include "stdint.h"
//#include <stdio.h>

#include "AS1.h"

#ifdef __cplusplus
extern "C" {
#endif

const char *Get = "machine.get";
const char *Set = "machine.set";

const char *Speed_ref = "machine.velocity_ref";
const char *Torque_ref = "machine.torque_ref";
const char *Position_ref = "machine.position_ref";

const char *Position = "machine.position";
const char *Pos_go = "machine.command.go";
const char *Go_Home = "machine.command.go_home";
const char *Pos_Home = "machine.command.set_home";

const char *Acceleration = "machine.acceleration";
const char *Deceleration = "machine.deceleration";

const char *Control_Mode = "machine.command.control_mode";

const char *Device_serial_num = "machine.serialnumber";
const char *Stop = "machine.command.cancel";



typedef union {
   struct {
      unsigned int int0;
      unsigned int int1;
    } toInt;
    struct {
      uint8_t bool0;
      uint8_t bool1;
      uint8_t bool2;
      uint8_t bool3;
    } toBool;
} binaryRepr;

struct protocol_setting {
	const char *PROTOCOL;
	const char *SERIAL_NUMBER; // Month/Year/VARM/Serie
	const char *END;
	const char DELIMITATOR;
}protocol_setting = {"ExmEisla" , "0716VARMO0001", "\r\n", ':'} ;

/*
struct {
    const char* string;
} myAnonymousStruct = { "some text" };*/

//protocol_setting define_protocol_setting(char*);

void serial_send_block(char*, char*);
void serial_send_string(char*);
void serial_send_char(char);
binaryRepr format_length(int);

#ifdef __cplusplus
}  /* extern "C" */
#endif



#endif /* SOURCES_PROTOCOL_H_ */
