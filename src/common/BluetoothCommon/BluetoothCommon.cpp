#include "BluetoothCommon.h"

BluetoothMod::BluetoothMod(Stream& stream) :
	serial_ref(&stream),
	rx_buffer(RX_BUFFER_REGISTERS),
	tx_buffer(TX_BUFFER_REGISTERS),
	rx_state(BluetoothStates::IDLE),
	tx_state(BluetoothStates::IDLE)
{ }

uint8_t BluetoothMod::receivePackage(blue_package_t& package)
{
	if (!rx_buffer.empty())
	{
		/* Copy the buffer into the package (ignoring the stop byte) */
		package = rx_buffer.pop();
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
	if (!tx_buffer.full())
	{
		// TODO: CRC Creation
		package.crc = 0xAE;
		/* Ensure reserved bits are set to 0 */
		package._reserved = 0;
		/* Copy the package into the buffer (ignoring the stop byte) */
		tx_buffer.push(package);
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
	static uint8_t rx_buf[MAX_PACKAGE_SIZE_W_STOP];
	blue_package_t in_pack;
	uint8_t in_byte;

	switch (rx_state)
	{
		case BluetoothStates::IDLE:
			/* Do nothing in idle */
			if (serial_ref->available() >= MAX_PACKAGE_SIZE_W_STOP && !rx_buffer.full())
			{
				rx_state = BluetoothStates::WORKING;
			}
			break;
		case BluetoothStates::WORKING:
			len_read = serial_ref->readBytes(rx_buf, MAX_PACKAGE_SIZE_W_STOP);
			if (len_read < MAX_PACKAGE_SIZE_W_STOP)
			{
				rx_state = BluetoothStates::ERROR;
			}
			/* Successful read. Copy buffer into package for storing. */
			memcpy(&in_pack, rx_buf, MAX_PACKAGE_SIZE);
			rx_buffer.push(in_pack);
			if (rx_buffer.full())
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
			if (!rx_buffer.full())
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
				rx_buf[len_read++] = in_byte;
				if (in_byte == STOP_BYTE)
				{
					/* Stop byte found, successfully rebuilt partial package. */
					memcpy(&in_pack, rx_buf, MAX_PACKAGE_SIZE);
					rx_buffer.push(in_pack);
					rx_state = BluetoothStates::IDLE;
				}
				/* Stop byte was missed or corrupted. Reading new package (BAD) */
				else if (len_read >= MAX_PACKAGE_SIZE_W_STOP)
				{
					/* Drop the old package and save this one */
					memset(rx_buf, 0, MAX_PACKAGE_SIZE_W_STOP);
					rx_buf[0] = in_byte;
					len_read = 1;
				}
			}
			break;
	}
}

void BluetoothMod::_tx_update(void)
{
	static size_t len_write;
	static uint8_t tx_buf[MAX_PACKAGE_SIZE_W_STOP];
	switch (tx_state)
	{
		case BluetoothStates::IDLE:
			if (!tx_buffer.empty())
			{
				tx_state = BluetoothStates::WORKING;
			}
			break;
		case BluetoothStates::WORKING:
			memcpy(tx_buf, &(tx_buffer.peek()), MAX_PACKAGE_SIZE);
			tx_buf[MAX_PACKAGE_SIZE_W_STOP - 1] = STOP_BYTE;
			len_write = serial_ref->write(tx_buf, MAX_PACKAGE_SIZE_W_STOP);
			if (len_write < MAX_PACKAGE_SIZE_W_STOP)
			{
				tx_state = BluetoothStates::ERROR;
			}
			else
			{
				tx_buffer.pop();
				tx_state = BluetoothStates::IDLE;
			}
			break;
		case BluetoothStates::FULL:
			/* Useless state for TX */
			break;
		case BluetoothStates::ERROR:
			/* Sent a partial package. Send the rest pronto! Block if necessary. */
			len_write = serial_ref->write(
				&(tx_buf[len_write]),
				MAX_PACKAGE_SIZE_W_STOP - len_write
			) + len_write;
			if (len_write >= MAX_PACKAGE_SIZE_W_STOP)
			{
				tx_buffer.pop();
				tx_state = BluetoothStates::IDLE;
			}
			break;
	}
}
