#include <Adafruit_NeoPixel.h> //include NeoPixel library

#include <Adafruit_NeoMatrix.h> //include NeoMatrix Library
#include <gamma.h>

#include <Adafruit_GFX.h> //include GFX

#define PIN 6 //define pin 6 as NeoMatrix pin
#define sw1 12 //switch 1 is on pin 12
#define sw2 10 //switch 2 is on pin 10
#define sw3 8 //switch 3 is on pin 8

//NeoPixel Matrix is 8 by 8 and runs from pin 6
//pixel (1,1) is top and right
//pixels are arranged in columns
//pixels are progressive, not zigzag
//pixels are wired for GRB bitstream and run at 800KHz
Adafruit_NeoMatrix matrix = Adafruit_NeoMatrix(8, 8, PIN,
  NEO_MATRIX_TOP     + NEO_MATRIX_RIGHT +
  NEO_MATRIX_COLUMNS + NEO_MATRIX_PROGRESSIVE,
  NEO_GRB            + NEO_KHZ800);

const uint16_t colors0[] = {
 matrix.Color(0, 167, 225),matrix.Color(148, 52, 140),matrix.Color(244, 36, 52),matrix.Color(255,158,21)};
const uint16_t colors1[] = {
   matrix.Color(87,255,23), matrix.Color(148, 30, 65), matrix.Color(30,77,128)};
const uint16_t colors2[] = {
  matrix.Color(69,211,144), matrix.Color(232,0,126)};
const uint16_t colors3[] = {
 matrix.Color(230,110,70), matrix.Color(0,42,124), matrix.Color(34,180,47)};  
int x = matrix.width(); //x is entire width of matrix
int pass = 0; //


void setup() 
{
  matrix.begin();// command to start matrix
  matrix.setTextWrap(false); //command to set textwrap to false
  matrix.setBrightness(40); //brightness is 40
  matrix.setTextColor(colors0[0]);//set text color as colors array
  pinMode(sw1, INPUT);
  pinMode(sw2, INPUT);
  pinMode(sw3, INPUT);
  
}


void loop()
{
  while (digitalRead(sw1) == false)
  {
  matrix.fillScreen(0);
  matrix.setCursor(x,0);
  matrix.print(F("input 1")); //prints ESE RULEZ
 if(--x < -64) //scrolls text
 {
   x = matrix.width();
   if (++pass >= 3) pass = 0;
   matrix.setTextColor(colors1[pass]); //changes text color
 }
  }
  while (digitalRead(sw2) == false)
  {
  matrix.fillScreen(0);
  matrix.setCursor(x,0);
  matrix.print(F("input 2")); //prints ESE RULEZ
 if(--x < -64) //scrolls text
 {
   x = matrix.width();
   if (++pass >= 2) pass = 0;
   matrix.setTextColor(colors2[pass]); //changes text color
 }
  }
  while (digitalRead(sw3) == false)
  {
  matrix.fillScreen(0);
  matrix.setCursor(x,0);
  matrix.print(F("input 3")); //prints ESE RULEZ
 if(--x < -64) //scrolls text
 {
   x = matrix.width();
   if (++pass >= 3) pass = 0;
   matrix.setTextColor(colors3[pass]); //changes text color
 }
  }
 
 matrix.fillScreen(0);
 matrix.setCursor(x,0);
 matrix.print(F("ESE RULEZ!")); //prints ESE RULEZ
 if(--x < -64) //scrolls text
 {
   x = matrix.width();
   if (++pass >= 4) pass = 0;
   matrix.setTextColor(colors0[pass]); //changes text color
 }
 matrix.show(); //turns on matrix
 delay(100); //gives delay

}
