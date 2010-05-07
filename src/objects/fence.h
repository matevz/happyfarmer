#ifndef FENCE_H_
#define FENCE_H_

#include "core/staticobject.h"
#include <osg/Node>
#include <vector>

class Fence : public StaticObject {
public:
	Fence( Player*, Tile* );
	virtual ~Fence();

	void rebuild();
	void draw( const unsigned long long& time );

private:
	void init();

	std::vector< osg::ref_ptr<osg::Node> > _nodes; // fence parts used in actual object

	static osg::ref_ptr<osg::Node>  _node;

	static osg::ref_ptr<osg::Node>  _node2; // top
	static osg::ref_ptr<osg::Node>  _node4; // right
	static osg::ref_ptr<osg::Node>  _node6; // left
	static osg::ref_ptr<osg::Node>  _node8; // bottom
};

#endif /* FENCE_H_ */
