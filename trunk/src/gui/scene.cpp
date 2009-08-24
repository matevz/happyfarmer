#include <string>
#include <algorithm>
#include <math.h>
#include <alut.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <SDL.h>
#include <SDL_image.h>

#include "gui/scene.h"
#include "gui/screen.h"
#include "core/terrain.h"
#include "core/tile.h"
#include "core/player.h"
#include "core/movingobject.h"
#include "control/resource.h"
#include "models/modelloader.h"

// new game
#include "objects/tractor.h"
#include "objects/grass.h"
#include "objects/fence.h"
#include "objects/road.h"

const float Scene::SCROLL_FACTOR = 0.8;
const float Scene::TERRAIN_ANGLE = 60.0f;
const float Scene::MAGNIFIER_FACTOR = 256;
Scene *Scene::_scene = 0;

Scene::Scene()
 : _terrainDispList(0), _timer(0), _speed(0), _userPlayer(0), _objectUpdater(0), _selectedTile(0) {
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

	_terrain->getTile(24,13)->addObject( new Road(_userPlayer, _terrain->getTile(24,13)) );
	_terrain->getTile(25,13)->addObject( new Road(_userPlayer, _terrain->getTile(25,13)) );
	_terrain->getTile(26,13)->addObject( new Road(_userPlayer, _terrain->getTile(26,13)) );
	_terrain->getTile(24,14)->addObject( new Road(_userPlayer, _terrain->getTile(24,14)) );
	_terrain->getTile(25,14)->addObject( new Road(_userPlayer, _terrain->getTile(25,14)) );
	_terrain->getTile(26,14)->addObject( new Road(_userPlayer, _terrain->getTile(26,14)) );
	_terrain->getTile(24,15)->addObject( new Road(_userPlayer, _terrain->getTile(24,15)) );
	_terrain->getTile(25,15)->addObject( new Road(_userPlayer, _terrain->getTile(25,15)) );
	_terrain->getTile(26,15)->addObject( new Road(_userPlayer, _terrain->getTile(26,15)) );

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

void Scene::mouseMoveEvent( const unsigned short& x, const unsigned short& y ) {
	calculateXY(x,y);
}

void Scene::calculateXY(int x, int y) {
	float centerX = Screen::getScreenWidth()/2, centerY = Screen::getScreenHeight()/2;

	float beta = atan((sqrt(2)/2) / ((sqrt(2)*cos((TERRAIN_ANGLE/180)*M_PI))/2))*2;
	float alpha = atan( (centerY-y) / (centerX-x) ) + M_PI_2 - (beta/2);
	float gamma = M_PI - (alpha+beta);
	float b = sqrt(pow(x-centerX,2) + pow(y-centerY,2));
	float a = (b / sin(beta)) * sin(alpha*((x-centerX<0)?1:-1)) / sqrt(0.5*(1+pow(cos((TERRAIN_ANGLE/180)*M_PI), 2)));
	float c = (b / sin(beta)) * sin(gamma*((x-centerX<0)?-1:1)) / sqrt(0.5*(1+pow(cos((TERRAIN_ANGLE/180)*M_PI), 2)));

	_sceneXY.x = _cameraPos.x + (3-_zoomLevel+1)*(c/(MAGNIFIER_FACTOR/4));
	_sceneXY.y = _cameraPos.y + (3-_zoomLevel+1)*(a/(MAGNIFIER_FACTOR/4));
}

void Scene::mouseClickEvent( SDL_MouseButtonEvent& button ) {
	if (button.button==SDL_BUTTON_WHEELUP) {
		_scene->zoomIn();
	} else if (button.button==SDL_BUTTON_WHEELDOWN) {
		_scene->zoomOut();
	} else if (button.button==SDL_BUTTON_LEFT) {
		_selectedTile = getTerrain()->getTile((int)_sceneXY.x, (int)_sceneXY.y);
	}
}

/*!
 * Draws the whole scene.
 */
void Scene::draw() {
    glOrtho( (3-_zoomLevel+1)*(-Screen::getScreenWidth()/(MAGNIFIER_FACTOR/2)), (3-_zoomLevel+1)*(Screen::getScreenWidth()/(MAGNIFIER_FACTOR/2)), (3-_zoomLevel+1)*(-Screen::getScreenHeight()/(MAGNIFIER_FACTOR/2)), (3-_zoomLevel+1)*(Screen::getScreenHeight()/(MAGNIFIER_FACTOR/2)), -500, 500 );
    glPushMatrix();
	glRotatef( -TERRAIN_ANGLE, 1.0f, 0.0f, 0.0f );
	glRotatef( 45.0f, 0.0f, 0.0f, 1.0f );
	glTranslatef( -_cameraPos.x, -_cameraPos.y, 0 );

	// draw tiles
	for (unsigned int x=0; x<getTerrain()->getWidth(); x++) {
		for (unsigned int y=0; y<getTerrain()->getHeight(); y++) {
			Tile *t = getTerrain()->getTile(x,y);
			for (unsigned int i=0; i<t->getObjectList().size(); i++) {
				t->getObjectList()[i]->draw( _time );
			}
		}
	}

	// draw moving objects
	for (unsigned int i=0; i<_objectList.size(); i++) {
		_objectList[i]->draw( _time );
	}

	// draw selected tile
	if (_selectedTile) {
		float x_m, y_m, z_m;
		glPushMatrix();
		glBegin(GL_LINE_LOOP);
		glColor3f(1.0f, 1.0f, 1.0f);
		x_m = _selectedTile->getPoint1()->x;
		y_m = _selectedTile->getPoint1()->y;
		z_m = _selectedTile->getPoint1()->z+0.02;
		glVertex3f( x_m, y_m, z_m );
		x_m = _selectedTile->getPoint2()->x;
		y_m = _selectedTile->getPoint2()->y;
		z_m = _selectedTile->getPoint2()->z+0.02;
		glVertex3f( x_m, y_m, z_m );
		x_m = _selectedTile->getPoint3()->x;
		y_m = _selectedTile->getPoint3()->y;
		z_m = _selectedTile->getPoint3()->z+0.02;
		glVertex3f( x_m, y_m, z_m );
		x_m = _selectedTile->getPoint4()->x;
		y_m = _selectedTile->getPoint4()->y;
		z_m = _selectedTile->getPoint4()->z+0.02;
		glVertex3f( x_m, y_m, z_m );
		glEnd();
		glPopMatrix();
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
	_cameraPos.x=x1; _cameraPos.y=y1; _zoomLevel = zoomLevel;

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
		setCamera( _cameraPos.x, _cameraPos.y, _zoomLevel+1 );
	}
}

void Scene::zoomOut() {
	if (_zoomLevel>0) {
		setCamera( _cameraPos.x, _cameraPos.y, _zoomLevel-1 );
	}
}

void Scene::moveDown() {
	if ( _cameraPos.x>0 && _cameraPos.y>0 ) {
		setCamera( _cameraPos.x-SCROLL_FACTOR, _cameraPos.y-SCROLL_FACTOR, _zoomLevel );
	}
}

void Scene::moveUp() {
	if ( _cameraPos.x<_terrain->getWidth() && _cameraPos.y<_terrain->getHeight() ) {
		setCamera( _cameraPos.x+SCROLL_FACTOR, _cameraPos.y+SCROLL_FACTOR, _zoomLevel );
	}
}

void Scene::moveRight() {
	if ( _cameraPos.x<_terrain->getWidth() && _cameraPos.y>0 ) {
		setCamera( _cameraPos.x+SCROLL_FACTOR, _cameraPos.y-SCROLL_FACTOR, _zoomLevel );
	}
}

void Scene::moveLeft() {
	if ( _cameraPos.x>0 && _cameraPos.y<_terrain->getHeight()-1 ) {
		setCamera( _cameraPos.x-SCROLL_FACTOR, _cameraPos.y+SCROLL_FACTOR, _zoomLevel );
	}
}
