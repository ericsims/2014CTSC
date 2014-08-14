#include "Ultrasonic.h"
#include <Arduino.h> 

static int echoPins[8];

int trigPin, echoPin;

int Ultrasonic::attach(int trigPinNew, int echoPinNew) {
  for(int i = 0; i < sizeof(echoPins)/sizeof(int); i++)
    if(echoPins[i] == echoPinNew)
      return -1;
  echoPin = echoPinNew;
  trigPin = trigPinNew;
  pinMode(echoPin, INPUT);
  pinMode(trigPin, OUTPUT);
  return echoPinNew;
}

double Ultrasonic::read() {
  long duration = 0, distance = 0;
  for(int avg = 0; avg < 10; avg++) {
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);
    duration = pulseIn(echoPin, HIGH, 80000);
    if(duration == 0)
      return 0;
    distance += (duration/2) / 29.1 / 10;
  }
  return distance;
}

int Ultrasonic::getEchoPin() {
  return echoPin;
}

