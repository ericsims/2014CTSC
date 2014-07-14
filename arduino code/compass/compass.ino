#include <Wire.h>

void setup() {
  Wire.begin();
  Serial.begin(115200);
}

void loop() {
  Wire.beginTransmission(0x3C);
  Wire.write(0x1E);
  Wire.endTransmission();

  Wire.requestFrom(0x3D,8);
  long a = Wire.read();
  long b = Wire.read();
  long c = Wire.read();
  long d = Wire.read();
  long e = Wire.read();
  long f = Wire.read();
  long g = Wire.read();
  long h = Wire.read();
  Serial.print(a);
  Serial.print(b);
  Serial.print(c);
  Serial.print(d);
  Serial.print(e);
  Serial.print(f);
  Serial.print(g);
  Serial.println(h);

  delay(200);
}



