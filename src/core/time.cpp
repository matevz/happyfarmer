#include "core/time.h"

Time::Time(){
	_day = 0;
	_month = 0;
	_year = 0;
	_passed = 0;
	_speedModifier = 0;
}

Time::~Time(){
	delete &_day;
	delete &_month;
	delete &_year;
	delete &_passed;
	delete &_speedModifier;
}

void Time::pass(short delta){
	_passed += delta * (short)_speedModifier;
	_day += _passed/1650;
	_passed %= 1650;
}

void Time::import(unsigned char year, char month, char day, char speedmodifier){
	_year = year;
	_month = month;
	_day = day;
	_speedModifier = speedmodifier;
}
