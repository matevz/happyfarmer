/*!
        Copyright (c) 2012, Matevž Jekovec, Happy farmer development team
        All Rights Reserved. See AUTHORS for a complete list of authors.

        Licensed under the GNU GENERAL PUBLIC LICENSE. See COPYING for details.
*/

#include <ui/mainwin.h>

#include <QGraphicsScene>
#include <QMouseEvent>
#include <QCursor> // mouse move on game view

#include <QDateTime>

#include <model/game.h>
#include <model/resource.h>
#include <model/settings.h>

#include <drawable/terrain/grass.h>
#include <drawable/drawable.h>

#include <model/terrain/grass.h>
#include <iostream>

#include "control/drawablectl.h"
#include "control/constructctl.h"

HFMainWin::HFMainWin(QMainWindow *parent)
 : QMainWindow( parent ),
   _game( nullptr ), _scene( nullptr ),
   _constructCtl( nullptr ),
   _objectCtl(nullptr) {
	_resource = new HFResource();
	_settings = new HFSettings();
	
	setupUi( this ); // initialize elements created by Qt Designer
	gameView->setScene( _drawableCtl.scene() );
	gameView->setDrawableCtl( &_drawableCtl );
	
	newGame();
	_game->start();
}

HFMainWin::~HFMainWin() {
}

void HFMainWin::on_gameView_mousePress( QMouseEvent* event ) {
	
}

void HFMainWin::on_gameView_mouseRelease( QMouseEvent* event ) {
//	std::cout << "HFMainWin::on_gameView_mouseRelease: tilex=" << tile->x() << " tiley=" << tile->y() << std::endl;
	QList<HFTile*> changedTiles;
	QList<HFObject*> placedObjects;
	
	if (event->button()==Qt::LeftButton) {
		if (asphaltRoadBtn->isChecked()) {
			changedTiles = _constructCtl.place(HFConstruction::AsphaltRoad, _drawableCtl.selectionArea());
		} else
		if (dirtRoadBtn->isChecked()) {
			changedTiles = _constructCtl.place(HFConstruction::DirtRoad, _drawableCtl.selectionArea());
		} else
		if (animalBtn->isChecked()) {
			placedObjects = _objectCtl.place(HFObject::AnimalSheep, _drawableCtl.selectionArea());
			for (int i=0; i<placedObjects.size(); i++) {
				changedTiles << _game->tileAt( placedObjects[i]->pos() );
			}
		}
	}
	
	for (int i=0; i<changedTiles.size(); i++) {
		_drawableCtl.rebuildTile( changedTiles[i], true );
	}
}

void HFMainWin::on_gameView_mouseMove( QMouseEvent* event ) {
}

void HFMainWin::newGame() {
	_game = new HFGame(128, 128, QDateTime::currentDateTimeUtc());
	
	_constructCtl = HFConstructCtl( _game );
	_objectCtl = HFObjectCtl( _game );
	_drawableCtl.rebuildScene(_game);
	
	qRegisterMetaType<HFObjectList>("HFObjectList");

	connect(&_game->gameLoop(), SIGNAL(objectsUpdated(HFObjectList)), &_drawableCtl, SLOT(on_objects_updated(HFObjectList)));
}

void HFMainWin::on_cursorBtn_toggled(bool checked) {
	_drawableCtl.setSelectionMode(HFDrawableCtl::None);
}

void HFMainWin::on_magnifierBtn_toggled(bool checked) {
	_drawableCtl.setSelectionMode(HFDrawableCtl::None);
}

void HFMainWin::on_roadBtn_toggled(bool checked) {
	_drawableCtl.setSelectionMode(HFDrawableCtl::HorizontalVertical);
}

void HFMainWin::on_dirtRoadBtn_toggled(bool checked) {
	_drawableCtl.setSelectionMode(HFDrawableCtl::HorizontalVertical);
}

void HFMainWin::on_animalBtn_toggled(bool checked) {
	_drawableCtl.setSelectionMode(HFDrawableCtl::Rectangular);
}

void HFMainWin::on_terrainUpBtn_toggled(bool checked) {
	_drawableCtl.setSelectionMode(HFDrawableCtl::Dot);
}

void HFMainWin::on_terrainDownBtn_toggled(bool checked) {
	_drawableCtl.setSelectionMode(HFDrawableCtl::Dot);
}

