#ifndef VERIT_TX_H_INCLUDED
#define VERIT_TX_H_INCLUDED
#include <Arduino.h>
#include <eisla.h>

#define StatusLed 13
#define StatusBlinkDelay 400        // in milliseconds

#define MainLedR 9
#define MainLedG 7
#define MainLedB 8

#define ResolveDelay 100000            // in microseconds ( 100µs = 0.10ms )
#define SwitchPinInterrupt 0
#define SwitchPin 2
#define TxPin 12

//#define DEBUG

eislaDevice verit = {VERIT_TX};

typedef struct {
    uint8_t r_pin;
    uint8_t g_pin;
    uint8_t b_pin;
} rgbLed;

void handleSwitchChange();
void set_main_led(uint8_t color);

#endif
