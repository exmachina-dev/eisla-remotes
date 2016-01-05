#include <Arduino.h>
#include "ST7036.h"
#include <Wire.h>
#include <protocol.h>
#include "./Varmo.h"


/*ENCODER*/
float encoder0Pos = 0;
float encoder0Pos_old = 0;

/*CONTRASTE*/
int F_contraste = 0;

/*MENU*/
int MODE = 0;
int MODE_OLD = -1;

bool FLAG_MENU = 1;
bool FLAG_RESOLUTION = 0;
bool Mode_chosen = 0;
bool resolution_chosen = 0;

/*PARAMETERS*/
float SPEED = 0;
float TORQUE = 0;
signed int POSITION = 0;
int CONTRASTE = 0;

float SPEED_OLD = 0;
float TORQUE_OLD = 0;
signed int CONTRASTE_OLD = 0;
int POSITION_OLD = 0;

/*RESOLUTION*/
float RESOLUTION = 1;
float RESOLUTION_old = 1;

/*SERIAL SEND*/
String Set_Speed = "Set_Speed_Target";
String Set_Torque = "Set_Torque_Target";
String Set_Position = "Set_Position_Target";

/*CUSTOM CHARACTER*/
const uint8_t charBitmap[][8] = {
   { 0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F },
};

unsigned long time_push = 0;

void setup() {
  
  /*ENCODER INITIALISATION*/
  pinMode(encoder0PinA, INPUT);
  pinMode(encoder0PinB, INPUT);

  // encoder pin on interrupt 0 (pin 2)
  attachInterrupt(0, doEncoderA, CHANGE);
  // encoder pin on interrupt 1 (pin 3)
  attachInterrupt(1, doEncoderB, CHANGE);

  pinMode(encoderE, INPUT);

  pinMode(SEND_BUTTON, INPUT);
  
  pinMode(LED_1, OUTPUT);
  pinMode(LED_2, OUTPUT);
  
  pinMode(DIRECTION_1, INPUT);
  pinMode(DIRECTION_2, INPUT);  

  
  /*LCD INITIALISATION*/
  lcd.init ();
  lcd.clear ();
  lcd.print("ExMachima");
  lcd.setCursor(1, 0);
  lcd.print(VARMO_VERSION);
  delay(1000);

  // Load Custom Character
  int charBitmapSize = (sizeof(charBitmap ) / sizeof (charBitmap[0]));
  // Load custom character set into CGRAM
   for (int i = 0; i < charBitmapSize; i++ )
   {
      lcd.load_custom_character ( i, (uint8_t *)charBitmap[i] );
   }

  /*SERIAL INITIALISATION*/
  Serial.begin(115200);

  Varmo.sendDeviceInfo();
}

void loop()
{
  encoder0Pos_old = encoder0Pos;
  
  int encoder_push = digitalRead(encoderE);
  if (encoder_push == LOW)  {
    encoder_push = digitalRead(encoderE);
    time_push = millis();
    while (encoder_push != HIGH)  {
      encoder_push = digitalRead(encoderE);
    }

    if (((millis() - time_push)  > 250 )||(MODE == 0) )    {
      Mode_chosen = 0;
      while (Mode_chosen == 0) {
        MODE = menu_set(MODE);
        encoder_push = digitalRead(encoderE);
        if (encoder_push == LOW)  {
          encoder_push = digitalRead(encoderE);
          while (encoder_push != HIGH)  {
            encoder_push = digitalRead(encoderE);
          }
          FLAG_MENU = 1;
          Mode_chosen = 1;
        }
      }
    }
    else  {
      resolution_chosen = 0;
      RESOLUTION_old = RESOLUTION;
      while (resolution_chosen == 0)  {
        RESOLUTION = resolution_set(RESOLUTION);
        encoder_push = digitalRead(encoderE);
        if (encoder_push == LOW)  {
          encoder_push = digitalRead(encoderE);
          while (encoder_push != HIGH)  {
            encoder_push = digitalRead(encoderE);
          }
          FLAG_RESOLUTION = 1;
          resolution_chosen = 1;
        }
      }
    }
  }

  if (FLAG_MENU == 1)  {
    lcd_print_menu(MODE, &CONTRASTE, &POSITION, &TORQUE, &SPEED, &encoder0Pos);
    if (MODE_OLD != MODE)    {
      menu_init(MODE, &CONTRASTE, &POSITION, &TORQUE, &SPEED,&encoder0Pos);
      MODE_OLD = MODE;
    }
    else    {
      encoder0Pos = encoder0Pos_old;
    }
    FLAG_MENU = 0;
  }

  if (FLAG_RESOLUTION == 1) {
    encoder0Pos = encoder0Pos_old * (RESOLUTION_old/ RESOLUTION);
    Serial.println(encoder0Pos);
    FLAG_RESOLUTION = 0;
    lcd.cursor_off();
  }

  switch (MODE)  {
    case 0 :
      contraste_convert(&CONTRASTE, &F_contraste, &encoder0Pos);
      if (CONTRASTE != CONTRASTE_OLD) {
        CONTRASTE_OLD = CONTRASTE;
        lcd_print_contraste_value(CONTRASTE);
        analogWrite(CONTRASTE_PWM, F_contraste);
      }
      break;
    case 1 :
      POSITION = encoder0Pos;
      if (POSITION != POSITION_OLD) {
        lcd_print_int_value(POSITION);
        POSITION_OLD = POSITION;
      }
      break;
    case 2 :
      torque_convert(&TORQUE, &encoder0Pos, RESOLUTION);
      if (TORQUE != TORQUE_OLD) {
        lcd_print_float_value(TORQUE);
        TORQUE_OLD = TORQUE;
      }
      break;
    case 3 :
      speed_convert(&SPEED, &encoder0Pos, RESOLUTION);
      if (SPEED != SPEED_OLD) {
        lcd_print_float_value(SPEED);
        SPEED_OLD = SPEED;
      }
      break;
  }

  int send_button_push = digitalRead(SEND_BUTTON);
  
  if (send_button_push == LOW) {
    switch(MODE)  {
      case 1 :
        Varmo.sendData(Set_Position, String(POSITION));        
        break;
      case 2 :
        Varmo.sendData(Set_Torque, String(TORQUE));  
        break;
      case 3 :
        Varmo.sendData(Set_Speed, String(SPEED));
        break;
      }
  }
}

