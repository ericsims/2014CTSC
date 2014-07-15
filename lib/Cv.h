#include "Cordinate.h"
typedef void (*PointCallback)(Cordinate);
typedef void (*UndefCallback)();
class Cv {
public:
	void debug();
	void locatePoint(PointCallback, UndefCallback);
};
