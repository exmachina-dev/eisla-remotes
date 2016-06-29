/*
 * protocol.h
 *
 *  Created on: 2016-06-27
 *      Author: Adrian
 */

#ifndef SOURCES_PROTOCOL_H_
#define SOURCES_PROTOCOL_H_

#include "stdint.h"
#include <stdio.h>
#include <string.h>
#include <stdarg.h>

#include "AS1.h"

#ifdef __cplusplus
extern "C" {
#endif

static const char *Get = "machine.get";
static const char *Set = "machine.set";


static const char *Velocity = "machine.velocity";

static const char *Speed_ref = "machine.velocity_ref";
static const char *Torque_ref = "machine.torque_ref";
static const char *Position_ref = "machine.position_ref";

static const char *Position = "machine.position";
static const char *Pos_go = "machine.command.go";
static const char *Go_Home = "machine.command.go_home";
static const char *Pos_Home = "machine.command.set_home";

static const char *Acceleration = "machine.acceleration";
static const char *Deceleration = "machine.deceleration";

static const char *Control_Mode = "machine.command.control_mode";

static const char *Device_serial_num = "machine.serialnumber";
static const char *Stop = "machine.command.cancel";

typedef union {
	unsigned int int0;
    struct {
      uint8_t toUint_8_0;
      uint8_t toUint_8_1;
    } toUint_8;
} binaryRepr;

static const struct protocol_setting {
	char *PROTOCOL;
	char *SERIAL_NUMBER; // Month/Year/VARM/Serie
	char  *END;
	char DELIMITATOR;
	binaryRepr length;//length of the structure with the protocol (23) and the length of the message (2)
}protocol_setting = {(char*)"ExmEisla", (char*)"0716VARM0001", (char*) "\r\n", ':', 25};

void serial_send_block(int, ...);
void serial_send_string(char*);
void serial_send_char(char);

void test_protocol();

#ifdef __cplusplus
}  /* extern "C" */
#endif



#endif /* SOURCES_PROTOCOL_H_ */
