#define RED 9//define pin for red led
#define ORA 10//define pin for orange led
#define GRN 11//define pin for orange led
#define BLU 12//define pin for green led
#define m0 3//define pin for MUX out 0
#define m1 5//define pin for MUX out 1
#define m2 6//define pin for MUX out 2

int r0 = 0;//value of select pin at 4051 (s0)
int r1 = 0;//value of select pin at 4051 (s1)
int r2 = 0;//value of select pin at 4051 (s2)
int button = 0; //value of y input



volatile int state = LOW;//volatile int state "volatile" means a variable qualifier


void setup() 
{
  Serial.begin(9600);//set up serial for debugging
  pinMode(RED, OUTPUT);//set pin mode for RED
  pinMode(BLU, OUTPUT);//set pin mode for BLU
  pinMode(ORA, OUTPUT);//set pin mode for ORA
  pinMode(GRN, OUTPUT);//set pin mode for GRN
  pinMode(m0, OUTPUT);//set pin mode for mux output 1
  pinMode(m1, OUTPUT);//set pin mode for mux output 2
  pinMode(m2, OUTPUT);//set pin mode for mux output 3
  
  //int btnNum = 0;//start at zero state for state machine
}//end set up

void loop() 
{
  //select bit
 r0 = bitRead(button, 0);
 r1 = bitRead(button, 1);
 r2 = bitRead(button, 2);
  
  
  digitalRead(m0);//digitalWrite(muxPin2, bit0)
  digitalRead(m1);//digitalWrite(muxPin3, bit1)
  digitalRead(m2);//digitalWrite(muxPin4, bit2)
 
  
  switch(button)//enter case statement
  { 
    case 1:
      while(button = 4)//if button == 4 on mux digitalWrite Red
         {
           Serial.println("red");
           digitalWrite(RED, HIGH);
           
//           break; //break
         }
      break;
    case 2:
      while(button = 6) //if button == 6 on mux digitalWrite Orange
        {
          Serial.println("Orange");
          digitalWrite(ORA, HIGH);
//          break;
        }
      break;
    case 3:
      while(button = 7) //if button == 7 on mux digitalWrite Green
        {              
        Serial.println("Green");
        digitalWrite(GRN, HIGH);  
//        break;
        }
      break;
    case 4: 
      while(button = 5)//if button == 5 on mux digitalWrite Blue
        {
          Serial.println("Blue");
          digitalWrite(BLU, HIGH);
//          break;
        }
      break;
        
      default:{}
          break;
  }// end case
}//end main
