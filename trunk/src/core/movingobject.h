#ifndef MOVINGOBJECT_H_
#define MOVINGOBJECT_H_

#include "core/object.h"

class MovingObject: public Object {
public:
	MovingObject( Player*, const float& x, const float& y, const float& z );
	virtual ~MovingObject();

	virtual void update( const unsigned long long& time ) {};
};

#endif /* MOVINGOBJECT_H_ */
