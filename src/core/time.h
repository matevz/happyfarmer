/*Used to keep track of game time as well as speed.*/

#ifndef TIME_H_
#define TIME_H_

class Time {
public:
	Time();
	~Time();
	void pass(short delta);

    char getDay() const
    {
        return _day;
    }

    char getMonth() const
    {
        return _month;
    }

    char getYear() const
    {
        return _year;
    }

private:
	unsigned char _year;
	char _month;
	char _day;
	short _passed;
	char _speedModifier;
};

#endif /* TIME_H_ */
