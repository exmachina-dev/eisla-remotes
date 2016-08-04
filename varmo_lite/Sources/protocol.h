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

static const char *Get;
static const char *Set = "machine.set";

/*
#define Get "machine.get";
#define Set "machine.set";
*/

static const char *Get_OK = "machine.get.ok";
static const char *Get_ERR = "machine.get.error";

static const char *Set_OK = "machine.set.ok";
static const char *Set_ERR = "machine.set.error";

static const char *Velocity = "machine.velocity";

static const char *Velocity_ref = "machine.velocity_ref";
static const char *Torque_ref = "machine.torque_ref";
static const char *Position_ref = "machine.position_ref";
static const char *Acceleration = "machine.acceleration";
static const char *Deceleration = "machine.deceleration";

static const char *Torque_rise = "machine.torque_rise_time";
static const char *Torque_fall = "machine.torque_fall_time";

static const char *Enable = "machine.command.enable";
static const char *Stop = "machine.command.cancel";
static const char *Pos_go = "machine.command.go";
static const char *Set_Home = "machine.command.set_home";
static const char *Reset = "machine.command.reset";

static const char *Move_Mode = "machine.command.move_mode";
static const char *Control_Mode = "machine.command.control_mode";

static const char *Device_serial_num = "machine.serialnumber";

extern char in_buffer[127];
extern uint8_t cnt;
extern bool FLAG_MSG_RCV;
extern bool FLAG_MSG_ERR;
extern bool FLAG_MSG_OK;
extern char msg[100];
extern int nb_data;

typedef union {
	struct{
		int int0;
	} toInt;
	struct {
      uint8_t toUint_8_0;
      uint8_t toUint_8_1;
    } toUint_8;
} binaryRepr;

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
    float toFloat;
    uint8_t toBytes[4];
} convert_to_send;

static const struct protocol_setting {
	char *PROTOCOL;
	char *SERIAL_NUMBER; // Month/Year/VARM/Serie
	char  *END;
	char DELIMITATOR;
	binaryRepr length;//length of the structure with the protocol (23) and the length of the message (2)
}protocol_setting = {(char*)"ExmEisla", (char*)"0716VARM0001", (char*) "\r\n", ':', 25};

void serial_send_block(int, ...);

void serial_send_float(float);
void serial_send_string(char*);
void serial_send_char(char);

void serial_send_end(void);

bool msg_parse(char*);
bool msg_processing(int n,...);


void test_protocol();

#ifdef __cplusplus
}  /* extern "C" */
#endif



#endif /* SOURCES_PROTOCOL_H_ */
