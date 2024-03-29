#include <AltSoftSerial.h>
#include <BluetoothCommon.h>
#include <StateMachine.h>
#include <IndicatorStateMachine.h>
#include "inc/nano.h"
#include "inc/weighting.h"

#ifdef DEBUG_WITH_ALTSOFT
AltSoftSerial BTserial;
#endif
BluetoothMod* mod;
BluetoothMod::blue_package_t in_package;
BluetoothMod::blue_package_t out_package;

uint16_t set_weight;
uint16_t set_threshold;

uint16_t curr_weight;
uint16_t prev_weight;

uint32_t curr_time_ms;
uint32_t diff_time_ms;

/** Polls for bluetooth communication.
 * 
 * Checks to see if the digital pin is still high for bluetooth connection.
 * Checks every 500ms if bluetooth communication is not established.
 */
void poll_for_bluetooth(void);

void setup() {
	/* Connect to bluetooth module */
	Serial.begin(9600);

	while (!Serial);

	#ifdef DEBUG_WITH_ALTSOFT
	BTserial.begin(9600);

	mod = new BluetoothMod(BTserial);
	#else
	mod = new BluetoothMod(Serial);
	#endif

	/* Wait for bluetooth module to establish connection */
	poll_for_bluetooth();

	no_alert_state.transitions[0].threshold.distance = 400;
	low_alert_state.transitions[0].threshold.distance = 400;
	low_alert_state.transitions[1].threshold.distance = 500;
	medium_alert_state.transitions[0].threshold.distance = 500;
	medium_alert_state.transitions[1].threshold.distance = 700;
	high_alert_state.transitions[0].threshold.distance = 700;

	initialize_state_machine(my_state_machine_config);
}

void loop() {
	curr_time_ms = millis();
	mod->update();
	/* Check for input from mega */
	if (mod->receivePackage(in_package) != BluetoothMod::BluetoothStatus::BUSY)
	{
		if (in_package.opcode == BluetoothMod::STATUS)
		{
			/* First 2 bytes are the weight, Second 2 bytes are the threshold */
			set_weight = (((uint16_t)in_package.data[1]) << 8) | in_package.data[0];
			set_threshold = (((uint16_t)in_package.data[3]) << 8) | in_package.data[2];
			/* Update state machine transition parameters */
			// Fixed for now
			// update_indicator_state_boundaries(set_weight, set_threshold);
			/* Re-initialize the state machine */
		}
	}
	/* Check for change in weight */
	if (curr_weight != prev_weight)
	{
		prev_weight = curr_weight;
		#ifdef DEBUG_WITH_ALTSOFT
		/* Print out to serial terminal */
		Serial.print("Weight: ");
		Serial.println(curr_weight);
		// #else
		/* Transmit the package over bluetooth */
		memcpy(out_package.data, &curr_weight, 2);
		out_package.opcode = BluetoothMod::WEIGHT;
		out_package.len = 2;
		mod->transmitPackage(out_package);
		#endif
	}
	/* Update LED State Machine */
	update_state_machine({.distance = curr_weight});
	/* Get measure new weight values */
	curr_weight = update_weights();
	/** Check to see if bluetooth connection is still valid. This will block if
	 * connection was broken.
	 */
	poll_for_bluetooth();
	/* Delay for at most 50ms */
	diff_time_ms = millis() - curr_time_ms;
	#ifdef DEBUG_WITH_ALTSOFT
	if (diff_time_ms > LOOP_TIME_DELAY_MS)
	{
		Serial.println("Timing slipped.");
		delay(LOOP_TIME_DELAY_MS);
	}
	else
	{
		delay(LOOP_TIME_DELAY_MS - diff_time_ms);
	}
	#else
	delay(LOOP_TIME_DELAY_MS - diff_time_ms);
	#endif
}

void poll_for_bluetooth()
{
	while (!digitalRead(BLUETOOTH_MOD_CONNECTION_PIN))
	{
		/* If not connected, wait for 500 ms */
		delay(500);
	}
}
