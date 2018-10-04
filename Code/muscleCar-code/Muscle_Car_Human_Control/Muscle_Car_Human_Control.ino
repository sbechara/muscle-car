
/*  Muscle Car Human Control
 *  Colorado State University
 *  Department of Mechanical Engineering
 *  
 *  When run, this code will take in analog voltage readings from two muscle sensors, that will then send 
 *  a voltage command for the left and right motors of the vehicle via a RF transmitter. It will also light up a blue 
 *  LED when the vehicle is commanded to turn right and an LED will turn green when the vehicle is commanded to turn
 *  left.
 *  
 *  Author: Marco Peyfuss, Ben Strauss, Samuel Bechara PhD
 *  
 *  Last Modified: 10 April 2018
 *  By: Samuel Bechara, PhD
 */

// Only one library will be needed: the library to use the radio transmitters. We will be using VirtualWire, as it is easy to use
// and has good documentation. 
// Library: http://www.airspayce.com/mikem/arduino/VirtualWire/VirtualWire-1.27.zip 
// Documentation: https://www.pjrc.com/teensy/td_libs_VirtualWire.html
 
#include <VirtualWire.h>

// In order to use the library, we must declare some variables that we will be using to send messages
// We must define the pin to which the RF transmitter is connected. We have already hooked it up to digital pin 3.
// We must also define a variable for the message we want to send. This will be a character array (basically a string) that has a size of 10.
// Lastly, we must define the rate at which we want to send data. We will set this to 2000 bits/second.
int txPin = 3;
char msg[10];
int sendRate = 2000;

// Now, let's set up the muscle sensors!
// These sensors are already configured to just output an analog voltage that has been rectified, amplified, and integrated so we don't have to 
// do any hard math. Nice, right? Since we are hooking up two muscle sensors, let's define them as left and right and hook them up to analog
// pin A0 and A3, respectively.
// See page 6 of this pdf to see what filtering is used on the muscle sensors! https://cdn-shop.adafruit.com/product-files/2699/AT-04-001.pdf
#define leftSensor A0
#define rightSensor A3

// We need to make sure we don't forget the LEDs!
// Let's let the left LED be on pin 9 and the right LED on pin 11. We will define this similar to how we did it for the RF transmitter pin.
int leftLED = 9;
int rightLED = 11;

// Now that we have defined some values, we can start the setup process for our components! The function below, called "setup" is run once at
// the start of each program and is used to configure all components and variables. 

void setup() 
{
  Serial.begin(9600);
  Serial.print("Initializing... ");
  // We must define whether the LED pins are inputs or outputs. This is easily done with the built in pinMode function
  
  pinMode(leftLED, OUTPUT);
  pinMode(rightLED, OUTPUT);

  // Let us have these LEDs off to start the program. This is accomplished with the digitalWrite function. This function takes two paramters: pin and value
  
  digitalWrite(leftLED, LOW);
  digitalWrite(rightLED, LOW);

  // We do not have to set up the muscle sensor inputs, as they will be automatically set when we read them!
  // We do, however, have to set up the RF transmitter properly. This includes setting the transmitter pin and setting the send rate. The built in functions are 
  // used below. Easy enough, right?
  
  vw_set_tx_pin(txPin);
  vw_setup(sendRate);

  Serial.println("Initialized!");
}

// The function below is where the main code resides and it is run continously until the Arduino is turned off! This is now where we will implement all our code!

void loop() 
{
  // Overall, the game plan is to read from the muscle sensors, send the values to the car via RF, and then light up LEDs accordingly.
  
  // We want to first define some variables that we will be needing. We need to store the raw values from the muscle sensors. We also need to convert the raw values into
  // values that we will send the vehicle via the RF transmitter. 
  
  int leftReading; 
  int rightReading;
  int leftMotorSpeed;
  int rightMotorSpeed;

  // Now that we have these defined, we can read from the muscle sensors! Arduino has a handy built in funciton called analogRead that will help us.
  
  leftReading = analogRead(leftSensor);
  rightReading = analogRead(rightSensor);
  
  // These values from the muscle sensor can vary greatly with fine mhttps://en.wikipedia.org/wiki/American_wire_gaugeovements of a muscle, which makes the vehicle control hard.
  // We want to make the control of the vehicle a bit easier so we will use on/off control of the motors!
  // The analog to digital converters that we are using are 10 bit, so the values from the sensors will be between 0 and 1023. When the value is between 0 and threshold,
  // we will set the speed to zero. When the value is above threshold, we will set the motor to full speed! The speed we set can be messed around with and the same with the 
  // threshold. This will require the use of if statements! We want to send values that can work with the analogWrite function, which takes values between
  // 0 (no speed) and 255 (full speed).

  int threshold = 250; // remember: this can be tweaked from 0 to 1023
  int motorSpeed = 255; // remember: this can be tweaked from 0 to 255

  if (leftReading >= 0 && leftReading <= threshold)
  {
    leftMotorSpeed = 0;
  }
  else
  {
    leftMotorSpeed = motorSpeed;
  }
  
  if (rightReading >= 0 && rightReading <= threshold)
  {
    rightMotorSpeed = 0;
  }
  else
  {
    rightMotorSpeed = motorSpeed;
  }

  Serial.println("Muscle sensor readings and corresponding speeds!");
  Serial.print(leftReading);
  Serial.print(", ");
  Serial.print(rightReading);
  Serial.print(", ");
  Serial.print(leftMotorSpeed);
  Serial.print(", ");
  Serial.println(rightMotorSpeed);
  
  // Now that we have the motor speeds set, we can send the values via the RF transmitter! We need to package these values into the variable, msg, that we defined earlier.
  // This will require some c programming functions, but not to worry, they aren't too bad! We will be using the sprintf function which basically takes in integer values
  // and then outputs a string, which is basically the same as a charater array in c (this is what msg is and is why we defined msg as a character arry)

  sprintf(msg, "%d,%d.", leftMotorSpeed, rightMotorSpeed);

  // Now that msg is filled with a comma-separated list that ends with a period, we can send it using vw_send form the virtualWire library! The uint8_t converts msg to an
  // unsigned integer that is 8 bits (one byte) and the * is a pointer to the msg array. strlen is a function that gets the length of a string. vw_wait_tx waits until the
  // message is sent before moving on to the next line.
  Serial.print("Message: ");
  Serial.println(msg);
  vw_send((uint8_t*)msg, strlen(msg));
  vw_wait_tx();

  // Now the last thing to do is set the LEDs on!

  if (rightMotorSpeed > leftMotorSpeed)
  {
    digitalWrite(rightLED, HIGH);
    digitalWrite(leftLED, LOW);
  }
  else if(rightMotorSpeed < leftMotorSpeed)
  {
    digitalWrite(leftLED, HIGH);
    digitalWrite(rightLED, LOW);
  }
  else
  {
    digitalWrite(leftLED, LOW);
    digitalWrite(rightLED, LOW);
  }

  // Once the program gets here, it will loop back to the top of void loop() and start over!!!
  delay(1);
}
