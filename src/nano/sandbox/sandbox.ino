#include <AltSoftSerial.h>
#include <BluetoothCommon.h>

String a;
char buffer[32];

AltSoftSerial BTserial;
BluetoothMod* mod;
BluetoothMod::blue_package_t package;

void setup() {
    Serial.begin(9600);
    Serial.setTimeout(100);
    while(!Serial);

    BTserial.begin(9600);

    mod = new BluetoothMod(BTserial);
    delay(1000);
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

    if (Serial.available() > 0) { //If Serial buffer >0, read line, print to serial and HM-10
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
            Serial.println(BTserial.availableForWrite());
        }
    }

    memset(&package, 0, sizeof(BluetoothMod::blue_package_t));
}
