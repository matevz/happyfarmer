#ifndef PLANT_H_
#define PLANT_H_

#include "core/stationaryobject.h"
#include <GL/gl.h>

class Plant : public StationaryObject {
public:
	Plant( Player*, Tile* );
	virtual ~Plant();

	void draw( const unsigned long long& time );

private:
	void init();

	static GLuint _dispList;
};

#endif /* PLANT_H_ */
