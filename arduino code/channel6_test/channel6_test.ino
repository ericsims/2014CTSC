void setup() {
  pinMode(13, OUTPUT);
}

void loop() {
  if(pulseIn(2, HIGH) > 2000)
    digitalWrite(13, HIGH);
  else
    digitalWrite(13, LOW);
}

