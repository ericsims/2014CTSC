#include <Servo.h>

int gainPin = 6,
  throttlePin = 10,
  rollPin = 11,
  pitchPin = 12,
  yawPin = 13;

Servo gain, throttle, roll, pitch, yaw;

void setup() {
  gain.attach(gainPin);
  throttle.attach(gainPin);
  roll.attach(gainPin);
  pitch.attach(gainPin);
  yaw.attach(yawPin);
  
  homeControls();
}

void loop() {
  gain.write(135);
}

void homeControls() {
  gain.write(170);
  throttle.write(10);
  gain.write(90);
  gain.write(90);
  gain.write(90);
}
