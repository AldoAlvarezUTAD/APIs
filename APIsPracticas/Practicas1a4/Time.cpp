#include "Time.h"

double deltaTime;

Time::Time()
{
	//deltaTime = 0.002f;
}


Time::~Time()
{
}

void Time::StartFrameTime()
{
	startTime = get_nanos();
}

void Time::EndFrameTime()
{
	endTime = get_nanos();
	deltaTime = (endTime - startTime)/1000000000.0f;
}
