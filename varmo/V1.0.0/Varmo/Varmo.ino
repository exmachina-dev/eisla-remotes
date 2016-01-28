#include <Arduino.h>
#include <ST7036.h>
#include <Wire.h>
#include <protocol.h>
#include "./Varmo.h"



char *Get = "machine.get";
char *Set = "machine.set";
char *Alive = "machine.alive";

char *Speed_ref = "machine.velocity_ref";
char *Torque_ref = "machine.torque_ref";
char *Position_ref = "machine.position_ref";

char *Speed = "machine.velocity";
char *Torque = "machine.torque";

char *Position = "machine.position";
char *Pos_go = "machine.command.go";
char *Pos_Home = "machine.command.set_home";

char *Acceleration = "machine.acceleration";
char *Deceleration = "machine.deceleration";

char *Control_Mode = "machine.command.control_mode";

char *Device_serial_num = "machine.serialnumber";
char *Drive_Enable = "status.drive_enable";
char *Stop = "machine.command.cancel";

/*ENCODER*/
float encoder0Pos = 0;
float encoder0Pos_old = 0;

/*CONTRAST*/
int F_contrast = 0;

/*MENU*/
int MODE = 1;
int MODE_OLD = -1;

bool FLAG_MENU = 1;
bool FLAG_RESOLUTION = 0;
bool Mode_chosen = 0;
bool resolution_chosen = 0;

/*PARAMETERS*/
float SPEED_TARGET = 0;
float TORQUE_TARGET = 0;
float POSITION_TARGET = 0;
float HOME_POSITION_TARGET = 0;
float ACCELERATION_TARGET = 0;
float DECELERATION_TARGET = 0;
float POS_SPEED_TARGET = 0;

int CONTRAST = 5;

int CONTRAST_OLD = 5;

float SPEED_GET = 0;
float TORQUE_GET = 0;
float POSITION_GET = 0;
float HOME_POSITION_GET = 0;
float ACCELERATION_GET = 0;
float DECELERATION_GET = 0;
float POS_SPEED_GET = 0;

/*RESOLUTION*/
float RESOLUTION = 1;
float RESOLUTION_old = 1;

/*CUSTOM CHARACTER*/
const uint8_t charBitmap[][8] = {
  { 0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F },
};



/*SEND*/
bool send_button_push_old = HIGH;
bool send_state = LOW;
unsigned long lastDebounceTime = 0;  // the last time the output pin was toggled
unsigned long debounceDelay = 50;    // the debounce time; increase if the output flickers
bool SEND = LOW;

/*GET*/
bool stringComplete = false;
String data1 = "";
String data2 = "";
String data3 = "";
String confirm_key = "";
String SerialNumber_receipt;
String protocol_receipt;
byte incoming_buffer[10];
byte packets_buffer[150];
Packet new_packet;
int pac_buf_pos;
bool packet_complet;
int inc_buf_size;

/*LED STATUS*/
bool LED_1_STATUS;
bool LED_2_STATUS;

bool DRIVE_ENABLE;

/*TIME OUT*/
bool Serial_OK = true;
unsigned long time_out = 200;
unsigned long time_ping;
/*TIMER*/
unsigned long time_push = 0;
unsigned long refresh = 1000;
unsigned long last_refresh = 0;

bool flag = false;

bool MOTOR_OFF;
unsigned long timer_motor_off;
unsigned long timer_motor_off_send;
bool SENS = 1;

unsigned long refresh_set_home = 2000;


void setup() {

  pinMode(13, OUTPUT);
  //ENCODER INITIALISATION
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

  analogWrite(CONTRAST_PWM, 0);
  //LCD INITIALISATION
  lcd.init ();
  lcd.clear ();
  lcd.print("ExMachina");
  lcd.setCursor(1, 0);
  lcd.print(VARMO_VERSION);
  delay(3000);

  // Load Custom Character
  int charBitmapSize = (sizeof(charBitmap ) / sizeof (charBitmap[0]));
  // Load custom character set into CGRAM
  for (int i = 0; i < charBitmapSize; i++ )  {
    lcd.load_custom_character ( i, (uint8_t *)charBitmap[i] );
  }

  //SERIAL INITIALISATION


  lcd.clear ();
  lcd.print("Connexion...");
  time_ping = millis();

  Serial.begin(57600);
  Varmo.sendData(Get, Device_serial_num);
  delay(50);
  Varmo.sendData(Get, Device_serial_num);
}

