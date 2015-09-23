
/*
Philly Tech Week 2015, I/O demoPanel source. Created at 
NextFab, 2025 Washington Ave Philadelphia, PA 19146 by Jonathan Eskow, Kyle Raskin
and Matt Garfield for demo purposes only. 
*/

#include <Wire.h>
#include <Adafruit_TCS34725.h>
#include <Adafruit_NeoMatrix.h>
#include <Adafruit_NeoPixel.h>
#include <Adafruit_GFX.h>

#ifndef PSTR
 #define PSTR // Make Arduino Due happy
#endif

#define hall A0; //pin A0 is hall effect
#define FSR A1 //pin for FSR
#define POT A2 //pin for POT
#define PIN 6 //pin 6 is Matrix
#define spk 11 //speaker pin


const int BB = 5; //pin 5 is break beam sensor
const int TILT = 4; //pin 4 is tilt sensor


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

 //the following arrays are numbers of pixels on the matrix
const int16_t xcord[8] = {0,1,2,3,4,5,6,7};
const int16_t ycord[8] = {0,1,2,3,4,5,6,7};

//folowing arrays dictate pixels to be lit for Hall effect
//center squa
const int16_t sq1[4] = {27,28,36,35};
//second square from center
const int16_t sq2[12] = {18,19,20,21,29,37,45,44,43,42,34,26};
//third square from center
const int16_t sq3[20] = {9,10,11,12,13,14,22,30,38,46,54,53,52,51,50,49,41,33,25,17};
//fourth square from center
const int16_t sq4[28] = {0,1,2,3,4,5,6,7,15,23,31,39,47,55,63,62,61,60,59,58,57,56,48,40,32,24,16,8};

//the following arrays are for coordinates of pixels on the matrix for the POT
const int16_t stairs[36] = {56,57,49,58,50,42,59,51,43,35,60,52,44,36,28,61,53,45,37,29,21,62,54,46,38,30,22,14,63,55,47,39,31,23,15,7};

//this array is colors for each spiral leg (BBeam) and are based off of the masks of the Ninja Turtles
const uint16_t colors[] = {
  matrix.Color(0, 167, 225),matrix.Color(148, 52, 140),matrix.Color(244, 36, 52),matrix.Color(255,158,21)};

int sensorState = 0, lastState = 0;

 int tonesC[8] = {262, 294, 330, 349, 392, 440, 494, 523}; //notes of C major
//                C   D    E    F    G    A    B    C

int tonesE[8] = {330, 369, 415, 440, 494, 554, 622, 659}; //notes of E major
//                E   F#   G#   A   B     C#   D#   E

int fsrRead = 0;

float sensorValue = 0.0; //sensor value initial starts at 0

//Buttons and LEDs
int r0 = 0;      //value of select pin at the 4051 (s0)
int r1 = 0;      //value of select pin at the 4051 (s1)
int r2 = 0;      //value of select pin at the 4051 (s2)
int buttonValue = 0;
int button = 0;
volatile int state = LOW;



int POTread = 0;
int x = matrix.width();
int pass = 0;

void setup() 
{
  matrix.begin(); //start matrix
  matrix.setBrightness(40);//set matrix brightness
  matrix.setTextWrap(false);
  matrix.setTextColor(matrix.Color(0, 167, 225));
  Serial.begin(9600);
  pinMode(BB,INPUT); //claim breakbeam as input
  pinMode(TILT,INPUT); //claim tilt as input
  digitalWrite(BB, HIGH); //use on board pull up resistor
  digitalWrite(TILT, HIGH); //use on board pull down resistor 
  //Buttons and LEDs
  pinMode(8, OUTPUT);    // s0
  pinMode(9, OUTPUT);    // s1
  pinMode(10, OUTPUT);    // s2
  pinMode(A3, INPUT);
  pinMode(2, INPUT);  
  attachInterrupt(0, int_serv, HIGH);
  
  if (tcs.begin()) //tests to see if sensor is active
  {
    Serial.println("Found sensor");
  } 
  else
  {
    Serial.println("No TCS34725 found ... check your connections");
    while (1); // halt!
  }

int btnNum; //start at this for statemachine

}

void loop() 
{
  
  IDbutton();
  if (button != 0) 
  {
  switch(button)
    {
       
      case 1:
          while(button = 1)
          {
            Serial.println("button 0");
            writeLED();
            BBeam();
            break;
          }
          break;
      case 2:
          while(button = 2)
          {
            Serial.println("button 1");
            writeLED();
            FSRcase();
             break;
          }
          break;
      case 3:
          while(button = 3)
          {
            Serial.println("button 2");
            writeLED();
            hallEffect();
             break;
          }
          break;
      case 4:
          while(button = 4)
          {
            Serial.println("button 3");
            writeLED();
            POTcase();
             break;
          } 
          break;  
      case 5:
          while(button = 5)
          {
            Serial.println("button 4");
            writeLED();
            rgbPTW();
             break;
          }   
          break;
      case 6:
          while(button = 6)
          {
            Serial.println("button 5");
            writeLED();
            tilt();
            break;
          }
      break;
     default:{}
         break;    
    }
  }
}

void int_serv()
{
  if (analogRead(A3) > 500) {
    buttonValue  = analogRead(A3);
  }
}

/*
What follows after the loop is all of the functions used to dictate the behavior of the inputs and
outputs
*/
void IDbutton()
{
  if (buttonValue > 1000 && buttonValue < 1024 ) {
    button = 1;
  }
  else if (buttonValue > 900 && buttonValue < 1000 ) {
    button = 2;
  }
  else if (buttonValue > 800 && buttonValue < 900 ) {
    button = 3;
  }
  else if (buttonValue > 715 && buttonValue < 800 ) {
    button = 4;
  }
  else if (buttonValue > 680 && buttonValue < 715 ) {
    button = 5;
  }
  else if (buttonValue > 600 && buttonValue < 680 ) {
    button = 6;
  }
  else {
    button = 0;
  }
}

