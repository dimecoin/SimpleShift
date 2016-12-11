#include <SimpleShift.h>

byte sleepTime = 1000;

SimpleShift simpleShift(2, 8, 9, 10);

void setup() {

	//reset all register pins
	simpleShift.clearBuffer();
	// Flush data to shift registers when done writing!
	simpleShift.writeRegisters();

}


bool a = true;
void loop() {

	// Set all pins to 1
	simpleShift.fillBuffer();

	// Flush data to shift registers when done writing!
	simpleShift.writeRegisters();
	delay(sleepTime);


	simpleShift.clearBuffer();
	// Set all odd pins
	for (int i=0; i<simpleShift.getNumberOfBits(); i++) {
		if (i%2==0) {
			simpleShift.setBufferBit(i, 1);
		}
	}
	
	// Flush data to shift registers when done writing!
	simpleShift.writeRegisters();
	delay(sleepTime);


	// Invert all pins, cool
	simpleShift.invertBuffer();
	// Flush data to shift registers when done writing!
	simpleShift.writeRegisters();
	delay(sleepTime);


	// Put random junk in all pins
	//simpleShift.randomFillBuffer();
	// Flush data to shift registers when done writing!
	//simpleShift.writeRegisters();
	//delay(sleepTime);

}





















