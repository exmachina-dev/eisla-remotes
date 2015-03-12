#include <Arduino.h>
#include <eisla.h>
#include <swill.h>

#include "digitalWriteFast.h"

volatile bool _EncoderPinASet;
volatile bool _EncoderPinBSet;

volatile long _EncoderTicks = 0;
long lastEncoderTicks = 0;

static unsigned int statusLedState = LOW;
static unsigned long statusLedTime = 0;

static unsigned long speedResolveTime = 0;
float speed;


int deviceId;

eislaCmd inputCmd;
bool newCmdEvent = false;

void setup() {
    // declare status led as output
    pinMode(StatusLed, OUTPUT);
    digitalWrite(StatusLed, HIGH);

    // Encoder pin A
    pinMode(EncoderPinA, INPUT);      // sets pin A as input
    digitalWrite(EncoderPinA, LOW);   // turn on pullup resistors
    attachInterrupt(EncoderPinAInterrupt, handleEncoderPinA, RISING);

    // Encoder pin B
    pinMode(EncoderPinB, INPUT);      // sets pin A as input
    digitalWrite(EncoderPinB, LOW);   // turn on pullup resistors
    attachInterrupt(EncoderPinBInterrupt, handleEncoderPinB, RISING);

    // Serial port
    Serial.begin(SwillSerialBaud);

    get_device_infos(&swill);
    if(swill.deviceId == 0)
    {
        set_device_id(&swill, 1);
        save_device_infos(&swill);
    }

    digitalWrite(StatusLed, LOW);
}

void loop() {
    if((micros()-speedResolveTime) >= (long)0)
    {
        long deltaTime = micros() - speedResolveTime;
        long deltaTicks = lastEncoderTicks - _EncoderTicks;
        speed = deltaTime / deltaTicks;

        lastEncoderTicks = _EncoderTicks;
        speedResolveTime = micros() + SpeedResolveDelay;
    }


    if(newCmdEvent)
    {
        switch(inputCmd.command) {
            eislaCmd _cmd;
            case 'R':
                if(0 <= inputCmd.data.toInt.int0 < 255)
                {
                    set_device_id(&swill, inputCmd.data.toInt.int0);
                    save_device_infos(&swill);
                }
                else
                {
                    send_device_infos(&swill);
                }
                break;
            case 'T':
                send_ticks();
                break;
            case 'S':
                send_speed();
                break;
        }

        newCmdEvent = false;
    }

    if((long)(millis()-statusLedTime) >= 0)
    {
        statusLedState =  (statusLedState==HIGH ? LOW : HIGH);
        digitalWriteFast(StatusLed, statusLedState);
        statusLedTime = millis()+StatusBlinkDelay;
    }
}

void serialEvent()
{
    if(Serial.available() > 0)
    {
        inputCmd.command = Serial.read();
        #ifdef EISLA_DEBUG
        if(Serial.readBytes((char*)inputCmd.data.toBytes, 4))
        {
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

void send_ticks()
{
    eislaCmd _c;
    _c.command = 'T';
    _c.data.toLong = _EncoderTicks;
    digitalWrite(StatusLed, HIGH);
    send(&_c);
}

void send_speed()
{
    eislaCmd _c;
    _c.command = 'S';
    _c.data.toFloat = speed;
    send(&_c);
}

void handleEncoderPinA()
{
    _EncoderPinBSet = digitalReadFast(EncoderPinB);

    _EncoderTicks -= _EncoderPinBSet ? -1 : +1;
}

void handleEncoderPinB()
{
    _EncoderPinASet = digitalReadFast(EncoderPinA);

    _EncoderTicks -= _EncoderPinASet ? -1 : +1;
}
