/*created by Jonathan Eskow 10/29/2015
 * this is a class for use with the LeafIt system that dictates the behavior of the moisture sensor. It uses analogRead() to take readings of soil
 * moisture and returns values
 */
 class moistureSense
 {
  /*
   * public methods
   */
   
  public:

  //member variables
  unsigned int moistSense; //initial read for moisture sensor

  //constructor, takes in pin # as parameter and initializes 
   moistureSense(int pin)
  {
    int sensePin = pin;
    moistSense = 0;
  }//end constructor

//method takes measurement 
 String measure(int sensePin)
 {
  int measure = takeMeasure(sensePin);
  String moistStat;

  if(measure <= 100)
  {
    moistStat = "Dry, water plant soon.";
  }
  else if(measure > 101 && measure < 200)
  {
    moistStat = "Just right";
  }
  else
  {
    moistStat = "Soggy, extended exposure could result in rot or Nutrient Deficiency";
  }
  return moistStat;
 } //end measure

;

/*
 * private methods
 */
 
private:

  // method takes raw voltage reading and gives english read out
   int takeMeasure(int sensePin)
  {
   moistSense = analogRead(sensePin);
   map(moistSense,0,1023,0,300); //map moist sensor readings
  
    return moistSense;
   }//end moistSense
  
 }
 ;

