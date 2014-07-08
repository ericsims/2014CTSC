#include <Servo.h>

int gainPin

Servo gain;

void setup()
{
  gain.attach(gainPin);

}

void loop() {
  gain.write(135);
}

