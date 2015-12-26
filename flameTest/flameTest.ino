#include <Servo.h>



/****************************************************************************************
 * global variables
 ****************************************************************************************/
 
#define sensePin 2
#define button 3
#define servoPin 6

/***********************************************************************************************************************
 * main method
 ***********************************************************************************************************************/
Servo myServo;

void setup()
{
  Serial.begin(9600);
  myServo.attach(servoPin);
  pinMode(sensePin, INPUT_PULLUP);
  pinMode(button, INPUT_PULLUP);
  attachInterrupt(0,trigger,RISING);
  attachInterrupt(1,closeBox, FALLING);
}

void loop() 
{
  //wait for interrupt
}


/************************************************************************************************
 * Interrupts and external methods
 * ********************************************************************************************/

 //ISR attached to EXT_interrupt 0 (pin 2) opens box when flame is recognized
void trigger() //ISR to activate servo
{
  Serial.println("Fire Detected");
  openBox(); 
}

//ISR attached to EXT_interrupt 1 (pin 3) closes box when switch is hit
void closeBox()
{
  Serial.println("Button Pressed");
  resetServo();
}

void resetServo()
{
 int interval = 15;
  for(int pos = 90; pos >= 0; pos--)
  {
      myServo.write(pos);
      delay(interval);
      break;
  }//end for
  int angle = myServo.read();
  Serial.println(angle);
} //end resetServo

void openBox()
{
 int interval = 15;
  for(int pos = 0; pos <= 90; pos++)
  {
      myServo.write(pos);
      delay(interval);
      break;
  }//end for
 int angle = myServo.read();
 Serial.println(angle);
}//end openBox

