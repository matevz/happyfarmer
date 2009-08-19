#include <string>
#include <algorithm>
#include <alut.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <SDL.h>
#include <SDL_image.h>

#include "gui/scene.h"
#include "gui/screen.h"
#include "core/terrain.h"
#include "core/tile.h"
#include "core/point3d.h"
#include "core/player.h"
#include "core/movingobject.h"
#include "control/resource.h"
#include "models/modelloader.h"

// new game
#include "objects/tractor.h"
#include "objects/grass.h"
#include "objects/fence.h"

const float Scene::SCROLL_FACTOR = 0.8;
const float Scene::TERRAIN_ANGLE = -60.0f;
Scene *Scene::_scene = 0;

Scene::Scene()
 : _terrainDispList(0), _timer(0), _speed(0), _userPlayer(0), _objectUpdater(0) {
	Scene::_scene = this;
	initScene();
}

Scene::~Scene() {
	_speed=-1;
	SDL_WaitThread(_timer, 0);
	SDL_WaitThread(_objectUpdater, 0);

	alutExit();
}

bool Scene::initScene() {
	_terrain = new Terrain( 128, 128 );

	for (unsigned int x=0; x<_terrain->getWidth(); x++) {
		for (unsigned int y=0; y<_terrain->getHeight(); y++) {
			_terrain->getTile(x,y)->addObject( new Grass(0,_terrain->getTile(x,y)) );
		}
	}
	rebuildTerrain();

	_timer = SDL_CreateThread(Scene::timerFunc, this);
	_objectUpdater = SDL_CreateThread(Scene::objectUpdaterFunc, this);

	setCamera( _terrain->getWidth()/2, _terrain->getHeight()/2, 2 );

	_userPlayer = new Player("Human1");
	_playerList.push_back( _userPlayer );
	addMovingObject( new Tractor( _userPlayer, 0.0, 0.0 ) );
	_terrain->getTile(10,10)->addObject( new Fence(_userPlayer, _terrain->getTile(10,10)) );
	_terrain->getTile(11,10)->addObject( new Fence(_userPlayer, _terrain->getTile(11,10)) );
	_terrain->getTile(12,10)->addObject( new Fence(_userPlayer, _terrain->getTile(12,10)) );
	_terrain->getTile(13,10)->addObject( new Fence(_userPlayer, _terrain->getTile(13,10)) );
	_terrain->getTile(10,11)->addObject( new Fence(_userPlayer, _terrain->getTile(10,11)) );
	_terrain->getTile(11,11)->addObject( new Fence(_userPlayer, _terrain->getTile(11,11)) );
	_terrain->getTile(12,11)->addObject( new Fence(_userPlayer, _terrain->getTile(12,11)) );
	_terrain->getTile(13,11)->addObject( new Fence(_userPlayer, _terrain->getTile(13,11)) );
	_terrain->getTile(10,12)->addObject( new Fence(_userPlayer, _terrain->getTile(10,12)) );
	_terrain->getTile(11,13)->addObject( new Fence(_userPlayer, _terrain->getTile(11,13)) );
	_terrain->getTile(12,14)->addObject( new Fence(_userPlayer, _terrain->getTile(12,14)) );
	_terrain->getTile(13,15)->addObject( new Fence(_userPlayer, _terrain->getTile(13,15)) );
	_terrain->getTile(11,10)->addObject( new Fence(_userPlayer, _terrain->getTile(11,10)) );
	_terrain->getTile(12,11)->addObject( new Fence(_userPlayer, _terrain->getTile(12,11)) );
	_terrain->getTile(13,12)->addObject( new Fence(_userPlayer, _terrain->getTile(13,12)) );
	_terrain->getTile(14,13)->addObject( new Fence(_userPlayer, _terrain->getTile(14,13)) );

	return true;
}

/*!
 * Timer function which increases the simulation time by the speed factor.
 */
int Scene::timerFunc(void *s) {
	Scene* scene = static_cast<Scene*>(s);
    while ( scene->_speed != -1 ) {
        SDL_Delay(40);
    	scene->_time += static_cast<int>(40*scene->_speed);
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

	for (unsigned int x=0; x<getTerrain()->getWidth(); x++) {
		for (unsigned int y=0; y<getTerrain()->getHeight(); y++) {
			Tile *t = getTerrain()->getTile(x,y);
			for (unsigned int i=0; i<t->getObjectList().size(); i++) {
				t->getObjectList()[i]->draw( _time );
			}
		}
	}

	for (unsigned int i=0; i<_objectList.size(); i++) {
		_objectList[i]->draw( _time );
	}

	glPopMatrix();
}

/*!
	Creates an OpenGL list of 3d vertices of the terrain using the World model.
*/
#include "objects/grass.h"
void Scene::rebuildTerrain() {
	for (int x = 0; x < _terrain->getWidth(); x++) {
		for (int y = 0; y < _terrain->getHeight(); y++) {
			Object *o = _terrain->getTile(x,y)->getObjectList()[0];
			static_cast<Grass*>(o)->rebuild();
		}
	}
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

/*!
 * Removes the given \a object.
 * Return True, if the object was found. Otherwise False.
 */
bool Scene::removeMovingObject( MovingObject *o ) {
	std::vector<MovingObject*>::iterator pos = std::find(_objectList.begin(), _objectList.end(), o);

	if (pos != _objectList.end()) {
		_objectList.erase(pos);
		return true;
	} else {
		return false;
	}
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
