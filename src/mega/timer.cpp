#include <Arduino.h>
#include "inc/timer.h"

void (*registered_callback)(void);

inline uint16_t _desired_freq(uint16_t target_freq, uint16_t prescaler);

Timer* TIM0 = new Timer();
Timer* TIM1 = new Timer();
Timer* TIM2 = new Timer();
#if defined(__AVR_ATmega1280__) || defined(__AVR_ATmega2560__)
Timer* TIM3 = new Timer();
Timer* TIM4 = new Timer();
Timer* TIM5 = new Timer();
#endif

void configure_timer0(void (*callback)(void), uint16_t target_freq, timer_prescaler_t prescaler);
void configure_timer1(void (*callback)(void), uint16_t target_freq, timer_prescaler_t prescaler);
void configure_timer2(void (*callback)(void), uint16_t target_freq, timer_prescaler_t prescaler);
#if defined(__AVR_ATmega1280__) || defined(__AVR_ATmega2560__)
void configure_timer3(void (*callback)(void), uint16_t target_freq, timer_prescaler_t prescaler);
void configure_timer4(void (*callback)(void), uint16_t target_freq, timer_prescaler_t prescaler);
void configure_timer5(void (*callback)(void), uint16_t target_freq, timer_prescaler_t prescaler);
#endif

void disable_timer0();
void disable_timer1();
void disable_timer2();
#if defined(__AVR_ATmega1280__) || defined(__AVR_ATmega2560__)
void disable_timer3();
void disable_timer4();
void disable_timer5();
#endif

Timer::Timer()
{
	// Nothing to do
}

void configure_timer(timer_module_t timx, void (*callback)(void), uint16_t target_freq, timer_prescaler_t prescaler)
{
	cli();

	switch(timx)
	{
		case TimerModule::TIM_0:
			configure_timer0(callback, target_freq, prescaler);
			break;
		case TimerModule::TIM_1:
			configure_timer1(callback, target_freq, prescaler);
			break;
		case TimerModule::TIM_2:
			configure_timer2(callback, target_freq, prescaler);
			break;
		#if defined(__AVR_ATmega1280__) || defined(__AVR_ATmega2560__)
		case TimerModule::TIM_3:
			configure_timer3(callback, target_freq, prescaler);
			break;
		case TimerModule::TIM_4:
			configure_timer4(callback, target_freq, prescaler);
			break;
		case TimerModule::TIM_5:
			configure_timer5(callback, target_freq, prescaler);
			break;
		#endif
		default:
			// Error: module does not contain the given tim module
			break;
	}

	sei();
}

void disable_timer(timer_module_t timx)
{
	cli();

	switch(timx)
	{
		case TimerModule::TIM_0:
			disable_timer0();
			break;
		case TimerModule::TIM_1:
			disable_timer1();
			break;
		case TimerModule::TIM_2:
			disable_timer2();
			break;
		#if defined(__AVR_ATmega1280__) || defined(__AVR_ATmega2560__)
		case TimerModule::TIM_3:
			disable_timer3();
			break;
		case TimerModule::TIM_4:
			disable_timer4();
			break;
		case TimerModule::TIM_5:
			disable_timer5();
			break;
		#endif
		default:
			// Error: Module does not contain the given tim module
			break;
	}

	sei();
}

void configure_timer0(void (*callback)(void), uint16_t target_freq, timer_prescaler_t prescaler)
{
	// Clear any previous configurations
	TCCR0A = 0;
	TCCR0B = 0;
	TCNT0  = 0;
	// Set timer to restart when matching (CTC Mode)
	TCCR0B |= (1 << WGM02);
	// set compare match register for desired frequency
	OCR0A = _desired_freq(target_freq, TIMER_PRESCALER_MAP[prescaler]);
	// Set prescaler bits as desired
	TCCR0B |= prescaler;
	// enable timer compare interrupt
	TIMSK0 |= (1 << OCIE0A);
	// Set callback
	TIM0->isr_callback = callback;
}

void disable_timer0()
{
	// Sets CSXX pins to 0 which disconnects the clock source
	TCCR0B = 0;
}

void configure_timer1(void (*callback)(void), uint16_t target_freq, timer_prescaler_t prescaler)
{
	// Clear any previous configurations
	TCCR1A = 0;
	TCCR1B = 0;
	TCNT1  = 0;
	// Set timer to restart when matching (CTC Mode)
	TCCR1B |= (1 << WGM12);
	// set compare match register for desired frequency
	OCR1A = _desired_freq(target_freq, TIMER_PRESCALER_MAP[prescaler]);
	// Set prescaler bits as desired
	TCCR1B |= prescaler;
	// enable timer compare interrupt
	TIMSK1 |= (1 << OCIE1A);
	// Set callback
	TIM1->isr_callback = callback;
}

