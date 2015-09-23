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
const int BB = 5; //pin 5 is break beam sensor


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

//this array is colors for each spiral leg and are based off of the masks of the Ninja Turtles
const uint16_t colors[] = {
  matrix.Color(0, 167, 225),matrix.Color(148, 52, 140),matrix.Color(244, 36, 52),matrix.Color(255,158,21)};

int sensorState = 0, lastState = 0;
  
void setup() 
{
  matrix.begin(); //start matrix
  matrix.setBrightness(40);//set matrix brightness
  Serial.begin(9600);
  pinMode(BB,INPUT); //claim breakbeam as input
  digitalWrite(BB, HIGH); //use on board pull up resistor 
}

void loop() 
{
  //read state of beam value
 matrix.fillScreen(0);
 matrix.show();
 sensorState = digitalRead(BB);
 
    if(sensorState == LOW)
   {
     matrix.fillScreen(0);
     tone(spk,294,500);
     spiral();
//delay(100);
   }
   else
   {
   matrix.fillScreen(0);
   }

if(sensorState && !lastState)
  {  
    Serial.println("Unbroken");
  }
  
if(!sensorState && lastState)
  {
    Serial.println("broken");
  }
lastState = sensorState;

}

void spiral()
{
  matrix.fillScreen(0); //clear panel
  matrix.show();
  
  for(uint16_t i = 0; i <= 7;i++) //first row of pixels y is constant, x is changing
  {
  matrix.drawPixel(xcord[i],0,colors[0]);
 delay(10);
  matrix.show();
  }
  for(uint16_t i = 0; i <=7; i++) //x is constant, y is changing
  {
    matrix.drawPixel(7, ycord[i], colors[0]);
    delay(10);
    matrix.show();
  }
   for(uint16_t i = 6; i >= 1; i--)//last row of pixels y is constant, x is changing  
   {
     matrix.drawPixel(xcord[i], 7, colors[0]);
    delay(10);
     matrix.show();
   }
   for(uint16_t i = 7; i >= 1; i--)//x is constant, y is changing
   {
     matrix.drawPixel(0, ycord[i], colors[0]);
     delay(10);
     matrix.show();
    }
  for(uint16_t i = 1; i <=6; i++) //second row, second spiral ,y == constant, x == changing
   {
     matrix.drawPixel(xcord[i], 1, colors[1]);
    delay(10);
     matrix.show();
    }
for(uint16_t i = 1; i <=6; i++) //second spiral ,x == constant, y == changing
   {
     matrix.drawPixel(6, ycord[i], colors[1]);
     delay(10);
     matrix.show();
    }
    for(uint16_t i = 6; i >= 1; i--) //second spiral ,y == constant, x == changing
   {
     matrix.drawPixel(xcord[i], 6, colors[1]);
    delay(10);
     matrix.show();
    }
    for(uint16_t i = 6; i >= 2; i--) // second spiral ,x == constant, y == changing
   {
     matrix.drawPixel(1, ycord[i], colors[1]);
    delay(10);
     matrix.show();
    }

for(uint16_t i = 2; i <= 5; i++) // third spiral, third row ,y == constant, x == changing
   {
     matrix.drawPixel(xcord[i], ycord[2], colors[2]);
    delay(10);
     matrix.show();
    }
    for(uint16_t i = 3; i <= 5; i++) // third spiral, x == constant, y == changing
   {
     matrix.drawPixel(xcord[5], ycord[i], colors[2]);
    delay(10);
     matrix.show();
    }
    for(uint16_t i = 2; i <= 5; i++) // third spiral,y == constant, x == changing
   {
     matrix.drawPixel(xcord[i], ycord[5], colors[2]);
    delay(10);
     matrix.show();
    }
    for(uint16_t i = 4; i >= 3; i--) // third spiral, x == constant, y == changing
   {
     matrix.drawPixel(xcord[2], ycord[i], colors[2]);
    delay(10);
     matrix.show();
    }
    for(uint16_t i = 3; i <= 4; i++) // third spiral, third row ,y == constant, x == changing
   {
     matrix.drawPixel(xcord[i], ycord[3], colors[3]);
    delay(10);
     matrix.show();
    }
    for(uint16_t i = 4; i >= 3; i--) // third spiral, third row ,y == constant, x == changing
   {
     matrix.drawPixel(xcord[i], ycord[4], colors[3]);
    delay(10);
     matrix.show();
    }
    
matrix.fillScreen(0); //clear matrix
matrix.show();
}
