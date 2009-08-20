#include <GL/gl.h>
#include <GL/glu.h>
#include <AL/alut.h>
#include "gui/screen.h"

int Screen::DEFAULT_SCREEN_WIDTH = 800;
int Screen::DEFAULT_SCREEN_HEIGHT = 600;
int Screen::DEFAULT_SCREEN_BPP = 32;
SDL_Surface *Screen::surface = 0;
int Screen::videoFlags = 0;

void Screen::cleanup() {
	alutExit();
	SDL_Quit();
}

/*!
	Initializes graphics subsystem.
*/
bool Screen::initGl() {
	bool error = false;
	SDL_Event event;
	const SDL_VideoInfo *videoInfo;

	// initialize SDL
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		fprintf(stderr, "Video initialization failed: %s\n", SDL_GetError());
		error = true;
	}

	videoInfo = SDL_GetVideoInfo();

	if (!videoInfo) {
		fprintf(stderr, "Video query failed: %s\n", SDL_GetError());
		error = true;
	}

	videoFlags = SDL_OPENGL; // Enable OpenGL in SDL
	videoFlags |= SDL_GL_DOUBLEBUFFER; // Enable double buffering
	videoFlags |= SDL_HWPALETTE; // Store the palette in hardware
	videoFlags |= SDL_RESIZABLE; // Enable window resizing

	// This checks to see if surfaces can be stored in memory
	if (videoInfo->hw_available) {
		videoFlags |= SDL_HWSURFACE;
	} else {
		videoFlags |= SDL_SWSURFACE;
	}

	// This checks if hardware blits can be done
	if (videoInfo->blit_hw) {
		videoFlags |= SDL_HWACCEL;
	}

	surface = SDL_SetVideoMode(DEFAULT_SCREEN_WIDTH, DEFAULT_SCREEN_HEIGHT, DEFAULT_SCREEN_BPP,
			videoFlags);

	// Verify there is a surface
	if (!surface) {
		fprintf(stderr, "Video mode set failed: %s\n", SDL_GetError());
		error = true;
	}

	// Enable key repeat
	if ((SDL_EnableKeyRepeat(100, SDL_DEFAULT_REPEAT_INTERVAL))) {
		fprintf(stderr, "Setting keyboard repeat failed: %s\n", SDL_GetError());
		error = true;
	}

	glEnable(GL_TEXTURE_2D);
	glShadeModel(GL_SMOOTH);
	glClearColor(0.0f, 0.0f, 0.6f, 0.0f);
	glEnable( GL_DEPTH_TEST );

	// Enable transparency
	glEnable (GL_BLEND); glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	return (!error);
}

/*!
	Initializes audio subsystem.
*/
bool Screen::initAl() {
	bool error = false;

	if (!alutInit(0, 0)) {
		error = true;
	}

	return (!error);
}

/*!
	Function to reset our viewport after a window resize.
*/
bool Screen::resizeEvent(int width, int height) {
	bool error = false;

	Screen::surface = SDL_SetVideoMode(width, height, Screen::getBpp(), Screen::videoFlags);
	if (!Screen::surface) {
		fprintf(stderr,
		"Could not get a surface after resize: %s\n",
		SDL_GetError());
		error = true;
	}

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

	return (!error);
}

int Screen::getScreenWidth() {
	if (surface) {
		return surface->w;
	} else {
		return DEFAULT_SCREEN_WIDTH;
	}
}

int Screen::getScreenHeight() {
	if (surface) {
		return surface->h;
	} else {
		return DEFAULT_SCREEN_HEIGHT;
	}
}

int Screen::getBpp() {
	if (surface) {
		return surface->format->BitsPerPixel;
	} else {
		return DEFAULT_SCREEN_BPP;
	}
}
