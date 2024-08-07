/*!
	Copyright (c) 2012, Matevž Jekovec, Happy Farmer development team
	All Rights Reserved. See AUTHORS for a complete list of authors.

	Licensed under the GNU GENERAL PUBLIC LICENSE. See COPYING for details.
*/

#include "control/drawablectl.h"
#include "model/game.h"
#include "model/tile.h"
#include "model/construction.h"
#include "model/construction/asphalt_road.h"
#include "model/construction/dirt_road.h"
#include "model/object.h"
#include "model/animal/sheep.h"

#include "drawable/drawable.h"
#include "drawable/helper/tile.h"
#include "drawable/helper/dot.h"
#include "drawable/terrain/grass.h"
#include "drawable/construction/asphalt_road.h"
#include "drawable/construction/dirt_road.h"
#include "drawable/animal/sheep.h"
#include "gameview.h"

#include <QDebug>

const QRect HFDrawableCtl::NO_SELECTION = QRect(0, 0, 0, 0);

HFDrawableCtl::HFDrawableCtl()
 : _game( nullptr ),
   _selectionMode( None ), _selectionTileArea( NO_SELECTION ), _selectionDotArea( NO_SELECTION )
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
				item = new HFDConsAsphaltRoad( static_cast<HFConsAsphaltRoad*>(tile->construction()) );
				break;
			case HFConstruction::DirtRoad:
				item = new HFDConsDirtRoad( static_cast<HFConsDirtRoad*>(tile->construction()) );
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
	
	QList<HFObject*> objects = tile->objects(); // make a copy
	for (int i=0; i<objects.size(); i++) {
		HFObject *obj = objects[i];
		HFDrawable *dObj = nullptr;
		
		if (_drawableObjects[obj]) {
			delete _drawableObjects[obj];
			_drawableObjects.remove(obj);
		}
		
		switch (obj->objType()) {
			case HFObject::AnimalSheep:
				dObj = new HFDObjSheep(static_cast<HFObjSheep*>(obj));
				break;
		}
		
		_scene.addItem(dObj);
		_drawableObjects[obj] = dObj;
		
		dObj->moveBy((obj->x()+obj->y())*128, (-obj->x()+obj->y())*64 - obj->z()*24 - dObj->childrenBoundingRect().height());
		dObj->setZValue( (-obj->x()+obj->y())*64 );
	}
}

void HFDrawableCtl::updateHelpers() {
	while (!_selectionHelpers.isEmpty()) {
		delete _selectionHelpers.takeFirst();
	}
	
	switch (_selectionMode) {
	case None:
		break;
	case HorizontalVertical:
	case Rectangular:
		for (int i=qMin(_selectionTileArea.x(), _selectionTileArea.right()); i<=qMax(_selectionTileArea.x(),_selectionTileArea.right()); i++) {
			for (int j=qMin(_selectionTileArea.y(), _selectionTileArea.bottom()); j<=qMax(_selectionTileArea.y(),_selectionTileArea.bottom()); j++) {
				HFTile *tile = _game->tileAt( i,j );
				HFDHelperTile *item = new HFDHelperTile( tile );
				_selectionHelpers << item;
				_scene.addItem(item);
				item->moveBy((tile->x()+tile->y())*128, (-tile->x()+tile->y())*64 - tile->z()*24 - item->childrenBoundingRect().height());
				item->setZValue( (-tile->x()+1+tile->y()+1)*64 );
			}
		}
		break;
	case Dot: {
		HFTile *tile = _game->tileAt( _selectionDotArea.x(), _selectionDotArea.y() );
		qDebug() << "HFDrawableCtl::updateHelpers() _selectionDotArea:" << _selectionDotArea;
		if (tile) {
			HFDHelperDot *item = new HFDHelperDot( tile );
			_selectionHelpers << item;
			_scene.addItem(item);
			HFDrawable *dTile = _drawableTiles[tile];
			item->moveBy(dTile->sceneBoundingRect().x(), dTile->sceneBoundingRect().y()+(dTile->childrenBoundingRect().height()/2));
			// Center the dot.
			item->moveBy(-item->childrenBoundingRect().width()/2, -item->childrenBoundingRect().height()/2);
			item->setZValue( (-tile->x()+1+tile->y()+1)*64 );
		}
		break;
	}
	case Horizontal:
	case Vertical:
	case Fixed:
		// TODO
		break;
	}
}

void HFDrawableCtl::on_objects_updated(HFObjectList objs) {
	for (int i=0; i<objs.size(); i++) {
		HFObject *obj = objs[i];
		HFDrawable *dObj = _drawableObjects[obj];
		if (dObj) {
			_drawableObjects[obj]->setPos((obj->x()+obj->y())*128, (-obj->x()+obj->y())*64 - obj->z()*24 - dObj->childrenBoundingRect().height());
			dObj->setZValue( (-obj->x()+obj->y()+1)*64 );
		}
	}
}
