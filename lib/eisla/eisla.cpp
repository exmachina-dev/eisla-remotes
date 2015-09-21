#include <eisla.h>

#include <Arduino.h>
#include <EEPROM.h>

void set_device_id(eislaDevice* _dev, int _devId)
{
    _dev->deviceId = _devId;

}
void get_device_infos(eislaDevice* _dev)
{
    int _devId = (int)EEPROM.read(EislaIdAddress);
    if(_devId == 255)
        _devId = 0;

    set_device_id(_dev, _devId);
}

void save_device_infos(eislaDevice* _dev)
{
    EEPROM.write(EislaIdAddress, _dev->deviceId);
}

void send_device_infos(eislaDevice* _dev)
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
