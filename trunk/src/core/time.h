#ifndef TIME_H_
#define TIME_H_

class Time {
public:
	Time(unsigned long long passed=0);
	~Time();

	float getSpeed() { return _speedMultiplier; }
	void setSpeed( float s ) { _speedMultiplier = s; }
	unsigned long long getTime() { return _time; }
	void setTime( unsigned long long time ) { _time = time; }

private:
	void pass(short delta);

	unsigned long long _time;
	float _speedMultiplier;
};

#endif /* TIME_H_ */
