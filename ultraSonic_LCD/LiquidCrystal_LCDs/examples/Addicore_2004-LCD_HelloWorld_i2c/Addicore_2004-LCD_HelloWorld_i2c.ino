#include <Wire.h>               // Includes the Wire library for I2C communication
#include <LiquidCrystal_I2C.h>  // Includes the LiquidCrystal_I2C library

#define lcdAddress 0x27         // LCD I2C Address

int count = 0;                  // Variable to hold current count value

LiquidCrystal_I2C lcd( lcdAddress );   // Create instance of LiquidCrystal_I2C and set the LCD I2C address

void setup()
{
  lcd.begin(20,4);              // initialize the lcd as a 20 characters by 4 rows display
  lcd.setBacklight(HIGH);       // Turn on the LCD's backlight 
  lcd.home ();                  // set the cursor to the home position (first row, first column)
  lcd.print("Hello World");     // print "Hello World" to the LCD
}

void loop()
{
  lcd.setCursor ( 0, 2 );       // set cursor to first character of line 3 
  lcd.print ("Count = ");       // print "Count = " to the LCD
  lcd.print (count);            // print the value of the variable named count
  delay ( 200 );                // pause the program for a brief moment to allow user to see current display characters
  count++;                      // increment the value of the variable count ( same as count + 1 )
  if( count > 100 ) {           // checks if the value of count is greater than 100
    count = 0;                  // sets the value of count to 0
    lcd.setCursor ( 8, 1 );     // set cursor to ninth character of line 2 
    lcd.print ("   ");          // print "   " to the LCD, this will clear the characters that last held displayed 100
  }
}
