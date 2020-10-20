#include "inc/timer.h"

void setup()
{
	pinMode(LED_BUILTIN, OUTPUT);
}

void loop()
{
	configure_timer(TIM_3, test, 8, TimerPrescaler::TEN_TWO_FOUR);

	delay(5000);

	disable_timer(TIM_3);
	digitalWrite(LED_BUILTIN, 0);

	delay(1000);

	configure_timer(TIM_3, test2, 2, TimerPrescaler::TEN_TWO_FOUR);

	delay(10000);
}

void test()
{
	digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN));
}

int fade = 0;
int dir = 0;
void test2()
{
	if (fade >= 255)
	{
		dir = 1;
		fade = 255;
	}
	else if (fade <= 0)
	{
		dir = 0;
		fade = 0;
	}

	if (dir == 0)
	{
		fade += 5;
	}
	else
	{
		fade -= 5;
	}

	analogWrite(9, fade);
}
