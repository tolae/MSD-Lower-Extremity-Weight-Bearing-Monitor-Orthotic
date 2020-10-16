#include "inc/bluetooth.h"

 BluetoothMod::BluetoothMod(Stream& stream): serial_ref(&stream)
{
	/* Reset internal buffers */
	memset(rx_buffer, 0, RX_BUFFER_REGISTERS * MAX_PACKAGE_SIZE * sizeof(unsigned char));
	/* Reset internal counters */
	_rx_packages = 0;
	_tx_packages = 0;
	/* Configure timer2 for 1 MHz checking rate */
	// TODO: Configure timer
	/* Reset internal state machines */
	_rx_state = BluetoothStates::IDLE;
	_tx_state = BluetoothStates::IDLE;
}

uint8_t BluetoothMod::receivePackage(blue_package_t& package)
{
	if (_rx_packages > 0)
	{
		/* Copy the buffer into the package (ignoring the stop byte) */
		memcpy(&package, rx_buffer[0], MAX_PACKAGE_SIZE-1);
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
	if (_tx_packages < TX_BUFFER_REGISTERS)
	{
		// TODO: CRC Creation
		package.crc = 0xAE;
		/* Copy the package into the buffer (ignoring the stop byte) */
		memcpy(tx_buffer[_tx_packages], &package, MAX_PACKAGE_SIZE-1);
		tx_buffer[_tx_packages++][MAX_PACKAGE_SIZE-1] = STOP_BYTE;
		return BluetoothStatus::OK;
	}

	/* If the tx registers are full, tell the user it's waiting */
	return BluetoothStatus::BUSY;
}

uint8_t BluetoothMod::fullReceive()
{
	return _rx_state == BluetoothStates::FULL;
}

uint8_t BluetoothMod::fullTransmit()
{
	return _tx_state == BluetoothStates::FULL;
}

void BluetoothMod::_update(void)
{
	_rx_update();
	_tx_update();
}

void BluetoothMod::_rx_update(void)
{
	static size_t len_read;
	uint8_t in_byte;
	switch (_rx_state)
	{
		case BluetoothStates::IDLE:
			/* Do nothing in idle */
			if (serial_ref->available() > MAX_PACKAGE_SIZE && _rx_packages < RX_BUFFER_REGISTERS)
			{
				_rx_state = BluetoothStates::WORKING;
			}
			break;
		case BluetoothStates::WORKING:
			len_read = serial_ref->readBytes(rx_buffer[_rx_packages++], MAX_PACKAGE_SIZE);
			if (len_read < MAX_PACKAGE_SIZE)
			{
				memcpy(emergency_buffer, rx_buffer[--_rx_packages], len_read);
				memset(rx_buffer[_rx_packages], 0, MAX_PACKAGE_SIZE);
				_rx_state = BluetoothStates::ERROR;
			}
			else if (_rx_packages >= RX_BUFFER_REGISTERS)
			{
				_rx_state = BluetoothStates::FULL;
			}
			else
			{
				_rx_state = BluetoothStates::IDLE;
			}
			break;
		case BluetoothStates::FULL:
			/* Wait for user to read. Ignore any incoming messages. */
			if (_rx_packages < RX_BUFFER_REGISTERS)
			{
				_rx_state = BluetoothStates::IDLE;
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
					memcpy(rx_buffer[_rx_packages++], emergency_buffer, MAX_PACKAGE_SIZE);
					_rx_state = BluetoothStates::IDLE;
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
	switch (_tx_state)
	{
		case BluetoothStates::IDLE:
			if (serial_ref->availableForWrite() > MAX_PACKAGE_SIZE && _tx_packages > 0)
			{
				_tx_state = BluetoothStates::WORKING;
			}
			else if (_tx_packages >= TX_BUFFER_REGISTERS)
			{
				_tx_state = BluetoothStates::FULL;
			}
			break;
		case BluetoothStates::WORKING:
			len_write = serial_ref->write(tx_buffer[0], MAX_PACKAGE_SIZE);
			if (len_write < MAX_PACKAGE_SIZE)
			{
				_tx_state = BluetoothStates::ERROR;
			}
			else
			{
				_tx_state = BluetoothStates::IDLE;
			}
			
			break;
		case BluetoothStates::FULL:
			/* Same as IDLE. Let's internal logic know the tx_buffers are full */
			if (serial_ref->availableForWrite() > MAX_PACKAGE_SIZE && _tx_packages > 0)
			{
				_tx_state = BluetoothStates::WORKING;
			}
			break;
		case BluetoothStates::ERROR:
			/* Sent a partial package. Send the rest pronto! Block if necessary. */
			len_write = serial_ref->write(
				&(tx_buffer[0][len_write]),
				MAX_PACKAGE_SIZE - len_write
			) + len_write;
			if (len_write >= MAX_PACKAGE_SIZE)
			{
				_tx_state = BluetoothStates::IDLE;
			}
			break;
	}
}
