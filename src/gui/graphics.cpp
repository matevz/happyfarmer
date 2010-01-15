#include "gui/graphics.h"

Graphics::Graphics(World *gameWorld){
	world = gameworld;
	init();
}

Graphics::~Graphics(){
	SDL_Quit();
}

void Graphics::init(){
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

	surface = SDL_SetVideoMode(DEFAULT_SCREEN_WIDTH, DEFAULT_SCREEN_HEIGHT, DEFAULT_SCREEN_BPP, videoFlags);

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
	glEnable (GL_BLEND);
	glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);


	Screen::surface = SDL_SetVideoMode(_screen_width, _screen_height, _bpp, videoFlags);
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

	ratio = (GLfloat) _screen_width / (GLfloat) _screen_height;

	// Setup our viewport.
	glViewport(0, 0, (GLint) _screen_width, (GLint) _screen_height);

	// change to the projection matrix and set our viewing volume.
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	// Make sure we're chaning the model view and not the projection
	glMatrixMode(GL_MODELVIEW);

	// Reset The View
	glLoadIdentity();

}

void Graphics::resizeEvent(int width, int height) {
	bool error = false;

	Screen::surface = SDL_SetVideoMode(width, height, _bpp, videoFlags);
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

}

void Graphics::genTerrain(){
	vector<Tile*> *terrain = world->getTerrain();
	glNewList(terrain, GL_COMPILE);
		glBegin(GL_QUADS);
		for(int i = 0; i < terrain->size(); i++){
			glVertex3f(terrain[i]->getPoint1()->x, terrain[i]->getPoint1()->y, terrain[i]->getPoint1()->z);
			glVertex3f(terrain[i]->getPoint2()->x, terrain[i]->getPoint2()->y, terrain[i]->getPoint2()->z);
			glVertex3f(terrain[i]->getPoint3()->x, terrain[i]->getPoint3()->y, terrain[i]->getPoint3()->z);
			glVertex3f(terrain[i]->getPoint4()->x, terrain[i]->getPoint4()->y, terrain[i]->getPoint4()->z);
		}
		glEnd();
	glEndList();
}
