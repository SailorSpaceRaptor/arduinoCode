/*
PTW2015 code for break beam sensor
*/
#include <Wire.h>
#include "Adafruit_TCS34725.h"
#include <Adafruit_GFX.h> //GFX library
#include <Adafruit_NeoMatrix.h> //neoMatrix library
#include <Adafruit_NeoPixel.h> //neoPixel library

#ifndef PSTR
 #define PSTR // Make Arduino Due happy
#endif

#define PIN 6 //pin 6 is Matrix
//pins A4 and A5 are the RGB sensor

//NeoPixel Matrix is 8 by 8 and runs from pin 6
//pixel (1,1) is top and right
//pixels are arranged in columns
//pixels are progressive, not zigzag
//pixels are wired for GRB bitstream and run at 800KHz
Adafruit_NeoMatrix matrix = Adafruit_NeoMatrix(8, 8, PIN,
  NEO_MATRIX_TOP     + NEO_MATRIX_RIGHT +
  NEO_MATRIX_COLUMNS + NEO_MATRIX_PROGRESSIVE,
  NEO_GRB            + NEO_KHZ800);

//Adafruit RGB sensor, takes reading for 50ms (10 cycles) with 2X gain
Adafruit_TCS34725 tcs = Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_50MS, TCS34725_GAIN_4X);

void setup() 
{
  Serial.begin(9600);
  matrix.begin(); //start matrix
  matrix.setBrightness(40);//set matrix brightness

if (tcs.begin()) //tests to see if sensor is active
  {
    Serial.println("Found sensor");
  } 
  else
  {
    Serial.println("No TCS34725 found ... check your connections");
    while (1); // halt!
  }
}

void loop() 
{
 uint16_t clear, red, green, blue; //raw data from color sensor

 tcs.setInterrupt(false);  // turn on LED

 delay(50);  // takes 50ms to read 
  
tcs.getRawData(&red, &green, &blue, &clear);

 tcs.setInterrupt(true);  // turn off LED

uint16_t color1 = matrix.Color(red,green,blue); //create variable of color one 
uint16_t color2; //create variable for next color, this helps with stablizer

matrix.fillScreen(color1); //fill screen with color reading
matrix.show(); //update matrix

Stablizer(red,green,blue); //call in red, green and blue from color1 
color1 = color2; //color 1 now equals color 2
matrix.show(); //update matrix

}

//function recognizes previous color, cleans up the reading, and gives the second color
uint16_t Stablizer(uint16_t red, uint16_t green,uint16_t  blue)
{
 uint16_t color1 = matrix.Color(red, green, blue);
 
 uint16_t color2;
 
  //recognize current color
 uint16_t r1 = red; //current color red
 uint16_t g1 = green; //current color green
 uint16_t b1 = blue; //current  color blue
 
 //place holders to recognize second color
 uint16_t r2 = 0; //second color red
 uint16_t g2 = 0; //second color blue
 uint16_t b2 = 0; //second color green
 
 uint16_t color[3] = {r1, g2, g2}; //array to hold color components of 1
 uint16_t color0[3] = {r2, g2, b2}; //array to hold color components of 2 

//map one color to the other
for(uint16_t i = 0; i <= 2; i++)
{
  for( uint16_t j = 0; i <= 2; i++)
  {
    color[i] = color0[j];
  }

color1 = color2;
return color2;

}

}
