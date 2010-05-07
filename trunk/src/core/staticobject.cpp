#include "core/staticobject.h"
#include "core/tile.h"
#include "core/point.h"

StaticObject::StaticObject( Player* owner, Tile* t )
 : Object(owner, t->getPoint1()->x, t->getPoint1()->y, t->getPoint1()->z) {
}

StaticObject::StaticObject( Player* owner, Tile* t, const float& z )
 : Object(owner, t->getPoint1()->x, t->getPoint1()->y, z) {
}

StaticObject::~StaticObject() {
}
