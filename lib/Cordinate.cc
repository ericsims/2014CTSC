#include "Cordinate.h"
#include <sstream>

string Cordinate::toString(){
	if(x && y) {
		ostringstream convert;
		convert << x << ',' << y;
		return convert.str();
	} else
		return("undef");
}

Cordinate::Cordinate(int newX, int newY) {
	x = newX;
	y = newY;
}
