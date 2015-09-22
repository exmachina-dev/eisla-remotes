#include <Arduino.h>
#include <eisla.h>
#include "swiip.h"

#include <digitalWriteFast.h>
#include <RH_ASK.h>
#include <SPI.h>

bool SwitchState;

static unsigned int statusLedState = LOW;
static unsigned long statusLedTime = 0;

RH_ASK rfDriver;
static unsigned int rfPinState = LOW;
static unsigned int lastRfPinState = LOW;
static unsigned long rfResolveTime = 0;


void setup() {
    // declare status led as output
    pinMode(StatusLed, OUTPUT);
    digitalWrite(StatusLed, HIGH);

    #ifdef DEBUG
    Serial.begin(9600);
    #endif // DEBUG

    // Switch pin
    pinMode(SwitchPin, OUTPUT);     // sets pin Switch as output
    digitalWrite(SwitchPin, LOW);   // turn on pullup resistors

    if(rfDriver.init()) {
        digitalWrite(StatusLed, LOW);
    } else {
        #ifdef DEBUG
        Serial.println("init failed");
        #endif // DEBUG
        delay(2000);
    }
}

void loop() {
    uint8_t buf[RH_ASK_MAX_MESSAGE_LEN];
    uint8_t buflen = sizeof(buf);

    if(rfDriver.recv(buf, &buflen))
    {
        #ifdef DEBUG
        Serial.println("received");
        rfDriver.printBuffer("Got:", buf, buflen);
        #endif // DEBUG
        digitalWriteFast(SwitchPin, HIGH);
        statusLedTime -= StatusBlinkDelay;
    } else {
        #ifdef DEBUG
        Serial.println("nothing received");
        #endif // DEBUG
        digitalWriteFast(SwitchPin, LOW);
    }

    if((long)(millis()-statusLedTime) >= 0)
    {
        statusLedState =  (statusLedState==HIGH ? LOW : HIGH);
        digitalWriteFast(StatusLed, statusLedState);
        statusLedTime = millis()+StatusBlinkDelay;
    }
}
