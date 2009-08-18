#include <string>
#include "gui/scene.h"
#include "gui/screen.h"
#include "core/terrain.h"
#include "core/tile.h"
#include "core/point3d.h"
#include "control/resource.h"
#include "models/modelloader.h"
#include <alut.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <SDL.h>
#include <SDL_image.h>

const float Scene::SCROLL_FACTOR = 0.8;

Scene::Scene( Terrain *t )
 : _terrain(t), _terrainDispList(0) {
	initScene();
}

Scene::~Scene() {
	alutExit();
}

bool Scene::initScene() {
	rebuildTerrain();

	alutInit(0, 0);

	setCamera( _terrain->getWidth()/2, _terrain->getHeight()/2, 2 );

	ModelLoader().loadModel( Resource::locateModel("tractor/tractor") );

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
    glOrtho( (3-_zoomLevel+1)*(-Screen::getScreenWidth()/128), (3-_zoomLevel+1)*(Screen::getScreenWidth()/128), (3-_zoomLevel+1)*(-Screen::getScreenHeight()/128), (3-_zoomLevel+1)*(Screen::getScreenHeight()/128), -500, 500 );
    glPushMatrix();
	glRotatef( -60.0f, 1.0f, 0.0f, 0.0f );
	glRotatef( 45.0f, 0.0f, 0.0f, 1.0f );
	glTranslatef( -_cameraXPos, -_cameraYPos, 0 );
	glCallList(_terrainDispList);
	glCallList( ModelLoader::modelList()[0]->objFiles[0].dispList );
	glPopMatrix();
}

/*!
	Creates an OpenGL list of 3d vertices of the terrain using the World model.
*/
void Scene::rebuildTerrain() {
	GLdouble x_m, y_m, z_m, u_m, v_m;

	SDL_Surface *textureImage;
	GLuint texture;
	textureImage = Resource::loadPng(Resource::locateResource("textures/terrain/grass.png"));
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, textureImage->w, textureImage->h, 0, GL_RGBA, GL_UNSIGNED_BYTE, textureImage->pixels );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST );

    if (_terrainDispList) {
    	glDeleteLists(_terrainDispList, 1);
    }

	_terrainDispList = glGenLists(1);
	glNewList(_terrainDispList, GL_COMPILE);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texture);
	for (int x = 0; x < _terrain->getWidth(); x++) {
		for (int y = 0; y < _terrain->getHeight(); y++) {
			glBegin(GL_QUADS);
			glNormal3f(0.0f, 0.0f, 1.0f);
			x_m = _terrain->getTile(x,y)->getPoint1()->getX();
			y_m = _terrain->getTile(x,y)->getPoint1()->getY();
			z_m = _terrain->getTile(x,y)->getPoint1()->getZ();
			u_m = 1.0f;
			v_m = 1.0f;
			glTexCoord2d( u_m, v_m );
			glVertex3d( x_m, y_m, z_m );

			x_m = _terrain->getTile(x,y)->getPoint2()->getX();
			y_m = _terrain->getTile(x,y)->getPoint2()->getY();
			z_m = _terrain->getTile(x,y)->getPoint2()->getZ();
			u_m = 1.0f;
			v_m = 0.0f;
			glTexCoord2d( u_m, v_m );
			glVertex3d( x_m, y_m, z_m );

			x_m = _terrain->getTile(x,y)->getPoint4()->getX();
			y_m = _terrain->getTile(x,y)->getPoint4()->getY();
			z_m = _terrain->getTile(x,y)->getPoint4()->getZ();
			u_m = 0.0f;
			v_m = 0.0f;
			glTexCoord2d( u_m, v_m );
			glVertex3d( x_m, y_m, z_m );

			x_m = _terrain->getTile(x,y)->getPoint3()->getX();
			y_m = _terrain->getTile(x,y)->getPoint3()->getY();
			z_m = _terrain->getTile(x,y)->getPoint3()->getZ();
			u_m = 0.0f;
			v_m = 1.0f;
			glTexCoord2d( u_m, v_m );
			glVertex3d( x_m, y_m, z_m );

			glColor3f(1.0f, 1.0f, 1.0f);
			glEnd();
		}
	}

	// horizontal lines
	for (int x = 0; x < _terrain->getWidth(); x++) {
		glBegin(GL_LINE_STRIP);
		for (int y = 0; y < _terrain->getHeight()-1; y++) {
			x_m = _terrain->getTile(x,y)->getPoint3()->getX();
			y_m = _terrain->getTile(x,y)->getPoint3()->getY();
			z_m = _terrain->getTile(x,y)->getPoint3()->getZ();
			glVertex3d( x_m, y_m, z_m );
		}
		glColor3f(0.0f, 0.8f, 0.0f);
		glEnd();
	}

	// vertical lines
	for (int y = 0; y < _terrain->getHeight(); y++) {
		glBegin(GL_LINE_STRIP);
		for (int x = 0; x < _terrain->getWidth()-1; x++) {
			x_m = _terrain->getTile(x,y)->getPoint2()->getX();
			y_m = _terrain->getTile(x,y)->getPoint2()->getY();
			z_m = _terrain->getTile(x,y)->getPoint2()->getZ();
			glVertex3d( x_m, y_m, z_m );
		}
		glColor3f(0.0f, 0.8f, 0.0f);
		glEnd();
	}

	glEndList();
	SDL_FreeSurface(textureImage);
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
	if ( _cameraXPos<_terrain->getWidth() && _cameraYPos<_terrain->getHeight() ) {
		setCamera( _cameraXPos+1*SCROLL_FACTOR, _cameraYPos+1*SCROLL_FACTOR, _zoomLevel );
	}
}

void Scene::moveRight() {
	if ( _cameraXPos<_terrain->getWidth() && _cameraYPos>0 ) {
		setCamera( _cameraXPos+1*SCROLL_FACTOR, _cameraYPos-1*SCROLL_FACTOR, _zoomLevel );
	}
}

void Scene::moveLeft() {
	if ( _cameraXPos>0 && _cameraYPos<_terrain->getHeight()-1 ) {
		setCamera( _cameraXPos-1*SCROLL_FACTOR, _cameraYPos+1*SCROLL_FACTOR, _zoomLevel );
	}
}
