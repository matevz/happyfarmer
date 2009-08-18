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

	Tile* getTile( int x, int y ) { return _tiles[x*_width + y]; }

	static const float HEIGHT_FACTOR; // Z / X ratio

private:
	void initTerrain();

	int _width;
	int _height;
	std::vector<Tile*> _tiles;
};

#endif
