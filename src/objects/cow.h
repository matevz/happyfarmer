#ifndef COW_H_
#define COW_H_

#include "core/movingobject.h"
#include <GL/gl.h>

class Cow: public MovingObject {
public:
	Cow(  Player*, const float& x=0, const float& y=0 );
	~Cow();

	void draw( const unsigned long long& time );
	void update( const unsigned long long& time );

private:
	enum State {
		Stand = 0,
		Walk = 1
	};

	float _dx, _dy, _dz;
	State _state;
	static GLuint _dispList;
};

#endif /* COW_H_ */
