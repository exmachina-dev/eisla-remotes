#include <Arduino.h>
#include "ST7036.h"
#include <Wire.h>

ST7036 lcd = ST7036 ( 2, 16, 0x78 );

/*ENCODER*/
#define encoder0PinA 2

#define encoder0PinB 3

int encoder0Pos = 0;
int encoder0Pos_old = 0;

#define encoderE 4

/*CONTRASTE*/
#define CONTRASTE_PWM 5

int F_contraste = 0;

/*MENU*/
int MODE = 0;
int MODE_OLD = -1;

bool FLAG_MENU = 1;
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

//Resolution
float RESOLUTION = 1;

/*Serial Send*/
String Protocol = "ExmEisla";
String SerialNumber = "012016001VARMO";

String Speed_Par = "Set_Speed_Target";
String Torque_Par = "Set_Torque_Target";
String Position_Par = "Set_Position_Target";

//Custon Character
const uint8_t charBitmap[][8] = {
   { 0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F },
};

void setup() {

  pinMode(encoder0PinA, INPUT);
  pinMode(encoder0PinB, INPUT);

  // encoder pin on interrupt 0 (pin 2)
  attachInterrupt(0, doEncoderA, CHANGE);
  // encoder pin on interrupt 1 (pin 3)
  attachInterrupt(1, doEncoderB, CHANGE);

  pinMode(encoderE, INPUT);

  lcd.init ();
  lcd.clear ();
  lcd.print("ExMachina");
  lcd.setCursor(1, 0);
  lcd.print("Varmo Rev 0.2");
  delay(1000);

  // Load Custom Character
  int charBitmapSize = (sizeof(charBitmap ) / sizeof (charBitmap[0]));
  // Load custom character set into CGRAM
   for (int i = 0; i < charBitmapSize; i++ )
   {
      lcd.load_custom_character ( i, (uint8_t *)charBitmap[i] );
   }
 
  Serial.begin(115200);

}

void loop()
{
  encoder0Pos_old = encoder0Pos;
  
  int encoder_push = digitalRead(encoderE);
  if (encoder_push == LOW)  {
    encoder_push = digitalRead(encoderE);
    
    while (encoder_push != HIGH)  {
      encoder_push = digitalRead(encoderE);
    }
    
    Mode_chosen = 0;
    while (Mode_chosen == 0) {
      MODE = menu(MODE);
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
  
  if (FLAG_MENU == 1)  {
    lcd_print_menu(MODE, &CONTRASTE, &POSITION, &TORQUE, &SPEED,&encoder0Pos);
    if (MODE_OLD != MODE)    {
      menu_init(MODE, &CONTRASTE, &POSITION, &TORQUE, &SPEED,&encoder0Pos);
      MODE_OLD = MODE;
    }
    else    {
      encoder0Pos = encoder0Pos_old;
    }
    FLAG_MENU = 0;
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
        //send_data(Position_Par, POSITION);
        POSITION_OLD = POSITION;
      }
      break;
    case 2 :
      torque_convert(&TORQUE, &encoder0Pos, RESOLUTION);
      if (TORQUE != TORQUE_OLD) {
        lcd_print_float_value(TORQUE);
        //send_data(Torque_Par, TORQUE);
        TORQUE_OLD = TORQUE;
      }
      break;
    case 3 :
      speed_convert(&SPEED, &encoder0Pos, RESOLUTION);
      if (SPEED != SPEED_OLD) {
        lcd_print_float_value(SPEED);
        //send_data(Speed_Par, SPEED);
        SPEED_OLD = SPEED;
      }
      break;
  }
}

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

int menu(int MENU)  {
  int RESOLUTION = 12;
  int MENU_SELECTOR = encoder0Pos % RESOLUTION;
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

int resolution_set(int RESOLUTION)  {
  int RESOLUTION_SELECTOR = encoder0Pos % 16;
  
  if (RESOLUTION_SELECTOR <  (16 / 4))  {
    lcd.setCursor(1, 6);
    lcd.cursor_on();
    RESOLUTION = 0.1;
  }
  else if (RESOLUTION_SELECTOR < (16 / 3))  {
    lcd.setCursor(1, 4);
    lcd.cursor_on();
    RESOLUTION = 1;
  }
  else if (RESOLUTION_SELECTOR < (16 / 2))  {
    lcd.setCursor(1, 3);
    lcd.cursor_on();
    RESOLUTION = 10;
  }
  else if (RESOLUTION_SELECTOR < 16)  {
    lcd.setCursor(1, 2);
    lcd.cursor_on();
    RESOLUTION = 100;
  }
  return RESOLUTION;
}

int lcd_print_menu(int MODE, int *CONTRASTE, int *POSITION, float *TORQUE, float *SPEED, int *encoder0Pos)  {
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

int menu_init(int MODE, int *CONTRASTE, int *POSITION, float *TORQUE, float *SPEED, int *encoder0Pos)  {
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

void lcd_print_contraste_value(int CONTRASTE){
  lcd.setCursor(1,3);
  lcd.print("          ");
  lcd.setCursor(1,2);
  lcd.print ( "-");
  for(int i=1; i<=CONTRASTE ; i++){
    lcd.print(char(0));
  }
  lcd.setCursor(1,13);
  lcd.print ( "+");
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
    lcd.print("0000.");
  }
  else if (abs(value) < 10) {
    lcd.print("000");
  }
  else if (abs(value) < 100) {
    lcd.print("00");
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

void contraste_convert(int *CONTRASTE, int *F_contraste, int *encoder0Pos) {
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

void speed_convert(float *SPEED, int *encoder0Pos, float resolution)  {
  float value = *encoder0Pos * resolution;
  if (value > -4400 && value < 4400) {
    *SPEED = value;
  }
  else if (value > 4400)  {
    *encoder0Pos = 4400 / resolution;
  }
  else if (value < -4400) {
    *encoder0Pos = -4400 / resolution;
  }
}


void torque_convert(float *TORQUE, int *encoder0Pos, float resolution)  {
  float value = *encoder0Pos * resolution;
  if (value > -4400 && value < 4400) {
    *TORQUE = value;
  }
  else if (value > 4400)  {
    *encoder0Pos = 4400 / resolution;
  }
  else if (value < -4400) {
    *encoder0Pos = -4400 / resolution;
  }
}

void send_data(String parameter, float value)
{
  String to_send = Protocol + SerialNumber + parameter + ":" + String(value) + "\r\n";
  Serial.print(to_send);
}

