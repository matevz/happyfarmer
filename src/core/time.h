/*Used to keep track of game time as well as speed.*/

#ifndef TIME_H_
#define TIME_H_

class Time {
public:
	Time();
	Time(unsigned long long passed);
	~Time();
	void pass(short delta);
	void import(unsigned long passed, float speedModifier);

private:
	unsigned long _passed;
	float _speedModifier;
};

#endif /* TIME_H_ */
