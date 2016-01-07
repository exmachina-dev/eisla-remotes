#ifndef VARMO_H_INCLUDED
#define VARMO_H_INCLUDED
#include <Arduino.h>
#include "ST7036.h"
#include <Wire.h>
#include <protocol.h>

#define VARMO_VERSION   "Varmo V0.4"
#define SERIAL_NUMBER   "0116VARM0001"
#define PROTOCOL        "exmeisla"
#define ARMAZ_ID        "amcp"


ST7036 lcd = ST7036 ( 2, 16, 0x78 );
Device Varmo = Device(SERIAL_NUMBER);

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

/*FONCTION*/
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

#endif // SWILL_H_INCLUDED
