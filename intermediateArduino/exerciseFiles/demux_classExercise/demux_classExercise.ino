/*
 *Code created by Jonathan Eskow and Kyle Raskin for NextFab llc in use for Intermediate Arduino Class, state machines exercise 
 */  
 
//define switch variables
#define sw1 9
#define sw2 10
#define sw3 11
#define sw4 12

//define demux variables
const int s0 = 3;
const int s1 = 5;

int r0 = 0;      //value of select pin  (s0)
int r1 = 0;      //value of select pin  (s1)
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

  IDbutton();  //call function for the IDbutton
  if (button != 5) 
    {
      switch (button) 
      {
        //insert code for the case statement 

     } //end case
    }  //end if
}  //end loop

//this function uses 2 of the 3 bits the demux provides users to work with to dictate which LED is lit
void muxleds(int led) 
  {
      r0 = bitRead(led,0);    // use this with arduino 0013 (and newer versions)     
      r1 = bitRead(led,1);    // use this with arduino 0013 (and newer versions)     
      digitalWrite(s0, r0);
      digitalWrite(s1, r1);
  }

void IDbutton()
  {
    //insert code to set up the ID process for the state machine
  }
