/*!
	Copyright (c) 2012, Matevž Jekovec, Happy Farmer development team
	All Rights Reserved. See AUTHORS for a complete list of authors.

	Licensed under the GNU GENERAL PUBLIC LICENSE. See COPYING for details.
*/

#include "drawable/construction/road.h"
#include "model/construction/road.h"
#include "model/resource.h"
#include "model/tile.h"

#include <iostream>

#include "model/game.h"

HFDConsRoad::HFDConsRoad( HFConsRoad *road )
 : HFDrawable(road->tile()) {
	_back = new QGraphicsPixmapItem(HFResource::PIXMAP_ROAD[HFTile::heightToString(road->tile()->height())+road->orientation()], this);
}

HFDConsRoad::~HFDConsRoad() {
	
}
