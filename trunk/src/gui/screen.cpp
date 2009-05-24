#include <GL/gl.h>
#include <GL/glu.h>
#include "gui/screen.h"

int Screen::SCREEN_WIDTH = 800;
int Screen::SCREEN_HEIGHT = 600;
int Screen::SCREEN_BPP = 32;
SDL_Surface *Screen::surface = 0;
int Screen::videoFlags = 0;

void Screen::quit(int returnCode) {
	SDL_Quit();
}

bool Screen::initGl() {
	bool done = false;
	SDL_Event event;
	const SDL_VideoInfo *videoInfo;

	// initialize SDL
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		fprintf(stderr, "Video initialization failed: %s\n", SDL_GetError());
		quit(1);
	}

	videoInfo = SDL_GetVideoInfo();

	if (!videoInfo) {
		fprintf(stderr, "Video query failed: %s\n", SDL_GetError());
		quit(1);
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

	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

	surface = SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP,
			videoFlags);

	// Verify there is a surface
	if (!surface) {
		fprintf(stderr, "Video mode set failed: %s\n", SDL_GetError());
		quit(1);
	}

	// Enable key repeat
	if ((SDL_EnableKeyRepeat(100, SDL_DEFAULT_REPEAT_INTERVAL))) {
		fprintf(stderr, "Setting keyboard repeat failed: %s\n", SDL_GetError());
		quit(1);
	}

    // Enable Texture Mapping
	glEnable(GL_TEXTURE_2D);

	// Enable smooth shading
	glShadeModel(GL_SMOOTH);

	// Set the background black
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

	// Depth buffer setup
	glClearDepth(1.0f);

	// Enables Depth Testing
	glEnable(GL_DEPTH_TEST);

	// The Type Of Depth Test To Do
	glDepthFunc(GL_LEQUAL);

	// Really Nice Perspective Calculations
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

	// Enable Light One
	glEnable(GL_LIGHT1);

	// Full Brightness, 50% Alpha
	glColor4f(1.0f, 1.0f, 1.0f, 0.5f);

	// Blending Function For Translucency Based On Source Alpha Value
	glBlendFunc(GL_SRC_ALPHA, GL_ONE);

	return true;
}
