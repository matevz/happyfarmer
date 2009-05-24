#include <stdlib.h>
#include <math.h>
#include <iostream>

#include "core/world.h"
#include "core/tile.h"
#include "core/point3d.h"
#include "gui/mainwin.h"
#include "gui/screen.h"
#include "gui/scene.h"

MainWin::MainWin() {
}

MainWin::~MainWin() {
}

void MainWin::show() {
	bool done=false;
	SDL_Event event;
	Screen::initGl();
	resizeWindow(Screen::SCREEN_WIDTH, Screen::SCREEN_HEIGHT);

	_scene = new Scene( new World( 10, 10 ) );
	_scene->startScene();

	float deltaX,deltaY,deltaZ,crossX,crossY,crossZ ;
	float r, phi, theta;
	float velocity=0.12;
	while (!done) {
		while (SDL_PollEvent(&event)) {
			switch (event.type) {
			case SDL_VIDEORESIZE:
				Screen::surface = SDL_SetVideoMode(event.resize.w, event.resize.h, Screen::SCREEN_BPP,
						Screen::videoFlags);
				if (!Screen::surface) {
					fprintf(stderr,
							"Could not get a surface after resize: %s\n",
							SDL_GetError());
					Screen::quit(1);
				}
				resizeWindow(event.resize.w, event.resize.h);
				break;
			case SDL_KEYDOWN:
				handleKeyPress(&event.key.keysym);
				break;
			case SDL_MOUSEMOTION:
				break;
			case SDL_MOUSEBUTTONDOWN:
				if (event.button.button==SDL_BUTTON_WHEELUP) {
					_scene->zoomIn();
				} else if (event.button.button==SDL_BUTTON_WHEELDOWN) {
					_scene->zoomOut();
				}
				break;
			case SDL_QUIT:
				done = true;
				break;
			default:
				break;
			}
		}

        glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
        glLoadIdentity();
        //glOrtho( 8.0, -8.0, -8.0, 8.0, 0.001f, 100.0f );
        gluPerspective( 45.0f, ((float)Screen::SCREEN_WIDTH)/Screen::SCREEN_HEIGHT, 0.001f, 300.0f );

        gluLookAt( _scene->cameraXPos(), _scene->cameraYPos(), _scene->cameraZPos(), _scene->cameraXOri(), _scene->cameraYOri(), _scene->cameraZOri(), 0.0, 0.0, 1.0 );

        _scene->draw();
        SDL_GL_SwapBuffers();

	}

	Screen::quit(0);
}

/*!
 Function to reset our viewport after a window resize.
 */
bool MainWin::resizeWindow(int width, int height) {
	// Height / width ration
	GLfloat ratio;

	// Protect against a divide by zero
	if (height == 0)
		height = 1;

	ratio = (GLfloat) width / (GLfloat) height;

	// Setup our viewport.
	glViewport(0, 0, (GLint) width, (GLint) height);

	// change to the projection matrix and set our viewing volume.
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	// Make sure we're chaning the model view and not the projection
	glMatrixMode(GL_MODELVIEW);

	// Reset The View
	glLoadIdentity();

	return true;
}

/*!
 Function to handle key press events.
 */
void MainWin::handleKeyPress(SDL_keysym *keysym) {
	switch (keysym->sym) {
	case SDLK_ESCAPE:
		Screen::quit(0);
		break;
	case SDLK_F1:
		SDL_WM_ToggleFullScreen(Screen::surface);
		break;
	default:
		break;
	}

	return;
}
