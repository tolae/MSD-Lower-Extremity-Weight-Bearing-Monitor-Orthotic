#include "BluetoothTestCommon.h"

char EXIST[2] = "OK";

BluetoothTestCommon::BluetoothTestCommon() {}

uint8_t BluetoothTestCommon::bt_check_exist(char* buffer) {
    for (int i = 0; i < sizeof(EXIST); i++) {
        if (buffer[i] != EXIST[i]) return FAILURE;
    }
    return SUCCESS;
}

uint8_t BluetoothTestCommon::bt_check_connect(char* buffer) {
    return SUCCESS; // TODO
}
