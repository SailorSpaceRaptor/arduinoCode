int fsrAnalogPin = 0;
int LEDpin = 5;
int fsrReading;
int LEDbrightness;

void setup() 
{
  Serial.begin(9600);
  pinMode(LEDpin,OUTPUT);
  
}

void loop() 
{
 fsrReading = analogRead(fsrAnalogPin);
 Serial.print("Analog reading = ");
 Serial.println(fsrReading);
 
 LEDbrightness = map(fsrReading, 0, 1023, 0, 255); //map analog reading from 0 to 1023 to 0 to 255
 
 analogWrite(LEDpin, LEDbrightness); //LED gets brighter the harder you press the sensor
 
 delay(100);

}
