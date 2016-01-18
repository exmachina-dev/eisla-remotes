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

#define VARMO_VERSION     "Varmo V0.4"
#define SERIAL_NUMBER     "0116VARM0001"
#define PROTOCOL          "ExmEisla"
#define ARMAZ_ID          "0000"

/*
String "machine.alive";
String "machme.alive:ok";
 */

String Get = "machine.get";
String Set = "machine.set";
String Alive = "machine.alive";

String Speed_ref = "machine.velocity_ref";
String Torque_ref = "machine.torque_ref";
String Position_ref = "machine.position_ref";

String Speed = "machine.velocity";
String Torque = "machine.torque";
String Position = "machine.position";

String Device_serial_num = "machine.serial_number";
String Drive_Enable = "status.drive_enable";


/*####################OBJECT####################*/

ST7036 lcd = ST7036 ( 2, 16, 0x78 );
Device Varmo = Device(SERIAL_NUMBER);

/*####################FUNCTION####################*/
void setup();
void loop();

void serialEvent();

void doEncoderA();
void doEncoderB();

int menu_set(int MENU);
float resolution_set(float RESOLUTION); 
void menu_init(int MODE, int *CONTRAST, int *POSITION, float *TORQUE, float *SPEED, float *encoder0Pos);

void lcd_print_menu(int MODE, int CONTRAST, int POSITION, float TORQUE, float SPEED, float torque_get,
					float speed_get, float position_get, float encoder0Pos);
void lcd_print_contrast_value(int CONTRAST);
void lcd_print_sign(float value);
void lcd_print_int_align_right(int value);
void lcd_print_float_align_right(float value);
void lcd_print_float_value(float value1, float value2);
void lcd_print_int_value(int value1, int value2);

void contrast_convert(int *CONTRAST, int *F_contrast, float *encoder0Pos);
void speed_convert(float * SPEED, float * encoder0Pos, float resolution);
void torque_convert(float * TORQUE, float * encoder0Pos, float resolution);

#endif // VARMO_H_INCLUDED

;