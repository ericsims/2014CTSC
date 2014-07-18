#include <string>
#include "Cordinate.h"

typedef void (*ErrorCall)(std::string);
class Cv {
public:
	void debug();
	void locatePoint(Cordinate&, ErrorCall);
};
