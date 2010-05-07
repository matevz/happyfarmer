#ifndef PLANT_H_
#define PLANT_H_

#include "core/staticobject.h"
#include <osg/Node>

class Plant : public StaticObject {
public:
	Plant( Player*, Tile* );
	virtual ~Plant();

	void draw( const unsigned long long& time );

private:
	void init();

	static osg::ref_ptr<osg::Node> _node;
};

#endif /* PLANT_H_ */
