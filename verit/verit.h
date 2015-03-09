#ifndef VERIT_H_INCLUDED
#define VERIT_H_INCLUDED
#include <Arduino.h>
#include <eisla.h>

#define StatusLed 13
#define StatusBlinkDelay 400        // in milliseconds

#define SpeedResolveDelay 10000     // in microseconds ( 10000µs = 10ms )
#define EncoderPinAInterrupt 0
#define EncoderPinBInterrupt 1
#define EncoderPinA 2
#define EncoderPinB 3

#define TicksPerRevolution 4096


eislaDevice verit = {VERIT};

#endif
