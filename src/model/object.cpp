/* 
 * File:   HFObject.cpp
 * Author: matevz
 * 
 * Created on Sreda, 6 avgust 2014, 21:05
 */

#include "model/object.h"

HFObject::HFObject( HFObjType t, QPointF pos )
 : _type(t), _x(pos.x()), _y(pos.y()) {
}

HFObject::HFObject(const HFObject& orig) {
}

HFObject::~HFObject() {
}
