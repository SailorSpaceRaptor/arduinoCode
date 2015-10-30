#include <Adafruit_NeoPixel.h>

/*
This code created by Jonathan Eskow is entirely open source and available to the public. It creates classes to dictate behavior of neopixel rings in a
foam pumpkin to create a halloween or all year installation.
*/



//pattern types
enum pattern {NONE, FASTSCAN, DUBCOL, FLAME, DEMON};

//DIRECTION
enum direction {FORWARD, REVERSE};

/* The following class contains every pattern and every update command to dictate behavior of neoPixels
* the tutorial https://learn.adafruit.com/multi-tasking-the-arduino-part-3/ aided in the design of this
*/

class NeoPatterns : public Adafruit_NeoPixel
{
    public:
    
    //Member Variables:
    pattern ActivePattern; //pattern that is currently running
    direction Direction; //direction to run pattern
    
    unsigned long Interval; //ms between updates
    unsigned long lastUpdate; //last update of position
    
    uint32_t Color1, Color2, Color3; //colors currently in use
    uint16_t TotalSteps; //total number of steps per pattern
    uint16_t Index; //current step within patter
    
    void (*OnComplete)(); //Callback on completion of pattern
    
    //constructor - calls base-class constructor to initialize strip
    NeoPatterns(uint16_t pixels, uint8_t pin, uint8_t type, void(*callback)())
    :Adafruit_NeoPixel(pixels, pin, type)
    {
        OnComplete = callback;    
    }
    
    //update pattern
    void Update()
    {
        if((millis() - lastUpdate)>Interval) //time to update
        {
            lastUpdate = millis();
            switch(ActivePattern)
            {
                case FASTSCAN: //case for fast scan function where a light goes around ring
                 fastscanUpdate();
                 break;
                 
                case FLAME: //case for flame flicker pattern
                flameUpdate();
                break;
                
                case DEMON: //case for "breath" function where lights pulse
                 demonUpdate();
                 break;
                
                case DUBCOL: //case for two colors to work as a scan
                 dubcolUpdate();
                 break;

                default:
                 break;
            }
        }
    }
    
    //Increment the index and reset at the end
    void Increment()
    {
        if (Direction == FORWARD)
        {
            Index++;
            if(Index >= TotalSteps)
            {
                Index = 0;
                if (OnComplete != NULL)
                {
                    OnComplete(); //call the completion callback
                }
            }
        }
        else //direction == REVERSE
        {
            --Index;
            if (Index <= 0)
            {
                Index = TotalSteps-1;
                if (OnComplete != NULL)
                {
                    OnComplete(); //call the completion call back
                }
            }
        }
    }

    
      
        // Initialize for a FASTSCAN
    void fastScan(uint32_t color1, uint8_t interval)
    {
        ActivePattern = FASTSCAN;
        Interval = interval;
        TotalSteps = (numPixels()) ; //total steps is just the amount of pixels in the ring as we don't need a return trip
        Color1 = color1; //whichever one is color 1
        Index = 0; 
    }
        // Update the Scanner Pattern
    void fastscanUpdate()
    { 
        for (int i = 0; i < numPixels(); i++)
        {
            if (i == Index) // first half of the scan
            {
                Serial.print(i);
                setPixelColor(i, Color1);
            }
            else  // fade to black
            {
                setPixelColor(i, DimColor(getPixelColor(i)));
            }
        }
        show();
        Increment();
    }
    
  
            // Initialize for demon
          void demon(uint32_t color1, uint32_t color2, uint16_t steps, uint8_t interval, direction dir = FORWARD)
    {
        ActivePattern = DEMON;
        Interval = interval;
        TotalSteps = steps;
        Color1 = color1;
        Color2 = color2;
        Index = 0;
        Direction = dir;
    }
    
    void demonUpdate()
    {
        uint8_t red = ((Red(Color1) * (TotalSteps - Index)) + (Red(Color2) * Index)) / TotalSteps;
        uint8_t green = ((Green(Color1) * (TotalSteps - Index)) + (Green(Color2) * Index)) / TotalSteps;
        uint8_t blue = ((Blue(Color1) * (TotalSteps - Index)) + (Blue(Color2) * Index)) / TotalSteps;
        ColorSet(Color(red, green, blue));
        show();
        Increment();
        
    }//end breatheUpdate

        void flame(uint32_t color1, uint32_t color2, uint8_t interval, direction dir = FORWARD) 
    {
        ActivePattern = FLAME;
        Interval = interval;
        TotalSteps = numPixels();
        Color1 = color1;
        Color2 = color2;
        Index = 0;
        Direction = dir;
    }

       void flameUpdate()
    {
        long currentMillis = millis();
        long lastMillis = 0;
        long lightning = 500; //1/2 second

       for(int i=0; i < numPixels(); i++)
          {
            if ((i+ Index) % 3 == 0) //every third pixel is lit with color 1, all others are lit with color 2
            {
                setPixelColor(i, Color1);
            }
            else
            {
                setPixelColor(i, Color2);
            }
         }
        show();
        Increment();
    }  
    void dubCol(uint32_t color1, uint32_t color2, uint8_t interval)
    {
        ActivePattern = DUBCOL;
        Interval = interval;
        TotalSteps = (numPixels() - 1) ; 
        Color1 = color1; //whichever one is color 1
        Color2 = color2;
        Index = 0; 
    }
    
