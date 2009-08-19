#ifndef OBJECT_H_
#define OBJECT_H_

class Player;
class Model;

class Object {
public:
	Object( Player* owner, const float& x, const float& y );
	virtual ~Object();

	virtual void draw( const unsigned long long& time ) {};

protected:
	Player *_owner;
	float   _x;
	float   _y;
	float   _z;
};

#endif /* OBJECT_H_ */
