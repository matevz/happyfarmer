#include "core/world.h"
#include "core/tile.h"
#include "core/point3d.h"
#include <stdlib.h>
#include <time.h>

World::World( int width, int height )
 : _width(width), _height(height) {
	initTerrain();
}

World::~World() {
	for (int i=0; i<_width; i++) {
		for (int j=0; j<_height; j++) {
			delete getTile(i, j);
		}
	}
}

void World::initTerrain() {
	srand ( time(NULL) );
	std::vector<Point3d*> points;
	for (int i=0; i<=_width; i++) {
		for (int j=0; j<=_height; j++) {
			points.push_back( new Point3d( i, j, (rand()%2)-1 ) );
		}
	}

	for (int i=0; i<_width; i++) {
		for (int j=0; j<_height; j++) {
			_tiles.push_back(
				new Tile(
					i, j,
					points[i*_width+j], points[(i+1)*_width+j],
					points[i*_width+j+1], points[(i+1)*_width+j+1]
				)
			);
		}
	}
}
