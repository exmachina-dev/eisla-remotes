#ifndef SWILL_H_INCLUDED
#define SWILL_H_INCLUDED
#include <Arduino.h>
#include <eisla.h>

#define StatusLed 5
#define LoopLed 6
#define TurnLed 7

#define StatusBlinkDelay 500        // in milliseconds
#define SpeedResolveDelay 10000     // in microseconds ( 10000µs = 10ms )
#define ContinuousModeDelay 250        // in milliseconds

#define EncoderPinA 2
#define EncoderPinB 3

#define TicksPerRevolution 4096

#define SwillSerialBaud 57600
#define SwillDataLenght 4

eislaDevice swill = {SWILL};

void setup();
void loop();

void sendTicks();
void sendSpeed();
void sendTurns();

#endif // SWILL_H_INCLUDED
