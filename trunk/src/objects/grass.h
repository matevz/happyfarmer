#ifndef GRASS_H_
#define GRASS_H_

#include "core/staticobject.h"
#include <osg/Node>

class Grass : public StaticObject {
public:
	Grass( Player*, Tile* );
	virtual ~Grass();

	void init();
	void rebuild();
	void draw( const unsigned long long& time );

private:
	//static GLuint _texture;
	osg::ref_ptr<osg::Node> _node;
};

#endif /* GRASS_H_ */
