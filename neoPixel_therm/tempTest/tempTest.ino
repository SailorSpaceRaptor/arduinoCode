// -----------------
// Read temperature
// -----------------

int sensorPin = 0;

void setup()
{
  Serial.begin(9600);
}

void loop()
{
  double reading = analogRead(sensorPin);
  
  double voltage = reading * 5.0;
  
  voltage /= 1024.0;
  
  Serial.print(voltage); Serial.println(" volts");
  
  double temperature = (voltage - 0.5) * 100;
  
  Serial.print(temperature); Serial.println(" degree C");
  
  double temperatureF = (temperature * 9.0 / 5.0) + 32.0 500m;
  
  Serial.println(temperatureF); Serial.println(" degree F");
  
  delay(1000);
  
}
