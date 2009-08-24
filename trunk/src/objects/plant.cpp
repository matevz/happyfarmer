#include "objects/plant.h"
#include "control/resource.h"
#include "models/modelloader.h"
#include "gui/scene.h"
#include "core/terrain.h"
#include "core/tile.h"

GLuint Plant::_dispList = 0;

Plant::Plant( Player* p, Tile* t )
 : StationaryObject(p,t) {
	init();
}

Plant::~Plant() {
}

void Plant::draw( const unsigned long long& time ) {
    glPushMatrix();
	glTranslatef( _x, _y, _z );

	glCallList( _dispList );
	glPopMatrix();
}

void Plant::init() {
	if (!Plant::_dispList) {
		Plant::_dispList = ModelLoader().loadModel( Resource::locateModel("plant/plant") );
	}

	_z += 0.02;
}
