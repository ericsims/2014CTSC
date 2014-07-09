#include <Servo.h>

const int minimumServoPos = 10, maximumServoPos = 170;
const boolean servoAdjust = false;

int gainPin = 6, // servo outputs to flight computer
  throttlePin = 10,
  rollPin = 11,
  pitchPin = 12,
  yawPin = 13;
int rollAdjustPin = 0, // analog inputs. 4,5 reserved for I2C
  pitchAdjustPin = 1,
  yawAdjustPin = 2;

Servo gain, throttle, roll, pitch, yaw;

void setup() {
  Serial.begin(115200);
  
  gain.attach(gainPin);
  throttle.attach(gainPin);
  roll.attach(gainPin);
  pitch.attach(gainPin);
  yaw.attach(yawPin);
  
  homeControls();
  
  Serial.println("Status: Setup Complete");
}

void loop() {
  //gain.write(135); //manual method...
  writeServo(gain, 1);
}

void homeControls() {
  /*gain.write(170); //manual method...
  throttle.write(10);
  roll.write(90);
  pitch.write(90);
  yaw.write(90);*/
  
  writeServo(gain, 1);
  writeServo(throttle, -1);
  writeServo(roll, 0);
  writeServo(pitch, 0);
  writeServo(yaw, 0);
}

boolean writeServo(Servo *servo, int value) { // value from -1 to 1
  if(servoAdjust) {
    switch(servo->getPin()) {
      case gainPin:
      break;
      case throttlePin:
      break;
      case rollPin:
        value += analogRead(rollAdjustPin)/(512)-1
      break;
      case pitchPin:
        value += analogRead(pitchAdjustPin)/(512)-1
      break;
      case yawPin:
        value += analogRead(yawAdjustPin)/(512)-1
      break;
      default:
      Serial.println("error: servo pin not found");
    }
  }
  
  Serial.print("servo pin: ");
  Serial.println(servo->getPin());
  
  servo->write(value*(maximumServoPos-minimumServoPos)/4);
  return false;
}
