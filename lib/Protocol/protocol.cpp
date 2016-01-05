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
	_End = "\t\n";
	_delimitateur = ':';
}

void Device::sendDeviceInfo()
{
	Serial.print(_Protocol);
	Serial.print(_SerialNumber);
	Serial.print(_End);
}

void Device::sendData(String data1, String data2) 
{
	Serial.print(_Protocol);
	Serial.print(_SerialNumber);
	Serial.print(data1);
	Serial.print(_delimitateur);
	Serial.print(data2);
	Serial.print(_End);

}
