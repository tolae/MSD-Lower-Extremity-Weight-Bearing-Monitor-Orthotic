#include <Arduino.h>

uint8_t mux_sel;
uint16_t sensor_input0;
uint16_t sensor_input1;

void setup() {
    Serial.begin(9600);
    while(!Serial);

    mux_sel = 0;

    delay(1000);
}

void loop() {
    digitalWrite(2, mux_sel & 0x01);
    digitalWrite(3, mux_sel & 0x02);

    delay(1);
    
    sensor_input0 = analogRead(A7);
    sensor_input1 = analogRead(A6);

    Serial.print("Weight A: ");
    Serial.println(sensor_input0);
    Serial.print("Weight B: ");
    Serial.println(sensor_input1);

    mux_sel = (++mux_sel) % 4;

    delay(1000);
}
