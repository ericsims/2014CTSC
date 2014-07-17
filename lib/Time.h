#include <iostream>
#include <ctime>
#include <unistd.h>
#include <sys/time.h>

class Time {
	public:
		Time(bool);
		double getElapsed();
		double getPerSecond();
	private:
		timeval lastTime;
};
