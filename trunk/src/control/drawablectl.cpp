/*!
	Copyright (c) 2012, Matevž Jekovec, Happy Farmer development team
	All Rights Reserved. See AUTHORS for a complete list of authors.

	Licensed under the GNU GENERAL PUBLIC LICENSE. See COPYING for details.
*/

#include "control/drawablectl.h"
#include "model/game.h"
#include "model/tile.h"
#include "model/construction.h"
#include "model/construction/road.h"

#include "drawable/drawable.h"

#include "drawable/helper/tile.h"

#include "drawable/terrain/grass.h"
#include "drawable/construction/road.h"

const QRect HFDrawableCtl::NO_SELECTION = QRect(0, 0, 0, 0);

HFDrawableCtl::HFDrawableCtl()
 : _selectionMode( HFDrawableCtl::None ), _selectionArea( HFDrawableCtl::NO_SELECTION ), _game( nullptr )
{
}

HFDrawableCtl::~HFDrawableCtl() {
}

void HFDrawableCtl::rebuildScene(HFGame *game) {
	_game = game;
	
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

void HFDrawableCtl::updateHelpers() {
	while (!_selectionHelpers.isEmpty()) {
		delete _selectionHelpers.takeFirst();
	}
	
	switch (_selectionMode) {
	case HorizontalVertical:
		for (int i=qMin(_selectionArea.x(), _selectionArea.right()); i<=qMax(_selectionArea.x(),_selectionArea.right()); i++) {
			for (int j=qMin(_selectionArea.y(), _selectionArea.bottom()); j<=qMax(_selectionArea.y(),_selectionArea.bottom()); j++) {
				HFTile *tile = _game->tileAt( i,j );
				HFDHelperTile *item = new HFDHelperTile( tile );
				_selectionHelpers << item;
				_scene.addItem(item);
				item->moveBy((tile->x()+tile->y())*128, (-tile->x()+tile->y())*64 - tile->z()*24 - item->childrenBoundingRect().height());
				item->setZValue( (-tile->x()+1+tile->y()+1)*64 );
			}
		}
		break;
	}

}