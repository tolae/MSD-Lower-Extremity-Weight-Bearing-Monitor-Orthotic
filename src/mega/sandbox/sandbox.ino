#include <Arduino.h>
#include <BluetoothCommon.h>
#include <Queue.h>

BluetoothMod::blue_package_t stuff;

void setup()
{
	Serial.begin(9600);
	while (!Serial);
	Queue<BluetoothMod::blue_package_t> q(3);
	Serial.print("Size: ");
	Serial.println(q.size);
	Serial.print("Empty?: ");
	Serial.println(q.empty());
	stuff.id = 0xFF;
	stuff.crc = 0xAE;
	q.push(stuff);
	stuff.id = 0xBB;
	stuff.crc = 0xAE;
	q.push(stuff);
	stuff.id = 0xAA;
	stuff.crc = 0xAE;
	q.push(stuff);
	Serial.print("Count: ");
	Serial.println(q.count);
	Serial.print("Full?: ");
	Serial.println(q.full());
	stuff = q.pop();
	Serial.print("Package: ");
	Serial.println(stuff.id);
	Serial.print("Count: ");
	Serial.println(q.count);
	stuff.id = 0xEE;
	stuff.crc = 0xAE;
	q.push(stuff);
	stuff = q.pop();
	Serial.print("Package: ");
	Serial.println(stuff.id);
	Serial.print("Count: ");
	Serial.println(q.count);
	stuff = q.pop();
	Serial.print("Package: ");
	Serial.println(stuff.id);
	Serial.print("Count: ");
	Serial.println(q.count);
	stuff = q.pop();
	Serial.print("Package: ");
	Serial.println(stuff.id);
	Serial.print("Count: ");
	Serial.println(q.count);
	stuff = q.pop();
	Serial.print("Package: ");
	Serial.println(stuff.id);
	Serial.print("Count: ");
	Serial.println(q.count);
}

void loop()
{

}
