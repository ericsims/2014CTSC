class State {
public:
  State(int);
  int read();
  void set(int);
  void update();
  void update(int);
  enum states {fatal, good, NUM_OF_STATES};  
private:
  const int delays [NUM_OF_STATES][2] = {{0,1000}, {1500,50}};
  int state = 1;
  int statePin;
  long unsigned lastStateUpdate = 0;
  bool stateLightState = false;
};
