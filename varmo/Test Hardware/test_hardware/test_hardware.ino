/*

*/
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

#define BUTTON_2 10

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
  pinMode(BUTTON_2 , INPUT);
  lcd.init ();
  lcd.clear ();
  lcd.print("ExMachina");

  Serial.begin(9600);
  while (!Serial) {
    ;
  }
  Serial.println("ASCII Table ~ Character Map");
}

int thisByte = 33;


void loop() {
  /*
  serial_test(thisByte);
  test_encoder();
  test_LED1();
  test_LED2();


  if (digitalRead(DIRECTION_1) == HIGH){
    lcd.setCursor(0,0);
    lcd.print("DIRECTION1 == 1");
  }
  else if (digitalRead(DIRECTION_1) == LOW){
    lcd.setCursor(0,0);
    lcd.print("DIRECTION1 == 0");
  }

  delay(500);

  if (digitalRead(DIRECTION_2) == HIGH){
    lcd.setCursor(1,0);
    lcd.print("DIRECTION2 == 1");
  }
  else if (digitalRead(DIRECTION_2) == LOW){
    lcd.setCursor(1,0);
    lcd.print("DIRECTION2 == 0");
  }

  delay(500);*/

  if (digitalRead(BUTTON_2) == HIGH){
    lcd.setCursor(1,0);
    lcd.print("BUTTON2 == 1");
  }
  else if (digitalRead(BUTTON_2) == LOW){
    lcd.setCursor(1,0);
    lcd.print("BUTTON2 == 0");
  }

  delay(100);

}


void test_LED1() {
  digitalWrite(LED_1, HIGH);
  delay(50);
  digitalWrite(LED_1, LOW);
}

void test_LED2 () {
  digitalWrite(LED_2, HIGH);
  delay(50);
  digitalWrite(LED_2, LOW);
}

void test_encoder() {
  lcd.setCursor(0, 0);
  lcd.print("Encoder: ");
  lcd.print(encoder0Pos);
  lcd.setCursor(1, 0);
  lcd.print("Push: ");

  int encoder_push = digitalRead(encoderE);
  if (encoder_push == LOW) {
    lcd.print("LOW");
  }
  else if (encoderE == HIGH) {
    lcd.print("HIGH");
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

void serial_test(int thisByte) {
  while (thisByte != 126) {
    Serial.write(thisByte);

    Serial.print(", dec: ");
    Serial.print(thisByte);
    Serial.print(", hex: ");

    Serial.print(thisByte, HEX);

    Serial.print(", oct: ");
    Serial.print(thisByte, OCT);

    Serial.print(", bin: ");
    Serial.println(thisByte, BIN);

    thisByte++;
  }
  thisByte = 33;
}

