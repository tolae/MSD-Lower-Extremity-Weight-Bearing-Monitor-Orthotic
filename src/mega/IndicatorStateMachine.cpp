#include <IndicatorStateMachine.h>
#include "inc/mega.h"
#include "inc/timer.h"

const timer_module_t TIMER_BEING_USED = TimerModule::TIM_2;

void _flash_green();
void _flash_yellow();

/* State Machine Functions */
// Nothing to do here...

/* Transfer Functions */

void into_no_func()
{
	disable_timer(TIMER_BEING_USED);
	speaker_vol.noTone();
	vib_motor.disable();
	tft.drawCircle(60, 160, 40, COLOR_LIGHTGREY);
	tft.fillCircle(60, 160, 40, COLOR_LIGHTGREY);
}

void into_low_func()
{
	configure_timer(TIMER_BEING_USED, _flash_green, 2, TimerPrescaler::TEN_TWO_FOUR);
}

void into_med_func()
{
	configure_timer(TIMER_BEING_USED, _flash_yellow, 10, TimerPrescaler::TEN_TWO_FOUR);
}

void into_high_func()
{
	disable_timer(TIMER_BEING_USED);
	speaker_vol.tone(100, 255);
    vib_motor.enable();
	tft.drawCircle(60, 160, 40, COLOR_RED);
	tft.fillCircle(60, 160, 40, COLOR_RED);
}

void ext_reset_state_machine(void)
{
    into_no_func();
}

void _flash_green()
{
	static int flash_green_flag = 0;
	if (flash_green_flag == 1)
	{
		flash_green_flag = 0;
		tft.drawCircle(60, 160, 40, COLOR_DARKGREY);
		tft.fillCircle(60, 160, 40, COLOR_DARKGREY);
	}
	else
	{
		flash_green_flag = 1;
		tft.drawCircle(60, 160, 40, COLOR_GREEN);
		tft.fillCircle(60, 160, 40, COLOR_GREEN);
	}
}

void _flash_yellow()
{
	static int flash_yellow_flag = 0;
	if (flash_yellow_flag == 1)
	{
		flash_yellow_flag = 0;
		speaker_vol.tone(100, 0);
		vib_motor.disable();
		tft.drawCircle(60, 160, 40, COLOR_DARKGREY);
		tft.fillCircle(60, 160, 40, COLOR_DARKGREY);
	}
	else
	{
		flash_yellow_flag = 1;
		speaker_vol.tone(100, 255);
        vib_motor.enable();
		tft.drawCircle(60, 160, 40, COLOR_YELLOW);
		tft.fillCircle(60, 160, 40, COLOR_YELLOW);
	}
}
