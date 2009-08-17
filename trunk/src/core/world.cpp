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
	for (int j=0; j<=_height; j++) {
		for (int i=0; i<=_width; i++) {
			if (j>_height/2) {
				points.push_back( new Point3d( i, j, rand()%2 ) );
			} else {
				points.push_back( new Point3d( i, j, 0 ) );
			}
		}
	}

	for (int j=0; j<_height; j++) {
		for (int i=0; i<_width; i++) {
			_tiles.push_back(
				new Tile(
					i, j,
					points[j*(_width+1)+i], points[j*(_width+1)+i+1],
					points[(j+1)*(_width+1)+i], points[(j+1)*(_width+1)+i+1]
				)
			);
		}
	}
}
