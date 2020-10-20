#include <Arduino.h>
#include <BluetoothCommon.h>

BluetoothMod* mod;
BluetoothMod::blue_package_t package;
String a;
String command[2] = {"AT","AT+CON90E2029FD1A7"};

void setup() {
	// put your setup code here, to run once:
	Serial.begin(9600);
	while(!Serial);

	Serial1.begin(9600);
	while(!Serial1);

	for(int i=0; i<2; i++){
		Serial.println(command[i]); //Write to Serial
		Serial1.print(command[i]); //Write HM-10
		while (!Serial1.available()) { //Wait for HM-10 to respond
		}
		a = Serial1.readString(); //Read from HM-10
		Serial.println(a); //Print HM-10 String to Serial
	}

	mod = new BluetoothMod(Serial1);
}

void loop() {
	mod->update();
	if (mod->receivePackage(package) != BluetoothMod::BluetoothStatus::BUSY)
	{
		Serial.println("Received package!");
		Serial.print("Opcode: ");
		Serial.println(package.opcode);
		Serial.print("Len: ");
		Serial.println(package.len);
		for (uint8_t i = 0; i < package.len; i++)
		{
			Serial.print("Data ");
			Serial.print(i);
			Serial.print(": ");
			Serial.println(package.data[i], HEX);
		}
		Serial.print("CRC: ");
		Serial.println(package.crc, HEX);
	}
    if (Serial.available())
    {
        BluetoothMod::blue_package_t package;
        a = Serial.readString();
        Serial.println(a);
        if (a == "A")
        {
            Serial.println("Sending alive package");
            // Send Alive package
            package.opcode = BluetoothMod::BluetoothPackageIDs::ALIVE;
            package.len = 0;
            package.crc = 0xAE;
            mod->transmitPackage(package);
        }
        else if (a == "S")
        {
            Serial.println("Sending status package");
            // Send random status value
            package.opcode = BluetoothMod::BluetoothPackageIDs::STATUS;
            package.len = random(0, 7);
            package.crc = 0xAE;
            for (uint8_t i = 0; i < package.len; i++)
            {
                package.data[i] = random(0, 255);
            }
            mod->transmitPackage(package);
        }
        else if (a == "W")
        {
            Serial.println("Sending weight package");
            // Send random weight value
            package.opcode = BluetoothMod::BluetoothPackageIDs::WEIGHT;
            package.len = 2;
            package.crc = 0xAE;
            package.data[0] = random(0, 255);
            package.data[1] = random(0, 255);
            mod->transmitPackage(package);
        }
        else
        {
            Serial.print("Packages: ");
            Serial.println(mod->tx_packages);
            Serial.print("State: ");
            Serial.println(static_cast<int>(mod->_tx_state));
            Serial.print("Can write: ");
            Serial.println(Serial1.availableForWrite());
        }
    }
}
