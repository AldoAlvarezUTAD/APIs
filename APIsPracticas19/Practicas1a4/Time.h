#pragma once
#include <time.h>

extern double deltaTime;

class Time
{
public:
	Time();
	~Time();


	void StartFrameTime();
	void EndFrameTime();

private:
	long startTime;
	long endTime;

	static long get_nanos(void) {
		struct timespec ts;
		timespec_get(&ts, TIME_UTC);
		return (long)ts.tv_sec * 1000000000L + ts.tv_nsec;
	}
};

