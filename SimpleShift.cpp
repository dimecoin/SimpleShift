#include "SimpleShift.h"

SimpleShift::SimpleShift(uint8_t numberOfShiftRegisters, uint8_t SERPin, uint8_t RCKPin, uint8_t SCKPin, int8_t SRCLRPin) {

	this->numberOfShiftRegisters = numberOfShiftRegisters;
	this->bits = (uint8_t *)malloc(numberOfShiftRegisters);

	this->SERPin = SERPin;
	this->RCKPin = RCKPin;
	this->SCKPin = SCKPin;
	this->SRCLRPin = SRCLRPin;

	pinMode(SERPin, OUTPUT);
	pinMode(RCKPin, OUTPUT);
	pinMode(SCKPin, OUTPUT);

	// -1 is software mode, only setup pins if we have one.
	if (SRCLRPin != -1) {
		pinMode(SRCLRPin, OUTPUT);
		digitalWrite(SRCLRPin, HIGH);
	}
};

SimpleShift::~SimpleShift() {
	free(bits);
	bits = NULL;
};

void SimpleShift::clearBuffer() {
	memset(bits, 0, numberOfShiftRegisters);
};

void SimpleShift::clearShiftRegister(bool wipeBuffer) {

	if (wipeBuffer) {
		clearBuffer();
	}

	digitalWrite(RCKPin, LOW);

	if (SRCLRPin == -1) {
		// Software mode, fake it.
		for (int8_t index=getNumberOfBits()-1; index>=0; index--) {
			digitalWrite(SCKPin, LOW);
			digitalWrite(SERPin, LOW);
			digitalWrite(SCKPin, HIGH);
		}

	} else {
		// Hardware mode
		digitalWrite(SRCLRPin, LOW);
		digitalWrite(SRCLRPin, HIGH);
	}
	
	digitalWrite(RCKPin, HIGH);
}

void SimpleShift::fillBuffer() {
	memset(bits, 255, numberOfShiftRegisters);
};

void SimpleShift::randomFillBuffer() {
	memset(bits, random(256), numberOfShiftRegisters);
};

void SimpleShift::invertBuffer() {
	for (int8_t i=0; i<numberOfShiftRegisters; i++) {
		bits[i] = ~bits[i];
	}
};

void SimpleShift::setModulusBuffer(uint8_t mod) {
	
	for (uint8_t i = 0; i<getNumberOfBits(); i++) {
		if (i % mod == 0) {
		       setBufferBit(i, HIGH);
		} else {
		       setBufferBit(i, LOW);
		}		
	}
	
}

void SimpleShift::setOddBuffer() {
	setModulusBuffer(2);
	invertBuffer();
};
void SimpleShift::setEvenBuffer() {
	setModulusBuffer(2);
}


void SimpleShift::chase(bool pingPong) {

	setBufferBit(chaseIndex, HIGH);
	chaseIndex+=chaseDirection;


	if (pingPong) {
		if (chaseIndex == getNumberOfBits()-1 ) {
			chaseDirection = -1;
		}
		if (chaseIndex == 0) {
			chaseDirection = 1;
		}

	}  else {
		if (chaseIndex == getNumberOfBits() ) {
			chaseIndex = 0;
		}
	}
}


uint8_t SimpleShift::getBufferArrayPos(uint8_t index) {
	uint8_t reg = index/8;
	return (reg);
}


uint8_t SimpleShift::getBitPos(uint8_t index) {

	// Get our register (ie, which position in array it is at);
	uint8_t reg = getBufferArrayPos(index);

	// Flip from least to most significate location
	uint8_t pos = 7 - ( index - (reg *8) );
	
       return (pos);	
};

bool SimpleShift::getBufferBit(uint8_t index) {

	uint8_t reg = getBufferArrayPos(index);
	uint8_t bit = getBitPos(index);

	bool val = bitRead(bits[reg], bit);
	return (val);
}

void SimpleShift::setBufferBit(uint8_t index, uint8_t value) {

	uint8_t reg = getBufferArrayPos(index);
	uint8_t bit = getBitPos(index);

	if (value) {
		bitSet(bits[reg], bit);
	} else {
		bitClear(bits[reg], bit);
	}

	/*
	Serial.print("I/V: "); Serial.print(index, DEC); Serial.print(" / "); Serial.println(value, DEC);
	Serial.print("R: "); Serial.println(r, DEC);
	Serial.print("bit: "); Serial.println(bit, DEC);
	Serial.print("0: " ); Serial.println(bits[0], BIN); Serial.print("1: " ); Serial.println(bits[1], BIN); Serial.println();
	*/
};

void SimpleShift::writeRegisters() {
		
	digitalWrite(RCKPin, LOW);

	for (int8_t index=getNumberOfBits()-1; index>=0; index--) {

		digitalWrite(SCKPin, LOW);

		bool val = getBufferBit(index);

		digitalWrite(SERPin, val);
		digitalWrite(SCKPin, HIGH);
	}

	digitalWrite(RCKPin, HIGH);
	delay(1);
};
