#include "core/stationaryobject.h"
#include "core/tile.h"
#include "core/point.h"

StationaryObject::StationaryObject( Player* owner, Tile* t )
 : Object(owner, t->getPoint1()->x, t->getPoint1()->y, t->getPoint1()->z) {
}

StationaryObject::StationaryObject( Player* owner, Tile* t, const float& z )
 : Object(owner, t->getPoint1()->x, t->getPoint1()->y, z) {
}

StationaryObject::~StationaryObject() {
}
