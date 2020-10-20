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
#define MAX_PACKAGE_SIZE 10
/**
 * @brief The maximum number of bytes that can be found within a single package.
 * 
 */
#define MAX_DATA_LEN 7

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
					 * Utilized with the STOP_BYTE so it's impossible to confuse
					 * the beginning and ending of a package.
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
			uint8_t data[MAX_DATA_LEN];
			/**
			 * @brief The Cyclical Redundancy Check
			 * 
			 * This does not need to be filled when transmitting. It will be
			 * re-computed when transmitting.
			 */
			uint8_t crc;
		} blue_package_t;

		/**
		 * @brief The opcodes that are standardized for this communication
		 * protocol.
		 * 
		 */
		enum BluetoothPackageIDs
		{
			ALIVE = 0x0,
			WEIGHT = 0x1,
			STATUS = 0x2,
		};

		/**
		 * @brief The status of the module after a transaction.
		 * 
		 */
		enum BluetoothStatus
		{
			OK,
			BUSY,
			ERROR,
		};

		/**
		 * @brief The various status to the internal state machine.
		 * 
		 */
		enum class BluetoothStates
		{
			IDLE,
			WORKING,
			FULL,
			ERROR,
		};

		/**
		 * @brief Construct a new Bluetooth Mod object
		 * 
		 * @param stream The stream used to communicate.
		 */
		BluetoothMod(Stream& stream);

		/**
		 * @brief Receives a single package and stores it in the supplied buffer.
		 * 
		 * @param package The buffer to store the received data.
		 * @return uint8_t The bluetooth status.
		 */
		uint8_t receivePackage(blue_package_t& package);

		/**
		 * @brief Transmits a single package.
		 * 
		 * This package is copied to an internal buffer so the original package
		 * can be later modified without worry.
		 * 
		 * @param package The package to transmit.
		 * @return uint8_t The bluetooth status.
		 */
		uint8_t transmitPackage(blue_package_t& package);
		uint8_t fullReceive();
		uint8_t fullTransmit();

		/**
		 * @brief The update function for this module.
		 * 
		 * This MUST be called for this module to operate. How or when this is
		 * called does not matter (main loop, timer, etc.).
		 * 
		 */
		void update(void);

		/**
		 * @brief Number
		 * 
		 */
		size_t rx_packages;
		size_t tx_packages;
		BluetoothStates rx_state;
		BluetoothStates tx_state;

	private:
		void _rx_update(void);
		void _tx_update(void);

	protected:
		Stream* serial_ref;
		uint8_t rx_buffer[RX_BUFFER_REGISTERS][MAX_PACKAGE_SIZE];
		uint8_t tx_buffer[TX_BUFFER_REGISTERS][MAX_PACKAGE_SIZE];
		uint8_t emergency_buffer[MAX_PACKAGE_SIZE];
};

#endif
