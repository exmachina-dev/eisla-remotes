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
	
	void getAlivePing();
	
	void sendAlivePing();
	
	void sendData(String data1, String data2);
	
	void getData(String data);
	
	private:
	
	String _Protocol;
	String _SerialNumber;
	String _End;
	String _delimitator;
	String _Alive;
	String _Confirm;

};


#endif