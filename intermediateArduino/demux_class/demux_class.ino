/*
 *Code created by Jonathan Eskow and Kyle Raskin for NextFab llc in use for Intermediate Arduino Class, state machines exercise 
 */  
 
//define switch variables
#define sw1 9
#define sw2 10
#define sw3 11
#define sw4 12

//define mux variables
const int s0 = 3;
const int s1 = 5;

int r0 = 0;      //value of select pin at the 4051 (s0)
int r1 = 0;      //value of select pin at the 4051 (s1)
int button = 0; //button variable

void setup()
{ 
  Serial.begin(9600);
  pinMode(s0, OUTPUT);    // define s0 as output
  pinMode(s1, OUTPUT);    // define s1 as output
  pinMode(sw1, INPUT);     // define button 1 as input
  pinMode(sw2, INPUT);    // define button 2 as input
  pinMode(sw3, INPUT);    // define button 3 as input
  pinMode(sw4, INPUT);    // define button 4 as input  
}

void loop () 
{

  IDbutton();  
  if (button != 5) 
    {
      switch (button) 
      {
        case 1:
            muxleds(0);
            break;
    
        case 2:
            muxleds(1);
            break;
    
        case 3:
            muxleds(2);
            break;
    
        case 4:
            muxleds(3);
            break;
  
        default:{}

    } //end case
  }  //end if
}  //end loop

void muxleds(int led) 
  {
      r0 = bitRead(led,0);    // use this with arduino 0013 (and newer versions)     
      r1 = bitRead(led,1);    // use this with arduino 0013 (and newer versions)     
      digitalWrite(s0, r0);
      digitalWrite(s1, r1);
  }

void IDbutton()
  {
    if (digitalRead(9)) 
    {
      button = 1;
      Serial.println(1);
    }
  else if (digitalRead(10)) 
    {
      button = 2;
      Serial.println(2);
    }
  else if (digitalRead(11)) 
    {
      button = 3;
      Serial.println(3);
    }
  else if (digitalRead(12)) 
    {
      button = 4;
      Serial.println(4);
    }
  else 
  {
    button = 5;
    Serial.println(5);
  }
 }
