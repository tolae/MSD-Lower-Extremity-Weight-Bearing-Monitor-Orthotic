#include <Arduino.h>
#include "inc\timer.h"

/**
 * @brief Configures timer 1 interrupt delays at 4Hz (250ms) and 2Hz (500ms)
 * 
 */
void configure_timer1()
{
    // Set to normal operation
    TCCR1A = 0;
    // Set the prescalar value to 1024
    TCCR1B |= (1 << CS22) | (1 << CS21) | (1 << CS20);
    // Clear count in case it is not zero
    TCNT1 = 0;
    // Set CH A for 250 ms delay (125 ticks)
    OCR1A = 124;
    // Set CH B for 500 ms delay (250 ticks)
    OCR1B = 249;
}
