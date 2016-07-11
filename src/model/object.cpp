/* 
 * File:   HFObject.cpp
 * Author: matevz
 * 
 * Created on Sreda, 6 avgust 2014, 21:05
 */

#include "model/object.h"

HFObject::HFObject( HFGame *game, HFObjType t, QVector3D pos )
 : _type(t), _pos(pos), _game(game) {
}

HFObject::HFObject(const HFObject& orig) {
}

HFObject::~HFObject() {
}
