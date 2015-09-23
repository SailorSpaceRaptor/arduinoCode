/*Code for Intermediate Arduino class, loops lesson
created by Jonathan Eskow for use by NextFab llc in teaching students how to define
and operate loops and arrays using the Arduino platform 
*/

//define pins to be used by LEDs

#define RED 3
#define ORA 5
#define YEL 6
#define GRN 9
#define BLU 10


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
     digitalWrite(RED,HIGH);  //digitalWrite RED LED to HIGH
     delay(100); //delay 100 ms
     digitalWrite(RED,LOW); //turn off RED LED
     delay(100); //delay 100 ms
     digitalWrite(ORA,HIGH);  //digitalWrite ORA LED to HIGH
     delay(100); //delay 100 ms
     digitalWrite(ORA,LOW); //turn off ORA LED
     delay(100); //delay 100 ms
     digitalWrite(YEL,HIGH);  //digitalWrite YEL LED to HIGH
     delay(100); //delay 100 ms
     digitalWrite(YEL, LOW); //turn off YEL LED
     delay(100); //delay 100 ms
     digitalWrite(GRN, HIGH); //digitalWrite GRN LED to HIGH
     delay(100); //delay 100 ms
     digitalWrite(GRN, LOW); //turn off GRN LED
     delay(100); //delay 100 ms
     digitalWrite(BLU, HIGH); //digitalWrite BLU LED to HIGH
     delay(100); //delay 100 ms
     digitalWrite(BLU, LOW); //turn off BLU LED
     delay(100); //delay 100 ms
      
}
