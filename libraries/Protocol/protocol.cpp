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

void Device::getAlivePing()
{
	Serial.print(_Protocol);
	Serial.print(_SerialNumber);
	Serial.print(_Alive);
	Serial.print(_End);
}

void Device::sendAlivePing()
{
	Serial.print(_Protocol);
	Serial.print(_SerialNumber);
	Serial.print(_Alive);
	Serial.print(_delimitator);
	Serial.print(_Confirm);
	Serial.print(_End);
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

void Device::getData(String data)
{
	Serial.print(_Protocol);
	Serial.print(_SerialNumber);
	Serial.print(data);
	Serial.print(_End);
}

String InsertLengthdata(String data){
	int data_size = data.length() + 2;
	return data = data.substring(0,8) + data_size + data.substring(8, data_size);
}

