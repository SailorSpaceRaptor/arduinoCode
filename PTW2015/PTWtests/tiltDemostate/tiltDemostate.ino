const int TILT = 5; //assign pin 5 to tilt switch
const int LED = 3; //assign pin 3 to LED
int sensorState = 0, lastState = 0;

void setup() 
{
  Serial.begin(9600); // open channel to serial monitor
  pinMode(TILT, INPUT); //set tilt switch to input
  pinMode(LED,OUTPUT); //set LED to output
  digitalWrite(TILT, HIGH); //pullup on tilt
}

void loop() 
{
 sensorState = digitalRead(TILT);
 
  while (digitalRead(TILT) == true) //while switch is broken
   {
     digitalWrite(LED,1); //turn on LED
   }
  digitalWrite(LED,0); //while switch is together, do nothing.

 if (sensorState && !lastState)
  {
    Serial.println("I've fallen and I can't get up!"); //send message to Serial Monitor
  }
 if (!sensorState && lastState)
 {
  Serial.println("All is well"); 
 } 

}
