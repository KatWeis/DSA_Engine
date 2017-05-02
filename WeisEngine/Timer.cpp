#include "Timer.h"


//default constructor
Timer::Timer()
{
	prev = cur = clock();//make the prev and cur equal to the clock
	t = dt = fps = 0;//set all time variables to 0 at initialization
}

//default destructor
Timer::~Timer()
{

}

//updates the timer each frame
void Timer::update()
{
	prev = cur; //set previous equal to the current of last frame
	cur = clock(); //set current equal to the clock
	dt = (cur - prev) / (float)CLOCKS_PER_SEC; //determine the time between the last update and this one
	t += dt; //add dt to the total time since the timer started
	fps = 1 / dt; //find the framerate by dividing 1 second by the time it took to change a frame
}
