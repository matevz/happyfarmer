/*!
	Copyright (c) 2019, Matevž Jekovec, Happy Farmer development team
	All Rights Reserved. See AUTHORS for a complete list of authors.

	Licensed under the GNU GENERAL PUBLIC LICENSE. See COPYING for details.
*/

#include "model/construction/dirt_road.h"
#include "model/game.h"

HFConsDirtRoad::HFConsDirtRoad(HFTile *tile)
: HFConstruction( DirtRoad, tile ) {
	calculateOrientation();
}

HFConsDirtRoad::~HFConsDirtRoad() {
}
