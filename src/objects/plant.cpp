#include "objects/plant.h"
#include "control/resource.h"
#include "models/modelloader.h"
#include "core/game.h"
#include "core/terrain.h"
#include "core/tile.h"

osg::ref_ptr<osg::Node> Plant::_node = 0;

Plant::Plant( Player* p, Tile* t )
 : StaticObject(p,t) {
	init();
}

Plant::~Plant() {
}

void Plant::draw( const unsigned long long& time ) {
/*    glPushMatrix();
	glTranslatef( _x, _y, _z );

	glCallList( _node );
	glPopMatrix();
*/}

void Plant::init() {
/*	if (!Plant::_node) {
		Plant::_node = ModelLoader().loadModel( Resource::locateModel("plant/plant") );
	}

	_z += 0.02;
*/}
