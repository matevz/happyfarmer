#include "objects/fence.h"
#include "control/resource.h"
#include "models/modelloader.h"
#include "gui/scene.h"
#include "core/terrain.h"
#include "core/tile.h"
#include "core/point3d.h"

GLuint Fence::_dispList = 0;
GLuint Fence::_dispList2 = 0;
GLuint Fence::_dispList4 = 0;
GLuint Fence::_dispList6 = 0;
GLuint Fence::_dispList8 = 0;

Fence::Fence( Player* p, Tile* t )
 : StationaryObject(p,t) {
	if (!Fence::_dispList) {
		Fence::_dispList = ModelLoader().loadModel( Resource::locateModel("fence/fence") );

		Fence::_dispList2 = glGenLists(1);
		glNewList(Fence::_dispList2, GL_COMPILE);
		glPushMatrix();
		glTranslatef( 0.5f, 0.75f, 0.0f );
		glRotatef( 90.0f, 0.0f, 0.0f, 1.0f );
		glTranslatef( -0.25f, -0.5f, 0.0f );
		glCallList(Fence::_dispList);
		glPopMatrix();
		glEndList();

		Fence::_dispList4 = glGenLists(1);
		glNewList(Fence::_dispList4, GL_COMPILE);
		glPushMatrix();
		glCallList(Fence::_dispList);
		glPopMatrix();
		glEndList();

		Fence::_dispList6 = glGenLists(1);
		glNewList(Fence::_dispList6, GL_COMPILE);
		glPushMatrix();
		glTranslatef( 0.5f, 0.0f, 0.0f );
		glCallList(Fence::_dispList);
		glPopMatrix();
		glEndList();

		Fence::_dispList8 = glGenLists(1);
		glNewList(Fence::_dispList8, GL_COMPILE);
		glPushMatrix();
		glTranslatef( 0.5f, 0.25f, 0.0f );
		glRotatef( 90.0f, 0.0f, 0.0f, 1.0f );
		glTranslatef( -0.25f, -0.5f, 0.0f );
		glCallList(Fence::_dispList);
		glPopMatrix();
		glEndList();
	}
	rebuild();
}

Fence::~Fence() {
}

void Fence::draw( const unsigned long long& time ) {
    glPushMatrix();
	glTranslatef( _x, _y, _z );

	for (unsigned int i=0; i<_dispLists.size(); i++) {
		glCallList( _dispLists[i] );
	}
	glPopMatrix();
}

void Fence::rebuild() {
	_z = Scene::getScene()->getTerrain()->getTile(_x,_y)->getPoint1()->getZ();

	_dispLists.clear();
	if (Scene::getScene()->getTerrain()->getTile(_x,_y+1) &&
	    Scene::getScene()->getTerrain()->getTile(_x,_y+1)->contains<Fence>()) {
		_dispLists.push_back( Fence::_dispList2 );
	}
	if (Scene::getScene()->getTerrain()->getTile(_x-1,_y) &&
	    Scene::getScene()->getTerrain()->getTile(_x-1,_y)->contains<Fence>()) {
		_dispLists.push_back( Fence::_dispList4 );
	}
	if (Scene::getScene()->getTerrain()->getTile(_x+1,_y) &&
	    Scene::getScene()->getTerrain()->getTile(_x+1,_y)->contains<Fence>()) {
		_dispLists.push_back( Fence::_dispList6 );
	}
	if (Scene::getScene()->getTerrain()->getTile(_x,_y-1) &&
	    Scene::getScene()->getTerrain()->getTile(_x,_y-1)->contains<Fence>()) {
		_dispLists.push_back( Fence::_dispList8 );
	}

	if (_dispLists.size()==0) {
		_dispLists.push_back( Fence::_dispList4 );
		_dispLists.push_back( Fence::_dispList6 );
	}
}
