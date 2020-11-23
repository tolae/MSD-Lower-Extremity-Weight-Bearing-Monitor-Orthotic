#include "inc/vibrator_motor.h"

void VibratorMotor::enable()
{
    analogWrite(pin, (uint8_t)(strength * 255.0f));
}

void VibratorMotor::disable()
{
    analogWrite(pin, 0);
}

