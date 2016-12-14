#ifndef SIMPLE_SHIFT
#define SIMPLE_SHIFT

#include <Arduino.h>

// Pins setup for 75HC595
// SERPin = pin 14
// RCKPin = pin 12
// SCKPin = pin 11

class SimpleShift {

	public :
		/** 
		 * numberOfShiftRegisters = number of shift registers connected together.  Starts at 1 instead of 0.
		 * SERPin is Arduino pin number that is connected to SER [pin 14] on 74HC595
		 * RCKPin is Arduino pin number that is connected to RCLK [pin 12] on 74HC595
		 * SCKPin is Arduino pin number that is connected to SRCLK [pin 11] on 74HC595
		 * SRCLRPin : 
		 * 	For hardware mode: this is Arduino pin number connected to to !SRCLRPIN [pin 10] on 74HC595.
		 * 	For software mode:  Use -1 in constructor and tie !SRCLR [pin 10] on 74HC595 to VCC.
		 * 	Do not float this pin.
		 */
		SimpleShift (uint8_t numberOfShiftRegisters, uint8_t SERPin, uint8_t RCKPin, uint8_t SCKPin, int8_t SRCLRPin);
		~SimpleShift ();

		/** Zero out all bits in memory buffer.  
		* Requires a writeRegisters() call to take affect on shift register[s].*/
		void clearBuffer();

		/** Instantly clears shift register and does NOT require a writeRegisters() to take affect.  Uses hardware if SRCLRPin is wired, otherwise uses software mode.
		 * clearBuffer:  You can either clear your memory buffer or not.   
		 */
		void clearShiftRegister(bool wipeBuffer);
		
		/** Set all bits to 1  in memory buffer
		* Requires a writeRegisters() call to take affect on shift register[s].*/
		void fillBuffer();

		/** Set random junk to memory buffer 
		* Requires a writeRegisters() call to take affect on shift register[s].*/
		void randomFillBuffer();

		/** Invert bits (bitewise opertation).  That is set all 0's to 1 and visa-versa 
		* Requires a writeRegisters() call to take affect on shift register[s].*/
		void invertBuffer();

		/** Set a single bit 
		* Requires a writeRegisters() call to take affect on shift register.*/
		void setBufferBit(uint8_t index, uint8_t value);

		/** Flushes memory buffer to Shift Registers.  This MUST been called after all memory/buffer operations. The only exception is clearShiftRegister(bool).*/	
		void writeRegisters();

		/** Get bit in memory buffer, not necessarily what is on shift register.  It will differ is writeRegisters() hasn't been called yet. */
		bool getBufferBit(uint8_t index);

		/** Total number of memory buffers/shift register pins we know about */
		uint8_t getNumberOfBits() {
			return (numberOfShiftRegisters*8);
		};

	private:
		uint8_t SERPin, RCKPin, SCKPin;
		int8_t SRCLRPin;
		uint8_t numberOfShiftRegisters=1;
		uint8_t *bits;

		uint8_t getBufferArrayPos(uint8_t index);
		uint8_t getBitPos(uint8_t index);

};





#endif 
