#include "core/object.h"
#include "models/model.h"

Object::Object( Player *p, const float& x, const float& y )
 : _owner(p), _x(x), _y(y) {
}

Object::~Object() {
}
