
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

/*SEND_BUTTON*/
#define SEND_BUTTON 10

/*SAVE BUTTON */
#define SAVE_BUTTON A6

/*DIRECTION*/
#define DIRECTION_1 8
#define DIRECTION_2 9

/*####################PROTCOL KEYS WORDS####################*/

#define VARMO_VERSION     "Varmo V1.1.0"
#define SERIAL_NUMBER     "0116VARM0001"


const uint8_t MODE_POS = 1;
const uint8_t MODE_POS_SPD = 2;
const uint8_t MODE_HOME = 3;
const uint8_t MODE_ACC = 4;
const uint8_t MODE_DEC = 5;
const uint8_t MODE_SPD = 6;
//const uint8_t MODE_TRQ = 7;

const uint8_t MODE_PLAY_CUE = 8;
const uint8_t MODE_REC_CUE = 9;
const uint8_t MODE_MOD_CUE = 10;
const uint8_t MODE_DEL_CUE = 11;


// Menu variables
MenuSystem ms;
Menu mm("Root menu");
Menu mu1("Position mode");
Menu mu2("Speed mode");
//Menu mu3("Torque mode");


MenuItem mu1_mi1("Set position");
MenuItem mu1_mi2("Set speed");
MenuItem mu1_mi3("Set acceleration");
MenuItem mu1_mi4("Set deceleration");
Menu mu1_mu5("Cue mode");
MenuItem mu1_mu5_mi1("Play cue");
MenuItem mu1_mu5_mi2("Record cue");
MenuItem mu1_mu5_mi3("Load cue");
MenuItem mu1_mu5_mi4("Delete cue");
MenuItem mu1_mu5_mi5("<-- Back");
MenuItem mu1_mi6("Set home");
MenuItem mu1_mi7("<-- Back");

MenuItem mu2_mi1("Set speed");
MenuItem mu2_mi2("Set acceleration");
MenuItem mu2_mi3("Set deceleration");
MenuItem mu2_mi4("<-- Back");
/*
MenuItem mu3_mi1("Set torque");
MenuItem mu3_mi2("Set torque rise");
MenuItem mu3_mi3("Set torque fall");
MenuItem mu3_mi4("<-- Back");
*/
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