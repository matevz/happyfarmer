/*!
        Copyright (c) 2012, Matevž Jekovec, Happy farmer development team
        All Rights Reserved. See AUTHORS for a complete list of authors.

        Licensed under the GNU GENERAL PUBLIC LICENSE. See COPYING for details.
*/

#include <ui/mainwin.h>

#include <QGraphicsScene>
#include <QMouseEvent>
#include <QCursor> // mouse move on game view

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
   _game( nullptr ), _scene( nullptr ), _gameViewDragStartTile( nullptr ) {
	_resource = new HFResource();
	_settings = new HFSettings();
	
	setupUi( this ); // initialize elements created by Qt Designer
	gameView->setScene( _drawableCtl.scene() );
	
	newGame();
}

HFMainWin::~HFMainWin() {
}

void HFMainWin::on_gameView_mousePress( QMouseEvent* event ) {
	_gameViewLastClickPos = event->pos();
	_gameViewDragStartTile = gameView->tileAt(event->pos());
}

void HFMainWin::on_gameView_mouseRelease( QMouseEvent* event ) {
	HFTile *tile = gameView->tileAt(event->pos());
	if (!tile) {
		return;
	}
	std::cout << tile->x() << tile->y() << std::endl;
	
	if (roadBtn->isChecked()) {
		if (_constructCtl.check(HFConstruction::AsphaltRoad, tile )) {
			_constructCtl.place(HFConstruction::AsphaltRoad, tile );
			_drawableCtl.rebuildTile( tile, true );
		}
	}
	
	_gameViewLastClickPos = event->pos();
	_gameViewDragStartTile = nullptr;
}

void HFMainWin::on_gameView_mouseMove( QMouseEvent* event ) {
	float TRANSLATE_WEIGHT=6.0/gameView->zoomLevel();
	if (event->buttons()&Qt::RightButton) {
		gameView->translate( (event->x()-_gameViewLastClickPos.x())*TRANSLATE_WEIGHT, (event->y()-_gameViewLastClickPos.y())*TRANSLATE_WEIGHT );
		_gameViewLastClickPos = event->pos();
	}
}

void HFMainWin::newGame() {
	_game = new HFGame(128, 128);
	
	_drawableCtl.rebuildTerrain(_game);
}

void HFMainWin::on_roadBtn_toggled(bool checked) {

}

void HFMainWin::on_dirtRoadBtn_toggled(bool checked) {
	
}