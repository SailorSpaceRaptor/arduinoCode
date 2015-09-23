/* Code for intermediate Arduino class, libraries lesson
created by Jonathan Eskow for use by NextFab llc in teaching students how to
use libraries to expand the capabilities of the Arduino Microcontroller platform.
This code will explore the LiquidCrystal library by Adafruit, the TMP36 temperature sensor, 
and AREF pin on the Arduino board.

/* The circuit:
 * LCD RS pin to digital pin 12
 * LCD Enable pin to digital pin 11
 * LCD D4 pin to digital pin 5
 * LCD D5 pin to digital pin 4
 * LCD D6 pin to digital pin 3
 * LCD D7 pin to digital pin 2
 * LCD R/W pin to ground
 * ends to +5V and ground
 * wiper to LCD VO pin (pin 3)
*/
#include<LiquidCrystal.h> //include library code

#define sw1 6//define pin for button
#define TMP A0//define pin for TMP36
#define aref_volt 3.3//define reference voltage

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);//initialize library with the numbers of interface pins

void setup() 
{
 Serial.begin(9600); //begin serial monitor
lcd.begin(16,2);//set up LCD columns and rows  
pinMode(sw1, INPUT);//set pinMode for button
analogReference(EXTERNAL);//analog reference for use with TMP36
}

void loop() 
{
  //set variables for temperature storage
  
  double temperature = tempMeasure();//call temp function
  double tempF = (temperature * 9.0/5.0 + 32);//take temp and run calculation for Fahrenheit measurement
  
  while(digitalRead(sw1) == false)//while button is pressed, readout is in Celsius
    {
      Serial.println(temperature);//prints in serial monitor for debugging
      lcd.print(temperature);//print temperature on lcd screen
      lcd.setCursor(0,1);//set cursor to 0,1
      delay(2000);//delay for 2 seconds between readings
      lcd.clear();//clear lcd buffer
    }
  
  Serial.println(tempF);//print faharenheit value in serial
  lcd.print(tempF);//print faharenheit value on LCD
  lcd.setCursor(0,1);//set cursor
  delay(2000);//read for 2 seconds between reading
  lcd.clear();//clear LCD buffer

} //end main method

/*
this function takes a voltage reading from the tmp36 and translates it into a
celsius value 
*/

double tempMeasure()
{
 double temp;
 int reading = analogRead(TMP); //take voltage reading
 double voltage = reading * aref_volt;//take voltage reading and multiply by aref voltage

 voltage /= 1024.0; //divide reading by 1024 to map (10 bit)

 temp = (voltage - 0.5) * 100; //convert 10mV per degree with a 500 mV offset

 return temp;//return temperature to main method
}//end
