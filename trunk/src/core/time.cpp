#include "core/time.h"

Time::Time(){
	_day = 0;
	_month = 0;
	_year = 0;
	_passed = 0;
	_speedModifier = 0;
}

Time::~Time(){

}

void Time::pass(short delta){
	_passed += delta * (short)_speedModifier;
	_day += _passed/1650;
	_passed %= 1650;
}
