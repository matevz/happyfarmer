#ifndef SCENE_H_
#define SCENE_H_

#include <vector>
#include <GL/gl.h>
#include <SDL_timer.h> // needed for time
#include <alut.h>
#include "control/modelloader.h"

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
	void move(GLfloat, GLfloat, GLfloat, GLfloat, GLfloat, GLfloat);
	World *getWorld() { return _world; }
	void setWorld( World* w ) { _world = w; }

	///////////////////////////
	// Getter/Setter methods //
	///////////////////////////
	/*! Returns the current absolute time in miliseconds */
	int getTime() { return SDL_GetTicks() - _deltaTime; }

	inline void setCamera( GLfloat x1, GLfloat y1, GLfloat z1, GLfloat x2, GLfloat y2, GLfloat z2 ) {
		_cameraPos[0]=x1; _cameraPos[1]=y1; _cameraPos[2]=z1;
		_cameraOri[0]=x2; _cameraOri[1]=y2; _cameraOri[2]=z2;

		ALfloat pos[3] = { x1, y1, z1 };
		ALfloat vel[3] = { 0, 0, 0 };
		ALfloat ori[3] = { x2, y2, z2 };

		alListenerfv(AL_POSITION,    pos);
		alListenerfv(AL_VELOCITY,    vel);
		alListenerfv(AL_ORIENTATION, ori);
	}
	inline GLfloat cameraXPos() { return _cameraPos[0]; }
	inline GLfloat cameraYPos() { return _cameraPos[1]; }
	inline GLfloat cameraZPos() { return _cameraPos[2]; }
	inline GLfloat cameraXOri() { return _cameraOri[0]; }
	inline GLfloat cameraYOri() { return _cameraOri[1]; }
	inline GLfloat cameraZOri() { return _cameraOri[2]; }

	void zoomIn();
	void zoomOut();

private:
	/*! Starts the global time */
	void startTime() { _deltaTime = SDL_GetTicks(); }

	void loadTerrain();

	World   *_world;
	GLuint   _terrain;
	int      _deltaTime;
	GLfloat  _cameraPos[3];
	GLfloat  _cameraOri[3];
};

#endif /* SCENE_H_ */
