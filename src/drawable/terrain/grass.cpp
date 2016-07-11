/*!
	Copyright (c) 2012, Matevž Jekovec, Happy Farmer development team
	All Rights Reserved. See AUTHORS for a complete list of authors.

	Licensed under the GNU GENERAL PUBLIC LICENSE. See COPYING for details.
*/

#include <drawable/terrain/grass.h>
#include <model/terrain/grass.h>
#include <model/resource.h>

HFDTerrGrass::HFDTerrGrass( HFTile *tile )
 : HFDrawable(tile) {
	QString combination;
	for (int i=0; i<4; i++) {
		combination += QString::number(tile->height()[i]);
	}
	
	_back = new QGraphicsPixmapItem(HFResource::PIXMAP_GRASS[combination], this);
}

HFDTerrGrass::~HFDTerrGrass() {
	
}
