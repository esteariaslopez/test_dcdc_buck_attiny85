//#include <Wire.h>

// Wire Master Writer
// by Nicholas Zambetti <http://www.zambetti.com>

// Demonstrates use of the Wire library
// Writes data to an I2C/TWI slave device
// Refer to the "Wire Slave Receiver" example for use with this

// Created 29 March 2006

// This example code is in the public domain.


#include <Wire.h>
#include <math.h>

byte light = 0;
byte voltage = 10;
byte c = 0;
byte c1 = 0;

int analogPin = A1;


void setup() {
  Serial.begin(9600);
  Wire.begin(); // join i2c bus (address optional for master)
  pinMode(analogPin, INPUT);
  
}
void loop() {
  Wire.beginTransmission(0x4); // transmit to device #8
  //Wire.write("x is ");        // sends five bytes
  int tosend = 100*log((light/58.2)+1); // %BRIGHTNESS IN LOGARITMIC  *TAKE A DECISION ABOUT THIS
  Wire.write(tosend);              // sends one byte
  Wire.write(voltage);              // sends one byte
  //char c = Wire.read(); // receive a byte as character
  Wire.endTransmission();    // stop transmitting
  

  Wire.requestFrom(0x4, 2);    // request 6 bytes from slave device #8

  while (Wire.available()) { // slave may send less than requested
    c = Wire.read(); // receive a byte as character //
    c1 = Wire.read(); // receive a byte as character
    Serial.println(c);         // print the character
    //Serial.print(" ");
    //Serial.println(c1);         // print the character

  }

  delay(2000);

  if (light < 100){
    light += 10;
    }else{light = 0;}
  //int currentVoltage = 0;
  //for (int i = 0; i < 2; i++){
  //  currentVoltage = (currentVoltage + analogRead(analogPin))/2;
  //}
  
  //Serial.println(currentVoltage*0.02362);         // print the character

}