void writeLED()
{
  int ledbut = button - 1;
    // select the bit
    r0 = bitRead(ledbut,0);    // use this with arduino 0013 (and newer versions)     
    r1 = bitRead(ledbut,1);    // use this with arduino 0013 (and newer versions)     
    r2 = bitRead(ledbut,2);    // use this with arduino 0013 (and newer versions)    
    digitalWrite(8, r0);
    digitalWrite(9, r1);
    digitalWrite(10, r2);
}

/*
this function controls the BreakBeam sensor. When the sensor is activated, a spiral of lights corresponding
with the colors of each ninja turtle mask is activated and a tone plays
*/
void BBeam()
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

/*
this function controls the pattern for the break beam sensor
*/
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

/*
this function controls the FSR, as the FSR is pressed, a line of pixels lights up and a tone plays. Every level
on the matrix corresponds with a note in the key of C
*/
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
    tone(spk, tonesC[0], 100);
     for(uint16_t i = 0; i <= 7; i++)
    {
     matrix.drawPixel(xcord[i], ycord[7], matrix.Color(242,147,39));
    matrix.show();
    }
   }
    else if (matrixRow == 2)
    {
      tone(spk, tonesC[1], 100);
      for(uint16_t i = 0; i <= 7; i++)
    {
    matrix.drawPixel(xcord[i], ycord[6], matrix.Color(242,147,39));
    matrix.show();
    }
    }
    else if (matrixRow == 3)
    {
    tone(spk, tonesC[2], 100);
      for(uint16_t i = 0; i <= 7; i++)
    {
    matrix.drawPixel(xcord[i], ycord[5], matrix.Color(242,147,39));
    matrix.show();
    }
    }
    else if (matrixRow == 4)
    {
      tone(spk, tonesC[3], 100);
      for(uint16_t i = 0; i <= 7; i++)
    {
    matrix.drawPixel(xcord[i], ycord[4], matrix.Color(242,147,39));
    matrix.show();
    }
   }
   else if (matrixRow == 5)
    {
      tone(spk, tonesC[4], 100);
      for(uint16_t i = 0; i <= 7; i++)
    {
    matrix.drawPixel(xcord[i], ycord[3], matrix.Color(242,147,39));
    matrix.show();
    }
    }
    else if (matrixRow == 6)
    {
      tone(spk, tonesC[5], 100);
      for(uint16_t i = 0; i <= 7; i++)
    {
    matrix.drawPixel(xcord[i], ycord[2], matrix.Color(242,147,39));
    matrix.show();
    }
    }
 else if (matrixRow == 7)
    {
     tone(spk, tonesC[6], 100);
      for(uint16_t i = 0; i <= 7; i++)
    {
    matrix.drawPixel(xcord[i], ycord[1], matrix.Color(242,147,39));
    matrix.show();
    }
    }
     else if (matrixRow == 8)
    {
      tone(spk, tonesC[7], 100);
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

/*
this function controls the Hall effect sensor, when activated, concentric squares of light are seen
*/
void hallEffect()
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

/*this function controls the pattern for the hall effect sensor*/
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

/*
this function dictates the behavior of the potentiometer, as the knob is turned, "stairs" light up on the matrix that correspond with the level on the sensor
*/
void POTcase()
{
 
  POTread = analogRead(POT);
  int col = map(POTread, 0, 1023, 0, 8); //map analog voltages from POT to match columns
  
 
 
     if(col == 1) //start at first column and lights go up the pattern
     {
       matrix.fillScreen(0);//clear screen
       matrix.show();
   
       tone(spk,tonesE[0],100); //play E
       matrix.setPixelColor(stairs[0],171,242,29);
       matrix.show();
     }
     else if(col == 2)
     {
       matrix.fillScreen(0);//clear screen
       matrix.show();
   
       tone(spk,tonesE[1],100); //play F#
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
   
       tone(spk,tonesE[2],100); //play G#
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
   
       tone(spk,tonesE[3],100); //play A
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
   
       tone(spk,tonesE[4],100); //play B
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
   
       tone(spk,tonesE[5],100); //play A
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
   
       tone(spk,tonesE[6],100); //play A
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
   
       tone(spk,tonesE[7],100); //play A
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

/*
this function dictates behavior of the RGB sensor, the RGB sensor takes a color reading and puts that color onto the matrix
*/

void rgbPTW()
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

/*this function dictates behavior for the tilt sensor. when the tilt sensor is stable a row of lights is lit, when activated the screen fills with orange*/

void tilt()
{
  while(digitalRead(TILT)== false)//while switch is stable
  {
    scanPattern();
    break;
  }
 while(digitalRead(TILT) == true)
    {
    tone(spk,494,80);
    scanPattern2();
    Serial.println("movement!");
    break;
    }
 }
 
 //this function gives the stable patter for tilt sensor
 void scanPattern()
{
 
 matrix.fillScreen(0);
 matrix.show();
 
  for(uint16_t i = 0; i <= 8; i++)
 {
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

//this function gives pattern for when tilt sensor is activated.
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

/*default function, scrolls "NextFab" in Leonardo Blue*/

void defaultCrawl()
{
  matrix.fillScreen(0);
  matrix.setCursor(x, 0);
  matrix.print(F("NextFab"));
  delay(100);
}

