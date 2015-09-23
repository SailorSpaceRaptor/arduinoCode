/*
PTW2015 code for Force Sensitive Resistor
*/

#include <Adafruit_GFX.h> //GFX library
#include <Adafruit_NeoMatrix.h> //neoMatrix library
#include <Adafruit_NeoPixel.h> //neoPixel library

#ifndef PSTR
 #define PSTR // Make Arduino Due happy
#endif

#define PIN 6 //pin 6 is Matrix
#define spk 11 //speaker pin
#define FSR A1 //pin for FSR

//NeoPixel Matrix is 8 by 8 and runs from pin 6
//pixel (1,1) is top and right
//pixels are arranged in columns
//pixels are progressive, not zigzag
//pixels are wired for GRB bitstream and run at 800KHz
Adafruit_NeoMatrix matrix = Adafruit_NeoMatrix(8, 8, PIN,
  NEO_MATRIX_TOP     + NEO_MATRIX_RIGHT +
  NEO_MATRIX_COLUMNS + NEO_MATRIX_PROGRESSIVE,
  NEO_GRB            + NEO_KHZ800);
 
 //the following arrays are for coordinates of pixels on the matrix
const int16_t xcord[8] = {0,1,2,3,4,5,6,7};
const int16_t ycord[8] = {0,1,2,3,4,5,6,7};
int tones[8] = {262, 294, 330, 349, 392, 440, 494, 523}; //notes of C major
//                C   D    E    F    G    A    B    C

int fsrRead = 0;

void setup() 
{
 matrix.begin(); //start matrix
 matrix.setBrightness(40); //set matrix brightness
Serial.begin(9600);
}

void loop() 
{
  FSRcase();
}

//this function takes analog reading from FSR and translates
//it to rows on the neoPixel matrix.
void FSRcase()
{
fsrRead = analogRead(FSR); //reading for FSR
int matrixRow = map(fsrRead, 0, 1023, 0, 8); //map FSR to match rows of matrix
Serial.println(fsrRead);
delay(100);

matrix.fillScreen(0); //clear screen
matrix.show();

  if(matrixRow == 1) //start at first row 
   {
    tone(spk, tones[0], 100);
     for(uint16_t i = 0; i <= 7; i++)
    {
     matrix.drawPixel(xcord[i], ycord[7], matrix.Color(242,147,39));
    matrix.show();
    }
   }
    else if (matrixRow == 2)
    {
      tone(spk, tones[1], 100);
      for(uint16_t i = 0; i <= 7; i++)
    {
    matrix.drawPixel(xcord[i], ycord[6], matrix.Color(242,147,39));
    matrix.show();
    }
    }
    else if (matrixRow == 3)
    {
    tone(spk, tones[2], 100);
      for(uint16_t i = 0; i <= 7; i++)
    {
    matrix.drawPixel(xcord[i], ycord[5], matrix.Color(242,147,39));
    matrix.show();
    }
    }
    else if (matrixRow == 4)
    {
      tone(spk, tones[3], 100);
      for(uint16_t i = 0; i <= 7; i++)
    {
    matrix.drawPixel(xcord[i], ycord[4], matrix.Color(242,147,39));
    matrix.show();
    }
   }
   else if (matrixRow == 5)
    {
      tone(spk, tones[4], 100);
      for(uint16_t i = 0; i <= 7; i++)
    {
    matrix.drawPixel(xcord[i], ycord[3], matrix.Color(242,147,39));
    matrix.show();
    }
    }
    else if (matrixRow == 6)
    {
      tone(spk, tones[5], 100);
      for(uint16_t i = 0; i <= 7; i++)
    {
    matrix.drawPixel(xcord[i], ycord[2], matrix.Color(242,147,39));
    matrix.show();
    }
    }
 else if (matrixRow == 7)
    {
     tone(spk, tones[6], 100);
      for(uint16_t i = 0; i <= 7; i++)
    {
    matrix.drawPixel(xcord[i], ycord[1], matrix.Color(242,147,39));
    matrix.show();
    }
    }
     else if (matrixRow == 8)
    {
      tone(spk, tones[7], 100);
      for(uint16_t i = 0; i <= 7; i++)
    {
    matrix.drawPixel(xcord[i], ycord[0], matrix.Color(242,147,39));
    matrix.show();
    }
    }
    else
    {
    matrix.fillScreen(0);
    matrix.show();
    }
}
