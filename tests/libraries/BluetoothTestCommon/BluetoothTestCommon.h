#ifndef BLUETOOTH_TEST_COMMON_H
#define BLUETOOTH_TEST_COMMON_H

#include "Arduino.h"
#include "TestCommon.h"

class BluetoothTestCommon
{
    public:
        BluetoothTestCommon();
        uint8_t bt_check_exist(char* buffer);
        uint8_t bt_check_connect(char* buffer); 
};

#endif
