#ifndef PROTOCOL_H_INCLUDED
#define PROTOCOL_H_INCLUDED
#include <ST7036.h>
#include <Arduino.h>

using namespace std ;


typedef union {
   struct {
      unsigned int int0;
      unsigned int int1;
    } toInt;
    struct {
      uint8_t bool0;
      uint8_t bool1;
      uint8_t bool2;
      uint8_t bool3;
    } toBool;
    float toFloat;
    char toChar[4];
    uint8_t toBytes[4];
} binaryRepr;

typedef struct {
  uint8_t length;
  byte data[150];
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
  void sendData(String data1, String command, bool value);
  void sendData(String data1, String command, unsigned int value);
  void sendData(String data1, String command, float value);
  void sendData(String data1, String command, String value);

  private:
  String _Protocol;
  String _SerialNumber;
  String _End;
  String _delimitator;

};

String get_confirm_key(String *str, String *key);


#endif