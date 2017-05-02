This project was debeloped by Ing.Esteban Arias for ECOmotion.S.A.

It is a version 1.0 of a Switching Buck Regulator controlled by AtTiny85.

To load the program to AtTiny85 we use an Arduino Uno as ISP.
This tutorial is a little bit diferent to the original tutorial from -> https://create.arduino.cc/projecthub/arjun/programming-attiny85-with-arduino-uno-afb829

-Configuring Arduino Uno as ISP Steps:
	-Connect the Arduino Uno to the computer.
	-Open the sketch: File->Examples->11.ArduinoISP ->Arduino as ISP
	-Load the program on the Arduino Uno 
	(Be sure that the board is the correct and the programmer is set as "AVRISP mkll")
	-Connect the AtTiny85 correct pin to the arduino Uno (That was described in "Arduino as ISP" sketch)
	or connect the AtTiny85 program shield
	
-Download the AtTiny85 wire library from -> https://github.com/rambo/TinyWire and install it.
	-On the Arduino IDE: Sketch-> Include Library-> Add .ZIP Library and search the location

-Programming the AtTiny85 Steps:
	-Configuring the Arduino IDE:
		-Tools  ->Board -> "ATtiny25/45/85"
			->Processor-> "ATtiny85"
			->Clock -> "Internal clock 16MHz"
			->Programmer -> "Arduino as ISP"
			->Burn Bootloader
	-Load the Sketch "receibe_tiny_esteban_regulator.ino" on ATtiny85

-An example to control ATtiny85 by I2C -> Load on the Arduino Uno the skecth "mater_writer_reader_tiny_esteban"

That's all. 