/*!
        Copyright (c) 2012, Matevž Jekovec, Happy farmer development team
        All Rights Reserved. See AUTHORS for a complete list of authors.

        Licensed under the GNU GENERAL PUBLIC LICENSE. See COPYING for details.
*/

#include <ui/mainwin.h>

#include <QGraphicsScene>

#include <model/game.h>
#include <model/resource.h>

#include <drawable/terrain/grass.h>
#include <drawable/drawable.h>

#include <model/terrain/grass.h>

HFMainWin::HFMainWin(QMainWindow *parent)
 : QMainWindow( parent ),
   _game( nullptr ), _scene( nullptr ) {
	_resource = new HFResource();
	
	setupUi( this ); // initialize elements created by Qt Designer
	
	newGame();
}

HFMainWin::~HFMainWin() {
}

void HFMainWin::newGame() {
	_game = new HFGame(5, 5);
	_scene = new QGraphicsScene();
	
	for (int j=0; j<_game->height(); j++) {
		for (int i=0; i<_game->width(); i++) {
			HFDTerrGrass *item = new HFDTerrGrass( static_cast<HFTerrGrass*>(_game->tileAt(i, j)) ) ;
			
			_scene->addItem(item);
			item->moveBy((i+j)*128, (-i+j)*64 - _game->tileAt(i, j)->z()*24);
			item->setZValue( (-i+j)*64 );
		}
	}
		
	gameView->setScene( _scene );
}