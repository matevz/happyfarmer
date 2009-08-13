#ifndef SCENE_H_
#define SCENE_H_

#include <vector>
#include <GL/gl.h>
#include <SDL_timer.h> // needed for time
#include <alut.h>
#include "models/modelloader.h"

class World;

using namespace std;

class Scene
{
public:
	Scene( World* );
	virtual ~Scene();

	bool initScene();
	void startScene();
	void draw( );
	World *getWorld() { return _world; }
	void setWorld( World* w ) { _world = w; }

	///////////////////////////
	// Getter/Setter methods //
	///////////////////////////
	/*! Returns the current absolute time in miliseconds */
	int getTime() { return SDL_GetTicks() - _deltaTime; }

	inline void setCamera( GLfloat x1, GLfloat y1, int zoomLevel ) {
		_cameraXPos=x1; _cameraYPos=y1; _zoomLevel = zoomLevel;

		ALfloat pos[3] = { x1, y1, 5-zoomLevel };
		ALfloat vel[3] = { 0, 0, 0 };
		ALfloat ori[3] = { x1-5, y1-5, 5-zoomLevel-5 };

		alListenerfv(AL_POSITION,    pos);
		alListenerfv(AL_VELOCITY,    vel);
		alListenerfv(AL_ORIENTATION, ori);
	}

	void zoomIn();
	void zoomOut();
	void moveLeft();
	void moveRight();
	void moveUp();
	void moveDown();

private:
	void startTime() { _deltaTime = SDL_GetTicks(); }

	void loadTerrain();

	static const float SCROLL_FACTOR;
	static const float HEIGHT_FACTOR; // Z / X relation

	World  *_world;
	GLuint  _terrain;   // 3d model of terrain
	int     _deltaTime;
	double  _cameraXPos;
	double  _cameraYPos;
	int     _zoomLevel;
};

#endif /* SCENE_H_ */
