#ifndef STATICOBJECT_H_
#define STATICOBJECT_H_

#include "core/object.h"

class Tile;
class Player;

class StaticObject: public Object {
public:
	StaticObject( Player* owner, Tile* t );
	StaticObject( Player* owner, Tile* t, const float& z );
	virtual ~StaticObject();
};

#endif /* STATICOBJECT_H_ */
