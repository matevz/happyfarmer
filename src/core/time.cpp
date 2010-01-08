#include "core/time.h"

Time::Time(){
	_passed = 0;
	_speedModifier = 1;
}

Time::Time(unsigned long passed){
	_passed = passed;
	_speedModifier = 1;
}

Time::~Time(){
	delete &_passed;
	delete &_speedModifier;
}

void Time::pass(short delta){
	_passed += delta * _speedModifier;

}

void Time::import(unsigned long passed, float speedModifier){
	_passed = passed;
	_speedModifier = speedModifier;
}
