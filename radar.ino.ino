#include <Servo.h>

Servo myServo;

const int servoPin = 9;
const int trigPin = 10;
const int echoPin = 11;

const int sweepStart = 0;
const int sweepEnd = 180;
const int step = 5;
const unsigned long scanDelay = 4000; // time taken to scan

int angle = 0;
bool sweepForward = true; // the sensor will move from 0 degree to 180 degree, once it reaches there the stament will turn false and it will go back to 0 degree again 

unsigned long lastTime = 0;
unsigned int lastDistance = 0;
unsigned long duration;
unsigned int distance;

void setup() {
  Serial.begin(9600);
  myServo.attach(9);
  pinMode(trigPin, OUTPUT); // OUTPUT because it send out the signal
  pinMode(echoPin, INPUT); // INPUT because it recieves the signal
  Serial.println("---- Arduino Radar System ----");
  Serial.println("Format: [Angle °] [Distance cm] [Size] [Speed cm/s]");
}

long getDistance() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  long d = pulseIn(echoPin, HIGH);
  return d * 0.034 / 2; // cm
}
// Object Size
String getObjectSize(int dist) {
  if (dist < 20) return "NARROW";
  else if (dist < 50) return "MEDIUM";
  else return "WIDE";
}

void loop() {
  unsigned long currentTime = millis(); // time measurement
  
  
  if (currentTime - lastTime >= scanDelay) {
    lastTime = currentTime;
  }
    // Sweep servo
    if (sweepForward) {
      angle += step;
      if (angle >= sweepEnd) sweepForward = false;
    } else {
      angle -= step;
      if (angle <= sweepStart) sweepForward = true;
    }

    myServo.write(angle);

    // Measure distance
    distance = getDistance();
    if (distance == 0) distance = lastDistance; // ignore zero readings

    // Speed calculation (cm/s)
    float speed = 0;
    if (lastDistance > 0) {
      speed = (distance - lastDistance) / (scanDelay / 1000.0); // distance change per second
    }
    lastDistance = distance;

    // Object size
    String size = getObjectSize(distance);

    // Print in clear format
    Serial.print("Angle: "); Serial.print(angle); Serial.print("° | ");
    Serial.print("Distance: "); Serial.print(distance); Serial.print(" cm | ");
    Serial.print("Size: "); Serial.print(size); Serial.print(" | ");
    Serial.print("Speed: "); Serial.print(speed, 2); Serial.println(" cm/s");
  }

