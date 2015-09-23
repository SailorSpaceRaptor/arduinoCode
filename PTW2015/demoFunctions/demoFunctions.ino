#include <Wire.h>
#include "Adafruit_TCS34725.h"
const int button = 8;
const int speakerPin = 11;
const int redPin = 3;
const int greenPin = 5;
const int bluePin = 6;
const int TILT = 4;
#define hall A7
#define fsrAnalogPin A0

int fsrReading;
int LEDbrightness;
const int sensorPin = 2;
float sensorValue = 0.0;
int sensorState = 0, lastState = 0;

int numTones = 4;
//int tones [] = {294, 330, 369, 440};
//                 D    E   Gflat, A

#define commonAnode false

byte gammatable[256];

Adafruit_TCS34725 tcs = Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_50MS, TCS34725_GAIN_4X);

void setup() 
{
   
  Serial.begin(9600); //start serial read
  pinMode(TILT, INPUT); //set tilt switch to input
  pinMode(button, INPUT);
  pinMode (sensorPin, INPUT); // set sensor to in
  digitalWrite(sensorPin, HIGH); //turn on pull-up resistor
  digitalWrite(TILT, HIGH);
  digitalWrite(button, HIGH);
   
   if (tcs.begin()) 
   {
    Serial.println("Found sensor");
  } 
  else 
  {
    Serial.println("No TCS34725 found ... check your connections");
    while (1); // halt!
  }
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);
    // thanks PhilB for this gamma table!
  // it helps convert RGB colors to what humans see
  for (int i=0; i<256; i++) 
  {
    float x = i;
    x /= 255;
    x = pow(x, 2.5);
    x *= 255;
      
    if (commonAnode) 
    {
      gammatable[i] = 255 - x;
    } 
    else 
    {
      gammatable[i] = x;      
    }
    //Serial.println(gammatable[i]);
  }
}

void loop()
{
 tiltDemo();
 hallDemo(); 
 FSRdemo();
 breakDemo();
 while(digitalRead(button) == true)
  { 
    colorView();
  }
}

void tiltDemo()
{
  while (digitalRead(TILT) == true) //while switch is broken
   {
     digitalWrite(redPin,1); //turn on LED
     Serial.println("I've fallen and I can't get up!"); //send message to Serial Monitor
     delay(100); //delay between readings
     tone(speakerPin, 294, 500); //play a D
   }
  digitalWrite(redPin,0); //while switch is together, do nothing.
}

void hallDemo()
{
   sensorValue = analogRead(hall); //start sensor at zero
   if (sensorValue <= 500) //if sensor comes in contact with magnetic field
    {
      digitalWrite(bluePin,1); //turn on LED
      Serial.println("Field Detected");
      tone(speakerPin, 330, 500); //play an E 
    }
   else
      digitalWrite(bluePin ,0); //else keep LED off

}

void FSRdemo()
{
   fsrReading = analogRead(fsrAnalogPin);
  Serial.print("Analog reading = ");
  Serial.println(fsrReading);
 
 LEDbrightness = map(fsrReading, 0, 1023, 0, 255); //map analog reading from 0 to 1023 to 0 to 255
 
 analogWrite(greenPin, LEDbrightness); //LED gets brighter the harder you press the sensor
 
 delay(100);
}

void breakDemo()
{
  //read state of pushbutton value
sensorState = digitalRead(sensorPin);

//check if sensor beam is broken
if(sensorState == LOW)
 {
  digitalWrite(redPin, 1);
  tone (speakerPin, 369, 500);
 }
else
 {
  digitalWrite(redPin, 0);
 }

if (sensorState && !lastState)
  {
  Serial.println("Unbroken");
  }

if (!sensorState && lastState)
  {
   Serial.println("Broken");
  }
  
  lastState = sensorState;
}  

void colorView()
{
  uint16_t clear, red, green, blue;

  tcs.setInterrupt(false);      // turn on LED

  delay(60);  // takes 50ms to read 
  
  tcs.getRawData(&red, &green, &blue, &clear);

  tcs.setInterrupt(true);  // turn off LED
  
  Serial.print("C:\t"); Serial.print(clear);
  Serial.print("\tR:\t"); Serial.print(red);
  Serial.print("\tG:\t"); Serial.print(green);
  Serial.print("\tB:\t"); Serial.print(blue);

  // Figure out some basic hex code for visualization
  uint32_t sum = clear;
  float r, g, b;
  r = red; r /= sum;
  g = green; g /= sum;
  b = blue; b /= sum;
  r *= 256; g *= 256; b *= 256;
  Serial.print("\t");
  Serial.print((int)r, HEX); Serial.print((int)g, HEX); Serial.print((int)b, HEX);
  Serial.println();

  //Serial.print((int)r ); Serial.print(" "); Serial.print((int)g);Serial.print(" ");  Serial.println((int)b );

  analogWrite(redPin, gammatable[(int)r]);
  analogWrite(greenPin, gammatable[(int)g]);
  analogWrite(bluePin, gammatable[(int)b]);
}
