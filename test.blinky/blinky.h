#ifndef BLINKY_H_INCLUDED
#define BLINKY_H_INCLUDED
#include <Arduino.h>
#include <eisla.h>

#define StatusLed 5
#define LoopLed 6
#define TurnLed 7

#define StatusBlinkDelay 500        // in milliseconds
#define TurnBlinkDelay 10     // in microseconds ( 10000µs = 10ms )
#define LoopBlinkDelay 250        // in milliseconds

void setup();
void loop();

#endif // BLINKY_H_INCLUDED
