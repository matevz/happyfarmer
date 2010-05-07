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

	if (!error) {
		_game = new Game( 256, 256 );
		_game->getTime()->setSpeed( 1 );
	}

	if (!error && !_graphics->init()) {
		error = true;
	}

	_graphics->getViewer()->run();

	return 0;
}
