# Arduino Radar Object Detection



### 

### \##Description

This Project is an Arduino based Radar System that detects object using an Ultrasonic sensor and it can measure distance, estimate object size and calculate speed in real time. this system is useful for educational purposes, robotics and small automation projects.



### \##Hardware Used

* Arduino Uno
* Ultrasonic Sensor
* Servo Motor
* Jumper wires 



### \##Circuit Connections

* Ultrasonic sensor Trig Pin - Arduino Pin 10
* Ultrasonic sensor Echo Pin - Arduino Pin 11
* Servo Signal Pin - Arduino Pin 9
* VCC and GND - Connected to 5V and GND of Arduino respectively



### \##Code Overview

* Servo Sweep - Moves the servo smoothly across a defined range.
* Distance Measurement - uses the ultrasonic sensor to calculate the distance.
* Object Size Estimation - Classifies objects as NARROW, MEDIUM and WIDE based on their distance.
* Speed Calculation - Estimates objects speed by comparing distance changes over time.
* Formatted output - Displays angle, distance, size and speed clearly on serial monitor.
* timing control - Uses millis() to ensure measurements are taken at fixed intervals(scanDelay) for stable readings.



### \##How to Run

1. Connect the hardware according to the circuit diagram.
2. Open the Arduino IDE and upload 'radar.ino' to your Arduino Uno.
3. open the serial monitor at "9600 baud" to view distance, size and speed.



### \##Applications

* Obstacle detection in small robots and drones.
* Security and surveillance systems.
* Industrial monitoring for moving objects.
* Educational and demonstration purposes.



