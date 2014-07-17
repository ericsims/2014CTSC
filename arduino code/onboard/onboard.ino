#include "Pwm.h"
#include "Ultrasonic.h"
#include "State.h"

const int statusPin = 13;


// TODO: fix pin numbers
const int ultrasonicTrigPin = 7,
ultrasonicEchoPin0 = 6,
ultrasonicEchoPin1 = 5;

const int minimumServoPos = 10, maximumServoPos = 170;
const boolean servoAdjust = false;

const int gainPin = 12, // servo outputs to flight computer
throttlePin = 11,
rollPin = 10,
pitchPin = 9,
yawPin = 8;
const int rollAdjustPin = 0, // analog inputs. 4,5 reserved for I2C
pitchAdjustPin = 1,
yawAdjustPin = 2;

Ultrasonic ultrasonicLeft;
State statusLed(statusPin);

Pwm gain, throttle, roll, pitch, yaw;

void setup() {
  Serial.begin(115200);

  gain.attach(gainPin);
  throttle.attach(gainPin);
  roll.attach(gainPin);
  pitch.attach(gainPin);
  yaw.attach(yawPin);

  homeControls();

  Serial.println("Status: Setup Complete");
  
  statusLed.set(State::good);
}

void loop() {
  statusLed.update();
  
  writeServo(&gain, 1);

  // TODO: include serial read/write commands
  // TODO: include relaying sensor values
}

void homeControls() {
  writeServo(&gain, 1);
  writeServo(&throttle, -1);
  writeServo(&roll, 0);
  writeServo(&pitch, 0);
  writeServo(&yaw, 0);
}

boolean writeServo(Pwm *servo, int value) { // value from -1 to 1
  if(servoAdjust) {
    switch(servo->getPin()) {
    case gainPin:
      break;
    case throttlePin:
      break;
    case rollPin:
      value += analogRead(rollAdjustPin)/(512)-1;
      break;
    case pitchPin:
      value += analogRead(pitchAdjustPin)/(512)-1;
      break;
    case yawPin:
      value += analogRead(yawAdjustPin)/(512)-1;
      break;
    default:
      Serial.println("error: servo pin not found");
    }
  }

  servo->write(value*(maximumServoPos-minimumServoPos)/4);
  return false;
}




