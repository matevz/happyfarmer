#include <string>
#include "gui/scene.h"
#include "gui/screen.h"
#include "core/terrain.h"
#include "core/tile.h"
#include "core/point3d.h"
#include "core/player.h"
#include "control/resource.h"
#include "models/modelloader.h"
#include "objects/tractor.h"
#include <alut.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <SDL.h>
#include <SDL_image.h>

const float Scene::SCROLL_FACTOR = 0.8;
const float Scene::TERRAIN_ANGLE = -60.0f;

Scene::Scene( Terrain *t )
 : _terrain(t), _terrainDispList(0), _timer(0), _speed(0), _userPlayer(0), _objectUpdater(0) {
	initScene();
}

Scene::~Scene() {
	_speed=-1;
	SDL_WaitThread(_timer, 0);
	SDL_WaitThread(_objectUpdater, 0);

	alutExit();
}

bool Scene::initScene() {
	rebuildTerrain();

	_timer = SDL_CreateThread(Scene::timerFunc, this);
	_objectUpdater = SDL_CreateThread(Scene::objectUpdaterFunc, this);

	setCamera( _terrain->getWidth()/2, _terrain->getHeight()/2, 2 );

	_userPlayer = new Player("Human1");
	_playerList.push_back( _userPlayer );
	addObject( new Tractor( _userPlayer, 0.0, 0.0 ) );

	return true;
}

/*!
 * Timer function which increases the simulation time by the speed factor.
 */
int Scene::timerFunc(void *s) {
	Scene* scene = static_cast<Scene*>(s);
    while ( scene->_speed != -1 ) {
        SDL_Delay(40);
    	scene->_time += 40*scene->_speed;
    }
    return 0;
}

/*!
 * Function which regularly updates the objects on the scene.
 */
int Scene::objectUpdaterFunc(void *s) {
	Scene* scene = static_cast<Scene*> (s);
	while (scene->_speed != -1) {
		SDL_Delay(50);
		for (unsigned int i=0; i < scene->_objectList.size(); i++) {
			scene->_objectList[i]->update(scene->_time);
		}
	}
	return 0;
}

/*!
 * Draws the whole scene.
 */
void Scene::draw() {
    glOrtho( (3-_zoomLevel+1)*(-Screen::getScreenWidth()/128), (3-_zoomLevel+1)*(Screen::getScreenWidth()/128), (3-_zoomLevel+1)*(-Screen::getScreenHeight()/128), (3-_zoomLevel+1)*(Screen::getScreenHeight()/128), -500, 500 );
    glPushMatrix();
	glRotatef( TERRAIN_ANGLE, 1.0f, 0.0f, 0.0f );
	glRotatef( 45.0f, 0.0f, 0.0f, 1.0f );
	glTranslatef( -_cameraXPos, -_cameraYPos, 0 );
	glCallList(_terrainDispList);

	for (unsigned int i=0; i<_objectList.size(); i++) {
		_objectList[i]->draw();
	}

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

void Scene::setCamera( GLfloat x1, GLfloat y1, int zoomLevel ) {
	_cameraXPos=x1; _cameraYPos=y1; _zoomLevel = zoomLevel;

	ALfloat pos[3] = { x1, y1, 5-zoomLevel };
	ALfloat vel[3] = { 0, 0, 0 };
	ALfloat ori[3] = { x1-5, y1-5, 5-zoomLevel-5 };

	alListenerfv(AL_POSITION,    pos);
	alListenerfv(AL_VELOCITY,    vel);
	alListenerfv(AL_ORIENTATION, ori);
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
