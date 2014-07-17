#include "Time.h"

Time::Time(bool start) {
	if(start)
		gettimeofday(&lastTime, 0);
}

double Time::getElapsed() {
	timeval now;
	long seconds, useconds;

	gettimeofday(&now, NULL);

	seconds  = now.tv_sec  - lastTime.tv_sec;
	useconds = now.tv_usec - lastTime.tv_usec;

	double elapsed = seconds + useconds/1000000.0;

	lastTime = now;

	return elapsed;
}

double Time::getPerSecond() {
	return 1.0/getElapsed();
}
