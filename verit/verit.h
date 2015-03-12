#ifndef VERIT_H_INCLUDED
#define VERIT_H_INCLUDED
#include <Arduino.h>
#include <eisla.h>

#define StatusLed 13
#define StatusBlinkDelay 400        // in milliseconds

#define MainLedR 9
#define MainLedG 8
#define MainLedB 7

#define ResolveDelay 100            // in microseconds ( 100µs = 0.10ms )
#define SwitchPinInterrupt 0
#define SwitchPin 2
#define TxPin 12

eislaDevice verit = {VERIT};

typedef struct {
    uint8_t r_pin;
    uint8_t g_pin;
    uint8_t b_pin;
} rgbLed;

void handleSwitchChange();
void set_main_led(uint8_t color);

#endif
