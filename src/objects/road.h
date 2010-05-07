#ifndef ROAD_H_
#define ROAD_H_

#include "core/staticobject.h"
#include <osg/Node>

class Road : public StaticObject {
public:
	Road( Player*, Tile* );
	virtual ~Road();

	void init();
	void rebuild();
	void draw( const unsigned long long& time );

private:
/*	GLuint genDispList( GLuint texture );
*/
	osg::ref_ptr<osg::Node> _node;

/*	static GLuint _texture258;
	static GLuint _texture456;
	static GLuint _texture245;
	static GLuint _texture256;
	static GLuint _texture458;
	static GLuint _texture568;
	static GLuint _texture2456;
	static GLuint _texture2458;
	static GLuint _texture2568;
	static GLuint _texture4568;
	static GLuint _texture24568;

	static GLuint _node258;
	static GLuint _node456;
	static GLuint _node245;
	static GLuint _node256;
	static GLuint _node458;
	static GLuint _node568;
	static GLuint _node2456;
	static GLuint _node2458;
	static GLuint _node2568;
	static GLuint _node4568;
	static GLuint _node24568;*/
};

#endif /* ROAD_H_ */
