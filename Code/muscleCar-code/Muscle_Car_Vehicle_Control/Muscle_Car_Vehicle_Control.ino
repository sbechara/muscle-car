/*  Muscle Car Vehicle Control
    Colorado State University
    Department of Mechanical Engineering

    When run, this code will receive signals sent from the transmitter attached to the control platform worn by you!
    This signal contains a message in the form of an array, and tells the Arduino on board the vehicle to move the left or right motor at a specified speed.
    The direction of your vehicle will essentially be controlled by your muscle movements. How cool!!

    Author: Ben Strauss

    Last Modified: 10 April 2018
    By: Samuel Bechara, PhD
*/

// Only one Library is needed for the Vehicle code, and this library is the same as used in the Human Control code.
// The VirtualWire library was used to transmitt messages to the vehicel, so it makes sense that we might need the same library to receive these messages!
// The Library can be found: http://www.airspayce.com/mikem/arduino/VirtualWire/VirtualWire-1.27.zip
// Documentation for VirtualWire library can be found: https://www.pjrc.com/teensy/td_libs_VirtualWire.html
#include <VirtualWire.h>

// We need to declare some variables before we can begin coding!
// We must define the pin to which the RF receiver is connected. This should already be hooked up to pin 3.
// We must also define a variable to store the message we want to send. Just like the human control code, this variable will be a character array that has a size of 10.
// Finally, we need to define the rate at which we want to send the data. To sync up with the transmitter, we will set this to 2000 bits/second.
int rxPin = 7;
char msg[10];
int receiveRate = 2000;

// These constants below are necessary to tell the motor controller how to work!
const byte PWMA = 3;  // PWM control (speed) for motor A
const byte PWMB = 11; // PWM control (speed) for motor B
const byte DIRA = 12; // Direction control for motor A
const byte DIRB = 13; // Direction control for motor B

// Clockwise and counter-clockwise definitions.
// Depending on how you wired your motors, you may need to swap.
#define CW  0
#define CCW 1

// Motor definitions to make life easier:
#define MOTOR_A 0
#define MOTOR_B 1

// Now that the required variables have been defined, and the motors and receiver have been set, we can start the setup process!
// The function below, called "setup", is only run once during start of the program, and is used to confugure all components and variables.

void setup()
{
  // First we need to run the setupArdumoto function to get the motor controller ready to go
  setupArdumoto();
  
  // Next, we need to set up the RF receiver. We can do this by using the built in functions below to set the receiver pin receving rate.
  // We can easily initialize the receiver by using the start function below. Now we are ready to begin writing the main code!
  Serial.begin(9600);
  vw_set_rx_pin(rxPin);
  vw_setup(receiveRate);
  vw_rx_start();

}

// The loop function below is where we will put all of our main code. This function loops continuously until the Arduino is turned off.

void loop()
{

  // Our objective here is to read an incoming message from the user (thats you!), and use this message to move the right or left motors accordingly.

  //

  uint8_t buf[VW_MAX_MESSAGE_LEN]; // a buffer for incoming data
  uint8_t buflen = VW_MAX_MESSAGE_LEN; // length of the buffer

  // The if statement below will check to see if the received data makes Weany sense. In other words, is the incoming data any good, or is it just scrambled nonsense?
  if (vw_get_message(buf, &buflen))
  {
    // If the data is all good, then we can run the following for loop. The purpose of this for loop is to store the message into a data array.
    // This loop will run until all of the incoming message is stored.

    for (int i = 0; i < buflen; i++)
    {
      //In order to store the incoming message, we must put the data into an array. The msgbuf structure below can be thought of as a template in which we can store this incoming data. We can then refer to the array msg later to convert the array from characters to integers.
      msg[i] = buf[i];
    }

    //The incoming message needs to be converted from characters to integers before we send this data to the motors! The analogWrite function uses values between 0 (no speed) and 250 (full speed) to set the speed of each motor.
    //This is done using a built-in function called "atoi".
    int LeftMotorValue = atoi(strtok(msg, ","));
    int RightMotorValue = atoi(strtok(NULL, "."));

    // For debugging purposes - uncomment the two lines below, plug the arduino into a computer, and look at serial monitor if necessary
    // Serial.println(LeftMotorValue); 
    // Serial.println(RightMotorValue);

    // With the LeftMotorValue and RightMotorValue variables defined with the value of the incoming message, we can tell the Arduino to run these motors accordingly!
    // This is done with a function defined below called driveArduomoto. 
    // Essentially, the left and right motors will now run at the speed given by your muscle contractions! Cool, right?
    if (LeftMotorValue > 0)
    {
      driveArdumoto(MOTOR_A, CCW, 255);
    }
    else
    {
      stopArdumoto(MOTOR_A);
    }

    if (RightMotorValue > 0)
    {
      driveArdumoto(MOTOR_B, CCW, 255);
    }
    else
    {
      stopArdumoto(MOTOR_B);
    }
  }
  delay(1);
  // Once the program reaches here, it will loop back to the top of the void loop() and begin again!
}

/*  ----------------------------------------------------------------------------------------------
    The functions below are necessary to setup arduomoto for easy
    control. Students SHOULD look through them to see how they work but shouldn't mess with them.
    ----------------------------------------------------------------------------------------------
*/

void setupArdumoto()
{
  // All pins should be setup as outputs:
  pinMode(PWMA, OUTPUT);
  pinMode(PWMB, OUTPUT);
  pinMode(DIRA, OUTPUT);
  pinMode(DIRB, OUTPUT);

  // Initialize all pins as low:
  digitalWrite(PWMA, LOW);
  digitalWrite(PWMB, LOW);
  digitalWrite(DIRA, LOW);
  digitalWrite(DIRB, LOW);
}

// driveArdumoto drives 'motor' in 'dir' direction at 'spd' speed
void driveArdumoto(byte motor, byte dir, byte spd)
{
  if (motor == MOTOR_A)
  {
    digitalWrite(DIRA, dir);
    analogWrite(PWMA, spd);
  }
  else if (motor == MOTOR_B)
  {
    digitalWrite(DIRB, dir);
    analogWrite(PWMB, spd);
  }
}

// stopArdumoto makes a motor stop
void stopArdumoto(byte motor)
{
  driveArdumoto(motor, 0, 0);
}

