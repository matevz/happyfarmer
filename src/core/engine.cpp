#include "core/engine.h"
#include "core/game.h"
#include "core/time.h"
#include "gui/graphics.h"
#include "gui/eventhandler.h"
#include <SDL/SDL.h>
#include <GL/gl.h>
#include <GL/glu.h>

Engine::Engine()
 : _game(0), _loop(false), _eventHandler(0), _mouseX(0), _mouseY(0) {
	_graphics = new Graphics();
	_eventHandler = new EventHandler();
}

Engine::~Engine(){
	if (_game) {
		delete _game;
	}

	delete _graphics;
}

int Engine::start() {
	bool error=false;
	SDL_Event event;

	if (!error && !_graphics->init()) {
		error = true;
	}

	if (!error && !_graphics->resize(_graphics->getWindowWidth(), _graphics->getWindowHeight())) {
		error = true;
	}

	if (!error) {
		_game = new Game( 256, 256 );
		_game->getTime()->setSpeed( 1 );
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
				_graphics->resize(event.resize.w, event.resize.h);
				break;
			}
			case SDL_KEYDOWN:
				_eventHandler->keyPressEvent(event.key.keysym);
				break;
			case SDL_MOUSEMOTION: {
				_eventHandler->mouseMotionEvent(event.motion);
				break;
			}
			case SDL_MOUSEBUTTONDOWN: {
				_eventHandler->mouseButtonEvent(event.button);
				break;
			}
			case SDL_QUIT:
				_loop = false;
				break;
			default:
				break;
			}
		}

		if ( _mouseX < 30 ) { _graphics->moveLeft(); }
		if ( _mouseX > _graphics->getWindowWidth()-30 ) { _graphics->moveRight(); }
		if ( _mouseY < 30 ) { _graphics->moveUp(); }
		if ( _mouseY > _graphics->getWindowHeight()-30 ) { _graphics->moveDown(); }

        glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
        glLoadIdentity();
//        _scene->draw();
        SDL_GL_SwapBuffers();

        // frame limiter
        if (SDL_GetTicks() > lastTime && (SDL_GetTicks() - lastTime) < 25) {
        	SDL_Delay( 30 - (SDL_GetTicks() - lastTime) );
        }
        lastTime=SDL_GetTicks();
	}

	return 0;
}
