 /*
  * This sketch created by Jonathan Eskow for use at NextFab North Fourth for demo purposes. Code is open source and available for copy and use.
  * The code prints the words "Make This Here" but when an object is sensed within a meter it gives the distance on the lcd readout.
  */

/**********************************************************************
 * Global variables ****
 **********************************************************************/
 
   #include <Wire.h>
    #include <NewPing.h>
    #include <LiquidCrystal_I2C.h>  // Includes the LiquidCrystal_I2C library
     
    #define TRIGGER_PIN  3
    #define ECHO_PIN     11
    #define MAX_DISTANCE 200
    #define BUZZER 4
    #define lcdAddress 0x27         // LCD I2C Address
  
  const int numReadings = 10;

  int readings[numReadings];      // the readings from the signal input
  int readIndex = 0;              // the index of the current reading
  int total = 0;                  // the running total
  int average = 0;                // the average

  
  volatile int state = LOW;
    LiquidCrystal_I2C lcd( lcdAddress ); //import I2C LCD library
    NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE);
 
 /**********************************************************************
 **** Main Method ****
 **********************************************************************/    
 
    void setup() 
    {
        Serial.begin(9600);
 
        Serial.println("Sensor is ready");
       lcd.clear(); 
       lcd.begin(16,2);              // initialize the lcd as a 16 characters by 2 row display
       lcd.setBacklight(HIGH);       // Turn on the LCD's backlight 
       lcd.home();                  // set the cursor to the home position (first row, first column)
 
    }
     
   //the loop takes several readings and inputs them into an array and gives back a moving average
    void loop() 
    {
      int uS = sonar.ping();
 
      // subtract the last reading:
    total = total - readings[readIndex];
    
    // read from the sensor:
    readings[readIndex] = (uS / US_ROUNDTRIP_CM);
    
    // add the reading to the total:
   total = total + readings[readIndex];
   
    // advance to the next position in the array:
   readIndex = readIndex + 1;
  
  
  // if we're at the end of the array...
  if (readIndex >= numReadings) 
  {
    // ...wrap around to the beginning:
    readIndex = 0;
  }
   // calculate the average:
   average = total / numReadings;
   // send it to the computer as ASCII digits
   
    Serial.println(average);

 if(average < 100 && average > 3)
    {
        String detected = ("Object detected : ");
        String dist = (" cm away");
        lcd.print(detected);
        lcd.setCursor(1,2);
        lcd.print(average + dist);
        delay(50);
        
        lcd.clear();
        lcd.home();
    } 
else
{
  lcd.home();
  lcd.print("Make this here!");
}
   
    }//end loop

