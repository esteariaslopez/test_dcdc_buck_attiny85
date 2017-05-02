// Get this from https://github.com/rambo/TinyWire
#include <TinyWireS.h>

#define I2C_SLAVE_ADDRESS 0x4 // the 7-bit address (remember to change this when adapting this example)

int pinFB = 3;
const int pinLight = 1;
const int pinVoltage = 4;
int PWMvoltage = 0;

byte light = 0 ;
byte voltage_receibed = 0;
byte currentvolt = 0;

///////////////////////////////////////////////////////////////////////////////////
/////////////////////////TO I2C////////////////////////////////////////////////////

//int I2C_SLAVE_ADDRESS = 8;  


void requestEvent()
{  
    TinyWireS.send(currentvolt);
    TinyWireS.send(PWMvoltage);
}

void receiveEvent()
{
  light = TinyWireS.receive();
  voltage_receibed = TinyWireS.receive();
}
/////////////////////////////////i2c/////////////////////////

//////////////////////////////////////////////////////////////
////////////////////////////////TO CONTROL////////////////////
////////////////AtTiny85/////////////
//////Reset - Pin1////Pin8 - Vcc/////
//////ADC   - Pin2////Pin7 - SCL/////
//pinVoltage- Pin3////Pin6 - pinLight
//////GND   - Pin4////Pin5 - SDA/////


  void SetLight(int bright){ // receives the brightness level to setup// receives int between 0 and 99
  //if error ...
    int nbright = 2.55*bright;
    analogWrite(pinLight,nbright);
  }
  
int SetVoltage(int pwmVoltage, int Voltage){  //it receives the last voltage measured and the voltage level to setup
  //if error...
  int nVoltage = 42.67*Voltage;
  int currentVoltage = 0;
  for (int i = 0; i < 10; i++){
    currentVoltage = (currentVoltage + analogRead(pinFB))/2;
  }
   
  currentvolt = byte(0.0234*currentVoltage);//byte(map(currentVoltage,0,1023,0,255));
  if ((currentVoltage < nVoltage) && (pwmVoltage < 255)){
    pwmVoltage = pwmVoltage +1;
    }
   else if ((currentVoltage > nVoltage) && (pwmVoltage > 0)){
    pwmVoltage = pwmVoltage -1;
    }else{
      pwmVoltage = pwmVoltage;
      }
  analogWrite(pinVoltage,pwmVoltage);
  return pwmVoltage;
  }

///////////////////////////////control////////////////////////

void setup() {
  // put your setup code here, to run once:
    TinyWireS.begin(I2C_SLAVE_ADDRESS);
    TinyWireS.onReceive(receiveEvent);
    TinyWireS.onRequest(requestEvent);

    pinMode(pinLight, OUTPUT);
    pinMode(pinVoltage, OUTPUT);
    pinMode(pinFB, INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  SetLight(light);
  //int pwmVoltage = 2.55*voltage_receibed;
  //analogWrite(pinVoltage,pwmVoltage);
  PWMvoltage = SetVoltage(PWMvoltage, voltage_receibed);
//tws_delay(100);
}
