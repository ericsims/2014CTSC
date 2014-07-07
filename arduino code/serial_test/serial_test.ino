void setup() {
  Serial.begin(9600);
};

int i = 0;
void loop() {
  //Serial.write(Serial.read());
  Serial.print(i);
  //Serial.write(0);
  Serial.write(10);
  i++;
  if(i > 100)
    i = 0;
};
