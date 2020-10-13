#include <AltSoftSerial.h>
#include <BluetoothTestCommon.h>

AltSoftSerial BTserial;
BluetoothTestCommon BTtester;

void setup()
{
	char buffer[10] = { 0 };
	uint8_t i = 0;
	// Setup serial connections
	Serial.begin(9600);
	while(!Serial);
	BTserial.begin(9600);
	// Pause so serial can initialize
	delay(1000);

	//// TEST BEGIN ////
	Serial.print("Running {bt_check_exist} test\n");
	// Send AT command
	BTserial.write("AT");
	// Wait for response
	delay(2000);
	// Save response to buffer
	i = 0;
	while (BTserial.available())
	{
		buffer[i++] = BTserial.read();
	}
	// Run test
	if (BTtester.bt_check_exist(buffer) == FAILURE)
	{
		Serial.print("Test {bt_check_exist} FAILED\n");
	}
	else
	{
		Serial.print("Test {bt_check_exist} PASSED\n");
	}
}

void loop() {}
