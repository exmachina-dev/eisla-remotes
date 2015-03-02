#include <swill.h>
#include <Arduino.h>
#include <EEPROM.h>
#include "digitalWriteFast.h"

volatile bool _EncoderPinASet;
volatile bool _EncoderPinBSet;

volatile long _EncoderTicks = 0;

int deviceId;

SerialCmd inputCmd;
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

    deviceId = EEPROM.read(SwillIdAddress);
    if(deviceId == 255)
        deviceId = 0;
    SerialCmd r;
    r.command = 'R';
    r.data[0] = ProductId;
    r.data[1] = deviceId;
    r.data_lenght = 2;
    send(r);
    digitalWrite(StatusLed, LOW);
}

void loop() {
    static unsigned int statusLedState = LOW;
    static unsigned long statusLedTime = 0;

    if(newCmdEvent)
    {
        switch(inputCmd.command) {
            case 'R':
                if(0 <= inputCmd.data[1] < 255)
                {
                    deviceId = int(inputCmd.data[1]);
                    EEPROM.write(SwillIdAddress, deviceId);
                }
                break;
            case 'G':
                SerialCmd r = {'T', _EncoderTicks};
                send(r);
        }

        newCmdEvent = false;
    }

    if((long)(millis()-statusLedTime) >=0)
    {
        statusLedState =  (statusLedState==HIGH ? LOW : HIGH);
        digitalWriteFast(StatusLed, statusLedState);
        statusLedTime = millis()+StatusBlinkDelay;
    }
}

void serialEvent()
{
    if(Serial.available() >= 2)
    {
        inputCmd.command = Serial.read();
        if(Serial.readBytesUntil('\n', (char*)inputCmd.data, SwillDataLenght))
        {
            Serial.print("CMD: ");
            Serial.print(inputCmd.command);
            Serial.print(" DAT: ");
            #ifndef SERIAL_PRINT_MODE
            Serial.println((char*)inputCmd.data);
            #else
            Serial.println(inputCmd.data);
            #endif // SERIAL_PRINT_MODE
        }
        newCmdEvent = true;
    }
}

void send(SerialCmd cmd)
{
    #ifndef SERIAL_PRINT_MODE
    Serial.write(cmd.command);
    Serial.write(cmd.data, cmd.data_lenght);
    Serial.write('\n');
    #else
    Serial.print(cmd.command);
    Serial.print(cmd.data);
    Serial.print('\n');
    #endif // SERIAL_PRINT_MODE
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
