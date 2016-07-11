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

QList<HFObject*> HFObjectCtl::place(HFObject::HFObjType type, const QRect& selectionArea) {
	QList<HFObject*> placedObjects;
	
	switch (type) {
	case HFObject::AnimalSheep:
		for (int i=qMin(selectionArea.x(), selectionArea.right()); i<=qMax(selectionArea.x(),selectionArea.right()); i++) {
			for (int j=qMin(selectionArea.y(), selectionArea.bottom()); j<=qMax(selectionArea.y(),selectionArea.bottom()); j++) {
				HFTile *tile = _game->tileAt(i,j);
				if (tile) {
					if (check(type, tile)) {
						HFObject *placedObj = place(type, tile);
						placedObjects << placedObj;
					}
				}
			}
		}
		break;
	}
	
	return placedObjects;
}

HFObject* HFObjectCtl::place(HFObject::HFObjType type, HFTile* tile) {
	HFObject* obj = nullptr;
	
	switch (type) {
		case HFObject::AnimalSheep:
			if (check(type, tile)) {
				obj = new HFObjSheep(_game, QVector3D(tile->x(), tile->y(), tile->z()));
				tile->addObject(obj);
			}
			break;
	}
	
	return obj;
}

bool HFObjectCtl::check(HFObject::HFObjType type, const HFTile* tile) {
	if (!tile) {
		return false;
	}
	
	// if objects are already on the tile, new objects cannot be placed there
	if (tile->objects().size()) {
		return false;
	}		

	switch (type) {
		case HFObject::AnimalSheep:
			return true;
	}
	
	return false;
}
