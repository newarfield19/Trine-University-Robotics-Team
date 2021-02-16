/* Some observations for those who will be working with the code
When the reciever loses connection what will happen is ch1 will go to 255 and ch2 will keep whatever value it had
before the loss of connection do with this information what you will i recomend a way to detect these anomalies using
a for loop and stating that if ch 1 is at 255 and ch2 is at the same number for a certain amount of time that all movement
should ceise until connection is made again which will be observable when ch1 goes back to a different value besides 255

The code for recieving information works by alternating between two values 0 and 1 to alternate which channel the arduino \
will be collecting information from this is due to myself being unable to figure out a way to collect values from more
than one pin at a time so i made a work around to where we recieve half the information in the same amount of time
this means while response time will take longer it is only around a ms of time so it should be unoticable

PWM : PWM is pulse width modulation the code currently works by taking the values from the reciever and converting them to
PWM values that the arduino can use to control a motor driver the values are from 0 to 255 or -255 the negative just means
the motors will run in the opposite direction don't freak out about the specifics if you need more info on it there are plenty
of sources on the arduino website and on youtube as well as other forums.

We also need to include a shut off switch i recomend an unused switch or combo of movements that does not include the
gear switch which will be used for the weapon

Do not forget to comment out all of the debugging code before using the robot in competition
Do not forget to comment out all of the debugging code before using the robot in competition
Do not forget to comment out all of the debugging code before using the robot in competition
Do not forget to comment out all of the debugging code before using the robot in competition


Pin D8 is bad on the arduino

*/

// i recomend declaring all variables within this section before the setup function unless they will need to be reset then
// put thim into the loop function


//------------------------------------------------------------------------------------------------------------------
             
int ch1 = 0; // We will avoid keeping these variables in the loop so that we can continue to use the values for every tick instead of everyother tick if they were to be contained within the loop
int ch2 = 0; //declares the ch2 variable and defines its placeholder value as 0 until the code starts
int x = 0; // the variable used to alternate between the channels

// declares the variable names and pins going to be used for the reciever
#define CH1 2 //left stick
#define CH2 10 //right stick

//---------------------------------

//Enabling the PWM Pins
//Motor A Controlling Pins
int enA = 9;
int in1 = 11;
int in2 = 7;
// Motor B connections
int enB = 3;
int in3 = 5;
int in4 = 4;

//this is one time use code that will only be ran when the arduino is starting up
void setup() {
 
  Serial.begin(9600); //Used to start the serial monitor for debugging

  //makes each pin on the arduino an input so we may read from the reciever
  pinMode(CH1, INPUT);
  pinMode(CH2, INPUT);

//----------------------------------------------

  // Defines that all PWM Pins are OUTPUTS
  pinMode(enA, OUTPUT);
  pinMode(enB,OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3,OUTPUT);
  pinMode(in4,OUTPUT);
  
  digitalWrite(in1,LOW);
  digitalWrite(in2,LOW);
  digitalWrite(in3,LOW);
  digitalWrite(in4,LOW);
  
}


//------------------------------------------------------------------------------------------------------------------

void loop() {
  // put your main code here, to run repeatedly:
  //----------------------------------------------------------------------------------------------------
  // this portion of the code is the alternate between the channels of the reciever
  
  if (x==0)
  {
    ch1 = map(pulseIn(CH1, HIGH, 30000), 1000, 2000, -500, 500); // creates a map of the anolog sticks location for control
    ch1 = constrain(ch1, -255, 255); //shrinks the input values into a range between -255 and 255

    Serial.print("Ch 1: "); //prints out some values for debugging
    Serial.print(ch1);
    Serial.print("     ");
    //Serial.println("0"); // used to see what x-value is being used
    x = 1;
  }


  
  else if (x==1)
  {
    ch2 = map(pulseIn(CH2, HIGH, 30000), 1000, 2000, -500, 500);
    ch2 = constrain(ch2, -255, 255);

    Serial.print("Ch 2: ");
    Serial.println(ch2);
    //Serial.println("1"); // used to see what x-value is being used
    x=0; //switches the alternating variable to the other value so that it infinately repeats
  }
  

  //-------------------------------------------------------------------------------------------------------

  //This portion of the code is used to now use the information for the reciever to control the motors using PWM signals
  // I recomend adding in ranges of values in the if then statements to create makeshift deadzones
  // review the input data to help you declare these deadzones.
  // to input deadzones use "and or" statements in the condition location of the statements just make sure not to have overlap

//------------------------------------------------------------------
  
  // PWM code for CH1

  if (ch1 > 25) //Declared as forward spin
  {
    digitalWrite(in1, LOW); // Declares the direction the motor will spin with the usage of HIGH and LOW
    digitalWrite(in2, HIGH); // if there are two HIGHs or LOWs then the motor will be considered stopped and or disabled so it wont spin even if a speed value is declared
    analogWrite(enA,ch1); // declares the speed that the motor will spin notice the usage of analof instead of digital
  } // the usage of analog instead of digital is due to digital meaning 0 or 1 or in this case HIGH or LOW and not a numerical value

  if (ch1 < -25)
  {
    digitalWrite(in1,HIGH);
    digitalWrite(in2,LOW);
    analogWrite(enA,ch1*(-1));
  }

  if ((ch1 > -25) && (ch1 < 25))
  {
    digitalWrite(in1,LOW);
    digitalWrite(in2,LOW);
    analogWrite(enA,ch1*(-1));
  }



//-------------------------------------------------------------------

// PWM code for CH2

  if (ch2 > 25) //declared as forward spin
  {
    digitalWrite(in4,HIGH);
    digitalWrite(in3,LOW);
    analogWrite(enB,ch2);
  }

  if (ch2 < -25)
  {
    digitalWrite(in4,LOW);
    digitalWrite(in3,HIGH);
    analogWrite(enB,ch2*(-1));
  }

  if ((ch2 > -25) && (ch2 < 25))
  {
    digitalWrite(in4,LOW);
    digitalWrite(in3,LOW);
    analogWrite(enB,ch2*(-1));
  }


//-----------------------------------------------------------------
  
//------------------------------------------------------------------------------------------------------------------------
  
  delay(1); //used for debugging with easier review of information by increasing the amount of time until the loop will reset

}


//----------------------------------------------------------------------------------------------------------------------
