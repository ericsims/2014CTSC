#include "Map.h"
#include <sstream>
using namespace std;

Map::Map() {
	cords.open("cordinates.log");
	cords << "x,y\n";
}

void Map::write(string str) {
	cords << str;
}

void Map::close() {
	cords.close();
}
