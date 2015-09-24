// Copyright 2015 Benoit Rapidel

#include <Arduino.h>
#include <eisla.h>
#include "./swill.h"

#include <digitalWriteFast.h>
//#define ENCODER_OPTIMIZE_INTERRUPTS
#include <Encoder.h>

long encoderTicks;
long lastEncoderTicks;
long encoderTurns;
float encoderSpeed;

static unsigned long statusLedState = LOW;

unsigned long statusLedTime = 0;
unsigned long speedResolveTime = 0;
unsigned long continuousModeTime = 0;

bool continuousMode = true;

int deviceId;

eislaCmd inputCmd;
bool newCmdEvent = false;

Encoder swillEnc(EncoderPinA, EncoderPinB);

void setup() {
    // declare status leds as output
    pinMode(StatusLed, OUTPUT);
    pinMode(LoopLed, OUTPUT);
    pinMode(TurnLed, OUTPUT);
    digitalWrite(StatusLed, HIGH);
    digitalWrite(LoopLed, HIGH);
    digitalWrite(TurnLed, HIGH);

    // Serial port
    //Serial.begin(SwillSerialBaud);

    getDeviceInfos(&swill);
    if (swill.deviceId == 0) {
        setDeviceId(&swill, 1);
        saveDeviceInfos(&swill);
    }

    digitalWrite(StatusLed, LOW);
}

void loop() {
    encoderTicks = swillEnc.read();
    //encoderTurns = encoderTicks / TicksPerRevolution;

    if (((long)micros()-speedResolveTime) >= 0) {
        long deltaTime = micros() - speedResolveTime;
        long deltaTicks = lastEncoderTicks - encoderTicks;
        encoderSpeed = deltaTime / deltaTicks;

        lastEncoderTicks = encoderTicks;
        speedResolveTime = micros() + SpeedResolveDelay;
    }

    if ((long)(millis()-statusLedTime) >= 0) {
        statusLedState = (statusLedState == HIGH ? LOW : HIGH);
        digitalWriteFast(StatusLed, statusLedState);
        statusLedTime = millis() + StatusBlinkDelay;
    }

    if (continuousMode && (long)(millis()-continuousModeTime) >= 0) {
        sendTicks();
        sendSpeed();
        sendTurns();
        statusLedTime = millis() + ContinuousModeDelay;
    }

    if (newCmdEvent) {
        switch (inputCmd.command) {
            case 'R':
                if (0 <= inputCmd.data.toInt.int0 && \
                    inputCmd.data.toInt.int0 < 255) {
                    setDeviceId(&swill, inputCmd.data.toInt.int0);
                    saveDeviceInfos(&swill);
                }
                else {
                    sendDeviceInfos(&swill);
                }
                break;
            case 'T':
                sendTicks();
                break;
            case 'S':
                sendSpeed();
                break;
        }

        newCmdEvent = false;
    }
}

void serialEvent() {
    if (Serial.available() > 0) {
        inputCmd.command = Serial.read();
        #ifdef EISLA_DEBUG
        if (Serial.readBytes((char*)inputCmd.data.toBytes, 4)) {
            Serial.print("CMD: ");
            Serial.print(inputCmd.command);
            Serial.print(" DAT: ");
            Serial.println((char*)inputCmd.data.toBytes);
        }
        #else
        Serial.readBytes((char*)inputCmd.data.toBytes, 4);
        #endif // EISLA_DEBUG
        newCmdEvent = true;
    }
}

void sendTicks() {
    eislaCmd _c;
    _c.command = 'T';
    _c.data.toLong = encoderTicks;
    digitalWrite(StatusLed, HIGH);
    send(&_c);
}

void sendSpeed()
{
    eislaCmd _c;
    _c.command = 'S';
    _c.data.toFloat = encoderSpeed;
    send(&_c);
}

void sendTurns()
{
    eislaCmd _c;
    _c.command = 'U';
    _c.data.toFloat = encoderTurns;
    send(&_c);
}