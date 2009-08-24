#include "core/terrain.h"
#include "core/tile.h"
#include "core/point.h"
#include <stdlib.h>
#include <time.h>

const float Terrain::HEIGHT_FACTOR = 0.4;

Terrain::Terrain( int width, int height )
 : _width(width), _height(height) {
	initTerrain();
}

Terrain::~Terrain() {
	for (int i=0; i<_width; i++) {
		for (int j=0; j<_height; j++) {
			delete getTile(i, j);
		}
	}
}

void Terrain::initTerrain() {
	srand ( time(NULL) );

	// first build the 3d points shared between the tiles
	std::vector<Point3d*> points;
	for (int j=0; j<=_height; j++) {
		for (int i=0; i<=_width; i++) {
			if (j>_height/2) {
				points.push_back( new Point3d( i, j, rand()%2*HEIGHT_FACTOR ) );
			} else {
				points.push_back( new Point3d( i, j, 0 ) );
			}
		}
	}

	// second assign the generated points to the tiles
	for (int j=0; j<_height; j++) {
		for (int i=0; i<_width; i++) {
			_tiles.push_back(
				new Tile(
					i, j,
					points[j*(_width+1)+i], points[j*(_width+1)+i+1],
					points[(j+1)*(_width+1)+i+1], points[(j+1)*(_width+1)+i]
				)
			);
		}
	}
}
