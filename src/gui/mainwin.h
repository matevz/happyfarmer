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
	bool resizeWindow( int width, int height );
	void handleKeyPress( SDL_keysym *keysym );

	Scene *_scene;
};

#endif
