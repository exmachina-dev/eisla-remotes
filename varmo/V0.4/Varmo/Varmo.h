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

#define CONFIRM_KEY_WORD  "ok"
#define ALIVE             "alive"
/*
String "machine.alive";
String "machme.alive:ok";
 */


String Get = "machine.get";
String Set = "machime.set";

String Set_Speed = "machine.set:velocity_ref";
String Set_Torque = "machine.set:torque_ref";
String Set_Position = "machine.set:position_ref";

String Get_Speed = "machine.get:velocity";
String Get_Torque = "machine.get:torque";
String Get_Position = "machine.get:position";

String Get_Drive_Enable = "machine.get:status.drive_enable";
String Get_Motor = "machine.get:status.motor";

/*####################OBJECT####################*/

ST7036 lcd = ST7036 ( 2, 16, 0x78 );
Device Varmo = Device(SERIAL_NUMBER);

/*####################FUNCTION####################*/
void setup();
void loop();

void doEncoderA();
void doEncoderB();

int menu_set(int MENU);
float resolution_set(float RESOLUTION); 
void menu_init(int MODE, int *CONTRAST, int *POSITION, float *TORQUE, float *SPEED, float *encoder0Pos);
void lcd_print_menu(int MODE, int CONTRAST, int POSITION, float TORQUE, float SPEED,float torque_get, float speed_get, float encoder0Pos);

void lcd_print_contraste_value(int CONTRASTE);
void lcd_print_float_value(float value);
void lcd_print_int_value(int value);

void contraste_convert(int *CONTRASTE, int *F_contraste, float *encoder0Pos);
void speed_convert(float *SPEED, float *encoder0Pos, float resolution);
void torque_convert(float *TORQUE, float *encoder0Pos, float resolution);

#endif // VARMO_H_INCLUDED
