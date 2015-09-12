#include <Adafruit_NeoPixel.h>

/*
* Poseidon Code created by Jonathan Eskow and Kyle Raskin for use in the Poseidon Installation at NextFab for B^2
* This one's for you, B!
*/



// This #include statement was automatically added by the Spark IDE.
//#include "neopixel/neopixel.h"

//pattern types
enum pattern {NONE, FASTSCAN, BREATHE, PRIDE, DUBCOL, FURY};

//DIRECTION
enum direction {FORWARD, REVERSE};

/* The following class contains every pattern and every update command to dictate behavior of neoPixels
* and borrows heavily from https://learn.adafruit.com/multi-tasking-the-arduino-part-3/
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
                
                case BREATHE: //case for "breath" function where lights pulse
                 breatheUpdate();
                 break;
                
                case PRIDE: //case for rainbow
                 prideUpdate();
                 break;
                
                case DUBCOL: //case for two colors to work as a scan
                 dubcolUpdate();
                 break;
                 
                case FURY: //case for when it rains, blue light will spin with occasional lightning flash effect 
                 furyUpdate();
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


    void pride(uint8_t interval, direction dir = FORWARD) //activates rainbow function
    {
        ActivePattern = PRIDE;
        Interval = interval;
        TotalSteps = 255; //total steps on color wheel 4
        Index = 0;
        Direction = dir;
    }

    void prideUpdate() //updates rainbow function
    {
        for(int i=0; i < numPixels(); i++) //starting at i, pixels go through every color
        {
            setPixelColor(i, Wheel(((i * 256 / numPixels() +Index) & 255)));
        }
     show(); //update
     Increment();//increment
    }
    
    /*
     *activates fury, fury has two colors do a theatre chase and after a certain amount of time color3 will "lightning flash"
     */
    
    void fury(uint32_t color1, uint32_t color2, uint32_t color3, uint8_t interval, direction dir = FORWARD) 
    {
        ActivePattern = FURY;
        Interval = interval;
        TotalSteps = numPixels();
        Color1 = color1;
        Color2 = color2;
        Color3 = color3;
        Index = 0;
        Direction = dir;
    }
    
    //updates Fury
    void furyUpdate()
    {
        long currentMillis = millis();
        long lastMillis = 0;
        long lightning = 500; //1/2 second
        long lightningInterval = 30000; //30 seconds
        long intervalFlash =  60000;//1 minutes

        
        if ((currentMillis - lastMillis >= intervalFlash) //every 1 minutes
        {
            lastMillis = currentMillis; //update time
           
                if(currentMillis - lastMillis <= lightningInterval)
                {
                   
                   if(currentMillis - lastMillis <= lightning) //while time is less than 1/2 second
                    {
                      //lastMillis = currentMillis;
                        
                        for(int i = 0; i < numPixels(); i++)
                        {
                            setPixelColor(i, Color3); //set all pixels to color3
                            setBrightness(255);//set brightness to top
                            show();//show
                        }    
                          clear();
                       setBrightness(64); //set brightness back to 64
                       show();
                       Increment(); 
                      
                  }//end if
                   }
               // }//end while
        
        } //end if
        else
         {
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
    } //end fury
      
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
    
  
            // Initialize for breathe
    void breathe(uint32_t color1)
    {
        Interval = 500;
        ActivePattern = BREATHE;
        TotalSteps = (numPixels());
        color1 = Color1;
        Index = 0;
        //Direction = dir;
    }
    
    void breatheUpdate()
    {
       long currentMillis = millis();
       long lastMillis = 0;
     
     lastMillis = currentMillis;
     
    
        for (int k = 0; k < numPixels(); k++)
        {
          setPixelColor(k, Color1); //set all pixels to color
          show();
        }
        
        lastMillis = currentMillis; //update clock
            
        if (lastMillis - currentMillis == Interval)
        {    
            for (int j = 1; j < 256; j++) //brightness starts at 0 goes to max
            {
                setBrightness(j);
                show();
            }
                
        }
        else if (lastMillis - currentMillis == Interval * 2) //equal to breathe interval times 2 to compensate for previous if
        {
            for (int k = 256; k > 0; k--) //brightness starts at 256 goes to min
            {
                setBrightness(k);
                show();
            }
        }
        
        
        setBrightness(64); //return brightness back to normal
        show();
        Increment();
    }//end breatheUpdate
    
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
    };//end class


NeoPatterns iris(24,5, NEO_GRB + NEO_KHZ800, &irisComplete);//define rings we're using
NeoPatterns pupil(12,6, NEO_GRB + NEO_KHZ800, &pupilComplete);

void setup() 
{
iris.begin();
pupil.begin();

iris.fury(iris.Color(0,0,255),iris.Color(60,144,144),iris.Color(255,255,255),50);
pupil.fastScan(pupil.Color(60,144,32),random(0,4));
}

void loop() 
{
// sequence = random(0,4); //random # gen
// Serial.println(sequence);
iris.Update();
pupil.Update();

}

void irisComplete()
{
  iris.fury(iris.Color(0,0,255),iris.Color(60,144,144),iris.Color(255,255,255),100);//
}

void pupilComplete()
{
  pupil.fastScan(pupil.Color(60,144,32),10);
}



