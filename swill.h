#ifndef SWILL_H_INCLUDED
#define SWILL_H_INCLUDED
#include <Arduino.h>

#define StatusLed 13
#define StatusBlinkDelay 500        // in milliseconds

#define SpeedResolveDelay 10000     // in microseconds ( 10000µs = 10ms )
#define EncoderPinAInterrupt 0
#define EncoderPinBInterrupt 1
#define EncoderPinA 2
#define EncoderPinB 3

#define TicksPerRevolution 4096

#define SwillSerialBaud 57600
#define SwillDataLenght 4

eislaDevice swill = {SWILL};

void send_ticks();
void send_speed();

void handleEncoderPinA();
void handleEncoderPinB();

#endif
