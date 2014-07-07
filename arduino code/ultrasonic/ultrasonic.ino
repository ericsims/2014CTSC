int echo0Pin = xxx, echo1Pin = xxx;
int trigPin = xxx;
int pwm0Pin = xxx, pwm1Pin = xxx, pwm2Pin = xxx, pwm3Pin = xxx, pwm4Pin = xxx;

void setup() {
  pinMode(pwm0Pin, OUTPUT);
  pinMode(pwm1Pin, OUTPUT);
  pinMode(pwm2Pin, OUTPUT);
  pinMode(pwm3Pin, OUTPUT);
  pinMode(pwm4Pin, OUTPUT);
  
  pinMode(echo0Pin, OUTPUT);
  pinMode(echo1Pin, OUTPUT);
  pinMode(trigPin, OUTPUT);
};

void loop() {
  long duration, distance;
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = (duration/2) / 29.1;
  Serial.print(distance);
  Serial.println(" cm");
  delay(500);
};
