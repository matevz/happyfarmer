#include "objects/grass.h"
#include "core/terrain.h"
#include "core/tile.h"
#include "core/game.h"
#include "core/point.h"
#include "control/resource.h"

//GLuint Grass::_texture = 0;

Grass::Grass(Player* p, Tile* t)
 : StaticObject(p, t), _node(0) {
	init();
}

Grass::~Grass() {
}

void Grass::draw( const unsigned long long& time ) {
	//glCallList(_node);
}

void Grass::init() {
	// open the texture file
/*	if (!Grass::_texture) {
		SDL_Surface *textureImage = Resource::loadPng(Resource::locateResource("textures/terrain/grass.png"));
		glGenTextures(1, &Grass::_texture);
		glBindTexture(GL_TEXTURE_2D, _texture);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, textureImage->w, textureImage->h, 0, GL_RGBA, GL_UNSIGNED_BYTE, textureImage->pixels );
	    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST );
	    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST );
	}
*/	rebuild();
}

void Grass::rebuild() {
/*	Tile *tile = Game::getInstance()->getTile((int)_x,(int)_y);
	GLfloat x_m, y_m, z_m, u_m, v_m;

	// build new display list
	if (_node) {
		glDeleteLists(_node, 1);
	}
	_node = glGenLists(1);
	glNewList(_node, GL_COMPILE);

	// 3d textured tile
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, Grass::_texture);
	glColor3f(1.0f, 1.0f, 1.0f);
	glBegin(GL_QUADS);
	glNormal3f(0.0f, 0.0f, 1.0f);
	x_m = tile->getPoint1()->x;
	y_m = tile->getPoint1()->y;
	z_m = tile->getPoint1()->z;
	u_m = 0.0f;
	v_m = 0.0f;
	glTexCoord2f( u_m, v_m );
	glVertex3f( x_m, y_m, z_m );
	x_m = tile->getPoint2()->x;
	y_m = tile->getPoint2()->y;
	z_m = tile->getPoint2()->z;
	u_m = 1.0f;
	v_m = 0.0f;
	glTexCoord2f( u_m, v_m );
	glVertex3f( x_m, y_m, z_m );
	x_m = tile->getPoint3()->x;
	y_m = tile->getPoint3()->y;
	z_m = tile->getPoint3()->z;
	u_m = 1.0f;
	v_m = 1.0f;
	glTexCoord2f( u_m, v_m );
	glVertex3f( x_m, y_m, z_m );
	x_m = tile->getPoint4()->x;
	y_m = tile->getPoint4()->y;
	z_m = tile->getPoint4()->z;
	u_m = 0.0f;
	v_m = 1.0f;
	glTexCoord2f( u_m, v_m );
	glVertex3f( x_m, y_m, z_m );
	glEnd();

	// lines around the tile
	glBegin(GL_LINE_LOOP);
	glColor3f(0.0f, 0.7f, 0.0f);
	x_m = tile->getPoint1()->x;
	y_m = tile->getPoint1()->y;
	z_m = tile->getPoint1()->z;
	glVertex3f( x_m, y_m, z_m );
	x_m = tile->getPoint2()->x;
	y_m = tile->getPoint2()->y;
	z_m = tile->getPoint2()->z;
	glVertex3f( x_m, y_m, z_m );
	x_m = tile->getPoint3()->x;
	y_m = tile->getPoint3()->y;
	z_m = tile->getPoint3()->z;
	glVertex3f( x_m, y_m, z_m );
	x_m = tile->getPoint4()->x;
	y_m = tile->getPoint4()->y;
	z_m = tile->getPoint4()->z;
	glVertex3f( x_m, y_m, z_m );
	glEnd();

	glEndList();*/
}
