// Copyright 2015 Benoit Rapidel

#include <Arduino.h>
#include <eisla.h>
#include "./blinky.h"

#include <digitalWriteFast.h>

static long statusLedState = LOW;
static long turnLedState = LOW;
static long loopLedState = LOW;

unsigned long statusLedTime = 0;
unsigned long turnLedTime = 0;
unsigned long loopLedTime = 0;

void setup() {
    // declare status leds as output
    pinMode(StatusLed, OUTPUT);
    pinMode(LoopLed, OUTPUT);
    pinMode(TurnLed, OUTPUT);
    digitalWrite(StatusLed, HIGH);
    digitalWrite(LoopLed, HIGH);
    digitalWrite(TurnLed, HIGH);
}

void loop() {
    if ((long)(millis()-statusLedTime) >= 0) {
        statusLedState = (statusLedState == HIGH ? LOW : HIGH);
        digitalWriteFast(StatusLed, statusLedState);
        statusLedTime = millis() + StatusBlinkDelay;
    }
    if ((long)(millis()-loopLedTime) >= 0) {
        loopLedState = (loopLedState == HIGH ? LOW : HIGH);
        digitalWriteFast(LoopLed, loopLedState);
        loopLedTime = millis() + LoopBlinkDelay;
    }
    if ((long)(millis()-turnLedTime) >= 0) {
        turnLedState = (turnLedState == HIGH ? LOW : HIGH);
        digitalWriteFast(TurnLed, turnLedState);
        turnLedTime = millis() + TurnBlinkDelay;
    }
}
