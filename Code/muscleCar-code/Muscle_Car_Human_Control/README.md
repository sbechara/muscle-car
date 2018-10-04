# Human Control Hookup Guide
Using the breadboard, make the following connections. Note it is highly reccomended you use the breadboard power rails for the muscle sensros!

| Arduino Pin | RF Transmitter |
|:-----------:|:--------------:|
|(No Connection)         | Pin 4 - Antenna|
| Vin         | Pin 3          |
| Digital 3   | Pin 2          |
| GND         | Pin 1          |

| Arduino Pin | Muscle Sensor 1 |
|:-----------:|:-------------:|
| A0          | Sig           |

| Arduino Pin | Muscle Sensor 2 |
|:-----------:|:-------------:|
| A3          | Sig           |

| Arduino Pin | Both Muscle Sensors |
|:-----------:|:-------------:|
| 5V         | (+)           |
| GND        | (-)           |
