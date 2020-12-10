#include <IndicatorStateMachine.h>
#include "inc/nano.h"

/* Colors for analog writing */
#define NO_COLOR \
	analogWrite(LED_R_PIN, 0); \
	analogWrite(LED_B_PIN, 0); \
	analogWrite(LED_G_PIN, 0)

#define LOW_COLOR \
	analogWrite(LED_R_PIN, 0); \
	analogWrite(LED_B_PIN, 0); \
	analogWrite(LED_G_PIN, 100)

#define MED_COLOR \
	analogWrite(LED_R_PIN, 85); \
	analogWrite(LED_B_PIN, 0); \
	analogWrite(LED_G_PIN, 70)

#define HIGH_COLOR \
	analogWrite(LED_R_PIN, 100); \
	analogWrite(LED_B_PIN, 0); \
	analogWrite(LED_G_PIN, 0)

/* State Machine Functions */
// Nothing to do here...

/* Transfer Functions */

/* Turn everything off */
void into_no_func()
{
	NO_COLOR;
}

/* Start low level indication to user */
void into_low_func()
{
	LOW_COLOR;
}

/* Start medium level indication to user */
void into_med_func()
{
	MED_COLOR;
}

/* Start high level indication to user */
void into_high_func()
{
	HIGH_COLOR;
}

void ext_reset_state_machine(void)
{
	NO_COLOR;
}
