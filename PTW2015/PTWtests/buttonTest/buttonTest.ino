void setup() 
{
  pinMode(6, INPUT);
  pinMode(3, OUTPUT);
  Serial.begin(9600);
}

void loop() 
{
  while(digitalRead(6) == false)
  {
    digitalWrite(3,HIGH);
    Serial.println("pressed");
  }
  
  digitalWrite(3,LOW);

}
