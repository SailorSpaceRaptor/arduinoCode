//define switch pins
#define sw1 9
#define sw2 10
#define sw3 11
#define sw4 12

//define mux pins
#define m0 3
#define m1 5
#define m2 6

int r0 = 0;//value of select pin at 4051(s0)
int r1 = 0;//value of select pin at 4051 (s1)
int r2 = 0;//value of select pin at 2045 (s2)
int LED = 0; //value for y input

volatile int state = LOW;//volatile int state "volatile" means variable qualifier

void setup() 
{
  Serial.begin(9600); //set up serial
  pinMode(sw1, INPUT);//set sw to input
  pinMode(sw2, INPUT);//set sw2 to input
  pinMode(sw3, INPUT);//set sw3 to input
  pinMode(sw4, INPUT);//set s4 to input
  pinMode(m0, OUTPUT);//set pin mode of mux input 1
  pinMode(m1, OUTPUT);//set pin mode of mux input 2
  pinMode(m2, OUTPUT);//set pin mode of mux input 3
}

void loop() 
{
  //select bit
r0 = bitRead(LED, 0);
r1 = bitRead(LED, 1);
r2 = bitRead(LED, 2);

digitalWrite(m0, r0); //digitalWrite(muxPin2, bit0)
digitalWrite(m1,r1); //digitalWrite(muxPin3, bit1)
digitalWrite(m2, r2);//digitalWrite(muxpin4, bit2)

 switch(LED)//enter case
  {
    case 1:
      while(LED = 0) //if sw=1 digitalWrite Yellow to High
        {
          Serial.println("yellow");
          digitalRead(sw1);
          break;  
        }
         break;
    case 2:
      while(LED = 1)//if sw ==2 digitalWrite Red high
      {
        Serial.println("red");
        digitalRead(sw2);
        break;
      }
     break;
    case 3: //if sw=3 digitalWrite blu to high
      while(LED = 2) 
      {
        Serial.println("blue");
        digitalRead(sw3);
        break;
      }
      break;
    case 4: //if sw=4 digitalWrite grn to high  
      while(LED = 3)
      {
        Serial.println("green");
        digitalRead(sw4);
        break;
      }
      break;
      default: {}
  }//end case

}//end main
