#ifndef _STATE_MACHINE_IMPL_H
#define _STATE_MACHINE_IMPL_H

#include "state_machine.h"

/* Hysteresis for this state machine in cm */
#define HYSTERESIS 0

/** Boundary Variables
 * 
 * These are used instead of constants as the boundaries are a function of the
 * given weight and threshold. So when these are updated, it will propagate to
 * the state machine.
*/
#define BOUNDARY_FUNC(weight, threshold, percentage) \
    ((((float)weight) / ((float)threshold)) * percentage)
#define NO_TO_LOW_BOUNDARY(weight, threshold) BOUNDARY_FUNC(weight, threshold, 0.75f)
#define LOW_TO_MEDIUM_BOUNDARY(weight, threshold) BOUNDARY_FUNC(weight, threshold, 0.85f)
#define MEDIUM_TO_HIGH_BOUNDARY(weight, threshold) BOUNDARY_FUNC(weight, threshold, 0.95f)

/** State Machine States
 * 
 * NO_ALERT: Weight is < 75% of threshold weight
 * LOW_ALERT: Weight is between 75% to 85% of threshold weight
 * MEDIUM_ALERT: Weight is between 85% to 95% of threshold weight
 * HIGH_ALERT: Weight is > 95% of threshold weight
 * END_STATE: Used to denote length of states (should always be last)
 */
typedef enum
{
	NO_ALERT = 0,
	LOW_ALERT,
	MEDIUM_ALERT,
	HIGH_ALERT,
	END_STATE
} state_t;

/* State Machine Functions */
void no_alert_func();
void low_alert_func();
void medium_alert_func();
void high_alert_func();

/* Transfer Functions */

/* States */
state_machine_state_t no_alert_state =
{
	.state = NO_ALERT,
	.state_execution = no_alert_func,
	.transitions =
	{
		{{0}, LT_EQUALS, LOW_ALERT, STATE_MACHINE_NO_FUNC},
		STATE_MACHINE_TRANSITION_TERMINATOR_DECL
	}
};

state_machine_state_t low_alert_state =
{
	.state = LOW_ALERT,
	.state_execution = low_alert_func,
	.transitions =
	{
		{{0}, GREATER_THAN, NO_ALERT, STATE_MACHINE_NO_FUNC},
		{{0}, LT_EQUALS, MEDIUM_ALERT, STATE_MACHINE_NO_FUNC},
		STATE_MACHINE_TRANSITION_TERMINATOR_DECL
	}
};

state_machine_state_t medium_alert_state =
{
	.state = MEDIUM_ALERT,
	.state_execution = medium_alert_func,
	.transitions =
	{
		{{0}, GREATER_THAN, LOW_ALERT, STATE_MACHINE_NO_FUNC},
		{{0}, LT_EQUALS, HIGH_ALERT, STATE_MACHINE_NO_FUNC},
		STATE_MACHINE_TRANSITION_TERMINATOR_DECL
	}
};

state_machine_state_t high_alert_state =
{
	.state = HIGH_ALERT,
	.state_execution = high_alert_func,
	.transitions =
	{
		{{0}, GREATER_THAN, MEDIUM_ALERT, STATE_MACHINE_NO_FUNC},
		STATE_MACHINE_TRANSITION_TERMINATOR_DECL
	}
};

/* State Machine State Pointer-Array */
state_machine_state_t* my_states[END_STATE] =
{
	&no_alert_state,
	&low_alert_state,
	&medium_alert_state,
	&high_alert_state
};

/** Final State Machine Configuration
 *
 * This is passed into the state machine init function.
 */
state_machine_config_t my_state_machine_config =
{
	.hysteresis = HYSTERESIS,
	.state_machine = my_states,
};

/* State Machine Function Implementation */
void no_alert_func()
{
}

void low_alert_func()
{
}

void medium_alert_func()
{
}

void high_alert_func()
{
}

#endif
