#ifndef BLUETOOTH_H
#define BLUETOOTH_H

#include <Stream.h>

#define RX_BUFFER_REGISTERS 8
#define TX_BUFFER_REGISTERS 2
/**
 * @brief The maximum number of bytes in a single package.
 * 
 * This includes the STOP byte.
 * 
 */
#define MAX_PACKAGE_SIZE 11

/**
 * @brief The stop byte for any given package.
 * 
 * Utilizes the reserved bits by setting them to one. This is to separate
 * the start (first byte of a package) and stop byte's.
 * 
 */
#define STOP_BYTE (0x14)

class BluetoothMod
{
	private:
		size_t _rx_packages;
		size_t _tx_packages;

	protected:
		Stream* serial_ref;
		uint8_t rx_buffer[RX_BUFFER_REGISTERS][MAX_PACKAGE_SIZE];
		uint8_t tx_buffer[TX_BUFFER_REGISTERS][MAX_PACKAGE_SIZE];
	
	public:
		/**
		 * @brief Serial message package structure.
		 * 
		 */
		typedef struct BluetoothPackage
		{
			union
			{
				/**
				 * @brief The message identifier.
				 * 
				 */
				uint8_t id;
				struct
				{
					/**
					 * @brief The operational code of this package.
					 * 
					 */
					uint8_t opcode: 3;
					/**
					 * @brief Reserved. Will always be zero.
					 * 
					 */
					uint8_t _reserved: 2;
					/**
					 * @brief The length of the payload.
					 * 
					 */
					uint8_t len: 3;
				};
			};
			/**
			 * @brief The data stored in the package.
			 * 
			 * Doesn't include the stop byte.
			 */
			uint8_t data[MAX_PACKAGE_SIZE-1];
			/**
			 * @brief The Cyclical Redundancy Check
			 * 
			 * This does not need to be filled when transmitting. It will be
			 * re-computed when transmitting.
			 */
			uint8_t crc;
		} blue_package_t;

		enum BluetoothStatus
		{
			OK = 0,
			BUSY = 1,
			ERROR = 99
		};

		BluetoothMod(Stream& stream);

		uint8_t receivePackage(blue_package_t& package);
		uint8_t transmitPackage(blue_package_t& package);

	private:
		void _update(void);
		void _rx_update(void);
		void _tx_update(void);
};

#endif
