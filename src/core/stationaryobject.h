#ifndef STATIONARYOBJECT_H_
#define STATIONARYOBJECT_H_

#include "core/object.h"

class Tile;
class Player;

class StationaryObject: public Object {
public:
	StationaryObject( Player* owner, Tile* t );
	StationaryObject( Player* owner, Tile* t, const float& z );
	virtual ~StationaryObject();
};

#endif /* STATIONARYOBJECT_H_ */
