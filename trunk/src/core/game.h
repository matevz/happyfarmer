#ifndef GAME_H_
#define GAME_H_

#include <vector>

class Tile;
class MovingObject;
class Economy;
class Time;

#include "core/movingobject.h"
#include "core/staticobject.h"

class Game {
public:
	Game( int height, int width );
	~Game();

	static Game *getInstance() { return Game::_game; }
    std::vector<Tile*>& getTerrain() { return _terrain; }
	std::vector<MovingObject*>& getObjectList() { return _movingObjects; }
	Tile* getTile(int x, int y);

	template<class T>
	bool contains(int x, int y) {
		for (unsigned int i=0; i<_movingObjects.size(); i++) {
			if ( ((int)_movingObjects[i]->getX())==x &&
			     ((int)_movingObjects[i]->getY())==y &&
			     dynamic_cast<T*>(_movingObjects[i]) ) {
				return true;
			}
		}
		return false;
	}

    inline int getTerrainHeight() { return _terrainHeight; }
    inline int getTerrainWidth() { return _terrainWidth; }

    inline Time *getTime() { return _time; }
private:
    static Game *_game;

	Economy *_economy;
	Time    *_time;

	int _terrainHeight;
	int _terrainWidth;
	std::vector<MovingObject*> _movingObjects;
	std::vector<Tile*> _terrain;
};

#endif /* GAME_H_ */
