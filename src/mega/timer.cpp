#include <Arduino.h>
#include "inc/timer.h"

void (*registered_callback)(void);

inline void _set_desired_freq(uint16_t target_freq, uint16_t prescaler);

void configure_timer1(void (*callback)(void), uint16_t target_freq, timer_prescaler_t prescaler)
{
	cli();

	// Clear any previous configurations
	TCCR1A = 0;
	TCCR1B = 0;
	TCNT1  = 0;
	// Set timer to restart when matching (CTC Mode)
	TCCR1B |= (1 << WGM12);
	// set compare match register for desired frequency
	_set_desired_freq(target_freq, TIMER_PRESCALER_MAP[prescaler]);
	// Set prescaler bits as desired
	TCCR1B |= prescaler;
	// enable timer compare interrupt
	TIMSK1 |= (1 << OCIE1A);

	registered_callback = callback;

	sei();
}

inline void _set_desired_freq(uint16_t target_freq, uint16_t prescaler)
{
	OCR1A = F_CPU / (target_freq * prescaler - 1);
}

ISR(TIMER1_COMPA_vect)          // timer compare interrupt service routine
{
	registered_callback();
}
