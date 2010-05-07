#include "objects/house.h"
#include "control/resource.h"
#include "models/modelloader.h"
#include "core/game.h"
#include "core/terrain.h"
#include "core/tile.h"

osg::ref_ptr<osg::Node> House::_node = 0;

House::House( Player* p, Tile* t )
 : StaticObject(p,t) {
	init();
}

House::~House() {
}

void House::draw( const unsigned long long& time ) {
/*    glPushMatrix();
	glTranslatef( _x, _y, _z );

	glCallList( _node );
	glPopMatrix();
*/}

void House::init() {
	if (!House::_node) {
		House::_node = ModelLoader().loadModel( Resource::locateModel("house/house") );
	}

	Game::getInstance()->getTile((int)_x+1, (int)_y)->addObject(this);
	Game::getInstance()->getTile((int)_x, (int)_y+1)->addObject(this);
	Game::getInstance()->getTile((int)_x+1, (int)_y+1)->addObject(this);
}
