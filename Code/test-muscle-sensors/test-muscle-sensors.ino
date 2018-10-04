
/*  test-muscle-sensors.ino
 *
 *  Colorado State University
 *  Department of Mechanical Engineering
 *  
 *  This code will allow you to visualize the signal that the muscle sensor is reading from your body. You can use
 *  this code to help you tweak your threshold (how to tell arduino your muscle has been activated) and just to make
 *  sure that everything works! Plus it is just kind of cool to see your muscles in action!
 *  
 *  Author: Samuel Bechara PhD
 *  
 *  Last Modified: 20 June 2018
 *  By: Samuel Bechara, PhD
 */

// Now, let's set up the muscle sensors!
// These sensors are already configured to just output an analog voltage that has been rectified, amplified, and integrated so we don't have to 
// do any hard math. Nice, right? Since we are hooking up two muscle sensors, let's define them as left and right and hook them up to analog
// pin A0 and A3, respectively.
// See page 6 of this pdf to see what filtering is used on the muscle sensors! https://cdn-shop.adafruit.com/product-files/2699/AT-04-001.pdf
#define leftSensor A0
#define rightSensor A3

// We need to make sure we don't forget the LEDs! This way we can get visual feedback when the sensor detects muscle activation. This will help GREATLY in figuring out a good threshold.
// Let's let the left LED be on pin 9 and the right LED on pin 11. Feel free to change the LED pins to whatever you like!
int leftLED = 11;
int rightLED = 9;

// Speaking of threshold...lets create an integer called threshold. When this threshold is crossed, we will assume that the muscle has been activated!
int threshold = 250; // This value will probably need to be changed to each individual!

// Now that we have defined some values, we can start the setup process for our components! The function below, called "setup" is run once at
// the start of each program and is used to configure all components and variables. 

void setup() 
{
  Serial.begin(9600);

  // We must define whether the LED pins are inputs or outputs. This is easily done with the built in pinMode function
  pinMode(leftLED, OUTPUT);
  pinMode(rightLED, OUTPUT);

  // Let us have these LEDs off to start the program. This is accomplished with the digitalWrite function. This function takes two paramters: pin and value
  digitalWrite(leftLED, LOW);
  digitalWrite(rightLED, LOW);

  // We do not have to set up the muscle sensor inputs, as they will be automatically set when we read them!

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
  
  // We want to make the control of the vehicle a bit easier so we will use on/off control of the motors!
  // The analog to digital converters that we are using are 10 bit, so the values from the sensors will be between 0 and 1023. When the value is between 0 and 250,
  // we will set the speed to zero. When the value is above threshold, we will set the motor to full speed! The speed we set can be messed around with and the same with the 
  // lower set point of 250. This will require the use of if statements! We want to send values that can work with the analogWrite function, which takes values between
  // 0 (no speed) and 255 (full speed).

  if (leftReading >= 0 && leftReading <= threshold)
  {
    digitalWrite(leftLED, LOW);
  }
  else
  {
    digitalWrite(leftLED, HIGH);
  }
  
  if (rightReading >= 0 && rightReading <= threshold)
  {
    digitalWrite(rightLED,LOW);
  }
  else
  {
    digitalWrite(rightLED,HIGH);
  }

  // The following will print the muscle sensor readings to the serial port so we can test. Go to Tools->SerialMonitor and see for yourself!
  Serial.print(leftReading);
  Serial.print(", ");
  Serial.print(rightReading);
  Serial.print(", ");
  
  // Once the program gets here, it will loop back to the top of void loop() and start over!!!
  delay(1);
}
