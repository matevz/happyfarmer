#ifndef TRACTOR_H_
#define TRACTOR_H_

#include "core/movingobject.h"
#include <osg/Node>

class Tractor : public MovingObject {
public:
	Tractor( Player*, const float& x=0, const float& y=0 );
	virtual ~Tractor();

	void draw( const unsigned long long& time );
	void update( const unsigned long long& time );

	float dX;
	float dY;
private:
	static osg::ref_ptr<osg::Node> _node;
};

#endif /* TRACTOR_H_ */
