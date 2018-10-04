# muscleCar-code
This folder contains sub-folders with the completed code necessary to wirelessly control your RC car with your muscles! Cool!

Keep in mind that you are going to need to download a library (just a different bunch of code someone has nicely written for us already) and add it to the arduino before you can get it to work.

## Sub-folder Descriptions
The sub-folders each contain different code and it is vitally important that you load the correct code onto the correct Arduino!

### VirtualWireLibrary
This folder contains the library (a .zip file) that you *must* download and load into Arduino before you can get anything else to work!

Once you download the zip file, follow these instructions explaining how to add a .zip library to arduino: [How to add .zip library to Arduino](https://www.arduino.cc/en/Guide/Libraries "How to add .zip library to Arduino")

### Muscle_Car_Human_Control
As the folder states, the code contained in this subfolder is for loading onto the Arduino that is going to be connected to your body!

**Don't forget to adjust the threshold appropriatley for your physiology!**

### Muscle_Car_Vehicle_Control
This folder contians the Arduino code required to be loaded onto your car. It has everything necessary to tell the Arduino how to listen for your muscle activation and work accordingly.

**Don't forget to adjust the motor speed to your preference!**