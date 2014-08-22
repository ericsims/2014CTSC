#include <iostream>
#include <fstream>
#include <string>
using namespace std;

class Map {
public:
	Map();
	void write(string);
	void exitCleanly();
private:
	  ofstream cords;
};
