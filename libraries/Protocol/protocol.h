#ifndef PROTOCOL_H_INCLUDED
#define PROTOCOL_H_INCLUDED
#include <ST7036.h>
#include <Arduino.h>

using namespace std ;

typedef union {
    char toChar[100];    
    uint8_t toBytes[100];

} buff;

typedef union {

	 struct {
    	uint8_t int0;
        uint8_t int1;
    } toInt;
    /*
    struct {
    	uint8_t char0;
        uint8_t char1;
    } toChar;*/
    char toChar[1];    
    uint8_t toBytes[1];

} binaryRepr;

typedef struct {
	uint8_t lenght;
	char data[100];
} Packet;

class Device 
{
	
	public: 
	
    /**
    Constructor for the device class
    
    @param SerialNumber SerialNumber of the device
    
    @return None
    
    DEVICE(String SerialNumber);
    */
	Device();

	void sendData(String data1, String command);

	void sendData(String data1, String command, String value);
	

	private:
	String _Protocol;
	String _SerialNumber;
	String _End;
	String _delimitator;


};


void serial_analyse(String inputString, String *protocol, String *serial_num, String *data1, String *data2, String *data3);

String get_confirm_key(String *str, String *key);


#endif