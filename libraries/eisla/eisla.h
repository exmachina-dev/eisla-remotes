#ifndef EISLA_H_INCLUDED
#define EISLA_H_INCLUDED

#include <Arduino.h>

#define EISLA_DEBUG

#define EislaIdAddress 0x0      // EEPROM address

enum ProductIds {
    SWILL = 0x01,
    TEEDI = 0x02,
    SWIIP = 0x03,
};

typedef struct {
    uint8_t productId;
    uint8_t deviceId;

} eislaDevice;

typedef union {
    float toFloat;
    long toLong;
    struct {
        uint8_t int0;
        uint8_t int1;
        uint8_t int2;
        uint8_t int3;
    } toInt;
    uint8_t toBytes[4];
} binaryRepr;

typedef struct {
    char command;
    binaryRepr data;
} eislaCmd;

void setDeviceId(eislaDevice*, int);
void getDeviceInfos(eislaDevice*);
void saveDeviceInfos(eislaDevice*);
void sendDeviceInfos(eislaDevice*);
void send(eislaCmd*);

typedef struct {
    uint8_t r;
    uint8_t g;
    uint8_t b;
} rgbLed;

void setLed(rgbLed*, uint8_t);

#endif // EISLA_H_INCLUDED
