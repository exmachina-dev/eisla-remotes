#include <Arduino.h>
#include "ST7036.h"
#include <Wire.h>
#include <protocol.h>
#include "./Varmo.h"


/*ENCODER*/
float encoder0Pos = 0;
float encoder0Pos_old = 0;

/*CONTRAST*/
int F_contrast = 0;

/*MENU*/
int MODE = 3;
int MODE_OLD = -1;

bool FLAG_MENU = 1;
bool FLAG_RESOLUTION = 0;
bool Mode_chosen = 0;
bool resolution_chosen = 0;

/*PARAMETERS*/
float SPEED_TARGET = 0;
float TORQUE_TARGET = 0;
signed int POSITION_TARGET = 0;
int CONTRAST = 0;

signed int CONTRAST_OLD = 0;

float SPEED_GET = 0;
float TORQUE_GET = 0;
signed int POSITION_GET = 0;

/*RESOLUTION*/
float RESOLUTION = 1;
float RESOLUTION_old = 1;

/*CUSTOM CHARACTER*/
const uint8_t charBitmap[][8] = {
  { 0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F },
};

/*TIMER*/
unsigned long time_push = 0;
unsigned long refresh = 500;
unsigned long last_refresh = 0;

/*SEND*/
bool send_button_push_old = LOW;
bool send_state = HIGH;
long lastDebounceTime = 0;  // the last time the output pin was toggled
long debounceDelay = 50;    // the debounce time; increase if the output flickers
bool SEND = LOW;

/*GET*/
String inputString = "";
boolean stringComplete = false;
String data1 = "";
String data2_string = "";
float data2_float = 0;
String SerialNumber_receipt;
String protocol_receipt;
float actual_speed;

/*LED STATUS*/
bool LED_1_STATUS;
bool LED_2_STATUS;

/*TIME OUT*/
bool Serial_OK = 1;
long time_out = 500;
long time_ping;

bool flag = false;

char inChar_old;

void setup() {

  pinMode(13, OUTPUT);
  /*ENCODER INITIALISATION*/
  pinMode(encoder0PinA, INPUT);
  pinMode(encoder0PinB, INPUT);

  // encoder pin on interrupt 0 (pin 2)
  attachInterrupt(0, doEncoderA, CHANGE);
  // encoder pin on interrupt 1 (pin 3)
  attachInterrupt(1, doEncoderB, CHANGE);

  pinMode(encoderE, INPUT);

  pinMode(SEND_BUTTON, INPUT_PULLUP);

  pinMode(LED_1, OUTPUT);
  pinMode(LED_2, OUTPUT);

  pinMode(DIRECTION_1, INPUT);
  pinMode(DIRECTION_2, INPUT);

  /*LCD INITIALISATION*/
  lcd.init ();
  lcd.clear ();
  lcd.print("ExMachina");
  lcd.setCursor(1, 0);
  lcd.print(VARMO_VERSION);
  delay(1000);

  // Load Custom Character
  int charBitmapSize = (sizeof(charBitmap ) / sizeof (charBitmap[0]));
  // Load custom character set into CGRAM
  for (int i = 0; i < charBitmapSize; i++ )  {
    lcd.load_custom_character ( i, (uint8_t *)charBitmap[i] );
  }

  /*SERIAL INITIALISATION*/
  Serial.begin(115200);

  lcd.clear ();
  lcd.print("Initialisation");
  time_ping = millis();
  while (flag == false) {
    serialEvent();
    if (stringComplete == true) {
      serial_analyse_string(inputString, &protocol_receipt, &SerialNumber_receipt, &data1, &data2_string);
      Serial.print(data1);
      if ((protocol_receipt == PROTOCOL) && (SerialNumber_receipt.substring(4, 8) == ARMAZ_ID)) {

        if (data1 == ALIVE) {

          flag = true;
        }
      }
      inputString = "";
      stringComplete = false;

    }
  }
  flag = false;
  Varmo.sendAlivePing();
}

