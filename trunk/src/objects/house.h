#ifndef HOUSE_H_
#define HOUSE_H_

#include "core/stationaryobject.h"
#include <GL/gl.h>

class House: public StationaryObject {
public:
	House( Player*, Tile* );
	virtual ~House();

	void draw( const unsigned long long& time );

private:
	void init();

	static GLuint _dispList;
};

#endif /* HOUSE_H_ */
