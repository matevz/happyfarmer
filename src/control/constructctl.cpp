/*!
	Copyright (c) 2012, Matevž Jekovec, Happy Farmer development team
	All Rights Reserved. See AUTHORS for a complete list of authors.

	Licensed under the GNU GENERAL PUBLIC LICENSE. See COPYING for details.
*/

#include "control/constructctl.h"

#include "model/game.h"
#include "model/tile.h"
#include "model/construction/asphalt_road.h"
#include "model/construction/dirt_road.h"

#include <iostream>

HFConstructCtl::HFConstructCtl( HFGame *g )
 : _game(g) {
}

HFConstructCtl::~HFConstructCtl() {
}

QList<HFTile*> HFConstructCtl::place(HFConstruction::HFConsType type, const QRect& selectionArea) {
	QList<HFTile*> placedTiles;
	
	switch (type) {
	case HFConstruction::AsphaltRoad:
	case HFConstruction::DirtRoad:
		for (int i=qMin(selectionArea.x(), selectionArea.right()); i<=qMax(selectionArea.x(),selectionArea.right()); i++) {
			for (int j=qMin(selectionArea.y(), selectionArea.bottom()); j<=qMax(selectionArea.y(),selectionArea.bottom()); j++) {
				HFTile *tile = _game->tileAt(i,j);
				if (tile) {
					if (check(type, tile)) {
						place(type, tile);
						placedTiles << tile;
					}
				}
			}
		}
		break;
	}
	
	return placedTiles;
}

bool HFConstructCtl::check(HFConstruction::HFConsType type, HFTile* tile) {
	if (!tile) {
		return false;
	}
	
	// if construction already exists, new construction cannot be placed on the same tile
	if (tile->construction()) {
		return false;
	}		


	switch (type) {
		case HFConstruction::AsphaltRoad:
		case HFConstruction::DirtRoad:
			int *height = tile->height();
			
			// correct tile only, if adjacent two vertices are of different heights or the tile is completely flat
			bool anomaly = false;
			for (int i=0; i<4; i++) {
				if (height[i]==1) {
					anomaly = true;
					if (height[(i+1)%4]==1 && height[(i+2)%4]==0 && height[(i+3)%4]==0) {
						return true;
					}
				}
			}
			return (!anomaly);
			break;
	}
}

bool HFConstructCtl::place(HFConstruction::HFConsType type, HFTile* tile) {
	if (!check(type, tile)) {
		return false;
	}
	
	HFConstruction *construction = nullptr;
	
	switch (type) {
		case HFConstruction::AsphaltRoad:
			construction = new HFConsAsphaltRoad(tile);
			break;
		case HFConstruction::DirtRoad:
			construction = new HFConsDirtRoad(tile);
			break;
	}
	
	
	if (construction) {
		tile->setConstruction( construction );
		HFTile *t;
		if ((t=tile->game()->tileAt( tile->x()+1, tile->y() )) && t->construction()) {
			t->construction()->calculateOrientation();
		}
		if ((t=tile->game()->tileAt( tile->x()-1, tile->y() )) && t->construction()) {
			t->construction()->calculateOrientation();
		}
		if ((t=tile->game()->tileAt( tile->x(), tile->y()+1 )) && t->construction()) {
			t->construction()->calculateOrientation();
		}
		if ((t=tile->game()->tileAt( tile->x(), tile->y()-1 )) && t->construction()) {
			t->construction()->calculateOrientation();
		}
		return true;
	}
	
	return false;
}