void loop()
{


  if (Serial_OK == false) {
    Varmo.getAlivePing();
    flag = false;
    while (flag == false) {
      serialEvent();
      if (stringComplete == true) {
        serial_analyse_string(inputString, &protocol_receipt, &SerialNumber_receipt, &data1, &data2_string);
        if ((protocol_receipt == PROTOCOL) && (SerialNumber_receipt.substring(4, 8) == ARMAZ_ID)) {
          if ((data1 == ALIVE) && (data2_string == CONFIRM_KEY_WORD)) {
            flag = true;
          }
        }
        inputString = "";
        stringComplete = false;
      }
    }
    flag = false;
    Serial_OK = true;
  }

  while (Serial_OK) {
    encoder0Pos_old = encoder0Pos;
    /*###############################MENU###############################*/
    int encoder_push = digitalRead(encoderE);
    if (encoder_push == LOW)  {
      encoder_push = digitalRead(encoderE);
      time_push = millis();
      while (encoder_push != HIGH)  {
        encoder_push = digitalRead(encoderE);
      }

      if (((millis() - time_push)  > 250 ) || (MODE == 0) || (MODE == 1) )   {
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
    /*###############################MENU###############################*/
    if (FLAG_MENU == 1)  {
      lcd_print_menu(MODE, CONTRAST, POSITION_TARGET, TORQUE_TARGET, SPEED_TARGET, TORQUE_GET, SPEED_GET, POSITION_GET, encoder0Pos);
      if (MODE_OLD != MODE)    {
        menu_init(MODE, &CONTRAST, &POSITION_TARGET, &TORQUE_TARGET, &SPEED_TARGET, &encoder0Pos);
        MODE_OLD = MODE;
      }
      else    {
        encoder0Pos = encoder0Pos_old;
      }
      FLAG_MENU = 0;
    }

    if (FLAG_RESOLUTION == 1) {
      encoder0Pos = encoder0Pos_old * (RESOLUTION_old / RESOLUTION);
      FLAG_RESOLUTION = 0;
      lcd.cursor_off();
    }

    switch (MODE)  {
      case 0 :
        contrast_convert(&CONTRAST, &F_contrast, &encoder0Pos);
        if (CONTRAST != CONTRAST_OLD) {
          CONTRAST_OLD = CONTRAST;
          lcd_print_contrast_value(CONTRAST);
          analogWrite(CONTRAST_PWM, F_contrast);
        }
        break;
      case 1 :
        POSITION_TARGET = encoder0Pos;
        lcd_print_int_value(POSITION_GET, POSITION_TARGET);
        break;
      case 2 :
        torque_convert(&TORQUE_TARGET, &encoder0Pos, RESOLUTION);
        lcd_print_float_value(TORQUE_GET, TORQUE_TARGET);
        break;
      case 3 :
        speed_convert(&SPEED_TARGET, &encoder0Pos, RESOLUTION);
        lcd_print_float_value(SPEED_GET, SPEED_TARGET);
        break;
    }

    /*###########################SET TARGET###########################*/
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

    if (SEND == HIGH) {
      SEND = LOW;
      switch (MODE)  {
        case 1 :
          Varmo.sendData(Set_Position, String(POSITION_TARGET));
          time_ping = millis();
          while (flag == false) {
            serialEvent();
            if ((millis() - time_ping) > time_out) {
              Serial_OK = false;
              flag = true;
            }

            if (stringComplete == true) {
              serial_analyse_string(inputString, &protocol_receipt, &SerialNumber_receipt, &data1, &data2_string);
              if ((protocol_receipt == PROTOCOL) && (SerialNumber_receipt.substring(4, 8) == ARMAZ_ID)) {
                if ((data1 == Set_Position) && (data2_string == CONFIRM_KEY_WORD)) {
                  flag = true;
                }
              }
              inputString = "";
              stringComplete = false;
            }
          }
          flag = false;
          break;
        case 2 :
          Varmo.sendData(Set_Torque, String(TORQUE_TARGET));
          time_ping = millis();
          while (flag == false) {
            serialEvent();
            if ((millis() - time_ping) > time_out) {
              Serial_OK = false;
              flag = true;
            }

            serialEvent();
            if (stringComplete == true) {
              serial_analyse_string(inputString, &protocol_receipt, &SerialNumber_receipt, &data1, &data2_string);
              if ((protocol_receipt == PROTOCOL) && (SerialNumber_receipt.substring(4, 8) == ARMAZ_ID)) {
                if ((data1 == Set_Torque) && (data2_string == CONFIRM_KEY_WORD)) {
                  flag = true;
                }
              }
              inputString = "";
              stringComplete = false;
            }
          }
          flag = false;
          break;
        case 3 :
          Varmo.sendData(Set_Speed, String(SPEED_TARGET));
          time_ping = millis();
          while (flag == false) {
            serialEvent();
            if ((millis() - time_ping) > time_out) {
              Serial_OK = false;
              flag = true;
            }
            serialEvent();
            if (stringComplete == true) {
              serial_analyse_string(inputString, &protocol_receipt, &SerialNumber_receipt, &data1, &data2_string);

              if ((protocol_receipt == PROTOCOL) && (SerialNumber_receipt.substring(4, 8) == ARMAZ_ID)) {
                if ((data1 == Set_Speed) && (data2_string == CONFIRM_KEY_WORD)) {
                  flag = true;
                }
              }
              inputString = "";
              stringComplete = false;
            }
          }
          flag = false;
          break;
      }

    }
    /*###########################GET VALUE###########################*/

    if ( (millis() - last_refresh) > refresh ) {
      last_refresh = millis();

      switch (MODE)  {
        case 1 :
          Varmo.getData(Get_Position);
          time_ping = millis();
          while (flag == false) {
            serialEvent();
            if ((millis() - time_ping) > time_out) {
              Serial_OK = false;
              flag = true;
            }

            serialEvent();
            if (stringComplete == true) {
              serial_analyse_float(inputString, &protocol_receipt, &SerialNumber_receipt, &data1, &data2_float);
              if ((protocol_receipt == PROTOCOL) && (SerialNumber_receipt.substring(4, 8) == ARMAZ_ID)) {
                if (data1 == Get_Position) {
                  POSITION_GET = (int) data2_float;
                }
                flag = true;
              }
              inputString = "";
              stringComplete = false;
            }
          }
          flag = false;
          break;
        case 2 :
          Varmo.getData(Get_Torque);
          time_ping = millis();
          while (flag == false) {
            serialEvent();
            if ((millis() - time_ping) > time_out) {
              Serial_OK = false;
              flag = true;
            }

            serialEvent();
            if (stringComplete == true) {
              serial_analyse_float(inputString, &protocol_receipt, &SerialNumber_receipt, &data1, &data2_float);
              if ((protocol_receipt == PROTOCOL) && (SerialNumber_receipt.substring(4, 8) == ARMAZ_ID)) {
                if (data1 == Get_Torque) {
                  TORQUE_GET = data2_float;
                }
                flag = true;
              }
              inputString = "";
              stringComplete = false;
            }
          }
          flag = false;
          break;
        case 3 :
          Varmo.getData(Get_Speed);
          time_ping = millis();
          while (flag == false) {
            serialEvent();
            if ((millis() - time_ping) > time_out) {
              Serial_OK = false;
              flag = true;
            }

            serialEvent();
            if (stringComplete == true) {
              serial_analyse_float(inputString, &protocol_receipt, &SerialNumber_receipt, &data1, &data2_float);
              if ((protocol_receipt == PROTOCOL) && (SerialNumber_receipt.substring(4, 8) == ARMAZ_ID)) {
                if (data1 == Get_Speed) {
                  SPEED_GET = data2_float;
                  Serial.println(SPEED_GET);
                }
                flag = true;
              }
              inputString = "";
              stringComplete = false;
            }
          }
          flag = false;
          break;
      }


      Varmo.getData(Get_Drive_Enable);
      time_ping = millis();
      while (flag == false) {
        serialEvent();
        if ((millis() - time_ping) > time_out) {
          Serial_OK = false;
          flag = true;
        }

        serialEvent();
        if (stringComplete == true) {
          serial_analyse_string(inputString, &protocol_receipt, &SerialNumber_receipt, &data1, &data2_string);
          if ((protocol_receipt == PROTOCOL) && (SerialNumber_receipt.substring(4, 8) == ARMAZ_ID)) {
            if (data1 == Get_Drive_Enable) {
              if (data2_string == "HIGH") {
                LED_1_STATUS = HIGH;
              }
              else if (data2_string == "LOW") {
                LED_1_STATUS = LOW;
              }
            }
            flag = true;
          }
          inputString = "";
          stringComplete = false;
        }
      }
      flag = false;
      Varmo.getData(Get_Motor);
      time_ping = millis();
      while (flag == false) {
        serialEvent();
        if ((millis() - time_ping) > time_out) {
          Serial_OK = false;
          flag = true;
        }
        serialEvent();
        if (stringComplete == true) {
          serial_analyse_string(inputString, &protocol_receipt, &SerialNumber_receipt, &data1, &data2_string);
          if ((protocol_receipt == PROTOCOL) && (SerialNumber_receipt.substring(4, 8) == ARMAZ_ID)) {
            if (data1 == Get_Motor) {
              if (data2_string == "HIGH") {
                LED_2_STATUS = HIGH;
              }
              else if (data2_string == "LOW") {
                LED_2_STATUS = LOW;
              }
            }
            flag = true;
          }
          inputString = "";
          stringComplete = false;
        }
      }
      flag = false;
    }

    /*###########################LED STATUS###########################*/

    if (LED_1_STATUS == 1) {
      digitalWrite(LED_1, HIGH);
    }
    else {
      digitalWrite(LED_1, LOW);
    }
    if (LED_2_STATUS == 1) {
      digitalWrite(LED_2, HIGH);
    }
    else {
      digitalWrite(LED_2, LOW);
    }
  }

}

/*##################SERIAL##################*/
void serialEvent() {

  while (Serial.available()) {
    // get the new byte:
    char inChar = (char)Serial.read();
    // add it to the inputString:
    inputString += inChar;
    // if the incoming character is a newline, set a flag
    // so the main loop can do something about it:
    if ((inChar_old == '\r') && (inChar == '\n')) {
      stringComplete = true;
    }

    inChar_old = inChar;
  }
}

void serial_analyse_float(String inputString, String * protocol, String * serial_num, String * data1, float * data2) {
  char chara;
  String temp = "";
  *protocol = inputString.substring(0, 8);
  *serial_num = inputString.substring(8, 20);
  *data1 = "";
  chara = inputString[20];
  int i = 20;
  while (!(chara == ':' || chara == '\r')) {
    *data1 += chara;
    i += 1;
    chara = inputString[i];
  }
  if (chara != '\r')  {
    i += 1;
    chara = inputString[i];
    while (chara != '\r')  {
      temp += chara;
      i += 1;
      chara = inputString[i];
    }
    *data2 = temp.toFloat();
  }
}

/*

  ExmEisla0116ARCP0001alive
  ExmEisla0116ARCP0001alive:ok
  ExmEisla0116ARCP0001get.speed:595

*/
void serial_analyse_string(String inputString, String * protocol, String * serial_num, String * data1, String * data2_string) {
  char chara;
  String temp = "";
  *protocol = inputString.substring(0, 8);
  *serial_num = inputString.substring(8, 20);
  *data1 = "";
  int i = 20;
  chara = inputString[20];
  while (!(chara == ':' || chara == '\r')) {
    *data1 += chara;
    i += 1;
    chara = inputString[i];
  }
  if (chara != '\r')  {
    i += 1;
    chara = inputString[i];
    while (chara != '\r')  {
      temp += chara;
      i += 1;
      chara = inputString[i];
    }
    *data2_string = temp.substring(0, temp.length());
  }
  else {
    *data2_string = "";
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
  int RESOLUTION = 12;
  int MENU_SELECTOR = int(encoder0Pos) % RESOLUTION;
  lcd.setCursor(0, 0);
  lcd.print("Menu            ");
  lcd.setCursor(1, 0);
  if (MENU_SELECTOR <  (RESOLUTION / 4))  {
    lcd.print("Contrast        ");
    MENU = 0;
  }
  else if (MENU_SELECTOR < (RESOLUTION / 3))  {
    lcd.print("Position        ");
    MENU = 1;
  }
  else if (MENU_SELECTOR < (RESOLUTION / 2))  {
    lcd.print("Torque          ");
    MENU = 2;
  }
  else if (MENU_SELECTOR < RESOLUTION)  {
    lcd.print("Speed           ");
    MENU = 3;
  }
  return MENU;
}

float resolution_set(float RESOLUTION)  {

  int RESOLUTION_SELECTOR = int(encoder0Pos) % 30;
  if (RESOLUTION_SELECTOR <  (30 / 5))  {
    lcd.setCursor(1, 14);
    lcd.cursor_on();
    RESOLUTION = 0.1;
  }
  else if (RESOLUTION_SELECTOR < (30 / 4))  {
    lcd.setCursor(1, 12);
    lcd.cursor_on();
    RESOLUTION = 1;
  }
  else if (RESOLUTION_SELECTOR < (30 / 3))  {
    lcd.setCursor(1, 11);
    lcd.cursor_on();
    RESOLUTION = 10;
  }
  else if (RESOLUTION_SELECTOR < (30 / 2))  {
    lcd.setCursor(1, 10);
    lcd.cursor_on();
    RESOLUTION = 100;
  }
  else if (RESOLUTION_SELECTOR < 30 / 1)  {
    lcd.setCursor(1, 9);
    lcd.cursor_on();
    RESOLUTION = 1000;
  }
  return RESOLUTION;
}

void menu_init(int MODE, int *CONTRAST, int *POSITION, float * TORQUE, float * SPEED, float * encoder0Pos)  {
  switch (MODE) {
    case 0:
      *CONTRAST = 5;
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

/*##################LCD PRINT##################*/
void lcd_print_menu(int MODE, int CONTRAST, int POSITION, float TORQUE, float SPEED, float torque_get, float speed_get, float position_get, float encoder0Pos)  {
  lcd.clear();
  switch (MODE) {
    case 0:
      lcd.print("Contrast        ");
      lcd_print_contrast_value(CONTRAST);
      break;
    case 1:
      lcd.print("Position:       ");
      lcd_print_int_value(position_get, POSITION);
      break;
    case 2:
      lcd.print("Torque:         ");
      lcd_print_float_value(torque_get, TORQUE);
      break;
    case 3:
      lcd.print("Speed:          ");
      lcd_print_float_value(speed_get, SPEED);
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

void lcd_print_float_value(float value1, float value2) {
  lcd.setCursor(0, 8);
  lcd_print_sign(value1);
  lcd_print_float_align_right(value1);

  lcd.setCursor(1, 0);
  lcd.setCursor(1, 0);
  lcd.print("Target: ");
  lcd_print_sign(value2);

  lcd_print_float_align_right(value2);
}

void lcd_print_int_value(int value1, int value2) {
  lcd.setCursor(0, 11);
  lcd_print_sign(value1);
  lcd_print_int_align_right(value1);

  lcd.setCursor(1, 0);
  lcd.setCursor(1, 0);
  lcd.print("Target: ");
  lcd.setCursor(1, 11);
  lcd_print_sign(value2);
  lcd_print_int_align_right(value2);
  lcd.print(value2);
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

void speed_convert(float * SPEED, float * encoder0Pos, float resolution)  {
  bool SENS;
  float value = *encoder0Pos * resolution;

  bool sens1 = digitalRead(DIRECTION_1);
  bool sens2 = digitalRead(DIRECTION_2);


  if ((sens1 == LOW) && (sens2 == HIGH))	{
    SENS = HIGH;
  }
  else if ((sens1 == HIGH) && (sens2 == LOW))	{
    SENS = LOW;
  }
  if (value >= 0 && value <= 4400) {
    if (SENS == HIGH)  {
      *SPEED = value;
    }
    else if (SENS == LOW)  {
      *SPEED = (-1) * value;
    }
  }
  else if (value > 4400)  {
    *encoder0Pos = 4400 / resolution;
  }
  else if (value < 0) {
    *encoder0Pos = 0;
  }


}

void torque_convert(float * TORQUE, float * encoder0Pos, float resolution)  {
  float value = *encoder0Pos * resolution;
  if (value >= -500 && value <= 500) {
    *TORQUE = value;
  }
  else if (value > 500)  {
    *encoder0Pos = 500 / resolution;
  }
  else if (value < -500) {
    *encoder0Pos = -500 / resolution;
  }
}
