const int TILT = 5; //assign pin 5 to tilt switch
const int LED = 3; //assign pin 3 to LED
void setup() 
{
  Serial.begin(9600); // open channel to serial monitor
  pinMode(TILT, INPUT); //set tilt switch to input
  pinMode(LED,OUTPUT); //set LED to output
  digitalWrite(TILT, HIGH);
}

void loop() 
{
 while (digitalRead(TILT) == false) //while switch is broken
   {
     digitalWrite(LED,1); //turn on LED
     Serial.println("I've fallen and I can't get up!"); //send message to Serial Monitor
     delay(100); //delay between readings
   }
  digitalWrite(LED,0); //while switch is together, do nothing.
}
