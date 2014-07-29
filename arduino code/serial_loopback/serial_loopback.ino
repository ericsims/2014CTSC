void setup() {
  Serial.begin(9600);     // opens serial port, sets data rate to 9600 bps
}

void loop() {
  if (Serial.available() > 0) {
    //char incomingByte = Serial.read();
    int val = Serial.parseInt();
    Serial.print(val);
  }
}

