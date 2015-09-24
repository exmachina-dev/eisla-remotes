#include "eisla.h"

#include <Arduino.h>
#include <EEPROM.h>

void setDeviceId(eislaDevice* _dev, int _devId)
{
    _dev->deviceId = _devId;

}
void getDeviceInfos(eislaDevice* _dev)
{
    int _devId = (int)EEPROM.read(EislaIdAddress);
    if(_devId == 255)
        _devId = 0;

    setDeviceId(_dev, _devId);
}

void saveDeviceInfos(eislaDevice* _dev)
{
    EEPROM.write(EislaIdAddress, _dev->deviceId);
}

void sendDeviceInfos(eislaDevice* _dev)
{
    eislaCmd _cmd = {0, 0};
    _cmd.command = 'R';
    _cmd.data.toInt.int0 = _dev->productId;
    _cmd.data.toInt.int1 = _dev->deviceId;
    send(&_cmd);
}

void send(eislaCmd* cmd)
{
    Serial.write(cmd->command);
    Serial.write(cmd->data.toBytes, 4);
    Serial.write('\n');
}

void setLed(rgbLed* led, uint8_t color)
{
    digitalWrite(led->r, color % 1);
    digitalWrite(led->g, color % 2);
    digitalWrite(led->b, color % 4);
}
