#include "State.h"
#include <Arduino.h> 
const static int delays [2][2] = {
  {
    0,1000      }
  , {
    1500,50      }
};
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
    if (millis() - lastStateUpdate >= delays[state][(int)stateLightState]) {
      lastStateUpdate = millis();
      stateLightState = !stateLightState;
      digitalWrite(statePin, stateLightState);
    }
  } else lastStateUpdate = millis();
}

int State::read() {
  return state;
}

void State::set(int newState) {
  state = newState;
}



