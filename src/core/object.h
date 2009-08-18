#ifndef OBJECT_H_
#define OBJECT_H_

class Player;
class Model;

class Object {
public:
	Object( Player*, const float& x, const float& y );
	virtual ~Object();

	virtual void draw() {};
	virtual void update( int time ) {};

protected:
	Player *_owner;
	float   _x;
	float   _y;
	float   _z;
};

#endif /* OBJECT_H_ */
