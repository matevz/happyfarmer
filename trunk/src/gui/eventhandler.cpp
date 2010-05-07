#include <SDL/SDL.h>
#include "gui/eventhandler.h"
#include "core/game.h"

EventHandler::EventHandler() {
}

EventHandler::~EventHandler() {
}

/*!
	Function for handling key press events.
*/
void EventHandler::keyPressEvent(SDL_keysym& keysym) {
	switch (keysym.sym) {
/*	case SDLK_ESCAPE:
		_loop = false;
		break;
	case SDLK_F1:
		SDL_WM_ToggleFullScreen(Screen::surface);
		break;
	case SDLK_LEFT: {
		Tractor *t =
				static_cast<Tractor*> (Game::getInstance()->getObjectList()[0]);
		if (t->dX < 0) {
			t->dX = 0.0;
			t->dY = -0.10;
		} else if (t->dY < 0) {
			t->dX = 0.10;
			t->dY = 0.0;
		} else if (t->dX > 0) {
			t->dX = 0.0;
			t->dY = 0.10;
		} else if (t->dY > 0) {
			t->dX = -0.10;
			t->dY = 0.0;
		}

		break;
	}
	case SDLK_RIGHT: {
		Tractor *t =
				static_cast<Tractor*> (Game::getInstance()->getObjectList()[0]);
		if (t->dX > 0) {
			t->dX = 0.0;
			t->dY = -0.10;
		} else if (t->dY > 0) {
			t->dX = 0.10;
			t->dY = 0.0;
		} else if (t->dX < 0) {
			t->dX = 0.0;
			t->dY = 0.10;
		} else if (t->dY < 0) {
			t->dX = -0.10;
			t->dY = 0.0;
		}
		break;
	}
*/	default:
		break;
	}

	return;
}

/*!
	Function for handling mouse move events.
*/
void EventHandler::mouseMotionEvent(SDL_MouseMotionEvent& evt) {
/*	if ( _mouseX < 30 ) { _graphics->moveLeft(); }
	if ( _mouseX > _graphics->getWindowWidth()-30 ) { _graphics->moveRight(); }
	if ( _mouseY < 30 ) { _graphics->moveUp(); }
	if ( _mouseY > _graphics->getWindowHeight()-30 ) { _graphics->moveDown(); }
*/}

void EventHandler::mouseButtonEvent(SDL_MouseButtonEvent& button) {
/*	Game::getInstance()->mouseClickEvent(button);
*/}
