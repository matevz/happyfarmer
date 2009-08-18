#include <stdlib.h>
#include <math.h>
#include <iostream>

#include "core/terrain.h"
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
	Screen::resizeEvent(Screen::getScreenWidth(), Screen::getScreenHeight());

	_scene = new Scene( new Terrain( 100, 100 ) );
	_scene->startScene();

	float deltaX,deltaY,deltaZ,crossX,crossY,crossZ ;
	float r, phi, theta;
	float velocity=0.12;
	while (!done) {
		while (SDL_PollEvent(&event)) {
			switch (event.type) {
			case SDL_VIDEORESIZE: {
				Screen::resizeEvent(event.resize.w, event.resize.h);
				break;
			}
			case SDL_KEYDOWN:
				handleKeyPress(event.key.keysym);
				break;
			case SDL_MOUSEMOTION: {
				handleMouseMotion(event.motion);
				break;
			}
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
        _scene->draw();
        SDL_GL_SwapBuffers();

	}

	Screen::quit(0);
}

/*!
	Function to handle key press events.
*/
void MainWin::handleKeyPress(SDL_keysym& keysym) {
	switch (keysym.sym) {
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

/*!
	Function to handle mouse move events.
*/
void MainWin::handleMouseMotion(SDL_MouseMotionEvent& evt) {
	if ( !_scene ) return;

	if ( evt.x < 20 ) {
		_scene->moveLeft();
	}
	if ( evt.x > Screen::getScreenWidth()-20 ) {
		_scene->moveRight();
	}
	if ( evt.y < 20 ) {
		_scene->moveUp();
	}
	if ( evt.y > Screen::getScreenHeight()-20 ) {
		_scene->moveDown();
	}
}
