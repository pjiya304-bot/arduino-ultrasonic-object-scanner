# Ultrasonic Object Scanner
An Arduino based scanning system that uses an ultrasonic sensor mounted on a servo motor to sweep a field of view and detect object distance, size and speed at each angle - an early exercise in sensor-based ranging and embedded control, foundational is later work in RF/signal-based sensing systems.

## Overview
This project interfaces with an HC-SR04 ultrasonic sensor with a SG90 servo motor, controlled by an Arduino Uno. the servo sweeps across a fixed angular range while the sensor measures distance at each step using pulse-echo timing, producing an angular distance map - the same core time-of-flight ranging principle used in radar and lidar systems, applied here at a small, accessible scale. 

## Components
| Component | Purpose |
| Arduino Uno | Microcontroller - controls servo, reads sensor, runs detection logic |
| HC-SR04 Ultrasonic Sensor | Emits ultrasonic pulse, measures echo return time |
| SG90 Servo Motor | Sweeps sensor across the scan angle |
| Jumper wire | Circuit connections |

## Hardware Setup

![Full setup](media/full-setup.jpg)
![Wiring closeup](media/wiring-closeup.jpg)

## How It Works
1. The servo sweeps from 0 degrees to 180 degrees in fixed steps, then back, continously.
2. At each scan step, the ultrasonic sensor emits a pulse and measures echo return time.
3. **Distance** is calculated from echo time using speed of sound: 'distance = (duration x 0.0343) / 2'.
4. **Proximity Category** (NEAR/MID/FAR0 is assigned based on distance thresholds - this is a simple proximity classification, not a true measurement of object size.
5. **Speed** is estimated by comparing distance readings between succesive scan steps, divided by the time interval between them.

## Code
Full code: ['src/scan.ino'](src/scan.ino)

Core functions:
- 'getDistance()' - triggers the sensor and calculates distance from echo time
- 'getProximityCategory()' - classifies distance into NEAR/MID/FAR
- 'loop()' - drives the servo sweep and runs detection logic once per scan interval 

## Limitations and Observations
Distance detection works reliably and consistently. A few things worth noting;
- **Proximity, not size:** the current version classifies objects into NEAR/MID/FAR bands based on the distance fromthe sensor - it doesnot measure actual physical size. A true size estimate would require tracking angular span across a sweep (i.e. how many consecutive angles detect the same object), which is a planned future improvement rather than a current feature.
- **Timing bug found and fixed:** an earlier version of the loop had a scoping error where the scan-interval check ('scanDelay') wasn't actually gating the sweep/measurement logic, causing readings to run on every loop iteration instead of at the intended interval - this was corrupting speed calculations, since the speed was being divided by an assumed 4-second interval thatwasn't the real time between readings. This has since been fixed.
- Ultrasonic reflections are angle-sensitive: flat surfaces facing the sensor reflect cleanly, while angled or irregular surfaces scatter the pulse and produce inconsistent readings.

## Future Improvements
- Implement true object-size estimation using angular span tracking across a sweep
- Add a real-time visual scan display (e.g. Processing or a small OLED)
- Increase angular resolution with finer servo steps
- Compare against alternative sensing method for accuracy benchmarking




