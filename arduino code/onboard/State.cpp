#include "State.h"
#include <Arduino.h> 

State::State(int pin) {
  statePin = pin;
  pinMode(pin, OUTPUT);
  digitalWrite(pin, LOW);
}

void State::update(int newState) {
  set(newState);
  update();
}

void State::update() {
  if(lastStateUpdate) {
    if (stateLightState) {
      if (millis() - lastStateUpdate >= delays[state][1]) {
        digitalWrite(statePin, LOW);
        stateLightState = false;
        lastStateUpdate = millis();
      }
    } 
    else {
      if (millis() - lastStateUpdate >= delays[state][0]) {
        digitalWrite(statePin, HIGH);
        stateLightState = true;
        lastStateUpdate = millis();
      }
    }
  } else {
    lastStateUpdate = millis();
  }
}

int State::read() {
  return state;
}

void State::set(int newState) {
  state = newState;
}
