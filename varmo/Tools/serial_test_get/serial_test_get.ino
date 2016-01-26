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

String Speed = "machine.velocity";
String Torque = "machine.torque";
String Position = "machine.position";

String Device_serial_num = "machine.serialnumber";
String Drive_Enable = "status.drive_enable";


char inChar_old;

String inputString = "";
bool stringComplete = false;
String data1 = "";
String data2 = "";
String data3 = "";

String SerialNumber_receipt;
String protocol_receipt;
float actual_speed;

bool flag;

long time_out = 1000;
long time_ping;

String confirm_key = "";
int k;
byte incoming_buffer[50];
byte packets_buffer[300];
Packet new_packet;
int pac_buf_pos;
int packet_complet;
int inc_buf_size;

void setup() {
  // put your setup code here, to run once:
  lcd.init();
  lcd.clear();
  lcd.print("init");
  pinMode(13, OUTPUT);
  Serial.begin(57600);
  Varmo.sendData(Get, Device_serial_num);
  delay(5);
  Varmo.sendData(Get, Device_serial_num);
}

void loop() {
  while (flag == false) {
/*
    if (millis() - time_ping > time_out) {
      Varmo.sendData(Get, Device_serial_num);
      time_ping = millis();
      lcd.setCursor(0,0);
      lcd.print("waiting");
    }*/
    serialEvent();
    if (packet_complet == 1) {
      lcd.setCursor(0,0);
      lcd.print("reading");
      serial_analyse(new_packet, &protocol_receipt, &SerialNumber_receipt, &data1, &data2, &data3);
      get_confirm_key(&data1, &confirm_key);
  /*  
      Serial.println(protocol_receipt);
      Serial.println(SerialNumber_receipt);
      Serial.println(data1);
      Serial.println(data2);
      Serial.println(data3);
      Serial.println(confirm_key);
  */
      if (confirm_key == "ok"){
        lcd.setCursor(1,0);
        if (protocol_receipt == "ExmEisla"){
          lcd.print("S/N : OK");
        }
        else {
          lcd.print("S/N : error");
        }      
      }
      /*for (int v = 0; v < new_packet.length; v++) {
        Serial.write(new_packet.data.toBytes[v]);
      }*/
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

        if (packets_buffer[pac_buf_pos + i-1] == 13 /*&& packets_buffer[pac_buf_pos+  i] == 10*/){  
          lcd.setCursor(0,0);
          lcd.print("packet end");
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
    if (packet_complet == 0){
      pac_buf_pos += inc_buf_size;
    }
  }
}

