#ifndef SCENE_H_
#define SCENE_H_

#include <vector>
#include <GL/gl.h>
#include <SDL_timer.h> // needed for time
#include <alut.h>
#include "models/modelloader.h"
#include "core/point.h"
#include "core/movingobject.h"

class Terrain;
class Player;
class Tile;

using namespace std;

class Scene
{
public:
	Scene();
	virtual ~Scene();

	bool initScene();
	void draw();
	void mouseMoveEvent( const unsigned short& x, const unsigned short& y );
	void mouseClickEvent( SDL_MouseButtonEvent& button );

	///////////////////////////
	// Getter/Setter methods //
	///////////////////////////
	static Scene* getScene() { return _scene; }
	std::vector<MovingObject*>& getObjectList() { return _objectList; }
	Point2d getXY() { return _sceneXY; }

	template<class T>
	bool contains(int x, int y) {
		for (unsigned int i=0; i<_objectList.size(); i++) {
			if ( ((int)_objectList[i]->getX())==x &&
			     ((int)_objectList[i]->getY())==y &&
			     dynamic_cast<T*>(_objectList[i]) ) {
				return true;
			}
		}
		return false;
	}

	Terrain *getTerrain() { return _terrain; }
	void setTerrain( Terrain* t ) { _terrain = t; }

	inline const unsigned long long& getTime() { return _time; }
	inline const float& getSpeed() { return _speed; }
	inline void setSpeed( const float& speed ) { _speed = speed; }

	void setCamera( GLfloat x1, GLfloat y1, int zoomLevel );

	void zoomIn();
	void zoomOut();
	void moveLeft();
	void moveRight();
	void moveUp();
	void moveDown();

	Player *getUserPlayer() { return _userPlayer; }
	void addMovingObject( MovingObject *o ) { _objectList.push_back(o); }
	bool removeMovingObject( MovingObject *o );

private:
	void rebuildTerrain();
	void calculateXY(int x, int y);
	void newGame();

	static const float SCROLL_FACTOR;
	static const float TERRAIN_ANGLE; // view angle in degrees
	static const float MAGNIFIER_FACTOR;

	// Scene elements
	Terrain *_terrain;
	GLuint   _terrainDispList;        // 3d model of terrain
	std::vector<Player*> _playerList; // list of all players
	Player              *_userPlayer; // the human player
	std::vector<MovingObject*> _objectList; // list of all the object in the scene

	// Time
	unsigned long long _time;  // absolute simulation time in mseconds
	float              _speed; // speed factor
	SDL_Thread        *_timer;
	static int timerFunc(void*);

	// Object management
	SDL_Thread *_objectUpdater;
	static int  objectUpdaterFunc(void*);

	// View
	Point2d _cameraPos;
	int     _zoomLevel;
	Point2d _sceneXY;
	Tile   *_selectedTile;

	// Static member
	static Scene *_scene;
};

#endif /* SCENE_H_ */
