const int LEDPIN = 3;

const int sensorPin = 6;

int sensorState = 0, lastState = 0;

void setup() 
{
 pinMode(LEDPIN, OUTPUT); // set led to out
 pinMode (sensorPin, INPUT); // set sensor to in
 digitalWrite(sensorPin, HIGH); //turn on pull-up resistor
 Serial.begin(9600);
}

void loop() 
{
//read state of pushbutton value
sensorState = digitalRead(sensorPin);

//check if sensor beam is broken
if(sensorState == LOW)
 {
  digitalWrite(LEDPIN, 1);
 }
else
 {
  digitalWrite(LEDPIN, 0);
 }

if (sensorState && !lastState)
  {
  Serial.println("Unbroken");
  }

if (!sensorState && lastState)
  {
   Serial.println("Broken");
  }
  
  lastState = sensorState;
}  
