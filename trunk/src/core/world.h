#ifndef WORLD_H_
#define WORLD_H_

#include <vector>

class Tile;

class World {
public:
	World( int width, int height );
	virtual ~World();

	int getWidth() { return _width; }
	int getHeight() { return _height; }

	Tile* getTile( int x, int y ) { return _tiles[x*_width + y]; }

private:
	void initTerrain();

	int _width;
	int _height;
	std::vector<Tile*> _tiles;
};

#endif
