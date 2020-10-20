#include "TestCommon.h"

void save_test_results(test_eeprom_t test_eeprom)
{
    EEPROM.put(0, *test_eeprom);
}

void get_test_results(test_eeprom_t *out_test_eeprom)
{
    EEPROM.get(0, *out_test_eeprom);
}
