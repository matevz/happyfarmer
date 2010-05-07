#include "objects/tractor.h"
#include "models/modelloader.h"
#include "control/resource.h"
#include "core/terrain.h"
#include "core/tile.h"
#include "core/point.h"
#include "core/game.h"

osg::ref_ptr<osg::Node> Tractor::_node = 0;

Tractor::Tractor( Player* p, const float& x, const float& y )
 : MovingObject( p, x, y, 0 ) {
	if (!Tractor::_node) {
		_node = ModelLoader().loadModel( Resource::locateModel("tractor/tractor") );
	}

	dX = 0.10;
	dY = 0;
}

Tractor::~Tractor() {
}

void Tractor::draw( const unsigned long long& time ) {
/*    glPushMatrix();

	glTranslatef( _x, _y, _z );
	glTranslatef( 0.5, 0.0, 0 );

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
	glCallList( Tractor::_node );
	glPopMatrix();*/
}

void Tractor::update( const unsigned long long& time ) {
	//_y += dY;
	//_x += dX;
	float roundY = _y - (int)_y;
	Tile *tile = Game::getInstance()->getTile( (int)_x, (int)_y );

	if (tile) {
		_z = (tile->getPoint1()->z+tile->getPoint2()->z+tile->getPoint3()->z+tile->getPoint4()->z)/4.0;
	}
}
