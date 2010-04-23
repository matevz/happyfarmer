#include "core/tile.h"
#include "core/terrain.h"
#include "core/stationaryobject.h"
#include "core/game.h"
#include <algorithm>

const double Tile::HEIGHT_FACTOR = 0.7;

Tile::Tile( int x, int y, Point3d *p1, Point3d *p2, Point3d *p3, Point3d *p4 )
 : _x(x), _y(y),
   _point1(p1), _point2(p2), _point3(p3), _point4(p4) {
}

Tile::~Tile() {
}

bool Tile::removeObject( StationaryObject* o, bool rebuildNeighbors ) {
	std::vector<StationaryObject*>::iterator pos = std::find(_objectList.begin(), _objectList.end(), o);

	if (pos != _objectList.end()) {
		_objectList.erase(pos);
		return true;
	} else {
		return false;
	}
}

void Tile::addObject( StationaryObject*o, bool rebuildNeighbors ) {
	_objectList.push_back(o);

	if (rebuildNeighbors) {
		// rebuilds the neighbors and this tile
		for (int x=_x-1; x<_x+2; x++) {
			for (int y=_y-1; y<_y+2; y++) {
				if (Game::getInstance()->getTile(x, y)) {
					Game::getInstance()->getTile(x, y)->rebuild();
				}
			}
		}
	}
}

void Tile::rebuild() {
	for (unsigned int i=0; i<_objectList.size(); i++) {
		_objectList[i]->rebuild();
	}
}
