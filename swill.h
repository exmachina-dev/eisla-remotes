#include <Arduino.h>

#define StatusLed 13
#define StatusBlinkDelay 100
#define EncoderPinAInterrupt 0
#define EncoderPinBInterrupt 1
#define EncoderPinA 2
#define EncoderPinB 3

#define TicksPerRevolution 4096

#define SwillSerialBaud 57600
#define SwillDataLenght 4

#define ProductId 0x1
#define SwillIdAddress 0x0

#define SERIAL_PRINT_MODE

struct SerialCmd
{
    char command;
    #ifndef SERIAL_PRINT_MODE
    uint8_t data[SwillDataLenght];
    #else
    char data[SwillDataLenght];
    #endif // SERIAL_PRINT_MODE
    int data_lenght;
};

void send(SerialCmd);
void handleEncoderPinA();
void handleEncoderPinB();
