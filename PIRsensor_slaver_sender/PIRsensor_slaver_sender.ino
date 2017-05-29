// Pir sensor slave sender
//
// This program will control a simple pir sensor and 
// notifyMaster through i2c communication whenever there is
// a change.
//
// by Esteban Arias, May 2017
// modified by Adrian Chacon
//
// Reference: wire>slave_sender example


#include <Wire.h>

//variable to send
int delayCheck = 100;

int sensorPIRPin = 3;
int sensorPIRValue = 0;
int deviceNumber = 8;
bool movementDetection = false;
bool notifyMaster = false;

void setup() {
  Wire.begin(8);      // join i2c bus with address #8
  Wire.onRequest(requestEvent); // register event
  Serial.begin(9600);
 pinMode(sensorPIRPin, OUTPUT);
}

void loop() {
  //get analog value of pin connected to PIR
  sensorPIRValue = analogRead(sensorPIRPin);
  //activate notify flag if value changes
  //check only if notify is disable
  if (sensorPIRValue > 250 && !notifyMaster)
  {
    if (movementDetection)
    {
      notifyMaster = false;  
    }else
    {
      notifyMaster = true;
    }
    movementDetection = true;
  }else if(!notifyMaster) 
  {
    if (movementDetection)
    {
      notifyMaster = true;  
    }else
    {
      notifyMaster = false;
    }
    movementDetection = false;
  }
  Serial.println("value");
  Serial.println(sensorPIRValue);
  
  
  delay(delayCheck);
}

// function that executes whenever data is requested by master
// this function is registered as an event, see setup()
void requestEvent() {
  if(notifyMaster)
  {
    if(movementDetection)
    {
      Wire.write("01");
      Serial.println("send 11");
    }else
    {
      Wire.write("00");
      Serial.println("send 10");
    }
    // as expected by master
    notifyMaster = false;
  }
}
