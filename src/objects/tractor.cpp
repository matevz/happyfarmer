#include "objects/tractor.h"
#include "models/modelloader.h"
#include "control/resource.h"
#include "gui/scene.h"
#include "core/terrain.h"
#include "core/tile.h"
#include "core/point3d.h"

Tractor::Tractor( Player* p, const float& x, const float& y )
 : MovingObject( p, x, y ) {
	_dispList = ModelLoader().loadModel( Resource::locateModel("tractor/tractor") );
	dX = 0.10;
	dY = 0;
}

Tractor::~Tractor() {
}

void Tractor::draw( const unsigned long long& time ) {
    glPushMatrix();

	glTranslatef( _x, _y, _z );

	if (dX > 0) {
    	glRotatef( -90.0f, 0.0, 0.0, 1.0 );
    }
    if (dX < 0) {
    	glRotatef( 90.0f, 0.0, 0.0, 1.0 );
    }
    if (dY > 0) {
    	glRotatef( 0.0f, 0.0, 0.0, 1.0 );
    }
    if (dY < 0) {
    	glRotatef( 180.0f, 0.0, 0.0, 1.0 );
    }

	glTranslatef( -0.5, -0.5, 0 );
	glCallList( _dispList );
	glPopMatrix();
}

void Tractor::update( const unsigned long long& time ) {
	_y += dY;
	_x += dX;
	float roundY = _y - (int)_y;
	Tile *tile = Scene::getScene()->getTerrain()->getTile( (int)_x, (int)_y );

	_z = (tile->getPoint1()->getZ()+tile->getPoint2()->getZ()+tile->getPoint3()->getZ()+tile->getPoint4()->getZ())/4.0;
}
