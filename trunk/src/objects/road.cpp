#include "objects/road.h"
#include "control/resource.h"
#include "core/game.h"
#include "core/terrain.h"
#include "core/tile.h"
#include "core/point.h"
#include <SDL/SDL.h>

GLuint Road::_texture258   = 0;
GLuint Road::_texture456   = 0;
GLuint Road::_texture245   = 0;
GLuint Road::_texture256   = 0;
GLuint Road::_texture458   = 0;
GLuint Road::_texture568   = 0;
GLuint Road::_texture2456  = 0;
GLuint Road::_texture2458  = 0;
GLuint Road::_texture2568  = 0;
GLuint Road::_texture4568  = 0;
GLuint Road::_texture24568 = 0;

GLuint Road::_dispList258   = 0;
GLuint Road::_dispList456   = 0;
GLuint Road::_dispList245   = 0;
GLuint Road::_dispList256   = 0;
GLuint Road::_dispList458   = 0;
GLuint Road::_dispList568   = 0;
GLuint Road::_dispList2456  = 0;
GLuint Road::_dispList2458  = 0;
GLuint Road::_dispList2568  = 0;
GLuint Road::_dispList4568  = 0;
GLuint Road::_dispList24568 = 0;

Road::Road(Player* p, Tile* t)
 : StationaryObject(p, t), _dispList(0) {
	init();
}

Road::~Road() {
}

void Road::init() {
	// open the texture file
	if (!Road::_texture258) {
		SDL_Surface *textureImage = 0;

		textureImage = Resource::loadPng(Resource::locateResource("textures/terrain/road258.png"));
		glGenTextures(1, &Road::_texture258);
		glBindTexture(GL_TEXTURE_2D, Road::_texture258);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, textureImage->w, textureImage->h, 0, GL_RGBA, GL_UNSIGNED_BYTE, textureImage->pixels );
	    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST );
	    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST );
	    Road::_dispList258 = genDispList( Road::_texture258 );

		textureImage = Resource::loadPng(Resource::locateResource("textures/terrain/road456.png"));
		glGenTextures(1, &Road::_texture456);
		glBindTexture(GL_TEXTURE_2D, Road::_texture456);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, textureImage->w, textureImage->h, 0, GL_RGBA, GL_UNSIGNED_BYTE, textureImage->pixels );
	    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST );
	    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST );
	    Road::_dispList456 = genDispList( Road::_texture456 );

		textureImage = Resource::loadPng(Resource::locateResource("textures/terrain/road245.png"));
		glGenTextures(1, &Road::_texture245);
		glBindTexture(GL_TEXTURE_2D, Road::_texture245);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, textureImage->w, textureImage->h, 0, GL_RGBA, GL_UNSIGNED_BYTE, textureImage->pixels );
	    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST );
	    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST );
	    Road::_dispList245 = genDispList( Road::_texture245 );

		textureImage = Resource::loadPng(Resource::locateResource("textures/terrain/road256.png"));
		glGenTextures(1, &Road::_texture256);
		glBindTexture(GL_TEXTURE_2D, Road::_texture256);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, textureImage->w, textureImage->h, 0, GL_RGBA, GL_UNSIGNED_BYTE, textureImage->pixels );
	    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST );
	    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST );
	    Road::_dispList256 = genDispList( Road::_texture256 );

		textureImage = Resource::loadPng(Resource::locateResource("textures/terrain/road458.png"));
		glGenTextures(1, &Road::_texture458);
		glBindTexture(GL_TEXTURE_2D, Road::_texture458);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, textureImage->w, textureImage->h, 0, GL_RGBA, GL_UNSIGNED_BYTE, textureImage->pixels );
	    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST );
	    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST );
	    Road::_dispList458 = genDispList( Road::_texture458 );

		textureImage = Resource::loadPng(Resource::locateResource("textures/terrain/road568.png"));
		glGenTextures(1, &Road::_texture568);
		glBindTexture(GL_TEXTURE_2D, Road::_texture568);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, textureImage->w, textureImage->h, 0, GL_RGBA, GL_UNSIGNED_BYTE, textureImage->pixels );
	    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST );
	    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST );
	    Road::_dispList568 = genDispList( Road::_texture568 );

		textureImage = Resource::loadPng(Resource::locateResource("textures/terrain/road2456.png"));
		glGenTextures(1, &Road::_texture2456);
		glBindTexture(GL_TEXTURE_2D, Road::_texture2456);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, textureImage->w, textureImage->h, 0, GL_RGBA, GL_UNSIGNED_BYTE, textureImage->pixels );
	    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST );
	    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST );
	    Road::_dispList2456 = genDispList( Road::_texture2456 );

		textureImage = Resource::loadPng(Resource::locateResource("textures/terrain/road2458.png"));
		glGenTextures(1, &Road::_texture2458);
		glBindTexture(GL_TEXTURE_2D, Road::_texture2458);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, textureImage->w, textureImage->h, 0, GL_RGBA, GL_UNSIGNED_BYTE, textureImage->pixels );
	    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST );
	    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST );
	    Road::_dispList2458 = genDispList( Road::_texture2458 );

		textureImage = Resource::loadPng(Resource::locateResource("textures/terrain/road2568.png"));
		glGenTextures(1, &Road::_texture2568);
		glBindTexture(GL_TEXTURE_2D, Road::_texture2568);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, textureImage->w, textureImage->h, 0, GL_RGBA, GL_UNSIGNED_BYTE, textureImage->pixels );
	    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST );
	    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST );
	    Road::_dispList2568 = genDispList( Road::_texture2568 );

		textureImage = Resource::loadPng(Resource::locateResource("textures/terrain/road4568.png"));
		glGenTextures(1, &Road::_texture4568);
		glBindTexture(GL_TEXTURE_2D, Road::_texture4568);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, textureImage->w, textureImage->h, 0, GL_RGBA, GL_UNSIGNED_BYTE, textureImage->pixels );
	    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST );
	    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST );
	    Road::_dispList4568 = genDispList( Road::_texture4568 );

		textureImage = Resource::loadPng(Resource::locateResource("textures/terrain/road24568.png"));
		glGenTextures(1, &Road::_texture24568);
		glBindTexture(GL_TEXTURE_2D, Road::_texture24568);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, textureImage->w, textureImage->h, 0, GL_RGBA, GL_UNSIGNED_BYTE, textureImage->pixels );
	    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST );
	    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST );
	    Road::_dispList24568 = genDispList( Road::_texture24568 );
	}
	rebuild();
}

