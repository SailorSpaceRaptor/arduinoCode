#include <Adafruit_TCS34725.h>

#include <Adafruit_NeoPixel.h>
#include <Adafruit_NeoMatrix.h>
#include <gamma.h>
#include <Adafruit_GFX.h>

#define inT 5 //simulates tilt switch
#define inH A1 //simulates hall effect
#define inF A0 //simulates FSR
#define inP A2 //potentiometer
#define inB 9 //simulates breakbeam
#define Mat 6 //Matrix on pin 6


//NeoPixel Matrix is 8 by 8 and runs from pin 6
//pixel (1,1) is top and right
//pixels are arranged in columns
//pixels are progressive, not zigzag
//pixels are wired for GRB bitstream and run at 800KHz
Adafruit_NeoMatrix matrix = Adafruit_NeoMatrix(8, 8, PIN,
  NEO_MATRIX_TOP     + NEO_MATRIX_RIGHT +
  NEO_MATRIX_COLUMNS + NEO_MATRIX_PROGRESSIVE,
  NEO_GRB            + NEO_KHZ800);

int inFRead = 0;
int x = matrix.width(); //x is entire width of matrix
int pass = 0;
unsigned long previousMillis = 0;
long OnTime = 250; //ms of on time
long OffTime = 750; //ms of off time
const uint16_t textColor[] = {matrix.Color(0, 167, 225)}

void setup() 
{
  matrix.begin(); //start matrix
  matrix.setTextWrap(false); //text will scroll
  matrix.setBrightness(40);
  matrix.setTextColor(textColor[0]); //text color is Leonardo Mask blue
  pinMode(inT, INPUT);
  pinMode(inB, INPUT);
}

void loop() 
{
  // put your main code here, to run repeatedly:
}
 
void defaultpattern()
{
 matrix.clear(); //clear buffer
 {
  matrix.fillScreen(0);
  matrix.setCursor(x, 0);
  matrix.print(F("NextFab"));
  if(--x < -36) 
  {
    x = matrix.width();
    matrix.setTextColor(textColor[0]);
  }
  matrix.show();
  delay(100);//when no switches are pressed, 
  //neoPixel Matrix scrolls "NextFab" in Leonardo Blue
}

void tiltPattern(uint32_t c1, uint32_t c2, long onT, long 0ffT)
{
 unsigned long currentMillis = millis();
 
  matrix.clear();//clear neoPixel buffer
 matrix.fillScreen(0);
// matrix.setCursor(x,3);
 if (currentMillis - previousMillis > on)
 {
   
   previousMillis = currentMillis;
   
 for(i=31; i >= 24; i--)//single green light scans across matrix
    {
      matrix.setPixelColor(i, c1);
      strip.show
    } 
 //every time the tilt sensor is activated a orange column scans across matrix
 matrix.show();
}

void forcePattern()
{
  matrix.clear();//clear neopixel buffer
  
  //as V-- 
  //lights fill matrix from the bottom up 
  //show();
}

void hallPattern()
{
  matrix.clear();//clear buffer
  
  //start with single pixel
  //as magnetic field grows stronger the entire matrix is filled
  //show();
}

void bbPattern()
{
  matrix.clear();//clear buffer
  
  while(digitalRead(inb)== true)
  {
  matrix.clear();
  
  }//when beam is broken, theater chase
  //show();
}

  
