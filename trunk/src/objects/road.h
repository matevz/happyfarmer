#ifndef ROAD_H_
#define ROAD_H_

#include "core/stationaryobject.h"
#include <GL/gl.h>

class Road : public StationaryObject {
public:
	Road( Player*, Tile* );
	virtual ~Road();

	void init();
	void rebuild();
	void draw( const unsigned long long& time );

private:
	GLuint genDispList( GLuint texture );

	GLuint *_dispList;

	static GLuint _texture258;
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

	static GLuint _dispList258;
	static GLuint _dispList456;
	static GLuint _dispList245;
	static GLuint _dispList256;
	static GLuint _dispList458;
	static GLuint _dispList568;
	static GLuint _dispList2456;
	static GLuint _dispList2458;
	static GLuint _dispList2568;
	static GLuint _dispList4568;
	static GLuint _dispList24568;
};

#endif /* ROAD_H_ */
