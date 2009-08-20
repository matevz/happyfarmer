#ifndef GRASS_H_
#define GRASS_H_

#include "core/stationaryobject.h"
#include <GL/gl.h>

class Grass : public StationaryObject {
public:
	Grass( Player*, Tile* );
	virtual ~Grass();

	void init();
	void rebuild();
	void draw( const unsigned long long& time );

private:
	static GLuint _texture;
	GLuint _dispList;
};

#endif /* GRASS_H_ */
