#ifndef EVENTHANDLER_H_
#define EVENTHANDLER_H_

#include <SDL/SDL.h>

class EventHandler {
public:
	EventHandler();
	~EventHandler();

	void keyPressEvent(SDL_keysym& keysym);
	void mouseMotionEvent(SDL_MouseMotionEvent& evt);
	void mouseButtonEvent(SDL_MouseButtonEvent& button);
};

#endif /* EVENTHANDLER_H_ */
