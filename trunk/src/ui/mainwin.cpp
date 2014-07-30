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
#include <qt4/QtCore/qnamespace.h>

#include "control/drawablectl.h"
#include "control/constructctl.h"

HFMainWin::HFMainWin(QMainWindow *parent)
 : QMainWindow( parent ),
   _game( nullptr ), _scene( nullptr ),
   _constructCtl( nullptr ) {
	_resource = new HFResource();
	_settings = new HFSettings();
	
	setupUi( this ); // initialize elements created by Qt Designer
	gameView->setScene( _drawableCtl.scene() );
	gameView->setDrawableCtl( &_drawableCtl );
	newGame();
}

HFMainWin::~HFMainWin() {
}

void HFMainWin::on_gameView_mousePress( QMouseEvent* event ) {
	
}

void HFMainWin::on_gameView_mouseRelease( QMouseEvent* event ) {
//	std::cout << "HFMainWin::on_gameView_mouseRelease: tilex=" << tile->x() << " tiley=" << tile->y() << std::endl;
	QList<HFTile*> changedTiles;
	
	if (event->button()==Qt::LeftButton) {
		if (roadBtn->isChecked()) {
			changedTiles = _constructCtl.place(HFConstruction::AsphaltRoad, _drawableCtl.selectionArea());
		}
	}
	
	for (int i=0; i<changedTiles.size(); i++) {
		_drawableCtl.rebuildTile( changedTiles[i], true );
	}
}

void HFMainWin::on_gameView_mouseMove( QMouseEvent* event ) {
}

void HFMainWin::newGame() {
	_game = new HFGame(128, 128);
	
	_constructCtl = HFConstructCtl( _game );
	_drawableCtl.rebuildScene(_game);
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