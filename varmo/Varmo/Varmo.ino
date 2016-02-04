#include <Arduino.h>
#include <ST7036.h>
#include <Wire.h>
#include <protocol.h>
#include "./Varmo.h"
#include <MenuSystem.h>


const char *Get = "machine.get";
const char *Set = "machine.set";

const char *Speed_ref = "machine.velocity_ref";
const char *Torque_ref = "machine.torque_ref";
const char *Position_ref = "machine.position_ref";

const char *Speed = "machine.velocity";
const char *Torque = "machine.torque";

const char *Position = "machine.position";
const char *Pos_go = "machine.command.go";
const char *Go_Home = "machine.command.go_home";
const char *Pos_Home = "machine.command.set_home";

const char *Acceleration = "machine.acceleration";
const char *Deceleration = "machine.deceleration";

const char *Control_Mode = "machine.command.control_mode";

const char *Device_serial_num = "machine.serialnumber";
const char *Drive_Enable = "status.drive_enable";
const char *Stop = "machine.command.cancel";


/*ENCODER*/
float encoder0Pos = 0;
float encoder0Pos_old = 0;

/*CONTRAST*/
uint8_t F_contrast = 0;

/*MENU*/
uint8_t MODE = 0;

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

uint8_t CONTRAST = 5;
uint8_t CONTRAST_OLD = 5;

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
const unsigned long debounceDelay = 50;    // the debounce time; increase if the output flickers
bool SEND = LOW;

/*GET*/
/*byte incoming_buffer[10];
byte packets_buffer[150];
Packet new_packet;
int pac_buf_pos;
bool packet_complet;
int inc_buf_size;*/

/*LED STATUS*/
/*bool LED_1_STATUS;
bool LED_2_STATUS;*/

//bool DRIVE_ENABLE;

/*TIME OUT*/
bool Serial_OK = true;
/*TIMER*/
unsigned long time_push = 0;
const unsigned long refresh = 1000;


bool flag = false;

bool MOTOR_OFF;
unsigned long timer_motor_off;
bool SENS = 1;

unsigned long refresh_set_home;


void setup() {

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

  mm.add_menu(&mu1);
  mm.add_menu(&mu2);
  mm.add_menu(&mu3);


  mu1.add_item(&mu1_mi1, &on_pos_selected);
  mu1.add_item(&mu1_mi2, &on_pos_speed_selected);
  mu1.add_item(&mu1_mi3, &on_home_selected);
  mu1.add_item(&mu1_mi4, &on_acc_selected);
  mu1.add_item(&mu1_mi5, &on_dec_selected);

  mu2.add_item(&mu2_mi1, &on_speed_selected);
  mu2.add_item(&mu2_mi2, &on_acc_selected);
  mu2.add_item(&mu2_mi3, &on_dec_selected);

  mu3.add_item(&mu3_mi1, &on_torque_selected);
  mu3.add_item(&mu3_mi2, &on_torque_rise_selected);
  mu3.add_item(&mu3_mi3, &on_torque_fall_selected);

  ms.set_root_menu(&mm);
  FLAG_MENU = 1;
  displayMenu();


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

  Serial.begin(57600);
  Varmo.sendData(Get, Device_serial_num);
  delay(50);
  Varmo.sendData(Get, Device_serial_num);
  displayMenu();
}

