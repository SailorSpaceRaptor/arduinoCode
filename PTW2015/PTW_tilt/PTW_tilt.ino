/*
PTW2015 code for tilt sensor
*/

#include <Adafruit_GFX.h> //GFX library
#include <Adafruit_NeoMatrix.h> //neoMatrix library
#include <Adafruit_NeoPixel.h> //neoPixel library

#ifndef PSTR
 #define PSTR // Make Arduino Due happy
#endif

#define PIN 6 //pin 6 is Matrix
#define spk 11 //speaker pin
const int TILT = 4; //pin 5 is break beam sensor
//

//NeoPixel Matrix is 8 by 8 and runs from pin 6
//pixel (1,1) is top and right
//pixels are arranged in columns
//pixels are progressive, not zigzag
//pixels are wired for GRB bitstream and run at 800KHz
Adafruit_NeoMatrix matrix = Adafruit_NeoMatrix(8, 8, PIN,
  NEO_MATRIX_TOP     + NEO_MATRIX_RIGHT +
  NEO_MATRIX_COLUMNS + NEO_MATRIX_PROGRESSIVE,
  NEO_GRB            + NEO_KHZ800);
 
 //the following arrays are numbers of pixels on the matrix
const int16_t xcord[8] = {0,1,2,3,4,5,6,7};
const int16_t ycord[8] = {0,1,2,3,4,5,6,7};

void setup() 
{
  matrix.begin(); //start matrix
  matrix.setBrightness(40);//set matrix brightness
  Serial.begin(9600);
  pinMode(TILT,INPUT); //claim tilt as input
//  digitalWrite(TILT, LOW); //use on board pull down resistor 
  Serial.begin(9600);

}

void loop() 
{
  while(digitalRead(TILT)== false)//while switch is stable
  {
    scanPattern();
  }
 while(digitalRead(TILT) == true);
    {
    tone(spk,494,80);
    scanPattern2();
    
    Serial.println("movement!");
    }
 }
 
void scanPattern()
{
 
 matrix.fillScreen(0);
 matrix.show();
 
  for(uint16_t i = 0; i <= 8; i++)
 {
   
//   matrix.setPixelColor(i,0,255,0);
////   delay(10);
//   matrix.show();
//   //delay(10);
   for(uint16_t j = 0; j <= 8; j++)
   {
   matrix.drawPixel(xcord[i], xcord[j], (matrix.Color(0,255,0)));
   matrix.show();
   matrix.drawPixel(xcord[i], xcord[j], (matrix.Color(0,0,0)));
   matrix.show();
   }
 }
matrix.fillScreen(0);
matrix.show();
}

void scanPattern2()
{
 
 matrix.fillScreen(0);
 matrix.show();
 
  for(uint16_t i = 0; i <= 8; i++)
 {
   
   for(uint16_t j = 0; j <= 8; j++)
   {
   matrix.drawPixel(xcord[i], xcord[j], (matrix.Color(240,141,67)));
   matrix.show();
   matrix.drawPixel(xcord[i], xcord[j], (matrix.Color(240,141,67)));
   matrix.show();
   delay(5);
   }
 }
matrix.fillScreen(0);
matrix.show();
}

