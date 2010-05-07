#include "control/worldgenerator.h"
#include "core/tile.h"

void WorldGenerator::genTerrain( std::vector<Tile*> tiles ) {
	glNewList(terrain, GL_COMPILE);
		glBegin(GL_QUADS);
		for(int i = 0; i < tiles->size(); i++){
			glVertex3f(tiles[i]->getPoint1()->x, tiles[i]->getPoint1()->y, tiles[i]->getPoint1()->z);
			glVertex3f(tiles[i]->getPoint2()->x, tiles[i]->getPoint2()->y, tiles[i]->getPoint2()->z);
			glVertex3f(tiles[i]->getPoint3()->x, tiles[i]->getPoint3()->y, tiles[i]->getPoint3()->z);
			glVertex3f(tiles[i]->getPoint4()->x, tiles[i]->getPoint4()->y, tiles[i]->getPoint4()->z);
		}
		glEnd();
	glEndList();
}
