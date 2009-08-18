#ifndef MAINWIN_H_
#define MAINWIN_H_

#include <GL/gl.h>
#include <GL/glu.h>
#include <SDL.h>

class Scene;

class MainWin {
public:
	MainWin();
	virtual ~MainWin();

	void show();
	int drawGLScene();
private:
	void handleKeyPress( SDL_keysym& );
	void handleMouseMotion( SDL_MouseMotionEvent& );

	Scene *_scene;
	bool   _loop;
	int    _mouseX; int _mouseY;
};

#endif