void loop()
{

  delay(100);
  
  /*###############################MENU###############################*/
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
      Menu const* cp_menu = ms.get_current_menu();
       if (cp_menu->get_selected()->get_name() == "Position Mode"){
        Varmo.sendData(Set, Control_Mode, (unsigned int) 3);
      }
      else if (cp_menu->get_selected()->get_name() == "Speed Mode"){
        Varmo.sendData(Set, Control_Mode, (unsigned int) 2);
      }
      else if (cp_menu->get_selected()->get_name() == "Torque Mode"){
        Varmo.sendData(Set, Control_Mode, (unsigned int) 1);
      }
      ms.select();
      if (MODE == 0){
        displayMenu();
      }
      FLAG_MENU = 1;
    }
    else if (FLAG_MENU == 1){
      if (MODE != 0){
        MODE = 0;
        displayMenu();
      }
      else {
        ms.back();
        displayMenu();
      }
      while(encoder_push != HIGH){
        encoder_push = digitalRead(encoderE);
      }
    }
    else  {
      resolution_chosen = 0;
      RESOLUTION_old = RESOLUTION;
      if (MODE == MODE_POS_SPD ||MODE == MODE_SPD || MODE == MODE_TRQ){
        init_resolution_three(RESOLUTION, &encoder0Pos);
      }
      else {
        init_resolution(RESOLUTION, &encoder0Pos);
      }
      while (resolution_chosen == 0 && MODE != MODE_HOME)  {
        if (MODE == MODE_POS) {
          RESOLUTION = resolution_set(RESOLUTION, 1, 5);
        }
        else if (MODE == MODE_POS_SPD){
          RESOLUTION = resolution_set_three(RESOLUTION, 4);
        }
        else if (MODE == MODE_SPD || MODE == MODE_TRQ){
          RESOLUTION = resolution_set_three(RESOLUTION, 5);
        }
        else{
          RESOLUTION = resolution_set(RESOLUTION, 1, 4);
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

  if (FLAG_MENU == 1 && MODE == 0){
    moveMenu();
    encoder0Pos_old = encoder0Pos;
  }

  if (MODE != 0){
    FLAG_MENU = 0;
  }

  if (FLAG_RESOLUTION == 1) {
    encoder0Pos = encoder0Pos_old * (RESOLUTION_old / RESOLUTION);
    FLAG_RESOLUTION = 0;
    lcd.cursor_off();
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
    lcd.setCursor(1,4);
    lcd.print(" ");
    MOTOR_OFF = true;
    Varmo.sendData(Set, Stop, true);
  }
  if (MOTOR_OFF == false){
    if (MODE == MODE_SPD || MODE == MODE_TRQ || MODE == MODE_POS ){
      lcd.setCursor(0,13);
      lcd.print(" on");
    }
  }
  else if (MOTOR_OFF == true){
    if (MODE == MODE_SPD || MODE == MODE_TRQ || MODE == MODE_POS ){
      lcd.setCursor(0,13);
      lcd.print("off");
    }
  }

  /*###########################SEND###########################*/

  if (MOTOR_OFF == false || MODE == MODE_HOME || MODE == MODE_ACC || MODE == MODE_DEC || MODE == MODE_POS_SPD)  {
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

  /*###############################REFRESH###############################*/
  /*if (FLAG_MENU == 1)  {
    lcd_print_menu(&MODE, CONTRAST, POSITION_TARGET, TORQUE_TARGET, SPEED_TARGET, HOME_POSITION_TARGET, ACCELERATION_TARGET, DECELERATION_TARGET, POS_SPEED_TARGET,
                   TORQUE_GET, SPEED_GET, POSITION_GET, HOME_POSITION_GET, ACCELERATION_GET, DECELERATION_GET, POS_SPEED_GET,&encoder0Pos);
    menu_init(MODE, &CONTRAST, &POSITION_TARGET, &TORQUE_TARGET, &SPEED_TARGET, &HOME_POSITION_TARGET, 
              &ACCELERATION_TARGET, &DECELERATION_TARGET, &POS_SPEED_TARGET,&encoder0Pos, RESOLUTION);

    FLAG_MENU = 0;
  }*/


  switch (MODE)  {

    case MODE_POS :

      if (SEND == HIGH){
        SEND = LOW;
        Varmo.sendData(Set, Position_ref, POSITION_TARGET);
        Varmo.sendData(Set, Pos_go, true);
      }
      converter(&POSITION_TARGET, &encoder0Pos, RESOLUTION, SENS, 9999.9);
      lcd_print_pos(POSITION_TARGET, POS_SPEED_TARGET, MOTOR_OFF);
      if (MOTOR_OFF == true){
        lcd.setCursor(1,4);
        lcd.print(" ");
      }
      break;

    case MODE_POS_SPD :

      if (SEND == HIGH){
        SEND = LOW;
        Varmo.sendData(Set, Speed_ref, POS_SPEED_TARGET);
        on_pos_selected(0);
        break;
      }
      converter_abs(&POS_SPEED_TARGET, &encoder0Pos, RESOLUTION, 99.9);
      lcd_print_abs_float_value_three(POS_SPEED_TARGET, POS_SPEED_TARGET);
      break;

    case MODE_TRQ :

      if (SEND == HIGH){
        SEND = LOW;
        Varmo.sendData(Set, Torque_ref, TORQUE_TARGET);
      }
      converter(&TORQUE_TARGET, &encoder0Pos, RESOLUTION, SENS, 150);
      lcd_print_float_value_three(TORQUE_GET, TORQUE_TARGET, MOTOR_OFF);
      if (MOTOR_OFF == true){
        lcd.setCursor(1,4);
        lcd.print(" ");
      }
      break;

    case MODE_SPD :

      if (SEND == HIGH){
        SEND = LOW;
        Varmo.sendData(Set, Speed_ref, SPEED_TARGET);
      }
      converter(&SPEED_TARGET, &encoder0Pos, RESOLUTION, SENS,999.9);
      lcd_print_float_value_three(SPEED_GET, SPEED_TARGET, MOTOR_OFF);
      if (MOTOR_OFF == true){
        lcd.setCursor(1,4);
        lcd.print(" ");
      }
      break;

    case MODE_HOME :

      if (SEND == HIGH){
        SEND = LOW;
        Varmo.sendData(Set, Pos_Home, true);
        lcd.setCursor(1,0);
        lcd.print("New home pos    ");
        refresh_set_home = millis();
      }
      if ( (millis() - refresh_set_home) > refresh ) {
        refresh_set_home = millis();
        lcd.setCursor(1,0);
        lcd.print("                ");
      }
      break;

    case MODE_ACC :

      if (SEND == HIGH){
        SEND = LOW;
        Varmo.sendData(Set, Acceleration, ACCELERATION_TARGET);
      }
      converter_abs(&ACCELERATION_TARGET, &encoder0Pos, RESOLUTION, 9999.9);
      lcd_print_abs_float_value(ACCELERATION_GET, ACCELERATION_TARGET);
      break;

    case MODE_DEC :
    
      if (SEND == HIGH){
        SEND = LOW;
        Varmo.sendData(Set, Deceleration, DECELERATION_TARGET);
      }
      converter_abs(&DECELERATION_TARGET, &encoder0Pos, RESOLUTION, 9999.9);
      lcd_print_abs_float_value(DECELERATION_GET, DECELERATION_TARGET);
      break;

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

void init_resolution(float RESOLUTION, float *encoder0Pos) {
  if (RESOLUTION == 0.1){
    *encoder0Pos = 25;
  }
  else if (RESOLUTION == 1) {
    *encoder0Pos = 20;
  }
  else if (RESOLUTION == 10) {
    *encoder0Pos = 15;
  }
  else if (RESOLUTION == 100) {
    *encoder0Pos = 10;
  }
  else if (RESOLUTION == 1000) {
    *encoder0Pos = 5;
  }
}

void init_resolution_three(float RESOLUTION, float *encoder0Pos) {
  if (RESOLUTION == 0.1) {
    *encoder0Pos = 20;
  }
  else if (RESOLUTION == 1) {
    *encoder0Pos = 15;
  }
  else if (RESOLUTION == 10) {
    *encoder0Pos = 10;
  }
  else if (RESOLUTION == 100) {
    *encoder0Pos = 5;
  }
}

float resolution_set(float RESOLUTION, bool format, int set_cursor)  {

  uint8_t RESOLUTION_SELECTOR = uint8_t(encoder0Pos);

  if (RESOLUTION_SELECTOR < 0) {
    encoder0Pos = 0;
    RESOLUTION_SELECTOR = 0;
  }
  else if (RESOLUTION_SELECTOR > 25){
    encoder0Pos = 25;
    RESOLUTION_SELECTOR = 25;
  }
  else if (format == 0 && RESOLUTION_SELECTOR > 20) {
    encoder0Pos = 20; 
    RESOLUTION_SELECTOR = 20;
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

float resolution_set_three(float RESOLUTION, uint8_t set_cursor)  {

  uint8_t RESOLUTION_SELECTOR = uint8_t(encoder0Pos);

  if (RESOLUTION_SELECTOR < 0) {
    encoder0Pos = 0;
  }
  else if (RESOLUTION_SELECTOR > 20){
    encoder0Pos = 20;
  }

  if (RESOLUTION_SELECTOR <= 5)  {
    lcd.setCursor(1, set_cursor);
    lcd.cursor_on();
    RESOLUTION = 100;
  }
  else if (RESOLUTION_SELECTOR <= 10)  {
    lcd.setCursor(1, set_cursor + 1);
    lcd.cursor_on();
    RESOLUTION = 10;
  }
  else if (RESOLUTION_SELECTOR <= 15)  {
    lcd.setCursor(1, set_cursor + 2);
    lcd.cursor_on();
    RESOLUTION = 1;
  }
  else if (RESOLUTION_SELECTOR <=  20)  {
    lcd.setCursor(1, set_cursor + 4);
    lcd.cursor_on();
    RESOLUTION = 0.1;
  }
  return RESOLUTION;
}


void lcd_print_contrast_value(uint8_t CONTRAST) {
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
  if (value == 0){
    lcd.print(" ");
  }
  else if (value >= 0)  {
    lcd.print("+");
  }
  else  {
    lcd.print("-");
  } 
}

void lcd_print_float_three_align_right(float value)  {
  if (value == 0) {
    lcd.print("00");
  }
  else if (abs(value) < 1) {
    lcd.print("00");
  }
  else if (abs(value) < 10) {
    lcd.print("00");
  }
  else if (abs(value) < 100) {
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

void lcd_print_int_align_right_three(int value)  {
  if (value == 0) {
    lcd.print("00");
  }
  else if (abs(value) < 10) {
    lcd.print("00");
  }
  else if (abs(value) < 100) {
    lcd.print("0");
  }
  lcd.print(abs(value));
}

void lcd_print_int_align_right_two(int value)  {
  if (value == 0) {
    lcd.print("0");
  }
  else if (abs(value) < 10) {
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
  else if (abs(value) < 1000){
    lcd.print("0");
  }
  lcd.print(abs(value));
}

void lcd_print_float_value(float value1, float value2, bool motor) {
  lcd.setCursor(1, 0);
  lcd.print("Tgt:");
  if (motor == false) {
    lcd_print_sign(value2);
  }
  else if (motor == true){
    lcd.print(" ");
  }
  lcd_print_float_align_right(value2);
}

void lcd_print_float_value_three(float value1, float value2, bool motor) {
  lcd.setCursor(1, 0);
  lcd.print("Tgt:");
  if (motor == false) {
    lcd_print_sign(value2);
  }
  else if (motor == true){
    lcd.print(" ");
  }
  lcd_print_float_three_align_right(value2);
}

void lcd_print_abs_float_value_three(float value1, float value2) {
  lcd.setCursor(1, 0);
  lcd.print("Tgt:");
  lcd_print_float_three_align_right(value2);
}

void lcd_print_abs_float_value(float value1, float value2) {
  lcd.setCursor(1, 0);
  lcd.print("Tgt:");
  lcd_print_float_align_right(value2);
}

void lcd_print_vit_pos(float value1, float value2) {
  lcd.setCursor(1,0);
  lcd.print("Spd Pos:");
  lcd.setCursor(1,8);
  lcd_print_int_align_right(int(value2));
}

void lcd_print_pos(float value1, float value2, bool motor) {
  lcd.setCursor(1,0);
  lcd.print("Tgt:");
  if (motor == false) {
    lcd_print_sign(value1);
  }
  else if (motor == true){
    lcd.print(" ");
  }
  lcd_print_float_align_right(value1);

  lcd.setCursor(1,11);
  lcd.print(" ");

  lcd.setCursor(1,12);
  lcd.print("S:");
  lcd.setCursor(1,14);
  lcd_print_int_align_right_two(int(value2));
}

/*##################CONVERTER##################*/
void contrast_convert(uint8_t *CONTRAST, uint8_t *F_contrast, float * encoder0Pos) {
  uint8_t resolution = 10;
  uint8_t sensibility = 4;
  uint8_t  value = *CONTRAST;
  value = uint8_t(*encoder0Pos / sensibility );
  if (value >= 0 && value <= 10)  {
    *CONTRAST = value;
    *F_contrast = uint8_t( 25.5 * value);
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

void on_speed_selected(MenuItem* p_menu_item) {
  lcd.clear();
  encoder0Pos = SPEED_TARGET;
  lcd.print("Speed Mode");
  lcd_print_float_value_three(SPEED_GET, SPEED_TARGET,MOTOR_OFF);
  lcd.setCursor(1,12);
  lcd.print("cm/s");
  MODE = MODE_SPD;
}

void on_acc_selected(MenuItem* p_menu_item) {
  lcd.clear();
  encoder0Pos = ACCELERATION_TARGET;
  lcd.print("Set Acceleration");
  lcd_print_abs_float_value(ACCELERATION_GET, ACCELERATION_TARGET);
  lcd.setCursor(1,13);
  lcd.print("sec");
  MODE = MODE_ACC;
}

void on_dec_selected(MenuItem* p_menu_item) {
  lcd.clear();
  encoder0Pos = DECELERATION_TARGET;
  lcd.print("Set Deceleration");
  lcd_print_abs_float_value(DECELERATION_GET, DECELERATION_TARGET);
  lcd.setCursor(1,13);
  lcd.print("sec");  
  MODE = MODE_DEC;
}

void on_pos_selected(MenuItem* p_menu_item) {
  lcd.clear();
  if (POS_SPEED_TARGET != 0){
    encoder0Pos = POSITION_TARGET;
    lcd.print("Set Position");
    lcd_print_pos(POSITION_TARGET, POS_SPEED_TARGET,MOTOR_OFF);
    MODE = MODE_POS;
  }
  else{
    on_pos_speed_selected(0);
  }
}

void on_pos_speed_selected(MenuItem* p_menu_item) {
  lcd.clear();
  encoder0Pos = POS_SPEED_TARGET;
  lcd.print("Speed Position"); 
  lcd_print_abs_float_value_three(POS_SPEED_TARGET, POS_SPEED_GET);
  lcd.setCursor(1,12);
  lcd.print("cm/s");
  MODE = MODE_POS_SPD;
}

void on_home_selected(MenuItem* p_menu_item)  {
  lcd.clear();
  lcd.print("Home Position:");
  MODE = MODE_HOME;
}

void on_torque_selected(MenuItem* p_menu_item)  {
  lcd.clear();
  encoder0Pos = TORQUE_TARGET;
  lcd.print("Torque Mode");
  lcd_print_float_value_three(TORQUE_GET, TORQUE_TARGET,MOTOR_OFF);
  lcd.setCursor(1,15);
  lcd.print("%");
  MODE = MODE_TRQ;
}

void on_torque_fall_selected(MenuItem* p_menu_item) {
  lcd.clear();
  lcd.print("Torque Fall Sel");
  MODE = 9;
}

void on_torque_rise_selected(MenuItem* p_menu_item) {
  lcd.clear();
  lcd.print("Torque rise Sel");
  MODE = 10;
}