#include "core/time.h"

/*!
	\class Time
	This class is used to keep track of the game time and speed.
*/

Time::Time(unsigned long long passed)
 : _time(passed), _speedMultiplier(1) {
}

Time::~Time(){
}

void Time::pass(short delta){
	_time += static_cast<short>(delta * _speedMultiplier);

}