/*###########ENCODER##########*/
void doEncoderA() {

  // look for a low-to-high on channel A
  if (digitalRead(encoder0PinA) == HIGH) {
    // check channel B to see which way encoder is turning
    if (digitalRead(encoder0PinB) == LOW) {
      encoder0Pos = encoder0Pos + 1;         // CW
    }
    else {
      encoder0Pos = encoder0Pos - 1;         // CCW
    }
  }
  else   // must be a high-to-low edge on channel A
  {
    // check channel B to see which way encoder is turning
    if (digitalRead(encoder0PinB) == HIGH) {
      encoder0Pos = encoder0Pos + 1;          // CW
    }
    else {
      encoder0Pos = encoder0Pos - 1;          // CCW
    }
  }
}

void doEncoderB() {

  // look for a low-to-high on channel B
  if (digitalRead(encoder0PinB) == HIGH) {
    // check channel A to see which way encoder is turning
    if (digitalRead(encoder0PinA) == HIGH) {
      encoder0Pos = encoder0Pos + 1;         // CW
    }
    else {
      encoder0Pos = encoder0Pos - 1;         // CCW
    }
  }
  // Look for a high-to-low on channel B
  else {
    // check channel B to see which way encoder is turning
    if (digitalRead(encoder0PinA) == LOW) {
      encoder0Pos = encoder0Pos + 1;          // CW
    }
    else {
      encoder0Pos = encoder0Pos - 1;          // CCW
    }
  }
}

/*##########MENU##################*/
int menu_set(int MENU)  {
  int RESOLUTION = 12;
  int MENU_SELECTOR = int(encoder0Pos) % RESOLUTION;
  lcd.setCursor(0, 0);
  lcd.print("Menu           ");
  lcd.setCursor(1, 0);
  if (MENU_SELECTOR <  (RESOLUTION / 4))  {
    lcd.print("Contraste       ");
    MENU = 0;
  }
  else if (MENU_SELECTOR < (RESOLUTION / 3))  {
    lcd.print("Position        ");
    MENU = 1;
  }
  else if (MENU_SELECTOR < (RESOLUTION / 2))  {
    lcd.print("Couple          ");
    MENU = 2;
  }
  else if (MENU_SELECTOR < RESOLUTION)  {
    lcd.print("Vitesse         ");
    MENU = 3;
  }
  return MENU;
}

float resolution_set(float RESOLUTION)  {
  
  int RESOLUTION_SELECTOR = int(encoder0Pos) % 30;
  if (RESOLUTION_SELECTOR <  (30 / 5))  {
    lcd.setCursor(1, 6);
    lcd.cursor_on();
    RESOLUTION = 0.1;
  }
  else if (RESOLUTION_SELECTOR < (30 / 4))  {
    lcd.setCursor(1, 4);
    lcd.cursor_on();
    RESOLUTION = 1;
  }
  else if (RESOLUTION_SELECTOR < (30 / 3))  {
    lcd.setCursor(1, 3);
    lcd.cursor_on();
    RESOLUTION = 10;
  }
  else if (RESOLUTION_SELECTOR < (30 / 2))  {
    lcd.setCursor(1, 2);
    lcd.cursor_on();
    RESOLUTION = 100;
  }
  else if (RESOLUTION_SELECTOR < 30 / 1)  {
    lcd.setCursor(1, 2);
    lcd.cursor_on();
    RESOLUTION = 1000;
  }
  return RESOLUTION;
}

