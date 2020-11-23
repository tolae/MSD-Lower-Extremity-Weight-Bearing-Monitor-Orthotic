#ifndef _VIBRATOR_MOTOR_H
#define _VIBRATOR_MOTOR_H

#include <Arduino.h>

class VibratorMotor
{
    private:
        uint8_t pin;

    public:
        float strength;

        VibratorMotor(uint8_t pin, float init_strgth) :
            pin(pin),
            strength(init_strgth)
        {
            pinMode(pin, OUTPUT);
        }

        void enable();
        void disable();
};

#endif
