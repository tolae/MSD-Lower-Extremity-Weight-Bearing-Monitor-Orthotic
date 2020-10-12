#ifndef _TIMER_H
#define _TIMER_H

#define F_CPU (16000000) // 16 MHz

/**
 * @brief Maps the timer prescaler values to their respective numbers.
 * 
 */
typedef enum TimerPrescaler
{
	// Disables the timer.
	DISABLED = 0,
	// Sets prescaler to 1.
	ONE = 0x1,
	// Sets prescaler to 8.
	EIGHT = 0x2,
	// Sets prescaler to 64.
	SIX_FOUR = 0x3,
	// Sets prescaler to 256.
	TWO_FIVE_SIX = 0x4,
	// Sets prescaler to 1024.
	TEN_TWO_FOUR = 0x5,
	// Sets prescaler to 1.
	EXTERNAL_FALLING = 0x6,
	// Sets prescaler to 1.
	EXTERNAL_RISING = 0x7
} timer_prescaler_t;

/**
 * @brief Maps the TimerPrescaler values to their respective numbers.
 * 
 * Disabled is assigned to 1 but it doesn't matter as the module is disabled 
 * when the prescaler register is set to 0.
 * 
 */
const uint16_t TIMER_PRESCALER_MAP[] = { 1, 1, 8, 64, 256, 1024, 1, 1 };

typedef enum TimerModule
{
	NONE = 0,
	TIM_1 = 1,
	TIM_2 = 2,
#if defined(__AVR_ATmega1280__) || defined(__AVR_ATmega2560__)
	TIM_3 = 3,
	TIM_4 = 4,
	TIM_5 = 5,
#endif
} timer_module_t;

/**
 * @brief Configures timer 1 with the desired callback, frequency, and
 * accompanying prescaler.
 * 
 * @param callback The function to call when timer 1 triggers.
 * @param target_freq The desired frequency to call the function.
 * @param prescaler The prescaler required for the desired frequency.
 */
void configure_timer1(void (*callback)(void), uint16_t target_freq, timer_prescaler_t prescaler);

class Timer
{
	public:
		Timer();

		configure_timer(timer_module_t timx, void (*callback)(void), uint16_t target_freq, timer_prescaler_t prescaler);
	
		void (*isr_callback)(void);

	private:
		void configure_timer1(uint16_t target_freq, timer_prescaler_t prescaler);
		void configure_timer2(uint16_t target_freq, timer_prescaler_t prescaler);
		#if defined(__AVR_ATmega1280__) || defined(__AVR_ATmega2560__)
		void configure_timer3(uint16_t target_freq, timer_prescaler_t prescaler);
		void configure_timer4(uint16_t target_freq, timer_prescaler_t prescaler);
		void configure_timer5(uint16_t target_freq, timer_prescaler_t prescaler);
		#endif
};

extern Timer* TIM1;
extern Timer* TIM2;
#if defined(__AVR_ATmega1280__) || defined(__AVR_ATmega2560__)
extern Timer* TIM3;
extern Timer* TIM4;
extern Timer* TIM5;
#endif

#endif
