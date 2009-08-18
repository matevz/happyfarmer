#include "objects/tractor.h"
#include "models/modelloader.h"
#include "control/resource.h"

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
	_y += 0.15;
}
