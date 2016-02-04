/*
 * serial_nav.ino - Example code using the menu system library
 *
 * This example shows the menu system being controlled over the serial port.
 *
 * Copyright (c) 2015 arduino-menusystem
 * Licensed under the MIT license (see LICENSE)
 */

#include <MenuSystem.h>
#include <ST7036.h>
#include <Wire.h>

/*ENCODER*/
#define encoder0PinA 2
#define encoder0PinB 3
#define encoderE 4

ST7036 lcd = ST7036 ( 2, 16, 0x78 );

/*ENCODER*/
float encoder0Pos = 0;
float encoder0Pos_old = 0;

bool Mode_chosen = 0;

/*MENU*/
uint8_t MODE = 0;
uint8_t MODE_OLD = 0;
bool FLAG_MENU;
unsigned long time_push;

// Menu variables
MenuSystem ms;
Menu mm("ROOT Menu Title");
Menu mu1("Position Mode");
Menu mu2("Speed Mode");
Menu mu3("Torque Mode");


MenuItem mu1_mi1("Set Position");
MenuItem mu1_mi2("Set Speed");
MenuItem mu1_mi3("Set Acceleration");
MenuItem mu1_mi4("Set Decceleration");

MenuItem mu2_mi1("Set Speed");
MenuItem mu2_mi2("Set Acceleration");
MenuItem mu2_mi3("Set Deceleration");

MenuItem mu3_mi1("Set Torque");
MenuItem mu3_mi2("Set Torque rise");
MenuItem mu3_mi3("Set Torque Fall");
// Menu callback function
// In this example all menu items use the same callback.

void on_speed_selected(MenuItem* p_menu_item)
{
  lcd.clear();
  lcd.print("Speed Sel");
  MODE = 1;
  //delay(1000);
}

void on_acc_selected(MenuItem* p_menu_item)
{
  lcd.clear();
  lcd.print("Acceleration Sel");
  MODE = 2;
  //delay(1000);
}

void on_dec_selected(MenuItem* p_menu_item)
{
  lcd.clear();
  lcd.print("Deceleration Sel");
  MODE = 3;
  //delay(1000);
}

void on_pos_selected(MenuItem* p_menu_item)
{
  lcd.clear();
  lcd.print("Position Sel");
  MODE = 4;
  //delay(1000);
}

void on_torque_selected(MenuItem* p_menu_item)
{
  lcd.clear();
  lcd.print("Torque Sel");
  MODE = 4;
  //delay(1000);
}

void on_torque_fall_selected(MenuItem* p_menu_item)
{
  lcd.clear();
  lcd.print("Torque Fall Sel");
  MODE = 5;
  //delay(1000);

}
void on_torque_rise_selected(MenuItem* p_menu_item)
{
  lcd.clear();
  lcd.print("Torque rise Sel");
  MODE = 6;
  //delay(1000);
}
// Standard arduino functions

void setup()
{

    //ENCODER INITIALISATION
  pinMode(encoder0PinA, INPUT);
  pinMode(encoder0PinB, INPUT);

  // encoder pin on interrupt 0 (pin 2)
  attachInterrupt(0, doEncoderA, CHANGE);
  // encoder pin on interrupt 1 (pin 3)
  attachInterrupt(1, doEncoderB, CHANGE);

  pinMode(encoderE, INPUT);

  lcd.init ();
  lcd.clear ();

  mm.add_menu(&mu1);
  mm.add_menu(&mu2);
  mm.add_menu(&mu3);


  mu1.add_item(&mu1_mi1, &on_pos_selected);
  mu1.add_item(&mu1_mi2, &on_speed_selected);
  mu1.add_item(&mu1_mi3, &on_acc_selected);
  mu1.add_item(&mu1_mi4, &on_dec_selected);

  mu2.add_item(&mu2_mi1, &on_speed_selected);
  mu2.add_item(&mu2_mi2, &on_acc_selected);
  mu2.add_item(&mu2_mi3, &on_dec_selected);

  mu3.add_item(&mu3_mi1, &on_torque_selected);
  mu3.add_item(&mu3_mi2, &on_torque_rise_selected);
  mu3.add_item(&mu3_mi3, &on_torque_fall_selected);

  ms.set_root_menu(&mm);
  FLAG_MENU = 1;
  displayMenu();
}

void loop()
{

  int encoder_push = digitalRead(encoderE);
  if (encoder_push == LOW )  {

    encoder_push = digitalRead(encoderE);
    time_push = millis();
    FLAG_MENU = 0;

    while (encoder_push != HIGH && FLAG_MENU == 0)  {
      encoder_push = digitalRead(encoderE);
      if ((millis() - time_push)  > 500 )  {
        FLAG_MENU = 1;
      }

    }

    if (FLAG_MENU == 0 && MODE==0){
      ms.select();
      displayMenu();
      FLAG_MENU = 1;
    }
    else if (FLAG_MENU == 1){
      if (MODE != 0){
        displayMenu();
        MODE = 0;
      }
      else {
        ms.back();
        displayMenu();
      }
      while(encoder_push != HIGH){
        encoder_push = digitalRead(encoderE);
      }
    }
    

  }


  if (FLAG_MENU ==1){
    moveMenu();
    encoder0Pos_old = encoder0Pos;
  }

  if (MODE != 0){
    FLAG_MENU = 0;
  }
  //FLAG_MENU = 0;
  switch (MODE) {
      case 1:
        lcd.setCursor(1,0);
        lcd.print("speed");
        break;
      case 2:
        lcd.setCursor(1,0);
        lcd.print("acceleration");
        break;
      case 3:
        lcd.setCursor(1,0);
        lcd.print("deceleration");
        break;
      case 4:
        lcd.setCursor(1,0);
        lcd.print("position");
        break;
      case 5:
        lcd.setCursor(1,0);
        lcd.print("torque");
      case 6:
        lcd.setCursor(1,0);
        lcd.print("rise");
      case 7:
        lcd.setCursor(1,0);
        lcd.print("fall");
        break;
  }
  delay(200);
}

void moveMenu(){
  if (encoder0Pos - encoder0Pos_old >= 2 ){
    ms.next();
    displayMenu();
  }
  else if(encoder0Pos - encoder0Pos_old <= -2){
    ms.prev();
    displayMenu();
  }
}

void displayMenu() {
  lcd.clear();
  lcd.setCursor(0,0);
  // Display the menu
  Menu const* cp_menu = ms.get_current_menu();
  lcd.print(cp_menu->get_selected()->get_name());
}




/*##################ENCODER##################*/
void doEncoderA() {

  // look for a low-to-high on channel A
  if (digitalRead(encoder0PinA) == HIGH) {
    // check channel B to see which way encoder is turning
    if (digitalRead(encoder0PinB) == LOW) {
      encoder0Pos = encoder0Pos + 1;               // CW
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
      encoder0Pos = encoder0Pos + 1;        // CW
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
      encoder0Pos = encoder0Pos - 1;           // CCW
    }
  }
}