/*!
	Copyright (c) 2012, Matevž Jekovec, Happy Farmer development team
	All Rights Reserved. See AUTHORS for a complete list of authors.

	Licensed under the GNU GENERAL PUBLIC LICENSE. See COPYING for details.
*/

#include "control/objectctl.h"

#include "model/game.h"
#include "model/tile.h"
#include "model/animal/sheep.h"

#include <iostream>

HFObjectCtl::HFObjectCtl( HFGame *g )
 : _game(g) {
}

HFObjectCtl::~HFObjectCtl() {
}

HFObject* HFObjectCtl::place(HFObject::HFObjType type, const HFTile* tile) {
	HFObject* obj = nullptr;
	
	switch (type) {
		case HFObject::AnimalSheep:
			if (check(type, tile)) {
				obj = new HFObjSheep(QPointF(tile->x(), tile->y()));
				tile->objects() << obj;
			}
	}
	
	return obj;
}

bool HFObjectCtl::check(HFObject::HFObjType type, HFTile* tile) {
	if (!tile) {
		return false;
	}
	
	// if construction already exists, new construction cannot be placed on the same tile
	if (tile->objects().size()) {
		return false;
	}		

	switch (type) {
		case HFObject::AnimalSheep:
			return true;
	}
	
	return false;
}
