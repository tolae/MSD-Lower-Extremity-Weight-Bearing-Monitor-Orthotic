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
    private:
        static const char EXIST[2] = "OK";
};

#endif
