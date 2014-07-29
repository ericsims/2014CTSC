class State {
public:
  State(int);
  int read();
  void set(int);
  void update();
  void update(int);
  enum states {fatal, good, running, NUM_OF_STATES};  
private:
  int state;
  int statePin;
  long unsigned lastStateUpdate;
  bool stateLightState;
};
