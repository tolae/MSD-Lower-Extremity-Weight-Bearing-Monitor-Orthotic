#include <AltSoftSerial.h>
#include <BluetoothCommon.h>
#include "inc/state_machine.h"
#include "inc/led_state_machine.h"
#include "inc/weighting.h"

AltSoftSerial BTserial;
BluetoothMod* mod;
BluetoothMod::blue_package_t in_package;
BluetoothMod::blue_package_t out_package;

uint16_t set_weight;
uint16_t set_threshold;

uint16_t curr_weight;
uint16_t prev_weight;

void setup() {
	BTserial.begin(9600);

    mod = new BluetoothMod(BTserial);
    delay(1000);
}

void loop() {
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
			no_alert_state.transitions[0].threshold.distance = NO_TO_LOW_BOUNDARY(set_weight, set_threshold);
			low_alert_state.transitions[0].threshold.distance = NO_TO_LOW_BOUNDARY(set_weight, set_threshold);
			low_alert_state.transitions[1].threshold.distance = LOW_TO_MEDIUM_BOUNDARY(set_weight, set_threshold);
			medium_alert_state.transitions[0].threshold.distance = LOW_TO_MEDIUM_BOUNDARY(set_weight, set_threshold);
			medium_alert_state.transitions[1].threshold.distance = MEDIUM_TO_HIGH_BOUNDARY(set_weight, set_threshold);
			high_alert_state.transitions[0].threshold.distance = MEDIUM_TO_HIGH_BOUNDARY(set_weight, set_threshold);
			/* Re-initialize the state machine */
			initialize_state_machine(my_state_machine_config);
		}
    }
	/* Check for change in weight */
	if (curr_weight != prev_weight)
	{
		prev_weight = curr_weight;
		memcpy(out_package.data, &curr_weight, 2);
		out_package.opcode = BluetoothMod::WEIGHT;
		out_package.len = 2;
		mod->transmitPackage(out_package);
	}
	/* Update LED State Machine */
	update_state_machine({.distance = curr_weight});
	/* Get measure new weight values */

	/* Delay for 50ms */
	delay(50);
}
