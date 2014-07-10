class Ultrasonic {
public:
  int attach(int echoTrig, int echoEcho);           // attach ananlogPin, returns pin if successful, -1 if unsuccessful
  double read();                    // returns current pulse width as an angle between 0 and 180 degrees
  int getEchoPin();                  // return pin number
};
