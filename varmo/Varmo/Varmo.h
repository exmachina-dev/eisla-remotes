/*

  ExmEisla0116ARCP0001alive
  ExmEisla0116ARCP0001alive:ok
  ExmEisla0116ARCP0001get.speed:595

*/

#ifndef VARMO_H_INCLUDED
#define VARMO_H_INCLUDED
#include <Arduino.h>
#include "ST7036.h"
#include <Wire.h>
#include <protocol.h>

/*####################PIN ASIGNMENTS####################*/

/*ENCODER*/
#define encoder0PinA 2
#define encoder0PinB 3
#define encoderE 4

/*CONTRASTE*/
#define CONTRAST_PWM 5

/*SEND_BUTTON*/
#define SEND_BUTTON 10

/*LED*/
#define LED_1 A0
#define LED_2 A1

/*DIRECTION*/
#define DIRECTION_1 8
#define DIRECTION_2 9

/*####################PROTCOL KEYS WORDS####################*/

#define VARMO_VERSION     "Varmo V1.0.0"
#define SERIAL_NUMBER     "0116VARM0001"
#define PROTOCOL          "ExmEisla"
#define ARMAZ_ID          "0000"

/*
String "machine.alive";
String "machme.alive:ok";
 */

const uint8_t MODE_POS = 1;
const uint8_t MODE_POS_SPD = 2;
const uint8_t MODE_HOME = 3;
const uint8_t MODE_ACC = 4;
const uint8_t MODE_DEC = 5;
const uint8_t MODE_SPD = 6;
const uint8_t MODE_TRQ = 7;

const uint8_t MODE_CUE = 8;

/*####################OBJECT####################*/

ST7036 lcd = ST7036 ( 2, 16, 0x78 );
Device Varmo = Device();

/*####################FUNCTION####################*/
void setup();
void loop();

void serialEvent();

void doEncoderA();
void doEncoderB();

uint8_t menu_set(uint8_t MENU);
float resolution_set(float RESOLUTION); 
void menu_init(uint8_t MODE, uint8_t *CONTRAST, float *POSITION, float * TORQUE, float * SPEED, float *HOME_POSITION, float *ACCELERATION, float *DECELERATION, float * encoder0Pos, float resolution);

void lcd_print_menu(uint8_t *MODE, uint8_t CONTRAST, float POSITION, float TORQUE, float SPEED, float HOME_POSITION, float ACCELERATION, float DECELERATION, float POS_SPEED, 
					float torque_get, float speed_get, float position_get, float home_position_get, float acceleration_get, float decelaration_get, float pos_speed_get, float *encoder0Pos);
void lcd_print_contrast_value(short CONTRAST);
void lcd_print_sign(float value);
void lcd_print_float_align_right(float value);
void lcd_print_float_value(float value1, float value2);
void lcd_print_float_value_three(float value1, float value2);

void converter(float *value, float *encoder0Pos, float resolution, bool sens, float max);
void contrast_convert(uint8_t *CONTRAST, uint8_t *F_contrast, float *encoder0Pos);

#endif // VARMO_H_INCLUDED

;