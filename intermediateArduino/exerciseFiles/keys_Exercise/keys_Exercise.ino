/*Code for Intermediate Arduino class, functions lesson
created by Jonathan Eskow for use by NextFab llc to teach students how to define and call
functions using the Arduino Platform.
*/

//define pins to be used by buttons
#define C 3
#define D 4
#define E 5
#define F7 6
#define G 8
#define A 9
#define B 10
#define C8 12

#define spk 11

const float tones[8] = {2093.00, 2349.32, 2637.02, 2793.83, 3135.96, 3520.00, 3951.07, 4186.01}; //set array for notes
//                        C7       D        E        F        G        A        B        C8

void setup() 
{
  pinMode(C, INPUT);//set pinMode as input for btn 0
  pinMode(D, INPUT);//set pinMode for btn 1
  pinMode(E, INPUT);//set pinMode for btn 2
  pinMode(F7, INPUT);//set pinMode for btn 3
  pinMode(G, INPUT);//set pinMode for btn 4
  pinMode(A, INPUT);//set pinMode for btn 5
  pinMode(B, INPUT);//set pinMode for btn 6
  pinMode(C8, INPUT);//set pinMode for btn 7
  pinMode(spk, OUTPUT);//set pinMode as output for speaker
}

void loop() 
{
   //insert code to call keys function
}

/*
This function will translate button presses into notes in the key of C
*/
void keys()
{
  while(digitalRead(C) == false)//while button 0 is pressed, play C
   {
    tone(spk, tones[0]);
   }//end while

    //insert code for the rest of the buttons in the function (hint, you can do a lot of copy and paste for this)

} //end keys
