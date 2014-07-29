#include <iostream>
#include <fstream>
#include <string>
using namespace std;

class Map {
public:
	Map();
	void close();
	void write(string);
private:
	  ofstream cords;
};
