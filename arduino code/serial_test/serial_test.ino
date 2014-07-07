void setup() {
  Serial.begin(115200);
  pinMode(13,OUTPUT);
};

int i = 0;
void loop() {
  if (Serial.available() > 0) {
    byte incomingByte = Serial.read();
    Serial.println(incomingByte, DEC);
    if(incomingByte == 97) {
      digitalWrite(13, HIGH);
    } else {
      digitalWrite(13, LOW);
    }
  }
  Serial.println(i);
  //Serial.write(0);
  //Serial.write(10);
  i++;
  if(i > 99) {
    i = 0;
  }
  delay(100);
};
