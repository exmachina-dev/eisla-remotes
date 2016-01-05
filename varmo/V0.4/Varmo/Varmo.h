#ifndef VARMO_H_INCLUDED
#define VARMO_H_INCLUDED
#include <Arduino.h>
#include "ST7036.h"
#include <Wire.h>
#include <protocol.h>

ST7036 lcd = ST7036 ( 2, 16, 0x78 );
Device Varmo = Device(SerialNumber);

#define VARMO_VERSION   "Varmo Version 0.4"
#define SerialNumber    "012016001VARMO"

/*ENCODER*/
#define encoder0PinA 2
#define encoder0PinB 3
#define encoderE 4

/*CONTRASTE*/
#define CONTRASTE_PWM 5

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
int menu_init(int MODE, int *CONTRASTE, int *POSITION, float *TORQUE, float *SPEED, float *encoder0Pos);
int lcd_print_menu(int MODE, int *CONTRASTE, int *POSITION, float *TORQUE, float *SPEED, float *encoder0Pos);

void lcd_print_contraste_value(int CONTRASTE);
void lcd_print_float_value(float value);
void lcd_print_int_value(int value);

void contraste_convert(int *CONTRASTE, int *F_contraste, float *encoder0Pos);
void speed_convert(float *SPEED, float *encoder0Pos, float resolution);
void torque_convert(float *TORQUE, float *encoder0Pos, float resolution);

#endif // SWILL_H_INCLUDED