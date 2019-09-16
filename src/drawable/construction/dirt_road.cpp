/*!
	Copyright (c) 2019, Matevž Jekovec, Happy Farmer development team
	All Rights Reserved. See AUTHORS for a complete list of authors.

	Licensed under the GNU GENERAL PUBLIC LICENSE. See COPYING for details.
*/

#include "drawable/construction/dirt_road.h"
#include "model/construction/dirt_road.h"
#include "model/resource.h"
#include "model/tile.h"

#include <iostream>

#include "model/game.h"

HFDConsDirtRoad::HFDConsDirtRoad( HFConsDirtRoad *road )
 : HFDrawable(road->tile()) {
	_back = new QGraphicsPixmapItem(HFResource::PIXMAP_DIRT_ROAD[HFTile::heightToString(road->tile()->height())+road->orientation()], this);
}

HFDConsDirtRoad::~HFDConsDirtRoad() {
	
}