    void dubcolUpdate()
    {
            for (int i = numPixels()/2; i < numPixels(); i++)
              {
                if (i == Index) // first half of the scan
                {
                    Serial.print(i);
                    setPixelColor(i, Color1);
                }
            
                else if (i == TotalSteps - Index) //return trip
                {
                    Serial.print(i);
                    setPixelColor(i, Color1);
                }
                else  // fade to black
                {
                    setPixelColor(i, DimColor(getPixelColor(i)));
                }
              }
         
             for (int i = 0; i < numPixels()/2; i++)
              {
                if (i == Index) // first half of the scan
                {
                    Serial.print(i);
                    setPixelColor(i, Color2);
                }
            
                else if (i == TotalSteps - Index) //return trip
                {
                    Serial.print(i);
                    setPixelColor(i, Color2);
                }
                else  // fade to black
                {
                    setPixelColor(i, DimColor(getPixelColor(i)));
                }
              }
              
        show();
        Increment();
        
        }//end dubcolUpdate
        
        //Returns Red component of 32-bit color
        uint8_t Red(uint32_t color)
        {
            return (color >> 16) & 0xFF;
        }//end red
        
        //returns Green component of 32-bit color
        uint8_t Green(uint32_t color)
        {
            return (color >> 8) & 0xFF;
        }//end green
        
        //return Blue Component of 32-bit color
        uint8_t Blue(uint32_t color)
        {
            return color & 0xFF;
        }//end blue
        
        //dim color uses red, blue, and green to pull apart a color and reconstruct a dimmed version, it shifts each 1 bit to the right
        uint32_t DimColor(uint32_t color)
        {
            uint32_t dimColor = Color(Red(color) >> 1, Green(color) >> 1, Blue(color) >> 1);
            return dimColor;
        }//end dimcolor
        
        //Input value 0 to 255 to get color value
        //the colors are a transition r - g - b back to r
        uint32_t Wheel(byte WheelPos)
            {
                WheelPos = 255 - WheelPos;
                if (WheelPos < 85)
                {
                    return Color(255 - WheelPos * 3, 0, WheelPos *3);
                }
                else if (WheelPos < 170)
                {
                    WheelPos -= 85;
                    return Color(0, WheelPos * 3, 255 - WheelPos * 3);
                }
                else
                {
                    WheelPos -= 170;
                    return Color(WheelPos * 3, 255 - WheelPos * 3, 0);
                }
            } //end wheel
            
            //reverse function reverses pattern execution
            void Reverse()
            {
                if(Direction == FORWARD)
                {
                    Direction = REVERSE;
                    Index = TotalSteps-1;
                }
                else
                {
                    Direction = FORWARD;
                    Index = 0;
                }
            }//end reverse
    
            // Set all pixels to a color (synchronously)
        void ColorSet(uint32_t color)
        {
            for (int i = 0; i < numPixels(); i++)
            {
                setPixelColor(i, color);
            }
            show();
        }
    };//end class

NeoPatterns eye1(24,3, NEO_GRB + NEO_KHZ800, &eye1Complete);

void setup() 
{
eye1.begin();
eye1.flame(eye1.Color(252,175,8),eye1.Color(255,0,0),random(10,30));
eye1.setBrightness(20);
eye1.show();

}

void loop() 
{
 
 eye1.Update();
 eye1.clear();


}//end loop

void eye1Complete() //this optional method dictates which pattern is currently active
{
 unsigned long lastMillis = 0;
 unsigned long currentMillis = millis();
 unsigned long interval = 10000; 
 unsigned long patInter = 30000;
 
 unsigned int rando = random(0,400);
 unsigned int r = randomizer(rando);
 
if((currentMillis - lastMillis) > interval)
{

 lastMillis = currentMillis;
 eye1.clear();

 
 switch(r)
 {
  case 1:
   eye1.clear();
   while((currentMillis - lastMillis) < patInter)
    { 
      lastMillis = currentMillis;
      eye1.dubCol(eye1.Color(178,102,255),eye1.Color(51,255,51), 50);
      //eye1.show();
      break;
    } 
  eye1.clear();
  break;

  case 2:
   
   while((currentMillis - lastMillis) < patInter)
   { 
     lastMillis = currentMillis;
     eye1.demon(eye1.Color(255,0,0), eye1.Color(0,0,0),20,100);
    // eye1.show();
     break;
   }
  eye1.clear();
  break;
  
  case 3:
   eye1.clear();
   while((currentMillis - lastMillis) < patInter)
   { 
     lastMillis = currentMillis;
     eye1.fastScan(eye1.Color(255,0,0),20);
     //eye1.show();
     break;
   }
  eye1.clear();
  break;
  
  case 4:
    eye1.clear();
    while((currentMillis - lastMillis) < patInter)
     {
      lastMillis = currentMillis;
      eye1.flame(eye1.Color(252,175,8),eye1.Color(255,0,0),random(10,30));
      //eye1.show();
      break;
     }
  eye1.clear();
  break;
  
 }//end case
}
}

 int randomizer(int r)
{
  if(r > 0 && r <= 100)
  {
    int r = 1;
  }
  else if(r > 101 && r <= 200)
  {
    int r = 2;
  }
  else if (r > 201 && r <= 300)
   {
    int r = 3;
   }
   else
   {
    int r = 4;
   }
   
   return r;
} // end randomizer



