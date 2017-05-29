 /*
 Chat  Server

 A simple server that distributes any incoming messages to all
 connected clients.  To use telnet to  your device's IP address and type.
 You can see the client's input in the serial monitor as well.
 Using an Arduino Wiznet Ethernet shield.

 Circuit:
 * Ethernet shield attached to pins 10, 11, 12, 13
 * Analog inputs attached to pins A0 through A5 (optional)

 created 18 Dec 2009
 by David A. Mellis
 modified 9 Apr 2012
 by Tom Igoe

 */

#include <SPI.h>
#include <Ethernet2.h>
#include <Wire.h>
#include <math.h>

void changeLightFrequency();
void checkSensors();

//variables

enum sensorsEnum {
  pirS, microphoneS, camaraS, temperatureS, ligthS
};

enum actuatorsEnum {
  lightA, soundA, motorA
};

//regulator
byte light = "g";
byte voltage = 11;
//ic2
byte c = 0;
byte c1 = 0;
char Device = 8; //device to hear in i2c bus
bool State;

//---sensors---
// check states of this types of sensors:  pirS, microphoneS, camaraS, temperatureS, ligthS
int sensorTypes = 5;
bool sensorsCheck[] = {true,false,false,false,false};
int sensorsDevices[5][10];//first value in each rows holds the total devices
//actuators

// Enter a MAC address and IP address for your controller below.
// The IP address will be dependent on your local network.
// gateway and subnet are optional:
byte mac[] = {
  0x90, 0xA2, 0xDA, 0x10, 0xAC, 0xD6
};
IPAddress ip(192, 168, 100, 177);
IPAddress gateway(192, 168, 100, 1);
IPAddress subnet(255, 255, 0, 0);


// telnet defaults to port 23
EthernetServer server(23);
boolean alreadyConnected = false; // whether or not the client was connected previously
void setup() {

  Wire.begin(); // join i2c bus (address optional for master)
  
  // initialize the ethernet device
  Ethernet.begin(mac, ip, gateway, subnet);
  // start listening for clients
  server.begin();
  // Open serial communications and wait for port to open:
  Serial.begin(9600);

  Serial.print("Chat server address:");
  Serial.println(Ethernet.localIP());
}

void loop() {

  
  
  //wait for message over ethernet
  EthernetClient client = server.available();
 
  
  // when the client sends the first byte, say hello:
  if (client) {
    Serial.println("debug when client");
    if (!alreadyConnected) {
      // clead out the input buffer:
      client.flush();
      Serial.println("We have a new client");
      client.println("Hello, client!"); //------use this to send messages
      alreadyConnected = true;
    }

    if (client.available() > 0) {
      Serial.println("debug available client");
      // read the bytes incoming from the client:
      char thisChar = client.read();
      // echo the bytes back to the client:
      server.write(thisChar);
      // echo the bytes to the server as well:
        light = thisChar;
        changeLightFrequency();
    
    }
    
    }


  //sensor i2c channel check
  checkSensors();
  int wireMessage = Wire.available();
    if(wireMessage > 1)
    {
      char indexSensorTypeChar = Wire.read();
      int indexSensorType = indexSensorTypeChar - 48;//convert char to and adjust value.
      char sensorValueChar = Wire.read();
      //TODO if there is a message do proper actions
      switch(indexSensorType)
      {
        case pirS:
          Serial.println("pir sensor");
          //TODO insert code for put request instead of this
          if (sensorValueChar == '1')
          {
            //turn on light 
            light = "f";
            changeLightFrequency();
            Serial.println("turn on");
        
            }else
            {
              //turn on light 
               light = "l";
               changeLightFrequency();
               Serial.println("turn off");
            }                    
         break;
         case microphoneS:                  
         break;
         default: 
          Serial.println("no sensor data change");
          break;
      }
    }

  }
  
      


void changeLightFrequency()
{

   Wire.beginTransmission(0x4); // transmit to device #4
    //Wire.write("x is ");        // sends five bytes
    byte tosend = (light-100)* 10;//100*log((light/58.2)+1);
    Wire.write(tosend);              // sends one byte
    Wire.write(voltage);              // sends one byte
    //char c = Wire.read(); // receive a byte as character
    Wire.endTransmission();    // stop transmitting
    Wire.requestFrom(0x4, 2);    // request 6 bytes from slave device #8
    while (Wire.available()) { // slave may send less than requested
    c = Wire.read(); // receive a byte as character
    c1 = Wire.read(); // receive a byte as character
    //Serial.println(c1);
 }
}
void checkSensors()
{
  //TODO logic to validate wich devices and sensors to check
  //for testing only pir sensor will be implemented
   Wire.requestFrom(Device, 2);    // request 2 bytes from slave device #8
}

  
  



