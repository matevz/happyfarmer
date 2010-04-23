#include "core/game.h"
#include "core/tile.h"

Game *Game::_game = 0;

/*!
	\class Game
	This class represents the current instance of the running game.
	It includes players, tiles, objects etc.
*/

Game::Game( int h, int w)
 : _terrainWidth(w), _terrainHeight(h) {
	Game::_game = this;
}

Game::~Game(){
}

Tile *Game::getTile( int x, int y ) {
	if (x >= 0 && y >= 0 && x < _terrainWidth && y < _terrainHeight) {
		return _terrain[y*_terrainWidth + x];
	} else {
		return 0;
	}
}
