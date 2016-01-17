#include <Arduino.h>
#include <protocol.h>

// CLASS METHODS
// ----------------------------------------------------------------------------

// Constructors:
// ---------------------------------------------------------------------------
Device::Device(String Serial)
{
	_Protocol = "ExmEisla";
	_SerialNumber = Serial;
	_End = "\r\n";
	_delimitator = ':';
	_Alive = "alive";
	_Confirm = "ok";
}

void Device::sendData(String data1, String command) 
{
	String data;

	if(data1 == "machine.get"){
		data = _Protocol + _SerialNumber + data1 + _delimitator + command + _End;
		data = InsertLengthdata(data);
	}

	Serial.print(data);
}

void Device::sendData(String data1, String command, String value= "") 
{
	String data;
	if (data1 == "machine.set"){
		data = _Protocol + _SerialNumber + data1 + _delimitator + command + _delimitator + value + _End;
		data = InsertLengthdata(data);
	}
	Serial.print(data);
}

String InsertLengthdata(String data){
	int data_size = data.length() + 2;
	return data = data.substring(0,8) + data_size + data.substring(8, data_size);
}

void serial_analyse(String inputString, String *protocol, String *serial_num, String *data1, String *data2, String *data3) {
  char chara;
  String temp = "";
  *protocol = inputString.substring(0, 8);
  temp = inputString.substring(8, 10);
  int data_length = temp.toInt();
  temp = "";


  *serial_num = inputString.substring(10, 22);
  *data1 = "";
  *data2 = "";
  *data3 = "";
  int i = 22;
  chara = inputString[i];
  while (!(chara == ':' || i == data_length)) {
    temp += chara;
    i += 1;
    chara = inputString[i];
  }

  if (i != data_length) {
    *data1 = temp;
    temp = "";
    i += 1;
    chara = inputString[i];
    while (!(chara == ':' || i == data_length) ) {
      temp += chara;
      i += 1;
      chara = inputString[i];
    }

    if (i != data_length) {
      *data2 = temp;
      temp = "";
      i += 1;
      chara = inputString[i];
      while (!(chara == ':' || i == data_length) ) {
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

String get_confirm_key(String data) {
  int i = 0;
  char chara = data[i];
  String confirm_key;
  while (chara != '.' ) {
    i += 1;
    chara = data[i];
  }
  i += 1;
  chara = data[i];
  while (chara != '.' ) {
    i += 1;
    chara = data[i];
  }
  i += 1;
  chara = data[i];
  while (!(chara == '.' || i == data.length() + 1)) {
    confirm_key += chara;
    i += 1;
    chara = data[i];
  }
  return confirm_key;
}