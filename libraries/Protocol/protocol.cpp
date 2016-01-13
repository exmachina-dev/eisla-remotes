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

void Device::sendData(String data1, String data2) 
{
	Serial.print(_Protocol);
	Serial.print(_SerialNumber);
	Serial.print(data1);
	Serial.print(_delimitator);
	Serial.print(data2);
	Serial.print(_End);

}

void Device::getData(String data)
{
	Serial.print(_Protocol);
	Serial.print(_SerialNumber);
	Serial.print(data);
	Serial.print(_End);
}
