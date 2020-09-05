#include "BluetoothTestCommon.h"

BluetoothTestCommon::BluetoothTestCommon() {}

uint8_t BluetoothTestCommon::bt_check_exist(char* buffer) {
    for (int i = 0; i < sizeof(BluetoothTestCommon::EXIST); i++) {
        if (buffer[i] != BluetoothTestCommon::EXIST[i]) return FAILURE;
    }
    return SUCCESS;
}

uint8_t BluetoothTestCommon::bt_check_connect(char* buffer) {
    return SUCCESS; // TODO
}
