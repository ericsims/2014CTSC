#include <iostream>
#include <fstream>
#include <string>
using namespace std;

class Map {
public:
	Map();
	void write(string);
	int exitCleanly();
private:
	  ofstream cords;
};
