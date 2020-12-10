#ifndef _STATE_MACHINE_IMPL_H
#define _STATE_MACHINE_IMPL_H

#include <StateMachine.h>

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
// Nothing to do here...

/* Transfer Functions */

/* Turn everything off */
void into_no_func();
/* Start low level indication to user */
void into_low_func();
/* Start medium level indication to user */
void into_med_func();
/* Start high level indication to user */
void into_high_func();

/* States */
static state_machine_state_t no_alert_state =
{
	.state = NO_ALERT,
	.state_execution = STATE_MACHINE_NO_FUNC,
	.transitions =
	{
		{{0}, GT_EQUALS, LOW_ALERT, into_low_func},
		STATE_MACHINE_TRANSITION_TERMINATOR_DECL
	}
};

static state_machine_state_t low_alert_state =
{
	.state = LOW_ALERT,
	.state_execution = STATE_MACHINE_NO_FUNC,
	.transitions =
	{
		{{0}, LESS_THAN, NO_ALERT, into_no_func},
		{{0}, GT_EQUALS, MEDIUM_ALERT, into_med_func},
		STATE_MACHINE_TRANSITION_TERMINATOR_DECL
	}
};

static state_machine_state_t medium_alert_state =
{
	.state = MEDIUM_ALERT,
	.state_execution = STATE_MACHINE_NO_FUNC,
	.transitions =
	{
		{{0}, LESS_THAN, LOW_ALERT, into_low_func},
		{{0}, GT_EQUALS, HIGH_ALERT, into_high_func},
		STATE_MACHINE_TRANSITION_TERMINATOR_DECL
	}
};

static state_machine_state_t high_alert_state =
{
	.state = HIGH_ALERT,
	.state_execution = STATE_MACHINE_NO_FUNC,
	.transitions =
	{
		{{0}, LESS_THAN, MEDIUM_ALERT, into_med_func},
		STATE_MACHINE_TRANSITION_TERMINATOR_DECL
	}
};

/* State Machine State Pointer-Array */
static state_machine_state_t* my_states[END_STATE] =
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
static state_machine_config_t my_state_machine_config =
{
	.hysteresis = HYSTERESIS,
	.state_machine = my_states,
};

/* State Machine Function Implementation */
/* These are specific to the device and should be implemented there. */

/* Custom Public Function */
static void update_indicator_state_boundaries(uint16_t weight, uint16_t threshold)
{
	no_alert_state.transitions[0].threshold.distance = NO_TO_LOW_BOUNDARY(weight, threshold);
	low_alert_state.transitions[0].threshold.distance = NO_TO_LOW_BOUNDARY(weight, threshold);
	low_alert_state.transitions[1].threshold.distance = LOW_TO_MEDIUM_BOUNDARY(weight, threshold);
	medium_alert_state.transitions[0].threshold.distance = LOW_TO_MEDIUM_BOUNDARY(weight, threshold);
	medium_alert_state.transitions[1].threshold.distance = MEDIUM_TO_HIGH_BOUNDARY(weight, threshold);
	high_alert_state.transitions[0].threshold.distance = MEDIUM_TO_HIGH_BOUNDARY(weight, threshold);
}

#endif
