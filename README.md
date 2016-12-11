# Simple Shift Library for the Arduino 


### Usage

See example folder.

### How to Wire

[74HC595 Datasheet (pdf)](http://www.ti.com/lit/ds/symlink/sn74hc595.pdf)

* SER [pin 14] on 74HC595 wired to Arduino Digital Pin 8
* RCLK [pin 12] on 74HC595 wired to Arduino Digital Pin 9
* SRCLK [pin 11] on 74HC595 wired to Arduino Digital Pin 10

* VCC [pin 16] should go to 5V 
* GND [pin 8] should go to Ground
* !OE [pin 13] should be tied to Ground 

![test](http://i.imgur.com/W5lKDp4.png)

Library needs to know about SER, RCLK and SRCLK pin.  They are configurable in software like this:

    SimpleShift simpleShift(1, 8, 9, 10);

Parameters are: (NumerOfShiftRegisters, SERPIN, RCKPIN, SCKPIN)

* Number of Shift Registers wired up (in this case, 1)

You can wire up multiple shift register by tying QH\` [pin 9] from first register to SER [pin 14] on second register.
    
* [Another Wiring Guide](http://bildr.org/2011/02/74hc595/)    


### TODO
* Return Number of registers
* Return byte value of register buffer
* Functions to set 7 segment display character


