#include "core/stationaryobject.h"
#include "core/tile.h"
#include "core/point3d.h"

StationaryObject::StationaryObject( Player* owner, Tile* t )
 : Object(owner, t->getPoint1()->getX(), t->getPoint1()->getY(), t->getPoint1()->getZ()) {
}

StationaryObject::StationaryObject( Player* owner, Tile* t, const float& z )
 : Object(owner, t->getPoint1()->getX(), t->getPoint1()->getY(), z) {
}

StationaryObject::~StationaryObject() {
}
