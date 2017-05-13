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

//variables

//regulator
byte light = "g";
byte voltage = 11;
//ic2
byte c = 0;
byte c1 = 0;
char Device = 8; //device to hear in i2c bus
bool State;

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
boolean ledState = false;
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
  pinMode(A1, OUTPUT);
  ledState = false;
}

void loop() {

  
  
  //wait for message over ethernet
  EthernetClient client = server.available();
  if(ledState)
  {
    digitalWrite(A1, HIGH);
    }else
    {
       digitalWrite(A1, LOW);
      }
  
  // when the client sends the first byte, say hello:
  if (client) {
    Serial.println("debug when client");
    if (!alreadyConnected) {
      // clead out the input buffer:
      client.flush();
      Serial.println("We have a new client");
      client.println("Hello, client!");
      alreadyConnected = true;
      ledState = true;
    }

    if (client.available() > 0) {
      Serial.println("debug available client");
      // read the bytes incoming from the client:
      char thisChar = client.read();
      // echo the bytes back to the client:
      server.write(thisChar);
      // echo the bytes to the server as well:
      Serial.write(thisChar);
      if(thisChar == 'n')
      {
        ledState = true;
        //digitalWrite(LED_BUILTIN, HIGH);
        Serial.println("-on-");
      }else if (thisChar == 'f')
      {
        ledState = false;
        //digitalWrite(LED_BUILTIN, LOW);
        Serial.println("-off-");
      } else {
        light = thisChar;
        changeLightFrequency();
        Serial.println("-changed-");
      }
        
      
    
  
    }
    
    }

   //i2c master reader
      Wire.requestFrom(Device, 1);    // request 1 bytes from slave device #8

       while (Wire.available()) { // slave may send less than requested
      State = Wire.read(); // receive a byte as character
      if (State == true){
        Serial.println("TRUE");

        //turn on light 
        light = "f";
        changeLightFrequency();
        
        }else{
          Serial.println("FALSE");
          //turn on light 
           light = "l";
           changeLightFrequency();
          }         // print the character
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
  
  



