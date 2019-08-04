/*!
	Copyright (c) 2012-2019, Matevž Jekovec, Happy Farmer development team
	All Rights Reserved. See AUTHORS for a complete list of authors.

	Licensed under the GNU GENERAL PUBLIC LICENSE. See COPYING for details.
*/

#include "model/construction/asphalt_road.h"
#include "model/game.h"

HFConsAsphaltRoad::HFConsAsphaltRoad(HFTile *tile)
 : HFConstruction( AsphaltRoad, tile ) {
	calculateOrientation();
}

HFConsAsphaltRoad::~HFConsAsphaltRoad() {
}
