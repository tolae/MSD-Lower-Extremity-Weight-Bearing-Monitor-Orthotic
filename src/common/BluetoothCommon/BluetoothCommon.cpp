#include "BluetoothCommon.h"

 BluetoothMod::BluetoothMod(Stream& stream): serial_ref(&stream)
{
	/* Reset internal buffers */
	memset(rx_buffer, 0, RX_BUFFER_REGISTERS * MAX_PACKAGE_SIZE * sizeof(unsigned char));
	/* Reset internal counters */
	rx_packages = 0;
	tx_packages = 0;
	/* Reset internal state machines */
	rx_state = BluetoothStates::IDLE;
	tx_state = BluetoothStates::IDLE;
}

uint8_t BluetoothMod::receivePackage(blue_package_t& package)
{
	if (rx_packages > 0)
	{
		/* Copy the buffer into the package (ignoring the stop byte) */
		memcpy(&package, rx_buffer[0], MAX_PACKAGE_SIZE-1);
		rx_packages--;
		// TODO: CRC Checking
		if (package.crc != 0xAE)
		{
			return BluetoothStatus::ERROR;
		}
		return BluetoothStatus::OK;
	}

	/* If no packages are found, tell the user it's waiting */
	return BluetoothStatus::BUSY;
}

uint8_t BluetoothMod::transmitPackage(blue_package_t& package)
{
	if (tx_packages < TX_BUFFER_REGISTERS)
	{
		// TODO: CRC Creation
		package.crc = 0xAE;
		/* Ensure reserved bits are set to 0 */
		package._reserved = 0;
		/* Copy the package into the buffer (ignoring the stop byte) */
		memcpy(tx_buffer[tx_packages], &package, MAX_PACKAGE_SIZE-1);
		tx_buffer[tx_packages++][MAX_PACKAGE_SIZE-1] = STOP_BYTE;
		return BluetoothStatus::OK;
	}

	/* If the tx registers are full, tell the user it's waiting */
	return BluetoothStatus::BUSY;
}

uint8_t BluetoothMod::fullReceive()
{
	return rx_state == BluetoothStates::FULL;
}

uint8_t BluetoothMod::fullTransmit()
{
	return tx_state == BluetoothStates::FULL;
}

void BluetoothMod::update(void)
{
	_rx_update();
	_tx_update();
}

void BluetoothMod::_rx_update(void)
{
	static size_t len_read;
	uint8_t in_byte;
	switch (rx_state)
	{
		case BluetoothStates::IDLE:
			/* Do nothing in idle */
			if (serial_ref->available() >= MAX_PACKAGE_SIZE && rx_packages < RX_BUFFER_REGISTERS)
			{
				rx_state = BluetoothStates::WORKING;
			}
			break;
		case BluetoothStates::WORKING:
			len_read = serial_ref->readBytes(rx_buffer[rx_packages++], MAX_PACKAGE_SIZE);
			if (len_read < MAX_PACKAGE_SIZE)
			{
				memcpy(emergency_buffer, rx_buffer[--rx_packages], len_read);
				memset(rx_buffer[rx_packages], 0, MAX_PACKAGE_SIZE);
				rx_state = BluetoothStates::ERROR;
			}
			else if (rx_packages >= RX_BUFFER_REGISTERS)
			{
				rx_state = BluetoothStates::FULL;
			}
			else
			{
				rx_state = BluetoothStates::IDLE;
			}
			break;
		case BluetoothStates::FULL:
			/* Wait for user to read. Ignore any incoming messages. */
			if (rx_packages < RX_BUFFER_REGISTERS)
			{
				rx_state = BluetoothStates::IDLE;
			}
			break;
		case BluetoothStates::ERROR:
			/* Error when partial package was read. */
			/* Attempt to rebuild the lost package. */
			if (serial_ref->available())
			{
				in_byte = serial_ref->read();
				emergency_buffer[len_read++] = in_byte;
				if (in_byte == STOP_BYTE)
				{
					/* Stop byte found, successfully rebuilt partial package. */
					memcpy(rx_buffer[rx_packages++], emergency_buffer, MAX_PACKAGE_SIZE);
					rx_state = BluetoothStates::IDLE;
				}
				/* Stop byte was missed or corrupted. Reading new package (BAD) */
				else if (len_read >= MAX_PACKAGE_SIZE)
				{
					/* Drop the old package and save this one */
					memset(emergency_buffer, 0, MAX_PACKAGE_SIZE);
					emergency_buffer[0] = in_byte;
					len_read = 1;
				}
			}
			break;
	}
}

void BluetoothMod::_tx_update(void)
{
	static size_t len_write;
	switch (tx_state)
	{
		case BluetoothStates::IDLE:
			if (tx_packages > 0)
			{
				tx_state = BluetoothStates::WORKING;
			}
			break;
		case BluetoothStates::WORKING:
			len_write = serial_ref->write(tx_buffer[0], MAX_PACKAGE_SIZE);
			if (len_write < MAX_PACKAGE_SIZE)
			{
				tx_state = BluetoothStates::ERROR;
			}
			else
			{
				tx_packages--;
				tx_state = BluetoothStates::IDLE;
			}
			break;
		case BluetoothStates::FULL:
			/* Useless state for TX */
			break;
		case BluetoothStates::ERROR:
			/* Sent a partial package. Send the rest pronto! Block if necessary. */
			len_write = serial_ref->write(
				&(tx_buffer[0][len_write]),
				MAX_PACKAGE_SIZE - len_write
			) + len_write;
			if (len_write >= MAX_PACKAGE_SIZE)
			{
				tx_packages--;
				tx_state = BluetoothStates::IDLE;
			}
			break;
	}
}
