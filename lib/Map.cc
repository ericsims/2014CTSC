#include "Map.h"
#include <sstream>
#include <ctime>
using namespace std;

Map::Map() {
	time_t now = time(0);
	tm *ltm = localtime(&now);

	ostringstream fileNameStream;
	fileNameStream << "logs/";
	fileNameStream << (1900 + ltm->tm_year);
	fileNameStream << " " << (1 + ltm->tm_mon);
	fileNameStream << " " << (ltm->tm_mday);
	fileNameStream << " "<< (1 + ltm->tm_hour) << ":" << (1 + ltm->tm_min) << ":" << (1 + ltm->tm_sec);
	fileNameStream << '\0';
	const char* fileName = fileNameStream.str().c_str();
	cout << fileName << endl;
	cords.open(fileName);
	//cords << "x,y\n";
}

void Map::write(string str) {
	//cords << str;
}

void Map::exitCleanly() {
	cords.close();
}
