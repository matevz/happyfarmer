#include "core/movingobject.h"

MovingObject::MovingObject( Player* p, const float& x, const float& y, const float& z )
 : Object(p,x,y,z) {
}

MovingObject::~MovingObject() {
}
