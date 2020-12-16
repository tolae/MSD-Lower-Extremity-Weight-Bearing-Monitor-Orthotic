#include <Arduino.h>
#include <AltSoftSerial.h>

#define CONNECTED 7

AltSoftSerial BTserial;

void setup() {
    Serial.begin(9600);
    while(!Serial);

    BTserial.begin(9600);

    delay(1000);
}

void loop() {
    if (Serial.available())
    {
        String str = Serial.readString();
        Serial.println(str);
        BTserial.print(str);
    }
    if (BTserial.available())
    {
        String str = BTserial.readString();
        Serial.println(str);
    }
}
