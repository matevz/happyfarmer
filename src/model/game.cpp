/*!
	Copyright (c) 2012, Matevž Jekovec, Happy Farmer development team
	All Rights Reserved. See AUTHORS for a complete list of authors.

	Licensed under the GNU GENERAL PUBLIC LICENSE. See COPYING for details.
*/

#include <model/game.h>
#include <model/gameloop.h>

#include <model/tile.h>
#include <model/terrain/grass.h>

#include <stdlib.h>
#include <iostream>

HFGame::HFGame(int w, int h, QDateTime dt) :
 _tiles(nullptr), _width(w), _height(h), _speed(Pause), _dateTime(dt), _gameLoop(this) {
	init();
}

HFGame::~HFGame() {
}

void HFGame::init() {
	_tiles = new HFTile*[_width*_height];
	
	genRndGame();
}

void HFGame::genRndGame() {
//	for (int i=0; i<_height; i++) {
//		for (int j=0; j<_width; j++) {
//			int height[] = {0,0,0,0};
//			_tiles[i*_width + j] = new HFTerrGrass(j, i, 0, height);
//		}
//	}

	int heightMap[(_width+1)*(_height+1)];
	for (int i=0; i<_height+1; i++) {
		for (int j=0; j<_width+1; j++) {
			heightMap[i*(_width+1) + j] = rand()%2;
		}
	}
	
	for (int i=0; i<_height; i++) {
		for (int j=0; j<_width; j++) {
			int height[] = { heightMap[i*(_width+1) + j], heightMap[i*(_width+1) + j+1], heightMap[(i+1)*(_width+1) + j+1], heightMap[(i+1)*(_width+1) + j] };
			int z = 0;
			
			if (heightMap[i*(_width+1) + j+1]==1 && heightMap[i*(_width+1) + j]==1 &&
				heightMap[(i+1)*(_width+1) + j]==1 && heightMap[(i+1)*(_width+1) + j+1]==1) {
				height[0] = 0; height[1] = 0; height[2] = 0; height[3] = 0;
				z = 1;
			}
			
			_tiles[i*_width + j] = new HFTerrGrass(this, j, i, z, height);
		}
	}
}

HFTile *HFGame::tileAt(int x, int y) {
	if (x>=0 && y>=0 && x<_width && y<_height) {
		return _tiles[y*_width + x];
	} else {
		return nullptr;
	}
}

HFTile *HFGame::tileAt(QPointF pos) {
	return tileAt((int) pos.x(), (int) pos.y());
}

HFTile *HFGame::tileAt(QVector3D pos) {
	return tileAt((int) pos.x(), (int) pos.y());
}

/*!
	Starts the simulation loop.
 */
void HFGame::start() {
	_gameLoop.start();
}

/*!
	Ends the simulation loop.
 */
void HFGame::end() {
	_gameLoop.exit(0);
}