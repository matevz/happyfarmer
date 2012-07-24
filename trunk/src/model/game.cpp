/*!
	Copyright (c) 2012, Matevž Jekovec, Happy Farmer development team
	All Rights Reserved. See AUTHORS for a complete list of authors.

	Licensed under the GNU GENERAL PUBLIC LICENSE. See COPYING for details.
*/

#include <model/game.h>

#include <model/terrain.h>
#include <model/terrain/grass.h>

HFGame::HFGame(int w, int h) :
 _terrain(nullptr), _width(w), _height(h) {
	init();
}

HFGame::~HFGame() {
}

void HFGame::init() {
	_terrain = new HFTerrain*[_width*_height];
	
	for (int i=0; i<_height; i++) {
		for (int j=0; j<_width; j++) {
			_terrain[i*_width + j] = new HFTerrGrass();
		}
	}
}

HFTerrain *HFGame::terrainAt(int x, int y) {
	return _terrain[y*_width + x];
}