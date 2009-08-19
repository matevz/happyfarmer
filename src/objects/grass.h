#ifndef GRASS_H_
#define GRASS_H_

#include "core/object.h"
#include <GL/gl.h>

class Grass : public Object {
public:
	Grass( Player*, const float&, const float&);
	virtual ~Grass();

	void draw( const unsigned long long& time );
	void rebuild();

private:
	static GLuint _texture;
	GLuint _dispList;
};

#endif /* GRASS_H_ */
