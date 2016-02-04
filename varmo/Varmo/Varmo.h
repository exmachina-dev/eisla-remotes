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
#include <MenuSystem.h>
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

#define VARMO_VERSION     "Varmo V1.1.0"
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


// Menu variables
MenuSystem ms;
Menu mm("ROOT Menu Title");
Menu mu1("Position Mode");
Menu mu2("Speed Mode");
Menu mu3("Torque Mode");


MenuItem mu1_mi1("Set Position");
MenuItem mu1_mi2("Set Speed");
MenuItem mu1_mi3("Set Home");
MenuItem mu1_mi4("Set Acceleration");
MenuItem mu1_mi5("Set Deceleration");

MenuItem mu2_mi1("Set Speed");
MenuItem mu2_mi2("Set Acceleration");
MenuItem mu2_mi3("Set Deceleration");

MenuItem mu3_mi1("Set Torque");
MenuItem mu3_mi2("Set Torque rise");
MenuItem mu3_mi3("Set Torque Fall");

/*####################OBJECT####################*/

ST7036 lcd = ST7036 ( 2, 16, 0x78 );
Device Varmo = Device();

/*####################FUNCTION####################*/
void setup();
void loop();

void doEncoderA();
void doEncoderB();

float resolution_set(float RESOLUTION); 

void lcd_print_contrast_value(short CONTRAST);
void lcd_print_sign(float value);
void lcd_print_float_align_right(float value);
void lcd_print_float_value(float value1, float value2);
void lcd_print_float_value_three(float value1, float value2);

void converter(float *value, float *encoder0Pos, float resolution, bool sens, float max);
void contrast_convert(uint8_t *CONTRAST, uint8_t *F_contrast, float *encoder0Pos);

#endif // VARMO_H_INCLUDED

;