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
}

uint8_t BluetoothMod::receivePackage(blue_package_t& package)
{
	if (_rx_packages > 0)
	{
		/* Copy the buffer into the package (ignoring the stop byte) */
		memcpy(&package, rx_buffer[0], MAX_PACKAGE_SIZE-1);
		// TODO: CRC Checking
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
		/* Copy the package into the buffer (ignoring the stop byte) */
		memcpy(tx_buffer[_tx_packages], &package, MAX_PACKAGE_SIZE-1);
		tx_buffer[_tx_packages++][MAX_PACKAGE_SIZE-1] = STOP_BYTE;
		return BluetoothStatus::OK;
	}

	/* If the tx registers are full, tell the user it's waiting */
	return BluetoothStatus::BUSY;
}

void BluetoothMod::_update(void)
{
	_rx_update();
	_tx_update();
}

void BluetoothMod::_rx_update(void)
{
	size_t len_read;
	/* Check if a package is available to read */
	if (serial_ref->available() > MAX_PACKAGE_SIZE && _rx_packages < RX_BUFFER_REGISTERS)
	{
		len_read = serial_ref->readBytes(rx_buffer[_rx_packages++], MAX_PACKAGE_SIZE);
		if (len_read < MAX_PACKAGE_SIZE)
		{
			// TODO: Just read a partial package. Promptly discard.
		}
	}
}

void BluetoothMod::_tx_update(void)
{
	size_t len_write;
	/* Checks if it can write without blocking */
	if (serial_ref->availableForWrite() > MAX_PACKAGE_SIZE && _tx_packages > 0)
	{
		len_write = serial_ref->write(tx_buffer[0], MAX_PACKAGE_SIZE);
		if (len_write < MAX_PACKAGE_SIZE)
		{
			// TODO: Just sent a partial package. Resend?
		}
	}
}
