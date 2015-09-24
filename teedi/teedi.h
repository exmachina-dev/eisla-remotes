#ifndef TEEDI_H_INCLUDED
#define TEEDI_H_INCLUDED
#include <Arduino.h>
#include <eisla.h>

#define StatusLed 13
#define StatusBlinkDelay 400        // in milliseconds

#define MainLedR 7
#define MainLedG 8
#define MainLedB 9

#define ChanPin1 A0
#define ChanPin2 A1
#define ChanPin4 A2
#define ChanPin8 A3
#define ChanDelay 1000					// in milliseconds

#define ResolveDelay 100000				// in microseconds ( 100us = 0.10ms )
#define SwitchPinInterrupt 0
#define SwitchPin 2
#define TxPin 12

// #define DEBUG

eislaDevice teedi = {TEEDI};

rgbLed mainLed = {MainLedR, MainLedG, MainLedB};

void handleSwitchChange();

#endif  // TEEDI_H_INCLUDED
