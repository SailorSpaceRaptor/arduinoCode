#define relay 8 //define relay to pin 8
#define beam 6 //define relay to pin 6

int sensorState = 0, lastState = 0; //states for break beam

void setup() 
{
  pinMode(relay, OUTPUT); //relay as output
  pinMode(beam, INPUT); //beam as input
  Serial.begin(); //begin serial
  digitalWrite(beam, HIGH); //use pull up resistor
}

void loop() 
{
 sensorState = digitalRead(beam); //variable for beam
  
if(sensorState == LOW)
{
  digitalWrite(relay, HIGH); //turn on relay to turn off light (sounds confusing I know)
  delay(120000); //delay for 2 minutes
}

if(sensorState && !lastState)//check for states
  {  
    Serial.println("Unbroken"); 
  }
  
if(!sensorState && lastState)
  {
    Serial.println("broken");
  }
lastState = sensorState; 
}
