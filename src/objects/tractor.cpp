#include "objects/tractor.h"
#include "models/modelloader.h"
#include "control/resource.h"
#include "gui/scene.h"
#include "core/terrain.h"
#include "core/tile.h"
#include "core/point3d.h"

Tractor::Tractor( Player* p, const float& x, const float& y )
 : Object( p, x, y ) {
	_dispList = ModelLoader().loadModel( Resource::locateModel("tractor/tractor") );
}

Tractor::~Tractor() {
}

void Tractor::draw() {
    glPushMatrix();
	glTranslatef( _x, _y, _z );
	glCallList( _dispList );
	glPopMatrix();
}

void Tractor::update( int time ) {
	if ((int)_y < Scene::getScene()->getTerrain()->getHeight()-1) {
		_y += 0.10;
		float roundY = _y - (int)_y;
		Tile *tile = Scene::getScene()->getTerrain()->getTile( (int)_x, (int)_y );

		_z = (tile->getPoint1()->getZ()+tile->getPoint2()->getZ()+tile->getPoint3()->getZ()+tile->getPoint4()->getZ())/4.0;
	}
}
