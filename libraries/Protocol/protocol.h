#ifndef PROTOCOL_H_INCLUDED
#define PROTOCOL_H_INCLUDED

#include <Arduino.h>


class Device 
{
	
	public: 

    /**
    Constructor for the device class
    
    @param SerialNumber SerialNumber of the device
    
    @return None
    
    DEVICE(String SerialNumber);
    */
	Device(String Serial);

	void sendData(String data1, String command);

	void sendData(String data1, String command, String value);
	

	private:
	
	String _Protocol;
	String _SerialNumber;
	String _End;
	String _delimitator;
	String _Alive;
	String _Confirm;

};

String InsertLengthdata(String data);

void serial_analyse(String inputString, String *protocol, String *serial_num, String *data1, String *data2, String *data3);

String get_confirm_key(String data);

#endif