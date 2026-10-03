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
bool sweepForward = true; // the sensor will move from 0 degree to 180 degree, once it reaches there the statement will turn false and it will go back to 0 degree again 

unsigned long lastTime = 0;
unsigned int lastDistance = 0;
unsigned int distance;

void setup() {
  Serial.begin(9600);
  myServo.attach(servoPin);
  pinMode(trigPin, OUTPUT); // OUTPUT because it send out the signal
  pinMode(echoPin, INPUT); // INPUT because it receives the signal
  Serial.println("---- Arduino Ultrasonic Object Scanner ----");
  Serial.println("Format: [Angle °] [Distance cm] [Proximity] [Speed cm/s]");
}

long getDistance() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  long d = pulseIn(echoPin, HIGH, 30000);
  return d * 0.0343 / 2; // cm
}
// Object Proximity
String getProximityCategory(int dist) {
  if (dist < 20) return "NEAR";
  else if (dist < 50) return "MID";
  else return "FAR";
}

void loop() {
  unsigned long currentTime = millis(); // time measurement
  
  
  if (currentTime - lastTime >= scanDelay) {
    lastTime = currentTime;
  
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
    bool noEcho = false;
    distance = getDistance();
    if (distance == 0) {         // no echo received
      noEcho = true;
      distance = lastDistance;  // reuse the previous reading
    }

    // Speed calculation (cm/s)
    float speed = 0;
    if (lastDistance > 0) {
      speed = ((int)distance - (int)lastDistance) / (scanDelay / 1000.0); // distance change per second
    }
    lastDistance = distance;

    // Object proximity
    String proximity = noEcho ? "NO ECHO" : getProximityCategory(distance);

    // Print in clear format
    Serial.print("Angle: "); Serial.print(angle); Serial.print("° | ");
    Serial.print("Distance: "); Serial.print(distance); Serial.print(" cm | ");
    Serial.print("Proximity: "); Serial.print(proximity); Serial.print(" | ");
    Serial.print("Speed: "); Serial.print(speed, 2); Serial.println(" cm/s");
  }
}