GLuint Road::genDispList( GLuint texture ) {
    // generate display lists
	GLuint dispList = glGenLists(1);
	glNewList( dispList, GL_COMPILE );

	// 3d textured tile
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texture);
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	glBegin(GL_QUADS);
	glNormal3f(0.0f, 0.0f, 1.0f);
	glTexCoord2f( 0.0f, 1.0f );
	glVertex3f( 0.0f, 0.0f, 0.02f );
	glTexCoord2f( 1.0f, 1.0f );
	glVertex3f( 1.0f, 0.0f, 0.02f );
	glTexCoord2f( 1.0f, 0.0f );
	glVertex3f( 1.0f, 1.0f, 0.02f );
	glTexCoord2f( 0.0f, 0.0f );
	glVertex3f( 0.0f, 1.0f, 0.02f );
	glEnd();
	glEndList();

	return dispList;
}


void Road::rebuild() {
	_z = Game::getInstance()->getTile(_x,_y)->getPoint1()->z;

	bool dir2=Game::getInstance()->getTile(_x,_y+1) && Game::getInstance()->getTile(_x,_y+1)->contains<Road>();
	bool dir4=Game::getInstance()->getTile(_x-1,_y) && Game::getInstance()->getTile(_x-1,_y)->contains<Road>();
	bool dir6=Game::getInstance()->getTile(_x+1,_y) && Game::getInstance()->getTile(_x+1,_y)->contains<Road>();
	bool dir8=Game::getInstance()->getTile(_x,_y-1) && Game::getInstance()->getTile(_x,_y-1)->contains<Road>();

	if (!dir2 && !dir4 && !dir6 && !dir8) { _dispList = &Road::_dispList456; }
	else if (!dir2 && !dir4 && !dir6 && dir8) { _dispList = &Road::_dispList258; }
	else if (!dir2 && !dir4 && dir6 && !dir8) { _dispList = &Road::_dispList456; }
	else if (!dir2 && !dir4 && dir6 && dir8) { _dispList = &Road::_dispList568; }
	else if (!dir2 && dir4 && !dir6 && !dir8) { _dispList = &Road::_dispList456; }
	else if (!dir2 && dir4 && !dir6 && dir8) { _dispList = &Road::_dispList458; }
	else if (!dir2 && dir4 && dir6 && !dir8) { _dispList = &Road::_dispList456; }
	else if (!dir2 && dir4 && dir6 && dir8) { _dispList = &Road::_dispList4568; }
	else if (dir2 && !dir4 && !dir6 && !dir8) { _dispList = &Road::_dispList258; }
	else if (dir2 && !dir4 && !dir6 && dir8) { _dispList = &Road::_dispList258; }
	else if (dir2 && !dir4 && dir6 && !dir8) { _dispList = &Road::_dispList256; }
	else if (dir2 && !dir4 && dir6 && dir8) { _dispList = &Road::_dispList2568; }
	else if (dir2 && dir4 && !dir6 && !dir8) { _dispList = &Road::_dispList245; }
	else if (dir2 && dir4 && !dir6 && dir8) { _dispList = &Road::_dispList2458; }
	else if (dir2 && dir4 && dir6 && !dir8) { _dispList = &Road::_dispList2456; }
	else if (dir2 && dir4 && dir6 && dir8) { _dispList = &Road::_dispList24568; }
}

void Road::draw( const unsigned long long& time ) {
	glPushMatrix();
	glTranslatef( _x, _y, _z );
	glCallList( *_dispList );
	glPopMatrix();
}
