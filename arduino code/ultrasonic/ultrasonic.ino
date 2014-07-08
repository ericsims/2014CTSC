int echo0Pin = 3;//, echo1Pin = xxx;
int trigPin = 2;
//int pwm0Pin = xxx, pwm1Pin = xxx, pwm2Pin = xxx, pwm3Pin = xxx, pwm4Pin = xxx;

void setup() {
  Serial.begin(115200);
/*  pinMode(pwm0Pin, OUTPUT);
  pinMode(pwm1Pin, OUTPUT);
  pinMode(pwm2Pin, OUTPUT);
  pinMode(pwm3Pin, OUTPUT);
  pinMode(pwm4Pin, OUTPUT);*/
  
  pinMode(echo0Pin, INPUT);
//  pinMode(echo1Pin, OUTPUT);
  pinMode(trigPin, OUTPUT);
};

void loop() {
  long duration = 0, distance = 0;
  for(int avg = 0; avg < 10; avg++) {
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);
    duration = pulseIn(echo0Pin, HIGH);
    distance += (duration/2) / 29.1 / 10;
  }
  Serial.print(distance);
  Serial.println(" cm");
  delay(100);
};
