#include "Ultrasonic.h"
#include <Arduino.h> 


Ultrasonic::Ultrasonic(int trigPinNew, int echoPinNew) {
  echoPin = echoPinNew;
  trigPin = trigPinNew;
  pinMode(echoPin, INPUT);
  pinMode(trigPin, OUTPUT);
}

double Ultrasonic::read() {
  long duration = 0, distance = 0;
  for(int avg = 0; avg < 4; avg++) {
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);
    duration = pulseIn(echoPin, HIGH, 20000);
    if(duration == 0)
      return 0;
    distance += (duration/2) / 29.1 / 4;
  }
  return distance;
}

int Ultrasonic::getEchoPin() {
  return echoPin;
}
