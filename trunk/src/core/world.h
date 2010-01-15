/*Contains the abstract parts of the world.*/

#ifndef WORLD_H_
#define WORLD_H_

#include <vector>
#include <core/tile.h>

class World {
public:
	World(int Height, int Width);
	~World();

	Tile* getTile(int x, int y){
		if(x >= 0 && y >= 0 && x < terrainWidth && y < terrainHeight){
			return Terrain[y*terrainWidth + x];
		}
		else{
			return 0;
		}
	}

    int getTerrainHeight() const
    {
        return terrainHeight;
    }

    int getTerrainWidth() const
    {
        return terrainWidth;
    }

    const float heightFactor;

    vector* getTerrain(){
    	return &Terrain;
    }

private:
	int terrainHeight;
	int terrainWidth;
	vector<Tile*> Terrain;
};

#endif /* WORLD_H_ */
