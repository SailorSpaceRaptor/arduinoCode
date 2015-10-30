/*
 * Created by Jonathan Eskow 10/29/2015 this is a class meant to define behavior of a light or UV sensor designed to be used with Seeed Studio grove
 * sensors but should be able to be carried over to other sensors
 */
 
 #include <LEEPROM.h>
 
 //types of sensors supported
 enum type {UV, LIGHT};

 class lightSense
 {
  
  /*
   * public methods
   */
   
  public:
  
  //member variables
  int sensorRead;
  unsigned long currentMillis = millis();
  unsigned long lastMillis;
  unsigned long duration;
  
  //default constructor, takes in pin attached and sensor type
  lightSense(int pin, type)
  {
    int sensePin = pin;
    sensorRead = 0;
    duration = 7200000;//two hour duration
  }

 ;
 
 /*
 * private methods
 */
 
  private: 
   
  // method takes raw voltage reading and gives english read out
   int takeMeasure(int sensePin)
  {
   int lightSense = analogRead(sensePin);
   map(lightSense,0,1023,0,255); //map light readings
  
   return lightSense;
  }//end takeMeasure
 
 }
;

