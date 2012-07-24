/*!
	Copyright (c) 2012, Matevž Jekovec, Happy Farmer development team
	All Rights Reserved. See AUTHORS for a complete list of authors.

	Licensed under the GNU GENERAL PUBLIC LICENSE. See COPYING for details.
*/

#include <drawable/terrain/grass.h>
#include <model/resource.h>

HFDTerrGrass::HFDTerrGrass()
 : HFDrawable() {
	_back = new QGraphicsPixmapItem(*HFResource::PIXMAP_GRASS_256, this, nullptr);
}

HFDTerrGrass::~HFDTerrGrass() {
	
}