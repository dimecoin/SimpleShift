#ifndef SIMPLE_SHIFT
#define SIMPLE_SHIFT

#include <Arduino.h>

// Pins setup for 75HC595
// SERPin = pin 14
// RCKPin = pin 12
// SCKPin = pin 11

class SimpleShift {

	public :
		SimpleShift (uint8_t numberOfShiftRegisters, uint8_t SERPin, uint8_t RCKPin, uint8_t SCKPin);
		~SimpleShift ();

		/** Zero out all bits in memory buffer*/
		void clearBuffer();

		/** Set all bits to 1  in memory buffer*/
		void fillBuffer();

		/** Set random junk to memory buffer */
		void randomFillBuffer();

		/** Invert bits (bitewise opertation).  That is set all 0's to 1 and visa-versa */
		void invertBuffer();

		/** Set a single bit */
		void setBufferBit(uint8_t index, uint8_t value);

		/** Flushes memory buffer to Shift Registers.  This must been called after all write operations. */	
		void writeRegisters();

		/** Get bit in memory buffer, not necessarily what is on shift register.  It will differ is writeRegisters() hasn't been called yet. */
		bool getBufferBit(uint8_t index);

		/** Total number of memory buffers/shift register pins we know about */
		uint8_t getNumberOfBits() {
			return (numberOfShiftRegisters*8);
		};

	private:
		uint8_t SERPin, RCKPin, SCKPin;
		uint8_t numberOfShiftRegisters=1;
		uint8_t *bits;

		uint8_t getBufferArrayPos(uint8_t index);
		uint8_t getBitPos(uint8_t index);

};





#endif 
