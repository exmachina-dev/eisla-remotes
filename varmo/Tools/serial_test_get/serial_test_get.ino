#include <protocol.h>
#include <ST7036.h>


#define VARMO_VERSION     "Varmo V0.4"
#define SERIAL_NUMBER     "0116VARM0001"
#define PROTOCOL          "ExmEisla"
#define ARMAZ_ID          "0000"

Device Varmo = Device();
ST7036 lcd = ST7036 ( 2, 16, 0x78 );

String Get = "machine.get";
String Set = "machine.set";
String Alive = "machine.alive";

String Speed_ref = "machine.velocity_ref";
String Torque_ref = "machine.torque_ref";
String Position_ref = "machine.position_ref";

char *Speed = "machine.velocity";
char *Torque = "machine.torque";
char *Position = "machine.position";
char *Acceleration = "machine.acceleration";
char *Deceleration = "machine.deceleration";

char *Device_serial_num ="machine.serialnumber";
//String Device_serial_num = "machine.serialnumber";
char *Drive_Enable = "status.drive_enable";

/*
  char inChar_old;

  String inputString = "";
  bool stringComplete = false;
  String data1 = "";
  String data2 = "";
  String data3 = "";
*/
bool SerialNumber_ok;
float SPEED_GET = 0;
float TORQUE_GET = 0;
float POSITION_GET = 0;
float HOME_POSITION_GET = 0;
float ACCELERATION_GET = 0;
float DECELERATION_GET = 0;
float POS_SPEED_GET = 0;

bool DRIVE_ENABLE;
/*
  String SerialNumber_receipt;
  String protocol_receipt;
  float actual_speed;
*/
bool flag;

long time_out = 1000;
long time_ping;

//String confirm_key = "";
//int k;
byte incoming_buffer[50];
byte packets_buffer[300];
Packet new_packet;
int pac_buf_pos;
bool packet_complet;
int inc_buf_size;

void setup() {
  // put your setup code here, to run once:
  lcd.init();
  lcd.clear();
  //lcd.print("init");
  pinMode(13, OUTPUT);
  Serial.begin(57600);
  Varmo.sendData(Get, Device_serial_num);
  delay(50);
  Varmo.sendData(Get, Device_serial_num);
  //Varmo.sendData(Set, Speed_ref, float(0.0));
}

void loop() {
  while (flag == false) {

    if (packet_complet == 1) {
      lcd.setCursor(0, 0);
      lcd.print("reading: ");

      int status_msg = serial_analyse(new_packet, &SerialNumber_ok, &POSITION_GET, &SPEED_GET, &TORQUE_GET, &ACCELERATION_GET, &DECELERATION_GET, &DRIVE_ENABLE);

      lcd.setCursor(0, 14);
      lcd.print(status_msg);

      lcd.setCursor(1, 14);
      lcd.print(SerialNumber_ok);

      packet_complet = 0;
    }
    flag = true;
  }
  flag = false;
}


void serialEvent() {
  int data_length;
  while (Serial.available() > 0) {
    inc_buf_size = Serial.readBytes(incoming_buffer, 50);
    if (inc_buf_size > 0) {
      for (int i = 0; i < inc_buf_size; i++) {
        packets_buffer[pac_buf_pos + i] = incoming_buffer[i];
        if (packets_buffer[pac_buf_pos + i - 1] == 13 && packets_buffer[pac_buf_pos +  i] == 10) {
          for (int j = 0; j <= pac_buf_pos + i; j++) {
            new_packet.data[j] = packets_buffer[j];
          }
          new_packet.length = pac_buf_pos + i + 1;
          packet_complet = 1;
          data_length = (new_packet.data [8] << 8) + new_packet.data[9];
          /*if (data_length == new_packet.length){
            packet_complet = 1;
            }*/
          pac_buf_pos = 0;
          delayMicroseconds(5);
        }
      }
    }
    if (packet_complet == 0) {
      pac_buf_pos += inc_buf_size;
    }
  }
}

int serial_analyse(Packet packet, bool *serialnum_ok, float *position, float *speed, float *torque, float *acceleration, float *deceleration, bool *drive_enable) {

  char chara;
  String temp = "";

  binaryRepr value;

  //Protocol
  for (int i = 0; i < 8; i++) {
    temp += char(packet.data[i]);
  }
  if (temp != "ExmEisla") {
    return 0;
  }

  //Serial number
  temp = "";
  for (int i = 10; i < 22; i++) {
    temp += char(packet.data[i]);
  }
  if (temp != "0416ARCP0001") {
    return 0;
  }


  //data1
  temp = "";
  int i = 22;
  while (char(packet.data[i]) != '.' ) {
    temp += char(packet.data[i]);
    i++;
  }
  if (temp != "machine") {
    return 0;
  }

  temp = "";
  i++;
  while (char(packet.data[i]) != '.' ) {
    temp += char(packet.data[i]);
    i++;
  }
  if (temp != "get") {
    return 0;
  }

  temp = "";
  i++;
  while (char(packet.data[i]) != ':' ) {
    temp += char(packet.data[i]);
    i++;
  }
  if (temp != "ok") {
    return 0;
  }

  //Command
  temp = "";
  i++;
  char cmd[21];
  int j =0;
  while (char(packet.data[i]) != ':' ) {
    cmd[j] = char(packet.data[i]);
    i++;
    j++;
  }
  cmd[j-1] = 0;

  //Value
  if (strcmp(cmd, Device_serial_num)) {
    temp = "";
    i++;
    while (i < packet.length - 2) {
      temp += char(packet.data[i]);
      i++;
    }
    if (temp == "0416ARCP0001") {
      *serialnum_ok = 1;
    }
    else {
      *serialnum_ok = 0;
      return 2;
    }
  }
  else if (temp == Position) {
  i++;
  int j = 0;
  while (i < packet.length-2) {
    value.toBytes[j] += packet.data[i];
    i++;
    j++;
  }
   *position = value.toFloat;
  }
  else if (temp == Speed) {
  i++;
  j = 0;
  while (i < packet.length-2) {
    value.toBytes[j] += packet.data[i];
    i++;
    j++;
  }
   *speed = value.toFloat;
  }
  else if (temp == Torque) {
  i++;
  j = 0;
  while (i < packet.length-2) {
    value.toBytes[j] += packet.data[i];
    i++;
    j++;
  }
   *torque = value.toFloat;
  }
  else if (temp == Acceleration) {
  i++;
  j = 0;
  while (i < packet.length-2) {
    value.toBytes[j] += packet.data[i];
    i++;
    j++;
  }
   *acceleration = value.toFloat;
  }
  else if (temp == Deceleration) {
  i++;
  j = 0;
  while (i < packet.length-2) {
    value.toBytes[j] += packet.data[i];
    i++;
    j++;
  }
   *deceleration = value.toFloat;
  }
  else if (temp == Drive_Enable)  {
  i++;
  j = 0;
  while (i < packet.length-2) {
    value.toBytes[j] += packet.data[i];
    i++;
    j++;
  }
   *drive_enable = value.toBool.bool0;
  }
  else {
    return 0;
  }
  return 1;
}
