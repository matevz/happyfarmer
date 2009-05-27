#include <string>
#include "gui/scene.h"
#include "gui/screen.h"
#include "core/world.h"
#include "core/tile.h"
#include "core/point3d.h"
#include "control/resource.h"
#include <alut.h>
#include <GL/gl.h>
#include <GL/glu.h>

const float Scene::SCROLL_FACTOR = 0.8;

Scene::Scene( World *w )
 : _world(w) {
	initScene();
}

Scene::~Scene()
{
	alutExit();
}

bool Scene::initScene() {
	loadTerrain();

	alutInit(0, 0);

	setCamera( _world->getWidth()/2, _world->getHeight()/2, 2 );

	return true;
}

/*!
 * Starts the scene.
 */
void Scene::startScene() {
	startTime();
}

/*!
 * Draws the whole scene.
 */
void Scene::draw() {
    glOrtho( (3-_zoomLevel+1)*(-Screen::SCREEN_WIDTH/128), (3-_zoomLevel+1)*(Screen::SCREEN_WIDTH/128), (3-_zoomLevel+1)*(-Screen::SCREEN_HEIGHT/128), (3-_zoomLevel+1)*(Screen::SCREEN_HEIGHT/128), -500, 500 );

    glPushMatrix();
	glRotatef( 60.0f, 1.0f, 0.0f, 0.0f );
	glRotatef( 45.0f, 0.0f, 0.0f, 1.0f );
	glTranslatef( -_cameraXPos, -_cameraYPos, 0 );
	glCallList(_terrain);
	glPopMatrix();
}

/*!
 * Loads the hall.
 */
void Scene::loadTerrain() {
	std::cout << "Loading terrain...";
	std::cout.flush();
	GLdouble x_m, y_m, z_m, u_m, v_m;

	SDL_Surface *textureImage;
	GLuint texture;
	textureImage = SDL_LoadBMP(Resource::locateResource("textures/grass.bmp").c_str());
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, textureImage->w, textureImage->h, 0, GL_BGR, GL_UNSIGNED_BYTE, textureImage->pixels );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST );

	_terrain = glGenLists(1);
	glNewList(_terrain, GL_COMPILE);
	glBindTexture(GL_TEXTURE_2D, texture);
	for (int x = 0; x < _world->getWidth(); x++) {
		for (int y = 0; y < _world->getHeight(); y++) {
			glBegin(GL_QUADS);
			glNormal3f(0.0f, 0.0f, 1.0f);
			x_m = _world->getTile(x,y)->getPoint1()->getX();
			y_m = _world->getTile(x,y)->getPoint1()->getY();
			z_m = _world->getTile(x,y)->getPoint1()->getZ();
			u_m = 1.0f;
			v_m = 1.0f;
			glTexCoord2d( u_m, v_m );
			glVertex3d( x_m, y_m, z_m );
			std::cout << "vertex: " << x_m << ", " << y_m << ", " << z_m << std::endl;

			x_m = _world->getTile(x,y)->getPoint2()->getX();
			y_m = _world->getTile(x,y)->getPoint2()->getY();
			z_m = _world->getTile(x,y)->getPoint2()->getZ();
			u_m = 1.0f;
			v_m = 0.0f;
			glTexCoord2d( u_m, v_m );
			glVertex3d( x_m, y_m, z_m );
			std::cout << "vertex: " << x_m << ", " << y_m << ", " << z_m << std::endl;

			x_m = _world->getTile(x,y)->getPoint4()->getX();
			y_m = _world->getTile(x,y)->getPoint4()->getY();
			z_m = _world->getTile(x,y)->getPoint4()->getZ();
			u_m = 0.0f;
			v_m = 0.0f;
			glTexCoord2d( u_m, v_m );
			glVertex3d( x_m, y_m, z_m );
			std::cout << "vertex: " << x_m << ", " << y_m << ", " << z_m << std::endl;

			x_m = _world->getTile(x,y)->getPoint3()->getX();
			y_m = _world->getTile(x,y)->getPoint3()->getY();
			z_m = _world->getTile(x,y)->getPoint3()->getZ();
			u_m = 0.0f;
			v_m = 1.0f;
			glTexCoord2d( u_m, v_m );
			glVertex3d( x_m, y_m, z_m );
			std::cout << "vertex: " << x_m << ", " << y_m << ", " << z_m << std::endl;

			glEnd();
		}
	}

	glEndList();
	SDL_FreeSurface(textureImage);
	std::cout << "done." << std::endl;
}

void Scene::zoomIn() {
	if (_zoomLevel<3) {
		setCamera( _cameraXPos, _cameraYPos, _zoomLevel+1 );
	}
}

void Scene::zoomOut() {
	if (_zoomLevel>0) {
		setCamera( _cameraXPos, _cameraYPos, _zoomLevel-1 );
	}
}

void Scene::moveDown() {
	if ( _cameraXPos>0 && _cameraYPos>0 ) {
		setCamera( _cameraXPos-1*SCROLL_FACTOR, _cameraYPos-1*SCROLL_FACTOR, _zoomLevel );
	}
}

void Scene::moveUp() {
	if ( _cameraXPos<_world->getWidth() && _cameraYPos<_world->getHeight() ) {
		setCamera( _cameraXPos+1*SCROLL_FACTOR, _cameraYPos+1*SCROLL_FACTOR, _zoomLevel );
	}
}

void Scene::moveRight() {
	if ( _cameraXPos<_world->getWidth() && _cameraYPos>0 ) {
		setCamera( _cameraXPos+1*SCROLL_FACTOR, _cameraYPos-1*SCROLL_FACTOR, _zoomLevel );
	}
}

void Scene::moveLeft() {
	if ( _cameraXPos>0 && _cameraYPos<_world->getHeight()-1 ) {
		setCamera( _cameraXPos-1*SCROLL_FACTOR, _cameraYPos+1*SCROLL_FACTOR, _zoomLevel );
	}
}
