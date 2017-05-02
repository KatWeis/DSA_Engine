#pragma once
//header files
#include <ctime>

class Timer
{
private:
	clock_t cur;
	clock_t prev;

public:
	Timer();//default constructor
	~Timer();//default destructor

	//field
	float t;//time in seconds since starting/constructor
	float dt;//time in seconds btw the 2 most recent updates
	float fps;//measures 1/dt -- or ~# of updates per second

	void update();//update the timer every frame
};

