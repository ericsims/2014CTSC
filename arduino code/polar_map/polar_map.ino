#include <Servo.h> 
#include <math.h> 

int echo0Pin = 3;//, echo1Pin = xxx;
int trigPin = 2;

Servo table;

void setup() {
  Serial.begin(115200);

  table.attach(11);

  pinMode(echo0Pin, INPUT);
//  pinMode(echo1Pin, INPUT);
  pinMode(trigPin, OUTPUT);
};

void loop() {
  table.write(0);
  delay(5000);
  for(int angle = 0; angle <= 180; angle+=10){
    table.write(angle);
    delay(200);
    long duration = 0, distance = 0;
    for(int avg = 0; avg < 10; avg++) {
      digitalWrite(trigPin, LOW);
      delayMicroseconds(2);
      digitalWrite(trigPin, HIGH);
      delayMicroseconds(10);
      digitalWrite(trigPin, LOW);
      duration = pulseIn(echo0Pin, HIGH);
      distance += (duration/2) / 29.1 / 10;
      //delay(1);
    }
    Serial.print(round(distance * cos(((angle + 90) * 71.0) / 4068.0)));
    Serial.print(",");
    Serial.println(round(distance * sin(((angle + 90) * 71.0) / 4068.0)));
    //delay(250);
  }
};
