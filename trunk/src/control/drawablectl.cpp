/*!
	Copyright (c) 2012, Matevž Jekovec, Happy Farmer development team
	All Rights Reserved. See AUTHORS for a complete list of authors.

	Licensed under the GNU GENERAL PUBLIC LICENSE. See COPYING for details.
*/

#include <control/drawablectl.h>
#include <model/game.h>
#include <model/tile.h>
#include <model/construction.h>
#include <model/construction/road.h>

#include <drawable/drawable.h>
#include <drawable/terrain/grass.h>
#include <drawable/construction/road.h>

HFDrawableCtl::HFDrawableCtl() {
}

HFDrawableCtl::~HFDrawableCtl() {
}

void HFDrawableCtl::rebuildTerrain(HFGame *game) {
	for (HFDrawable *drawable: _drawableTiles) {
		_scene.removeItem(drawable);
		delete drawable;
	}
	_drawableTiles.clear();
	
	for (int j=0; j<game->height(); j++) {
		for (int i=0; i<game->width(); i++) {
			rebuildTile( game->tileAt(i, j), false );
		}
	}
}

void HFDrawableCtl::rebuildTile(HFTile *tile, bool rebuildAdjacentTiles) {
	if (_drawableTiles[tile]) {
		delete _drawableTiles[tile];
		_drawableTiles.remove(tile);
	}
	
	HFDrawable *item = nullptr;
	if (!tile->construction()) {
		item = new HFDTerrGrass( tile );
	} else {
		switch (tile->construction()->consType()) {
			case HFConstruction::AsphaltRoad:
				item = new HFDConsRoad( static_cast<HFConsRoad*>(tile->construction()) );
				break;
		}
	}
	
	_drawableTiles[tile] = item;
	
	_scene.addItem(item);
	item->moveBy((tile->x()+tile->y())*128, (-tile->x()+tile->y())*64 - tile->z()*24 - item->childrenBoundingRect().height());
	item->setZValue( (-tile->x()+tile->y())*64 );
	
	if (rebuildAdjacentTiles) {
		HFTile *t;
		if (t=tile->game()->tileAt( tile->x()+1, tile->y() )) {
			rebuildTile( t, false );
		}
		if (t=tile->game()->tileAt( tile->x()-1, tile->y() )) {
			rebuildTile( t, false );
		}
		if (t=tile->game()->tileAt( tile->x(), tile->y()+1 )) {
			rebuildTile( t, false );
		}
		if (t=tile->game()->tileAt( tile->x(), tile->y()-1 )) {
			rebuildTile( t, false );
		}
	}
}