void disable_timer1()
{
	// Sets CSXX pins to 0 which disconnects the clock source
	TCCR1B = 0;
}

void configure_timer2(void (*callback)(void), uint16_t target_freq, timer_prescaler_t prescaler)
{
	// Clear any previous configurations
	TCCR2A = 0;
	TCCR2B = 0;
	TCNT2  = 0;
	// Set timer to restart when matching (CTC Mode)
	TCCR2B |= (1 << WGM22);
	// set compare match register for desired frequency
	OCR2A = _desired_freq(target_freq, TIMER_PRESCALER_MAP[prescaler]);
	// Set prescaler bits as desired
	TCCR2B |= prescaler;
	// enable timer compare interrupt
	TIMSK2 |= (1 << OCIE2A);
	// Set callback
	TIM2->isr_callback = callback;
}

void disable_timer2()
{
	// Sets CSXX pins to 0 which disconnects the clock source
	TCCR2B = 0;
}

#if defined(__AVR_ATmega1280__) || defined(__AVR_ATmega2560__)
void configure_timer3(void (*callback)(void), uint16_t target_freq, timer_prescaler_t prescaler)
{
	// Clear any previous configurations
	TCCR3A = 0;
	TCCR3B = 0;
	TCNT3  = 0;
	// Set timer to restart when matching (CTC Mode)
	TCCR3B |= (1 << WGM32);
	// set compare match register for desired frequency
	OCR3A = _desired_freq(target_freq, TIMER_PRESCALER_MAP[prescaler]);
	// Set prescaler bits as desired
	TCCR3B |= prescaler;
	// enable timer compare interrupt
	TIMSK3 |= (1 << OCIE3A);
	// Set callback
	TIM3->isr_callback = callback;
}

void disable_timer3()
{
	// Sets CSXX pins to 0 which disconnects the clock source
	TCCR3B = 0;
}

void configure_timer4(void (*callback)(void), uint16_t target_freq, timer_prescaler_t prescaler)
{
	// Clear any previous configurations
	TCCR4A = 0;
	TCCR4B = 0;
	TCNT4  = 0;
	// Set timer to restart when matching (CTC Mode)
	TCCR4B |= (1 << WGM42);
	// set compare match register for desired frequency
	OCR4A = _desired_freq(target_freq, TIMER_PRESCALER_MAP[prescaler]);
	// Set prescaler bits as desired
	TCCR4B |= prescaler;
	// enable timer compare interrupt
	TIMSK4 |= (1 << OCIE4A);
	// Set callback
	TIM4->isr_callback = callback;
}

void disable_timer4()
{
	// Sets CSXX pins to 0 which disconnects the clock source
	TCCR4B = 0;
}

void configure_timer5(void (*callback)(void), uint16_t target_freq, timer_prescaler_t prescaler)
{
	// Clear any previous configurations
	TCCR5A = 0;
	TCCR5B = 0;
	TCNT5  = 0;
	// Set timer to restart when matching (CTC Mode)
	TCCR5B |= (1 << WGM52);
	// set compare match register for desired frequency
	OCR5A = _desired_freq(target_freq, TIMER_PRESCALER_MAP[prescaler]);
	// Set prescaler bits as desired
	TCCR5B |= prescaler;
	// enable timer compare interrupt
	TIMSK5 |= (1 << OCIE5A);
	// Set callback
	TIM5->isr_callback = callback;
}

void disable_timer5()
{
	// Sets CSXX pins to 0 which disconnects the clock source
	TCCR5B = 0;
}

#endif

inline uint16_t _desired_freq(uint16_t target_freq, uint16_t prescaler)
{
	return F_CPU / (target_freq * prescaler - 1);
}

ISR(TIMER0_COMPA_vect)
{
	TIM0->isr_callback();
}

ISR(TIMER1_COMPA_vect)
{
	TIM1->isr_callback();
}

ISR(TIMER2_COMPA_vect)
{
	TIM2->isr_callback();
}

#if defined(__AVR_ATmega1280__) || defined(__AVR_ATmega2560__)
ISR(TIMER3_COMPA_vect)
{
	TIM3->isr_callback();
}

ISR(TIMER4_COMPA_vect)
{
	TIM4->isr_callback();
}

ISR(TIMER5_COMPA_vect)
{
	TIM5->isr_callback();
}
#endif
