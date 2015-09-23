/*Code for Intermediate Arduino class, loops lesson
created by Jonathan Eskow for use by NextFab llc to teach students how to define
and operate loops and arrays using the Arduino platform 
*/

//define pins to be used by LEDs
#define RED 3
#define ORA 5
#define YEL 6
#define GRN 9
#define BLU 10

const int LED[5] = {RED, ORA, YEL, GRN, BLU};//create array for LED pins
void setup() 
{
 pinMode(RED,OUTPUT);//set pinMode for red LED
 pinMode(ORA, OUTPUT);//set pinMode for orange LED
 pinMode(YEL, OUTPUT);//set pinMode for yellow LED
 pinMode(GRN, OUTPUT);//set pinMode for green LED
 pinMode(BLU, OUTPUT);//set pinMode for blue LED
}

void loop() 
{
 for(int i = 0; i <= 4; i++)//for i = 0 (start of array) i <= 4 (to last object in array) i ++ (increment array)
    { 
     digitalWrite(LED[i],HIGH);  //digitalWrite each LED to HIGH
     delay(100); //delay 100 ms
     digitalWrite(LED[i],LOW); //turn off each LED
     delay(100); //delay 100 ms
    }//end for 
}
