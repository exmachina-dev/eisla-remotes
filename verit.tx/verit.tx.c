#include <Arduino.h>
#include <eisla.h>
#include <verit.tx.h>

#define RH_ASK_ARDUINO_USE_TIMER2

#include <digitalWriteFast.h>
#include <RH_ASK.h>

RH_ASK rfDriver;

volatile bool _SwitchState;

static unsigned int statusLedState = LOW;
static unsigned long statusLedTime = 0;

static unsigned int rfPinState = LOW;
static unsigned long rfResolveTime = 0;

rgbLed mainLed = {MainLedR, MainLedG, MainLedB};


void setup() {
    // declare status led as output
    pinMode(StatusLed, OUTPUT);
    digitalWrite(StatusLed, HIGH);

    // Serial debug
    #ifdef DEBUG
    Serial.begin(9600);
    #endif // DEBUG

    // Main led
    pinMode(mainLed.r_pin, OUTPUT);
    pinMode(mainLed.g_pin, OUTPUT);
    pinMode(mainLed.b_pin, OUTPUT);
    set_main_led(3);

    // Switch pin
    pinMode(SwitchPin, INPUT);      // sets pin Switch as input
    digitalWrite(SwitchPin, LOW);   // turn on pullup resistors
    attachInterrupt(SwitchPinInterrupt, handleSwitchChange, CHANGE);

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
    if((micros()-rfResolveTime) >= (long)0)
    {
        if (_SwitchState == HIGH) {
            const char *msg = "OK";

            #ifdef DEBUG
            Serial.println("sending OK");
            #endif // DEBUG
            rfDriver.send((uint8_t *)msg, strlen(msg));
            rfDriver.waitPacketSent();

            set_main_led(2);
        }
        else {
            set_main_led(1);
            #ifdef DEBUG
            Serial.println("not sending OK");
            #endif // DEBUG
        }

        rfResolveTime = micros() + ResolveDelay;
    }

    if((long)(millis()-statusLedTime) >= 0)
    {
        statusLedState =  (statusLedState==HIGH ? LOW : HIGH);
        digitalWriteFast(StatusLed, statusLedState);
        statusLedTime = millis()+StatusBlinkDelay;
    }
}

void handleSwitchChange()
{
    _SwitchState = digitalReadFast(SwitchPin);
}

void set_main_led(uint8_t color)
{
    if (color == 1) {
        digitalWrite(mainLed.r_pin, HIGH);
        digitalWrite(mainLed.g_pin, LOW);
        digitalWrite(mainLed.b_pin, LOW);
    }
    else if (color == 2) {
        digitalWrite(mainLed.r_pin, LOW);
        digitalWrite(mainLed.g_pin, HIGH);
        digitalWrite(mainLed.b_pin, LOW);
    }
    else if (color == 3) {
        digitalWrite(mainLed.r_pin, LOW);
        digitalWrite(mainLed.g_pin, LOW);
        digitalWrite(mainLed.b_pin, HIGH);
    }
    else {
        digitalWrite(mainLed.r_pin, LOW);
        digitalWrite(mainLed.g_pin, LOW);
        digitalWrite(mainLed.b_pin, LOW);
    }
}
