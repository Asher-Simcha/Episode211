
// Look at your driver board and you will see pins labeled "IN1", "IN2", "IN3", & "IN4"
// These are the pins that need to be connected to digital out pins on your Arduino.
// The variables below give you an easy way to assign which pins on the driver board are
// connected to corresponding pins on the Arduino.

int IN1 = 4;    
int IN2 = 5;
int IN3 = 6;
int IN4 = 7;

int Speed = 1;        // This controls how long we wait between pulses (In seconds)
int Distance = 0;        // Creating an integer variable named "Distance" that counts the number of steps we've made
int FullRotation = 4096; // How many steps are in a full revolution of the motor shaft?
int lookup[8] = {B01000, B01100, B00100, B00110, B00010, B00011, B00001, B01001};
                          // This array contains bimary values that will be pushed to the outpur pins to properly pulse the stepper

int incomingByte = 0;   // Variable to hold incoming serial data

void setup()
{
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  // We set the mode of our 4 pins to output
  Serial.begin(9600);     // opens serial port, sets data rate to 9600 bps
}

void loop()
{
        // We only want to do something when we receive data
        // This if statement puts us into pause until the arduino receives data from the serial port
        
        if (Serial.available() > 0) 
          {
                incomingByte = Serial.read(); // Read the incoming data

                Serial.print("I received: ");
                Serial.println(incomingByte);

                // IF the arduino has received data, then evaluate the following two IF statements
                
                if (incomingByte == 97)
                {
                  for (int x=0; x < 3; x++)
                  {
                    CCW();
                  }
                }
                

                if (incomingByte == 100)
                {
                  for (int x=0; x < 3; x++)
                  {
                    CW();
                  }
                }
        }


}


void CW()
{
  for(int stepper = 7; stepper >= 0; stepper--)
  {
    MoveStep(stepper);
    delay(Speed);
  }
}

void CCW()
{
  for(int stepper = 0; stepper < 8; stepper++)
  {
    MoveStep(stepper);
    delay(Speed);
  }
}


// This function will move the motor one step in either direction (depending on which function called this function)
void MoveStep(int eighth)
{
  digitalWrite(IN1, bitRead(lookup[eighth], 0));
  digitalWrite(IN2, bitRead(lookup[eighth], 1));
  digitalWrite(IN3, bitRead(lookup[eighth], 2));
  digitalWrite(IN4, bitRead(lookup[eighth], 3));


}

