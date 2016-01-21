#include <Arduino.h>
#include <protocol.h>

using namespace std ;

// CLASS METHODS
// ----------------------------------------------------------------------------

// Constructors:
// ---------------------------------------------------------------------------
Device::Device() {

  _Protocol = "ExmEisla";
	_SerialNumber = "0116VARM0001";
	_End= "\r\n";
	_delimitator = ':';
}

void Device::sendData(String data1, String command) {

    int length = _Protocol.length() + _SerialNumber.length() + data1.length() + _delimitator.length() + command.length() + _End.length() + 2;
    binaryRepr data_size;

    if (length<255){
      data_size.toInt.int0 = length;
      data_size.toInt.int1 = 0x00;
    }
    else if (length > 255) {
      data_size.toInt.int0 = (length&0x00FF);
      data_size.toInt.int1 = (length&0XFF00) >> 8;
    }

    Serial.print(_Protocol);
    Serial.write(data_size.toInt.int1);
    Serial.write(data_size.toInt.int0);
    Serial.print(_SerialNumber);
    Serial.print(data1);
    Serial.print(_delimitator);
    Serial.print(command);
    Serial.print(_End);

}

void Device::sendData(String data1, String command, String value= "") {
	
    int length = _Protocol.length() + _SerialNumber.length() + data1.length() + _delimitator.length() + command.length() + _delimitator.length() + value.length() + _End.length() + 2;
    binaryRepr data_size;

    if (length<255){
      data_size.toInt.int0 = length;
      data_size.toInt.int1 = 0x00;
    }
    else if (length > 255) {
      data_size.toInt.int0 = (length&0x00FF);
      data_size.toInt.int1 = (length&0XFF00) >> 8;
    }

    Serial.print(_Protocol);
    Serial.write(data_size.toInt.int1);
    Serial.write(data_size.toInt.int0);
    Serial.print(_SerialNumber);
    Serial.print(data1);
    Serial.print(_delimitator);
    Serial.print(command);
    Serial.print(_delimitator);
    Serial.print(value);
    Serial.print(_End);
}


void serial_analyse(String inputString, String *protocol, String *serial_num, String *data1, String *data2, String *data3) {
  char chara;
  String temp = "";
  *protocol = inputString.substring(0, 8);
  temp = inputString.substring(8, 10);
  binaryRepr length;
  temp.getBytes(length.toBytes, 3);

  int length_data = length.toInt.int0 * 0xFF + length.toInt.int1;

  temp = "";

  *serial_num = inputString.substring(10, 22);

  *data1 = "";
  *data2 = "";
  *data3 = "";
  int i = 22;
  chara = inputString[i];

  while (!(chara == ':' || i == length_data)) {
    temp += chara;
    i += 1;
    chara = inputString[i];
  }
  
  if (i != length_data) {
    *data1 = temp;
    temp = "";
    i += 1;
    chara = inputString[i];
    while (!(chara == ':' || i == length_data) ) {
      temp += chara;
      i += 1;
      chara = inputString[i];
    }
    
    if (i != length_data) {
      *data2 = temp;
      temp = "";
      i += 1;

      chara = inputString[i];
      while (!(chara == ':' || i == length_data) ) {
        temp += chara;
        i += 1;
        chara = inputString[i];

      }
      *data3 = temp.substring(0, temp.length() - 2);
      temp = "";
    }
    else {
      *data2 = temp.substring(0, temp.length() - 2);
      *data3 = "";
    }
  }
  else {
    *data1 = temp.substring(0, temp.length() - 2);
    *data2 = "";
    *data3 = "";
  }
}

String get_confirm_key(String *str, String *key) {
  int i = 0;

  char chara;
  String temp = *str;

  String temp_key;

  temp_key = "";

  chara = temp[i];

  while (chara != '.' ) {
    i += 1;
    chara = temp[i];
  }
  i += 1;
  chara = temp[i];
  while (chara != '.' ) {
    i += 1;
    chara = temp[i];
  }
  i += 1;
  chara = temp[i];
  while (!(chara == '.' || i == temp.length())) {

    temp_key += chara;
    i += 1;
    chara = temp[i];
  }
  *key = temp_key;
}