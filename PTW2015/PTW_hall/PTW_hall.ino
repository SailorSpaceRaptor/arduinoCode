/*
PTW2015 code for break beam sensor
*/

#include <Adafruit_GFX.h> //GFX library
#include <Adafruit_NeoMatrix.h> //neoMatrix library
#include <Adafruit_NeoPixel.h> //neoPixel library

#ifndef PSTR
 #define PSTR // Make Arduino Due happy
#endif

#define PIN 6 //pin 6 is Matrix
#define spk 11 //speaker pin
#define hall A0; //pin A0 is hall effect

//NeoPixel Matrix is 8 by 8 and runs from pin 6
//pixel (1,1) is top and right
//pixels are arranged in columns
//pixels are progressive, not zigzag
//pixels are wired for GRB bitstream and run at 800KHz
Adafruit_NeoMatrix matrix = Adafruit_NeoMatrix(8, 8, PIN,
  NEO_MATRIX_TOP     + NEO_MATRIX_RIGHT +
  NEO_MATRIX_COLUMNS + NEO_MATRIX_PROGRESSIVE,
  NEO_GRB            + NEO_KHZ800);
 
float sensorValue = 0.0; //sensor value initial starts at 0

//folowing arrays dictate pixels to be lit

//center square
const int16_t sq1[4] = {27,28,36,35};
//second square from center
const int16_t sq2[12] = {18,19,20,21,29,37,45,44,43,42,34,26};
//third square from center
const int16_t sq3[20] = {9,10,11,12,13,14,22,30,38,46,54,53,52,51,50,49,41,33,25,17};
//fourth square from center
const int16_t sq4[28] = {0,1,2,3,4,5,6,7,15,23,31,39,47,55,63,62,61,60,59,58,57,56,48,40,32,24,16,8};

void setup() 
{
 matrix.begin(); //start matrix
 matrix.setBrightness(40);//set matrix brightness
 Serial.begin(9600);
// pinMode(spk, OUTPUT);
}

void loop() 
{
  matrix.fillScreen(0);
  matrix.show();
 
 sensorValue = analogRead(A0); //start readings from sensor
 
  if (sensorValue <= 500) 
    {
      tone(spk, 440, 500); //play G# for half a second
      hallPattern(); //activate concentric square pattern
    }
  else
   {
     matrix.fillScreen(0); //clear screen
     matrix.show();
   }
}

void hallPattern()
{
 matrix.fillScreen(0); //clear matrix
 matrix.show();

  for(uint16_t i = 0; i <= 4; i++)
    {
     matrix.setPixelColor(sq1[i], (0,255,255)); //light inner square
     matrix.show();
    }

delay(10);

  for(uint16_t i = 0; i <= 12; i++)
  {
    matrix.setPixelColor(sq2[i], (0,255,255)); //light second square
    matrix.show();
  }
  
 delay(10);
 
 for(uint16_t i = 0; i <= 20; i++)
 {
   matrix.setPixelColor(sq3[i], (0,255,255)); //light third square
   matrix.show();
 }
 delay(10);
 
 for(uint16_t i = 0; i <= 28; i++)
 {
   matrix.setPixelColor(sq4[i], (0,255,255)); //light fourth square
   matrix.show();
 }
  delay(10);
  
 matrix.fillScreen(0); ///clear matrix
 matrix.show();
 
}
