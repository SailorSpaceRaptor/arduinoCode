#include <LiquidCrystal.h>

LiquidCrystal lcd(12, 11 ,5 ,4 ,3, 2);
double temperature = 0.0;

void setup()
{
  lcd.begin(16, 2);
 
  pinMode(A0, INPUT);
  
}

void loop()
{
  int reading = 0;
  double voltage = 0.0;
  
  lcd.display();
 
  //read from A0
 reading = analogRead(A0);
  
  //returned value will be between 0 and 4095
 voltage = (reading * 5) / 1023;
  
  //calculate temp
 temperature = (voltage - 0.5) * 100;
  
  //print message
  lcd.print(temperature);
  delay(5000);
}
