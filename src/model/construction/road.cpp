/*!
	Copyright (c) 2012, Matevž Jekovec, Happy Farmer development team
	All Rights Reserved. See AUTHORS for a complete list of authors.

	Licensed under the GNU GENERAL PUBLIC LICENSE. See COPYING for details.
*/

#include <model/construction/road.h>

#include "model/game.h"

HFConsRoad::HFConsRoad(HFTile *tile)
 : HFConstruction( AsphaltRoad, tile ) {
	calculateOrientation();
}

HFConsRoad::~HFConsRoad() {
}
