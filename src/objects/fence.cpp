#include "objects/fence.h"
#include "control/resource.h"
#include "models/modelloader.h"
#include "core/game.h"
#include "core/terrain.h"
#include "core/tile.h"
#include "core/point.h"

osg::ref_ptr<osg::Node> Fence::_node = 0;
osg::ref_ptr<osg::Node> Fence::_node2 = 0;
osg::ref_ptr<osg::Node> Fence::_node4 = 0;
osg::ref_ptr<osg::Node> Fence::_node6 = 0;
osg::ref_ptr<osg::Node> Fence::_node8 = 0;

Fence::Fence( Player* p, Tile* t )
 : StaticObject(p,t) {
	init();
}

Fence::~Fence() {
}

void Fence::draw( const unsigned long long& time ) {
/*    glPushMatrix();
	glTranslatef( _x, _y, _z );

	for (unsigned int i=0; i<_nodes.size(); i++) {
		glCallList( _nodes[i] );
	}
	glPopMatrix();*/
}

void Fence::init() {
/*	if (!Fence::_node) {
		Fence::_node = ModelLoader().loadModel( Resource::locateModel("fence/fence") );

		Fence::_node2 = glGenLists(1);
		glNewList(Fence::_node2, GL_COMPILE);
		glPushMatrix();
		glTranslatef( 0.5f, 0.75f, 0.0f );
		glRotatef( 90.0f, 0.0f, 0.0f, 1.0f );
		glTranslatef( -0.25f, -0.5f, 0.0f );
		glCallList(Fence::_node);
		glPopMatrix();
		glEndList();

		Fence::_node4 = glGenLists(1);
		glNewList(Fence::_node4, GL_COMPILE);
		glPushMatrix();
		glCallList(Fence::_node);
		glPopMatrix();
		glEndList();

		Fence::_node6 = glGenLists(1);
		glNewList(Fence::_node6, GL_COMPILE);
		glPushMatrix();
		glTranslatef( 0.5f, 0.0f, 0.0f );
		glCallList(Fence::_node);
		glPopMatrix();
		glEndList();

		Fence::_node8 = glGenLists(1);
		glNewList(Fence::_node8, GL_COMPILE);
		glPushMatrix();
		glTranslatef( 0.5f, 0.25f, 0.0f );
		glRotatef( 90.0f, 0.0f, 0.0f, 1.0f );
		glTranslatef( -0.25f, -0.5f, 0.0f );
		glCallList(Fence::_node);
		glPopMatrix();
		glEndList();
	}*/
	rebuild();
}

void Fence::rebuild() {
/*	_z = Game::getInstance()->getTile(_x,_y)->getPoint1()->z;

	_nodes.clear();
	if (Game::getInstance()->getTile(_x,_y+1) &&
		Game::getInstance()->getTile(_x,_y+1)->contains<Fence>()) {
		_nodes.push_back( Fence::_node2 );
	}
	if (Game::getInstance()->getTile(_x-1,_y) &&
		Game::getInstance()->getTile(_x-1,_y)->contains<Fence>()) {
		_nodes.push_back( Fence::_node4 );
	}
	if (Game::getInstance()->getTile(_x+1,_y) &&
		Game::getInstance()->getTile(_x+1,_y)->contains<Fence>()) {
		_nodes.push_back( Fence::_node6 );
	}
	if (Game::getInstance()->getTile(_x,_y-1) &&
		Game::getInstance()->getTile(_x,_y-1)->contains<Fence>()) {
		_nodes.push_back( Fence::_node8 );
	}

	if (_nodes.size()==0) {
		_nodes.push_back( Fence::_node4 );
		_nodes.push_back( Fence::_node6 );
	}*/
}
