#include <IndicatorStateMachine.h>
#include "inc/mega.h"
#include "inc/timer.h"

void _flash_green();
void _flash_yellow();

/* State Machine Functions */
// Nothing to do here...

/* Transfer Functions */

/* Turn everything off */
void into_no_func()
{
	disable_timer(TimerModule::TIM_3);
	speaker_vol.noTone();
	analogWrite(3, 0);
	tft.drawCircle(60, 160, 40, COLOR_LIGHTGREY);
	tft.fillCircle(60, 160, 40, COLOR_LIGHTGREY);
}

/* Start low level indication to user */
void into_low_func()
{
	configure_timer(TimerModule::TIM_3, _flash_green, 2, TimerPrescaler::TEN_TWO_FOUR);
}

/* Start medium level indication to user */
void into_med_func()
{
	configure_timer(TimerModule::TIM_3, _flash_yellow, 10, TimerPrescaler::TEN_TWO_FOUR);
}

/* Start high level indication to user */
void into_high_func()
{
	disable_timer(TimerModule::TIM_3);
	speaker_vol.tone(100, 255);
	analogWrite(3, 255);
	tft.drawCircle(60, 160, 40, COLOR_RED);
	tft.fillCircle(60, 160, 40, COLOR_RED);
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
		analogWrite(3, 0);
		tft.drawCircle(60, 160, 40, COLOR_DARKGREY);
		tft.fillCircle(60, 160, 40, COLOR_DARKGREY);
	}
	else
	{
		flash_yellow_flag = 1;
		speaker_vol.tone(100, 255);
		analogWrite(3, 255);
		tft.drawCircle(60, 160, 40, COLOR_YELLOW);
		tft.fillCircle(60, 160, 40, COLOR_YELLOW);
	}
}
