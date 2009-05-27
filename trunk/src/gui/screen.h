#ifndef SCREEN_H_
#define SCREEN_H_

#include <SDL.h>

class Screen {
public:
	static bool initGl();
	static void quit( int returnCode );
	static bool resizeEvent( int width, int height );

	static int getScreenWidth();
	static int getScreenHeight();
	static int getBpp();

	static SDL_Surface *surface;

private:
	static int DEFAULT_SCREEN_WIDTH;
	static int DEFAULT_SCREEN_HEIGHT;
	static int DEFAULT_SCREEN_BPP;
	static int videoFlags;
};

#endif /* SCREEN_H_ */
