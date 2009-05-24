#ifndef SCREEN_H_
#define SCREEN_H_

#include <SDL.h>

class Screen {
public:
	static bool initGl();
	static void quit( int returnCode );

	static int SCREEN_WIDTH;
	static int SCREEN_HEIGHT;
	static int SCREEN_BPP;
	static SDL_Surface *surface;
	static int videoFlags;
};

#endif /* SCREEN_H_ */
