
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
///#define CONTRAST_PWM 5

/*SEND_BUTTON*/
#define SEND_BUTTON 10

/*LED*/
/*#define LED_1 A0
#define LED_2 A1
*/
/*SAVE BUTTON */
#define SAVE_BUTTON A6

/*DIRECTION*/
#define DIRECTION_1 8
#define DIRECTION_2 9

/*####################PROTCOL KEYS WORDS####################*/

#define VARMO_VERSION     "Varmo V1.1.0"
#define SERIAL_NUMBER     "0116VARM0001"
/*#define PROTOCOL          "ExmEisla"
#define ARMAZ_ID          "0000"
*/
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

const uint8_t MODE_PLAY_CUE = 8;
const uint8_t MODE_REC_CUE = 9;
const uint8_t MODE_MOD_CUE = 10;
const uint8_t MODE_DEL_CUE = 11;


// Menu variables
MenuSystem ms;
Menu mm("Root Menu");
Menu mu1("Position Mode");
Menu mu2("Speed Mode");
Menu mu3("Torque Mode");


MenuItem mu1_mi1("Set Position");
MenuItem mu1_mi2("Set Speed");
MenuItem mu1_mi3("Set Acceleration");
MenuItem mu1_mi4("Set Deceleration");
Menu mu1_mu5("Cue Mode");
MenuItem mu1_mu5_mi1("Play Cue");
MenuItem mu1_mu5_mi2("Rec Cue");
MenuItem mu1_mu5_mi3("Mod Cue");
MenuItem mu1_mu5_mi4("Del Cue");
MenuItem mu1_mu5_mi5("Back");
MenuItem mu1_mi6("Set Home");
MenuItem mu1_mi7("Back");

MenuItem mu2_mi1("Set Speed");
MenuItem mu2_mi2("Set Acceleration");
MenuItem mu2_mi3("Set Deceleration");
MenuItem mu2_mi4("Back");

MenuItem mu3_mi1("Set Torque");
MenuItem mu3_mi2("Set Torque rise");
MenuItem mu3_mi3("Set Torque Fall");
MenuItem mu3_mi4("Back");

struct MyObject {
  byte data;
  byte cue_num;
  float pos;
  float pos_speed;
  float acc;
  float dec;
};

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