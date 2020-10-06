#include <Arduino.h>
#include "inc/mega.h"
#include "inc/timer.h"
#include "inc/home_screen.h"

/**
 * @brief Configures timer 1 interrupt delays at 4Hz (250ms) and 2Hz (500ms)
 *
 */
int circle_status = 0; //0 is off

void call(void (*circle_on)(void), void (*circle_off)(void)) {
    if (circle_status == 0) {
        circle_on();
        circle_status = 1;
    }
    else {
        circle_off();
        circle_status = 0;
    }
}

void configure_timer1()
{
    // initialize timer1 
	Serial.println("Start");
    //noInterrupts();           // disable all interrupts
    TCCR1A = 0;
    TCCR1B = 0;
    TCNT1 = 0;
    OCR1A = 124;            // Set CH A for 250 ms delay (125 ticks)

    TCCR1B |= (1 << WGM12);   // CTC mode
    TCCR1B |= (1 << CS22) | (1 << CS21) | (1 << CS20);;    // 1024 prescaler 
    TIMSK1 |= (1 << OCIE1A);  // enable timer compare interrupt
    //interrupts();             // enable all interrupts


//	noInterrupts();
//    // Set to normal operation
//    TCCR1A = 0;
//    // Set the prescalar value to 1024
//    TCCR1B |= (1 << CS22) | (1 << CS21) | (1 << CS20);
//    // Clear count in case it is not zero
//    TCNT1 = 0;
//    // Set CH A for 250 ms delay (125 ticks)
//    OCR1A = 124;
//    // Set CH B for 500 ms delay (250 ticks)
//    OCR1B = 249;
	Serial.println("Finish");
}


ISR(TIMER1_COMPA_vect)          // timer compare interrupt service routine
{
    call(&circle_on, &circle_off);

}
