/*!
	Copyright (c) 2012, Matevž Jekovec, Happy Farmer development team
	All Rights Reserved. See AUTHORS for a complete list of authors.

	Licensed under the GNU GENERAL PUBLIC LICENSE. See COPYING for details.
*/

#include <drawable/helper/tile.h>
#include <model/resource.h>
#include <model/tile.h>

#include <iostream>

#include "model/game.h"

HFDHelperTile::HFDHelperTile( HFTile *tile )
 : HFDrawable(tile) {
	_back = new QGraphicsPixmapItem(HFResource::PIXMAP_HELPERTILE[HFTile::heightToString(tile->height())], this, nullptr);
}

HFDHelperTile::~HFDHelperTile() {
	
}