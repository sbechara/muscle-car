/*  test-motors.ino

    Colorado State University
    Department of Mechanical Engineering

    This code will do a couple of things. First, it will help you figure out and learn what you need and what you need to do in order to program your Ardumoto motors.
    Second, you can use this code as a template to program your robot for the autonomous challange!

    Author: Samuel Bechara, PhD

    Last Modified: 20 June 2018
    By: Samuel Bechara, PhD
*/

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

}

// The loop function below is where we will put all of our main code. This function loops continuously until the Arduino is turned off.
void loop()
{
  // Just like our blinking LED activity, we are going to have to tell the arduino to turn on, wait, and then turn it off
  // For example this program will drive the car forward, wait, back to its original position, and then repeat.
  stopArdumoto(MOTOR_A);
  stopArdumoto(MOTOR_B);
  delay(2000);
  driveArdumoto(MOTOR_A, CW, 100);
  driveArdumoto(MOTOR_B, CW, 100);
  delay(2000);
  stopArdumoto(MOTOR_A);
  stopArdumoto(MOTOR_B);
  delay(2000);
  driveArdumoto(MOTOR_A, CCW, 100);
  driveArdumoto(MOTOR_B, CCW, 100);
  delay(2000);
  // Once the program reaches here, it will loop back to the top of the void loop() and begin again!
}

/*  ----------------------------------------------------------------------------------------------
    The functions below are necessary to setup arduomoto for easy
    control. Students SHOULD look through them to see how they work but shouldn't mess with them.
    You will need these functions included in any arduino code that uses the ardumoto shield and
    motors.
    ----------------------------------------------------------------------------------------------
*/

// setupArdumoto() is a helper function to clean up our setup loop and make it pretty
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