int menu_init(int MODE, int *CONTRASTE, int *POSITION, float *TORQUE, float *SPEED, float *encoder0Pos)  {
  switch (MODE) {
    case 0:
      *CONTRASTE = 5;
      *encoder0Pos = 20;
      break;
    case 1:
      *POSITION = 0;
      *encoder0Pos = 0;
       break;
    case 2:
      *TORQUE = 0;
      *encoder0Pos = 0;
      break;
    case 3:
      *SPEED = 0;
      *encoder0Pos = 0;
      break;
  }
}

/*################LCD PRINT################*/
int lcd_print_menu(int MODE, int *CONTRASTE, int *POSITION, float *TORQUE, float *SPEED, float *encoder0Pos)  {
  lcd.clear();
  switch (MODE) {
    case 0:
      lcd.print("Contraste Mode");
      lcd_print_contraste_value(*CONTRASTE);
      break;
    case 1:
      lcd.print("Position Mode");
      lcd_print_int_value(*POSITION);
       break;
    case 2:
      lcd.print("Couple Mode");
      lcd_print_float_value(*TORQUE);
      break;
    case 3:
      lcd.print("Speed Mode");
      lcd_print_float_value(*SPEED);
      break;
  }
}

void lcd_print_contraste_value(int CONTRASTE){
  lcd.setCursor(1,3);
  lcd.print("          ");
  lcd.setCursor(1,2);
  lcd.print ("-");
  for(int i=1; i<=CONTRASTE ; i++){
    lcd.print(char(0));
  }
  lcd.setCursor(1,13);
  lcd.print ("+");
}

void lcd_print_float_value(float value) {

  lcd.setCursor(1, 0);
  lcd.print("                ");
  lcd.setCursor(1, 0);
  if (value >= 0)  {
    lcd.print("+");
  }
  else  {
    lcd.print("-");
  }

  lcd.setCursor(1, 1);
  if (value == 0) {
    lcd.print("000");
  }
  else if (abs(value) < 1) {
    lcd.print("000");
  }
  else if (abs(value) < 10) {
    lcd.print("000");
  }
  else if (abs(value) < 100) {
    lcd.print("00");
  }
    else if (abs(value) < 1000) {
    lcd.print("0");
  }
  lcd.print(abs(value));
}

void lcd_print_int_value(int value) {
  lcd.setCursor(1, 0);
  lcd.print("                ");
  lcd.setCursor(1, 0);
  if (value >= 0)  {
    lcd.print("+");
  }
  lcd.print(value);
}

/*#############CONVERTER##########*/
void contraste_convert(int *CONTRASTE, int *F_contraste, float *encoder0Pos) {
  int resolution = 10;
  int sensibility = 4;
  int  value = *CONTRASTE;
  value = int(*encoder0Pos / sensibility );
  if (value >= 0 && value <= 10)  {
    *CONTRASTE = value;
    *F_contraste = int( 25.5 * value);
  }
  else if (value > 10)  {
    *encoder0Pos = resolution * sensibility;
  }
  else if (value < 0)  {
    *encoder0Pos = 0;
  }
}

void speed_convert(float *SPEED, float *encoder0Pos, float resolution)  {
  float value = *encoder0Pos * resolution;

  bool sens1 = digitalRead(DIRECTION_1);
  bool sens2 = digitalRead(DIRECTION_2);
  
  if ((sens1 == LOW) && (sens2 == HIGH))	{
	float value = *encoder0Pos * resolution;
  }
  else if ((sens1 == HIGH) && (sens2 == LOW))	{
	float value = *encoder0Pos * resolution * (-1);
  }
  
  if (value >= -4400 && value <= 4400) {
    *SPEED = value;
  }
  else if (value > 4400)  {
    *encoder0Pos = 4400 / resolution;
  }
  else if (value < -4400) {
    *encoder0Pos = 4400;
  }
}

void torque_convert(float *TORQUE, float *encoder0Pos, float resolution)  {
  float value = *encoder0Pos * resolution;
  if (value >= -4400 && value <= 4400) {
    *TORQUE = value;
  }
  else if (value > 4400)  {
    *encoder0Pos = 4400 / resolution;
  }
  else if (value < -4400) {
    *encoder0Pos = -4400 / resolution;
  }
}
