#include <stdlib.h>
#include <math.h>
#include <iostream>

#include "core/terrain.h"
#include "core/tile.h"
#include "core/point.h"
#include "gui/mainwin.h"
#include "gui/screen.h"
#include "gui/scene.h"

#include "objects/tractor.h"

MainWin::MainWin()
 : _loop(true), _scene(0), _mouseX(50), _mouseY(50) {
}

MainWin::~MainWin() {
}

void MainWin::show() {
	bool error=false;
	SDL_Event event;

	if (!error && !Screen::initGl()) {
		error = true;
	}

	if (!error && !Screen::resizeEvent(Screen::getScreenWidth(), Screen::getScreenHeight())) {
		error = true;
	}

	if (!error) {
		_scene = new Scene();
		_scene->setSpeed( 1 );
	}

	float deltaX,deltaY,deltaZ,crossX,crossY,crossZ ;
	float r, phi, theta;
	float velocity=0.12;

	_loop = !error;
	unsigned int lastTime = SDL_GetTicks();
	while (_loop) {
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
			case SDL_MOUSEBUTTONDOWN: {
				handleMouseClick(event.button);
				break;
			}
			case SDL_QUIT:
				_loop = false;
				break;
			default:
				break;
			}
		}

		if ( _mouseX < 30 ) { _scene->moveLeft(); }
		if ( _mouseX > Screen::getScreenWidth()-30 ) { _scene->moveRight(); }
		if ( _mouseY < 30 ) { _scene->moveUp(); }
		if ( _mouseY > Screen::getScreenHeight()-30 ) { _scene->moveDown(); }

        glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
        glLoadIdentity();
        _scene->draw();
        SDL_GL_SwapBuffers();

        // frame limiter
        if (SDL_GetTicks() > lastTime && (SDL_GetTicks() - lastTime) < 25) {
        	SDL_Delay( 30 - (SDL_GetTicks() - lastTime) );
        }
        lastTime=SDL_GetTicks();
	}

	Screen::cleanup();
}

/*!
	Function to handle key press events.
*/
void MainWin::handleKeyPress(SDL_keysym& keysym) {
	switch (keysym.sym) {
	case SDLK_ESCAPE:
		_loop = false;
		break;
	case SDLK_F1:
		SDL_WM_ToggleFullScreen(Screen::surface);
		break;
	case SDLK_LEFT: {
		Tractor *t = static_cast<Tractor*>(Scene::getScene()->getObjectList()[0]);
		if (t->dX<0) {
			t->dX=0.0;
			t->dY=-0.10;
		} else if (t->dY<0) {
			t->dX=0.10;
			t->dY=0.0;
		} else if (t->dX>0) {
			t->dX=0.0;
			t->dY=0.10;
		} else if (t->dY>0) {
			t->dX=-0.10;
			t->dY=0.0;
		}

		break;
	}
	case SDLK_RIGHT: {
		Tractor *t = static_cast<Tractor*>(Scene::getScene()->getObjectList()[0]);
		if (t->dX>0) {
			t->dX=0.0;
			t->dY=-0.10;
		} else if (t->dY>0) {
			t->dX=0.10;
			t->dY=0.0;
		} else if (t->dX<0) {
			t->dX=0.0;
			t->dY=0.10;
		} else if (t->dY<0) {
			t->dX=-0.10;
			t->dY=0.0;
		}
		break;
	}
	default:
		break;
	}

	return;
}

/*!
	Function to handle mouse move events.
*/
void MainWin::handleMouseMotion(SDL_MouseMotionEvent& evt) {
	_mouseX = evt.x;
	_mouseY = evt.y;

	_scene->mouseMoveEvent( evt.x, evt.y );
}

void MainWin::handleMouseClick( SDL_MouseButtonEvent& button ) {
	_scene->mouseClickEvent( button );
}
