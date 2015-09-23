const int OUT = 6; // output on pin 6
const int hall = A0;
float sensorValue = 0.0;

void setup() 
{
  Serial.begin(9600); //start serial read
//  pinMode(OUT,OUTPUT); //pin 6 is output
}

void loop() 
{
   sensorValue = analogRead(A0); //start sensor at zero
   
   if (sensorValue <= 500) //if sensor comes in contact with magnetic field
    {
//      digitalWrite(LED,1); //turn on LED
      Serial.println("Detected");
    }
   else
//      digitalWrite(LED,0); //else keep LED off
      Serial.println("all clear");

}
