# Ultrasonic Object Scnner
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
2. At each angle, the ultrasonic sensor emits a pulse and measures echo return time.
3. **Distance** is calculated from echo time using speed of sound: 'distance = (duration x 0.0343) / 2'.
4. **Object Size** is estimated by checking how many consecutive angular steps detect an object at a similar distance - a wider detected span suggests a larger object.
5. **Speed** is estimated by comparing distance readings for the same object across successive scans, divided by the time between them.

## Code
Full code: ['src/scan.ino'](src/scan.ino)

Core functions:
- 'getDistance()' - triggers the sensor and calculates distance from echo time
- 'getObjectSize'()' - infers object width from the angular span of consistent directions
- 'loop()' - drives the servo sweep and calls detection functions at each step

## Limitations and Observations
Distance detection works reliably and consistently. however, size and speed estimates are noticibly inconsistent - this is an inherent limitation of the approach rather than a bug:
- A single HC-SR04 gives one distance reading per angle; it cannot measure size directly. Size is inferred from how many consecutives angles detect the same object, which is easily thrown off by the sensor's ~15 degrees beam width picking up overlapping points.
- Speed is estimated from distance change over time between scans, but the servo's mechanical sweep introduces timing lag - readings aren't simultaneous, so speed calculation inherit that noise.
- Ultrasonic reflections are angle-sensitive: flat surfaces facing the sensor reflect cleanly, while angled or irregular surfaces scatter the pulse and produce inconsistent readings.

## Future Improvements
- Use multiple ultrasonic sensors or add a second sensing modality to improve size/speed accuracy
- Add a real-time visual scan display
- Increase angular resolution with finer servo steps
- Compare against an alternative sensing menthod for accuracy benchmarking






### \##Applications

* Obstacle detection in small robots and drones.
* Security and surveillance systems.
* Industrial monitoring for moving objects.
* Educational and demonstration purposes.



