#ifndef FENCE_H_
#define FENCE_H_

#include "core/stationaryobject.h"
#include <GL/gl.h>
#include <vector>

class Fence: public StationaryObject {
public:
	Fence( Player*, Tile* );
	virtual ~Fence();

	void rebuild();
	void draw( const unsigned long long& time );

private:
	std::vector<GLuint> _dispLists; // fence parts used in actual object

	static GLuint _dispList;

	static GLuint _dispList2; // top
	static GLuint _dispList4; // right
	static GLuint _dispList6; // left
	static GLuint _dispList8; // bottom
};

#endif /* FENCE_H_ */
