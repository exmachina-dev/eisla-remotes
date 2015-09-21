#ifndef EISLA_H_INCLUDED
#define EISLA_H_INCLUDED

#include <Arduino.h>

#define EISLA_DEBUG

#define EislaIdAddress 0x0      // EEPROM address

enum ProductIds {
    SWILL = 1,
    VERIT_TX = 2,
    VERIT_RX = 3,
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

void set_device_id(eislaDevice*, int);
void get_device_infos(eislaDevice*);
void save_device_infos(eislaDevice*);
void send_device_infos(eislaDevice*);
void send(eislaCmd*);

#endif // EISLA_H_INCLUDED
