#ifndef HOUSE_H_
#define HOUSE_H_

#include "core/staticobject.h"
#include <osg/Node>

class House: public StaticObject {
public:
	House( Player*, Tile* );
	virtual ~House();

	void draw( const unsigned long long& time );

private:
	void init();

	static osg::ref_ptr<osg::Node> _node;
};

#endif /* HOUSE_H_ */
