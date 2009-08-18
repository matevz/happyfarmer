#ifndef TRACTOR_H_
#define TRACTOR_H_

#include "core/object.h"
#include <GL/gl.h>

class Tractor : public Object {
public:
	Tractor( Player*, const float& x=0, const float& y=0 );
	virtual ~Tractor();

	void draw();
	void update( int time );
private:
	GLuint _dispList;
};

#endif /* TRACTOR_H_ */
