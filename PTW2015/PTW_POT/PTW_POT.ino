/*
PTW2015 code for potentiometer
*/

#include <Adafruit_GFX.h> //GFX library
#include <Adafruit_NeoMatrix.h> //neoMatrix library
#include <Adafruit_NeoPixel.h> //neoPixel library

#ifndef PSTR
 #define PSTR // Make Arduino Due happy
#endif

#define PIN 6 //pin 6 is Matrix
#define spk 11 //speaker pin
#define POT A2 //pin for POT

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
const int16_t stairs[36] = {56,57,49,58,50,42,59,51,43,35,60,52,44,36,28,61,53,45,37,29,21,62,54,46,38,30,22,14,63,55,47,39,31,23,15,7};
int tones[8] = {330, 369, 415, 440, 494, 554, 622, 659}; //notes of E major
//                E   F#   G#   A   B     C#   D#   E
int POTread = 0;

void setup() 
{
  matrix.begin(); //start matrix
  matrix.setBrightness(40); //set brightness
}

void loop()
{ 
  POTcase();
}

/*this function creates stairs when the potentiometer is activated
*/

void POTcase()
{
 
  POTread = analogRead(POT);
  int col = map(POTread, 0, 1023, 0, 8); //map analog voltages from POT to match columns
  
 
 
     if(col == 1) //start at first column and lights go up the pattern
     {
       matrix.fillScreen(0);//clear screen
       matrix.show();
   
       tone(spk,tones[0],100); //play E
       matrix.setPixelColor(stairs[0],171,242,29);
       matrix.show();
     }
     else if(col == 2)
     {
       matrix.fillScreen(0);//clear screen
       matrix.show();
   
       tone(spk,tones[1],100); //play F#
        for(uint16_t i = 0; i <= 2; i++)
        {
          matrix.setPixelColor(stairs[i],171,242,29);
          matrix.show();
        }
     }
     else if(col == 3)
     {
       matrix.fillScreen(0);//clear screen
       matrix.show();
   
       tone(spk,tones[2],100); //play G#
        for(uint16_t i = 0; i <= 5; i++)
        {
          matrix.setPixelColor(stairs[i],171,242,29);
          matrix.show();
        }
     }
   else if(col == 4)
     {
       matrix.fillScreen(0);//clear screen
       matrix.show();
   
       tone(spk,tones[3],100); //play A
        for(uint16_t i = 0; i <= 9; i++)
        {
          matrix.setPixelColor(stairs[i],171,242,29);
          matrix.show();
        }
     }
   else if(col == 5)
     {
       matrix.fillScreen(0);//clear screen
       matrix.show();
   
       tone(spk,tones[4],100); //play B
        for(uint16_t i = 0; i <= 14; i++)
        {
          matrix.setPixelColor(stairs[i],171,242,29);
          matrix.show();
        }
     }
     else if(col == 6)
     {
       matrix.fillScreen(0);//clear screen
       matrix.show();
   
       tone(spk,tones[5],100); //play A
        for(uint16_t i = 0; i <= 20; i++)
        {
          matrix.setPixelColor(stairs[i],171,242,29);
          matrix.show();
        }
     }
     else if(col == 7)
     {
       matrix.fillScreen(0);//clear screen
       matrix.show();
   
       tone(spk,tones[6],100); //play A
        for(uint16_t i = 0; i <= 27; i++)
        {
          matrix.setPixelColor(stairs[i],171,242,29);
          matrix.show();
        }
     }
     else if(col == 8)
     {
       matrix.fillScreen(0);//clear screen
       matrix.show();
   
       tone(spk,tones[7],100); //play A
        for(uint16_t i = 0; i <= 35; i++)
        {
          matrix.setPixelColor(stairs[i],171,242,29);
          matrix.show();
        }
     }
     else
     {
       matrix.fillScreen(0);
       matrix.show();
     }
}
