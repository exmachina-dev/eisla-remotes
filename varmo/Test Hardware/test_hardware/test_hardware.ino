/*

*/

#include <Arduino.h>
#include <Wire.h>
#include "ST7036.h"
ST7036 lcd = ST7036 ( 2, 16, 0x78 );

/*ENCODER*/
#define encoder0PinA 2
#define encoder0PinB 3
#define encoderE 4
float encoder0Pos = 0;

/*LED*/
#define LED_1 A0
#define LED_2 A1

/*DIRECTION*/
#define DIRECTION_1 8
#define DIRECTION_2 9

/*SEND_BUTTON*/
#define SEND_BUTTON 10

/*SAVE BUTTON */
#define SAVE_BUTTON A6

void setup() {
  /*ENCODER INITIALISATION*/
  pinMode(encoder0PinA, INPUT);
  pinMode(encoder0PinB, INPUT);

  attachInterrupt(0, doEncoderA, CHANGE);
  attachInterrupt(1, doEncoderB, CHANGE);

  pinMode(encoderE, INPUT);

  pinMode(LED_1, OUTPUT);
  pinMode(LED_2, OUTPUT);

  pinMode(DIRECTION_1, INPUT);
  pinMode(DIRECTION_2, INPUT);
  pinMode(SEND_BUTTON , INPUT);
  lcd.init ();
  lcd.clear ();
  lcd.print("LCD screen work");
  delay(3000);

  Serial.begin(57600);

}

void loop() {
  lcd.print("Test encoder");
  delay(1000);

  bool encoder_push  = digitalRead(encoderE);
  while (encoder_push != HIGH){
    test_encoder();
  encoder_push = digitalRead(encoderE);
  }

  lcd.print("Test send button");
  delay(1000);

  while (encoder_push != HIGH){
    test_button(SEND_BUTTON);
  encoder_push = digitalRead(encoderE);
  }

  lcd.print("Test save button");
  delay(1000);

  while (encoder_push != HIGH){
    test_button_analog(SAVE_BUTTON);
  encoder_push = digitalRead(encoderE);
  }

  lcd.print("Test save button");
  delay(1000);

  while (encoder_push != HIGH){
    test_button_analog(SAVE_BUTTON);
  encoder_push = digitalRead(encoderE);
  }

  lcd.print("Test LED");
  delay(1000);

  while (encoder_push != HIGH){
    test_LED(LED_1);
  test_LED(LED_2);
  encoder_push = digitalRead(encoderE);
  }

  lcd.print("Test direction");
  delay(1000);

  bool sens1 = digitalRead(DIRECTION_1);
  bool sens2 = digitalRead(DIRECTION_2);
  bool SENS;
  if ((sens1 == LOW) && (sens2 == HIGH)) {
    SENS = HIGH;
  }
  else if ((sens1 == HIGH) && (sens2 == LOW)) {
    SENS = LOW;
  }

  delay(100);

}

void test_button_analog(int button){
  bool save_button_push;
  if (analogRead(SAVE_BUTTON) > 127){
    save_button_push = true;
    lcd.print("SAVE = 1");
  }
  else {
    lcd.setCursor(1,0);
  lcd.print("SAVE = 0");
  save_button_push = false;
  }
}

void test_button(int button)  {
  if (digitalRead(button) == HIGH){
    lcd.setCursor(1,0);
  lcd.print("SEND = 1");
  }
  else if (digitalRead(button) == LOW){
    lcd.setCursor(1,0);
  lcd.print("SEND = 0");
  }
}

void test_LED(int LED) {
  digitalWrite(LED, HIGH);
  delay(100);
  digitalWrite(LED, LOW);
  delay(100);
}


void test_encoder() {
  lcd.setCursor(0, 0);
  lcd.print("rotary encoder: ");

  lcd.setCursor(1, 0);
  lcd.print(encoder0Pos);
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
