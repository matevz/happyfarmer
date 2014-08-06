/*!
	Copyright (c) 2012, Matevž Jekovec, Happy Farmer development team
	All Rights Reserved. See AUTHORS for a complete list of authors.

	Licensed under the GNU GENERAL PUBLIC LICENSE. See COPYING for details.
*/

#include "drawable/animal/sheep.h"
#include "model/animal/sheep.h"
#include "model/resource.h"
#include "model/tile.h"

#include <iostream>

#include "model/game.h"

HFDObjSheep::HFDObjSheep( HFObjSheep *s )
 : HFDrawable(nullptr) {
	_front = new QGraphicsPixmapItem(HFResource::PIXMAP_SHEEP[0], this, nullptr);
}

HFDObjSheep::~HFDObjSheep() {
	
}