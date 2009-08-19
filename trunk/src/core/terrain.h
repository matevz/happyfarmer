#ifndef WORLD_H_
#define WORLD_H_

#include <vector>

class Tile;

class Terrain {
public:
	Terrain( int width, int height );
	virtual ~Terrain();

	int getWidth() { return _width; }
	int getHeight() { return _height; }

	Tile* getTile( int x, int y ) { if (x>=0 && y>=0 && x<_width && y<_height) { return _tiles[y*_width + x]; } else { return 0; } }

	static const float HEIGHT_FACTOR; // Z / X ratio

private:
	void initTerrain();

	int _width;
	int _height;
	std::vector<Tile*> _tiles;
};

#endif
