#ifndef ECONOMY_H_
#define ECONOMY_H_

class Economy {
public:
	Economy(Time *timekeeper);
	~Economy();
	void pass();

private:
	Time *_timekeeper;
};

#endif /* ECONOMY_H_ */
