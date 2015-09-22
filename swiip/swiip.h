#ifndef SWIIP_H_INCLUDED
#define SWIIP_H_INCLUDED
#include <Arduino.h>
#include <eisla.h>

#define StatusLed 13
#define StatusBlinkDelay 200        // in milliseconds

#define MainLedR 9
#define MainLedG 7
#define MainLedB 8

#define ResolveDelay 100            // in microseconds ( 100µs = 0.10ms )
#define CarriageDetectPin 4
#define RxPin 7

#define SwitchPin 2

#define DEBUG

eislaDevice swiip = {SWIIP};

void handleSwitchChange();
void set_main_led(uint8_t color);

#endif