void loop()
{
  while (Serial_OK) {
    delay(100);
    encoder0Pos_old = encoder0Pos;

    /*###############################MENU###############################*/
    int encoder_push = digitalRead(encoderE);
    if (encoder_push == LOW)  {

      encoder_push = digitalRead(encoderE);
      time_push = millis();
      Mode_chosen = 0;
      while (encoder_push != HIGH && Mode_chosen == 0)  {
        encoder_push = digitalRead(encoderE);
        if ((millis() - time_push)  > 500 )  {
          Mode_chosen = 1;
        }
      }

      if (Mode_chosen == 1)  {
        Mode_chosen = 0;
        encoder0Pos = MODE * 2;
        MODE = menu_set(MODE);
        while (encoder_push != HIGH)  {
          encoder_push = digitalRead(encoderE);
        }
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
        while (resolution_chosen == 0 && MODE != 4)  {
          if (MODE == MODE_POS) {
            RESOLUTION = resolution_set(RESOLUTION, 0, 4);
          }
          else if (MODE == MODE_POS_SPD){
            RESOLUTION = resolution_set(RESOLUTION, 0, 8);
          }
          else{
            RESOLUTION = resolution_set(RESOLUTION, 1, 5);
          }

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

    /*###########################GET DIRECTION###########################*/
    bool sens1 = digitalRead(DIRECTION_1);
    bool sens2 = digitalRead(DIRECTION_2);

    if (!(sens1 == HIGH) && (sens2 == HIGH))  {
      timer_motor_off = millis();
    }

    if ((sens1 == LOW) && (sens2 == HIGH)) {
      SENS = HIGH;
      MOTOR_OFF = false;
    }
    else if ((sens1 == HIGH) && (sens2 == LOW)) {
      SENS = LOW;
      MOTOR_OFF = false;
    }
    else if (millis() - timer_motor_off > 50 && MOTOR_OFF != HIGH) {
      timer_motor_off = millis();
      timer_motor_off_send = millis();
      MOTOR_OFF = true;
      Varmo.sendData(Set, Stop, true);    
    }

    /*###########################SET TARGET###########################*/
/*    
    if (MOTOR_OFF == true) {
      if ( (millis() - timer_motor_off_send) > refresh ) {
        timer_motor_off_send = millis();
        Varmo.sendData(Set, Stop, true);
      }      
    }
*/
    if (MOTOR_OFF == false || MODE == MODE_HOME || MODE == MODE_ACC || MODE == MODE_DEC)  {
      bool send_button_push = digitalRead(SEND_BUTTON);
      if (send_button_push != send_button_push_old) {
        lastDebounceTime = millis();
      }

      if ((millis() - lastDebounceTime) > debounceDelay) {
        if (send_button_push != send_state) {
          send_state = send_button_push;

          if (send_button_push == LOW)  {
            SEND = HIGH;
          }
        }
      }
      send_button_push_old = send_button_push;
    }

    if (SEND == HIGH) {
      SEND = LOW;
      switch (MODE)  {
        case MODE_POS :
          Varmo.sendData(Set, Position_ref, POSITION_TARGET);
          Varmo.sendData(Set, Pos_go, true);
          break;
        case MODE_POS_SPD:
          Varmo.sendData(Set, Speed_ref, POS_SPEED_TARGET);
          MODE = MODE_POS;
          FLAG_MENU = 1;
        case MODE_TRQ :
          Varmo.sendData(Set, Torque_ref, TORQUE_TARGET);
          break;
        case MODE_SPD :
          Varmo.sendData(Set, Speed_ref, SPEED_TARGET);
          break;
        case MODE_HOME :
          Varmo.sendData(Set, Pos_Home, true);
          lcd.setCursor(1,0);
          lcd.print("New home pos    ");
          refresh_set_home = millis();
          break;
        case MODE_ACC :
          Varmo.sendData(Set, Acceleration, ACCELERATION_TARGET);
          break;
        case MODE_DEC :
          Varmo.sendData(Set, Deceleration, DECELERATION_TARGET);
          break;

      }
    }

    /*###############################REFRESH MENU###############################*/
    if (FLAG_MENU == 1)  {
      lcd_print_menu(&MODE, CONTRAST, POSITION_TARGET, TORQUE_TARGET, SPEED_TARGET, HOME_POSITION_TARGET, ACCELERATION_TARGET, DECELERATION_TARGET, POS_SPEED_TARGET,
                     TORQUE_GET, SPEED_GET, POSITION_GET, HOME_POSITION_GET, ACCELERATION_GET, DECELERATION_GET, POS_SPEED_GET,encoder0Pos);
      menu_init(MODE, &CONTRAST, &POSITION_TARGET, &TORQUE_TARGET, &SPEED_TARGET, &HOME_POSITION_TARGET, 
                &ACCELERATION_TARGET, &DECELERATION_TARGET, &POS_SPEED_TARGET,&encoder0Pos, RESOLUTION);
        
      
      if (MODE_OLD == MODE)    {
        encoder0Pos = encoder0Pos_old;
      }
      else {
        MODE_OLD = MODE;
      }
      FLAG_MENU = 0;
    }

    if (FLAG_RESOLUTION == 1) {
      encoder0Pos = encoder0Pos_old * (RESOLUTION_old / RESOLUTION);
      FLAG_RESOLUTION = 0;
      lcd.cursor_off();
    }

    switch (MODE)  {
      /*case 0 :
        contrast_convert(&CONTRAST, &F_contrast, &encoder0Pos);
        if (CONTRAST != CONTRAST_OLD) {
          CONTRAST_OLD = CONTRAST;
          lcd_print_contrast_value(CONTRAST);
          analogWrite(CONTRAST_PWM, F_contrast);
        }
        break;*/
      case MODE_POS :
        converter_abs(&POSITION_TARGET, &encoder0Pos, RESOLUTION, 9999);
        lcd_print_pos(POSITION_GET, POSITION_TARGET, SPEED_GET);
        break;
      case MODE_POS_SPD :
        converter_abs(&POS_SPEED_TARGET, &encoder0Pos, RESOLUTION, 9999);
        lcd_print_vit_pos(POS_SPEED_GET, POS_SPEED_TARGET);
        break;
      case MODE_TRQ :
        converter(&TORQUE_TARGET, &encoder0Pos, RESOLUTION, SENS, 500);
        lcd_print_float_value(TORQUE_GET, TORQUE_TARGET);
        break;
      case MODE_SPD :
        converter(&SPEED_TARGET, &encoder0Pos, RESOLUTION, SENS,4400);
        lcd_print_float_value(SPEED_GET, SPEED_TARGET);
        break;
      case MODE_HOME :
        if ( (millis() - refresh_set_home) > refresh ) {
          refresh_set_home = millis();
          lcd.setCursor(1,0);
          lcd.print("                ");
        }
        break;
      case MODE_ACC :
        converter_abs(&ACCELERATION_TARGET, &encoder0Pos, RESOLUTION, 9999);
        lcd_print_float_value(ACCELERATION_GET, ACCELERATION_TARGET);
        break;
      case MODE_DEC :
        converter_abs(&DECELERATION_TARGET, &encoder0Pos, RESOLUTION, 9999);
        lcd_print_float_value(DECELERATION_GET, DECELERATION_TARGET);
        break;
    }

    /*###########################REFRESH LEDS###########################*/

/*    if (DRIVE_ENABLE == 1) {
      lcd.setCursor(0,15);
      lcd.print('d');
    }
    else {
      lcd.setCursor(0,15);
      lcd.print('n');
    }
    if (LED_2_STATUS == 1) {
      digitalWrite(13, HIGH);
    }
    else {
      digitalWrite(13, LOW);
    }*/
  }

}
/*##################ENCODER##################*/
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

/*##################MENU##################*/
int menu_set(int MENU)  {
  int RESOLUTION = 2;
  int MENU_SELECTOR = int(encoder0Pos);
  lcd.setCursor(0, 0);
  lcd.print("Menu            ");
  lcd.setCursor(1, 0);

  if (MENU_SELECTOR < 0){
    encoder0Pos = 0;
  }
  else if (MENU_SELECTOR > (RESOLUTION * 7)) {
    encoder0Pos = RESOLUTION * 7;
  }

  if (MENU_SELECTOR <= RESOLUTION )  {
    lcd.print("Position        ");
    MENU = MODE_POS;
  }
  else if (MENU_SELECTOR <= RESOLUTION * 2)  {
    lcd.print("Speed Position  ");
    MENU = MODE_POS_SPD;
  }
  else if (MENU_SELECTOR <= RESOLUTION * 3)  {
    lcd.print("Speed           ");
    MENU = MODE_SPD;
  }
  else if (MENU_SELECTOR <= RESOLUTION * 4) { 
    lcd.print("Torque          ");
    MENU = MODE_TRQ;
  }
  else if (MENU_SELECTOR <= RESOLUTION * 5) { 
    lcd.print("Set Home        ");
    MENU = MODE_HOME;
  }
  else if (MENU_SELECTOR <= RESOLUTION * 6) {
    lcd.print("Acceleration    ");
    MENU = MODE_ACC;
  }
  else if (MENU_SELECTOR <= RESOLUTION *7){
    lcd.print("Deceleration    ");
    MENU = MODE_DEC;
  }
  /*
  else if (MENU_SELECTOR <= RESOLUTION * 7)  {
    lcd.print("Contrast        ");
    MENU = 0;
  }*/
  return MENU;
}

float resolution_set(float RESOLUTION, bool format, int set_cursor)  {

  int RESOLUTION_SELECTOR = int(encoder0Pos);

  if (RESOLUTION_SELECTOR < 0) {
    encoder0Pos = 0;
  }
  else if (RESOLUTION_SELECTOR > 25){
    encoder0Pos = 25;
  }
  else if (format == 0 && RESOLUTION_SELECTOR > 20) {
    encoder0Pos = 20; 
  }

  if (RESOLUTION_SELECTOR <= 5)  {
    lcd.setCursor(1, set_cursor);
    lcd.cursor_on();
    RESOLUTION = 1000;
  }
  else if (RESOLUTION_SELECTOR <= 10)  {
    lcd.setCursor(1, set_cursor + 1);
    lcd.cursor_on();
    RESOLUTION = 100;
  }
  else if (RESOLUTION_SELECTOR <= 15)  {
    lcd.setCursor(1, set_cursor + 2);
    lcd.cursor_on();
    RESOLUTION = 10;
  }
  else if (RESOLUTION_SELECTOR <= 20)  {
    lcd.setCursor(1, set_cursor + 3);
    lcd.cursor_on();
    RESOLUTION = 1;
  }
  else if (RESOLUTION_SELECTOR <=  25 && format == 1)  {
    lcd.setCursor(1, set_cursor + 5);
    lcd.cursor_on();
    RESOLUTION = 0.1;
  }
  return RESOLUTION;
}

void menu_init(int MODE, int *CONTRAST, float *POSITION, float * TORQUE, float * SPEED, float *HOME_POSITION, float *ACCELERATION, float *DECELERATION, float *POS_SPEED, float * encoder0Pos, float resolution)  {
  switch (MODE) {
    /*case 0:
      *encoder0Pos = *CONTRAST * 4;
      break;*/
    case MODE_POS:
      *encoder0Pos = *POSITION;
      Varmo.sendData(Set, Control_Mode, (unsigned int)3);
      break;

    case MODE_TRQ:
      *encoder0Pos = *TORQUE / resolution;
      Varmo.sendData(Set, Control_Mode, (unsigned int)1);

      break;
    case MODE_SPD:
      *encoder0Pos = *SPEED / resolution;
      Varmo.sendData(Set, Control_Mode, (unsigned int)2);

      break;
    case MODE_HOME:
      break;
    case MODE_ACC:
      *encoder0Pos = *ACCELERATION / resolution;
      break;
    case MODE_DEC:
      *encoder0Pos = *DECELERATION / resolution;
      break;
    case MODE_POS_SPD :
      *encoder0Pos = *POS_SPEED /resolution;
      Varmo.sendData(Set, Control_Mode, (unsigned int)3);
  }
}

/*##################LCD PRINT##################*/

void lcd_print_menu(int *MODE, int CONTRAST, float POSITION, float TORQUE, float SPEED, float HOME_POSITION, float ACCELERATION, float DECELERATION, float POS_SPEED, 
                    float torque_get, float speed_get, float position_get, float home_position_get, float acceleration_get, float decelaration_get, float pos_speed_get, float encoder0Pos)  {
  lcd.clear();
  lcd.setCursor(0,0);
  switch (*MODE) {
    /*case 0:
      lcd.print("CONTRAST");
      lcd_print_contrast_value(CONTRAST);
      break;*/
    case MODE_POS:
      if (POS_SPEED == 0) {
        *MODE = MODE_POS_SPD;
        lcd.print("Spd:"); 
        lcd_print_abs_float_value(pos_speed_get, POS_SPEED);
      break;
      }
      else {  
        lcd.print("Spd:");
        lcd_print_pos(position_get, POSITION, SPEED);
        break;
      }
    case MODE_TRQ:
      lcd.print("Trq:");
      lcd_print_float_value(torque_get, TORQUE);
      break;
    case MODE_SPD:
      lcd.print("Spd:");
      lcd_print_float_value(speed_get, SPEED);
      break;
    case MODE_HOME:
      lcd.print("Set Home:");
      break;
    case MODE_ACC:
      lcd.print("Acc:");
      lcd_print_abs_float_value(acceleration_get, ACCELERATION);
      break;
    case MODE_DEC:
      lcd.print("Dec:");
      lcd_print_abs_float_value(decelaration_get, DECELERATION);
      break;
    case MODE_POS_SPD:
      lcd.print("Spd:"); 
      lcd_print_abs_float_value(pos_speed_get, POS_SPEED);
      break;
  }
}

void lcd_print_contrast_value(int CONTRAST) {
  lcd.setCursor(1, 3);
  lcd.print("          ");
  lcd.setCursor(1, 2);
  lcd.print ("-");
  for (int i = 1; i <= CONTRAST ; i++) {
    lcd.print(char(0));
  }
  lcd.setCursor(1, 13);
  lcd.print ("+");
}

void lcd_print_sign(float value)  {
  if (value >= 0)  {
    lcd.print("+");
  }
  else  {
    lcd.print("-");
  } 
}

void lcd_print_float_align_right(float value)  {
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

void lcd_print_int_align_right(int value)  {
  if (value == 0) {
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

void lcd_print_float_value(float value1, float value2) {
  lcd.setCursor(0, 4);
  lcd_print_sign(value1);
  lcd_print_float_align_right(value1);

  lcd.setCursor(1, 0);
  lcd.setCursor(1, 0);
  lcd.print("Tgt:");
  lcd_print_sign(value2);

  lcd_print_float_align_right(value2);
}

void lcd_print_abs_float_value(float value1, float value2) {
  lcd.setCursor(0, 4);
  lcd_print_float_align_right(value1);

  lcd.setCursor(1, 0);
  lcd.setCursor(1, 0);
  lcd.print("Tgt:");
  lcd_print_sign(value2);

  lcd_print_float_align_right(value2);
}

void lcd_print_vit_pos(float value1, float value2) {
  lcd.setCursor(0,4);
  lcd_print_float_align_right(value1);

  lcd.setCursor(1,0);
  lcd.print("Spd Pos:");
  lcd.setCursor(1,8);
  lcd_print_int_align_right(int(value2));

}

void lcd_print_pos(float value1, float value2, float value3) {
  lcd.setCursor(0,4);
  lcd_print_float_align_right(value3);

  lcd.setCursor(1,0);
  lcd.print("Tgt:");
  lcd.setCursor(1,4);
  lcd_print_int_align_right(int(value2));

  lcd.setCursor(1,9);
  lcd.print("Ps:");
  lcd.setCursor(1,12);
  lcd_print_int_align_right(int(value1));
}

/*##################CONVERTER##################*/
void contrast_convert(int *CONTRAST, int *F_contrast, float * encoder0Pos) {
  int resolution = 10;
  int sensibility = 4;
  int  value = *CONTRAST;
  value = int(*encoder0Pos / sensibility );
  if (value >= 0 && value <= 10)  {
    *CONTRAST = value;
    *F_contrast = int( 25.5 * value);
  }
  else if (value > 10)  {
    *encoder0Pos = resolution * sensibility;
  }
  else if (value < 0)  {
    *encoder0Pos = 0;
  }
}

void converter(float *value, float *encoder0Pos, float resolution, bool sens, float max){
  float temp = *encoder0Pos * resolution;
  if (temp > 0 && temp < max) {
    if (sens == HIGH)  {
      *value = temp;
    }
    else if (sens == LOW)  {
      *value = (-1) * temp;
    }
  }
  else if (temp >= max)  {
    if (sens == HIGH)  {
      *value = max;
    }
    else if (sens == LOW)  {
      *value = (-1) * max;
    }
    *encoder0Pos = max / resolution;
  }
  else if (temp <= 0) {
    *value = 0;
    *encoder0Pos = 0;
  }
}

void converter_abs(float *value, float *encoder0Pos, float resolution, float max){
  float temp = *encoder0Pos * resolution;
  if (temp > 0 && temp < max) {
    *value = temp;
  }
  else if (temp >= max)  {
    *value = max;
    *encoder0Pos = max / resolution;
  }
  else if (temp <= 0) {
    *value = 0;
    *encoder0Pos = 0;
  }
}
