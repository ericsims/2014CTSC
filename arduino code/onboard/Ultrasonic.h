class Ultrasonic {
public:
  Ultrasonic(int, int);           // attach ananlogPins
  double read();                    // returns current pulse width as an angle between 0 and 180 degrees
  int getEchoPin();                  // return pin number
private:
  int trigPin, echoPin;
};

