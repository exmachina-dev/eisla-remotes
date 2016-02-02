/***
    eeprom_put example.

    This shows how to use the EEPROM.put() method.
    Also, this sketch will pre-set the EEPROM data for the
    example sketch eeprom_get.

    Note, unlike the single byte version EEPROM.write(),
    the put method will use update semantics. As in a byte
    will only be written to the EEPROM if the data is actually
    different.

    Written by Christopher Andrews 2015
    Released under MIT licence.
***/

#include <EEPROM.h>
float POS = -95;
float SPEED = 1547;
float ACCELERATION = 5;
float DECELERATION = 2;

struct MyObject {
  byte data;
  byte cue_num;
  float pos;
  float pos_speed;
  float acc;
  float dec;
};

const char SERIAL_NUMBER[14] = "0116VARM0001";
const int deviceAdress = 900;

void setup() {

  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }

  //Serial.println(EEPROM.length());
  save_device_eeprom(SERIAL_NUMBER);
/*  get_device_eeprom(SERIAL_NUMBER);

  write_cue_eeprom(7, POS, SPEED, ACCELERATION, DECELERATION);

  Serial.println("Read float from EEPROM: ");

  reading_cue_eeprom(7);

  erase_cue_eeprom(7);
  write_cue_eeprom(7, POS, SPEED, ACCELERATION, DECELERATION);

  reading_cue_eeprom(7);*/
}

void save_device_eeprom(const char* serialnumber){
  byte temp = EEPROM.read(900);
  Serial.println(temp);
  if (temp != 1){
    EEPROM.write(900, 1);
    EEPROM.put(901, SERIAL_NUMBER);
  }
  
}

void get_device_eeprom(const char* serialnumber){
  for (int i = 900; i<912; i++){
    Serial.print(char(EEPROM.read(i)));
  }
}

void erase_cue_eeprom(byte cue){
  int eeAddress = 18 * (cue-1);
  EEPROM.write(eeAddress, 0);
}

void write_cue_eeprom(byte cue, float pos, float speed, float acceleration, float deceleration) {
  int eeAddress = 0;   //Location we want the data to be put.
  Serial.println("Written float data type!");

  MyObject writing;

  eeAddress = sizeof(writing) * (cue-1);

  byte temp = EEPROM.read(eeAddress);

  if (temp != 1)  {
    Serial.print("New cue");
    writing.data = 1;
    writing.cue_num = cue;
    writing.pos = pos;
    writing.pos_speed = speed;
    writing.acc = acceleration;
    writing.dec = deceleration;
  }
  else if (temp == 1) {
    Serial.print("Erase cue");
    writing.data = 1;
    writing.cue_num = cue;
    writing.pos = pos;
    writing.pos_speed = speed;
    writing.acc = acceleration;
    writing.dec = deceleration;
  }

  EEPROM.put(eeAddress, writing);
  Serial.print("\n\n");
}

void reading_cue_eeprom(byte cue) {
  int eeAddress = 0; //Move address to the next byte after float 'f'.

  MyObject reading; //Variable to store custom object read from EEPROM.

  eeAddress = sizeof(reading) * (cue-1);

  EEPROM.get(eeAddress, reading);

 // Serial.println("Read custom object from EEPROM: ");
  Serial.print("data: ");
  Serial.println(reading.data);
  if (reading.data == 1 ) {
    Serial.print("cue num: ");
    Serial.println(reading.cue_num);
    Serial.print("pos: ");
    Serial.println(reading.pos);
    Serial.print("spd: ");
    Serial.println(reading.pos_speed);
    Serial.print("acc: ");
    Serial.println(reading.acc);
    Serial.print("dec: ");
    Serial.println(reading.dec);
  }
}

void loop() {
  /* Empty loop */
}
