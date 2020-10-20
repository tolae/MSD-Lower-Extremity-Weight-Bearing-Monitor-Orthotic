#ifndef TEST_COMMON_H
#define TEST_COMMON_H

#include <Arduino.h>

#define SUCCESS 0
#define FAILURE 1

typedef struct test_eeprom
{
    uint8_t bluetooth_test_results : 1;
} test_eeprom_t;

void save_test_results(test_eeprom_t *test_eeprom);
void get_test_results(test_eeprom_t *out_test_eeprom);

#endif
