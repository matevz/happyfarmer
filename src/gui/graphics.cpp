#include <SDL/SDL.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include "gui/graphics.h"
#include "core/game.h"

const int Graphics::DEFAULT_SCREEN_WIDTH = 1024;
const int Graphics::DEFAULT_SCREEN_HEIGHT = 768;
const int Graphics::DEFAULT_SCREEN_BPP = 32;
const double Graphics::SCROLL_FACTOR = 0.8;
const double Graphics::TERRAIN_ANGLE = 60.0f;
const double Graphics::MAGNIFIER_FACTOR = 256;

/*!
	\class Graphics
	Contains graphics subsystem.
*/

Graphics::Graphics()
 : _surface(0), _windowWidth(1024), _windowHeight(768), _bpp(32), _videoFlags(0) {
}

Graphics::~Graphics() {
	SDL_Quit();
}

bool Graphics::init() {
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

	_videoFlags = SDL_OPENGL; // Enable OpenGL in SDL
	_videoFlags |= SDL_GL_DOUBLEBUFFER; // Enable double buffering
	_videoFlags |= SDL_HWPALETTE; // Store the palette in hardware
	_videoFlags |= SDL_RESIZABLE; // Enable window resizing

	// This checks to see if surfaces can be stored in memory
	if (videoInfo->hw_available) {
		_videoFlags |= SDL_HWSURFACE;
	} else {
		_videoFlags |= SDL_SWSURFACE;
	}

	// This checks if hardware blits can be done
	if (videoInfo->blit_hw) {
		_videoFlags |= SDL_HWACCEL;
	}

	_surface = SDL_SetVideoMode(DEFAULT_SCREEN_WIDTH, DEFAULT_SCREEN_HEIGHT, DEFAULT_SCREEN_BPP, _videoFlags);

	// Verify there is a surface
	if (!_surface) {
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

	return (!error);
}

bool Graphics::resize(int width, int height) {
	bool error = false;

	Graphics::_surface = SDL_SetVideoMode(width, height, _bpp, _videoFlags);
	if (!Graphics::_surface) {
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

	return true;
}

void Graphics::zoomIn() {
	if (_cameraZoom<3) {
		setCamera( _cameraX, _cameraY, _cameraZoom+1 );
	}
}

void Graphics::zoomOut() {
	if (_cameraZoom>0) {
		setCamera( _cameraX, _cameraY, _cameraZoom-1 );
	}
}

void Graphics::moveDown() {
	if ( _cameraX>0 && _cameraY>0 ) {
		setCamera( _cameraX-SCROLL_FACTOR, _cameraY-SCROLL_FACTOR, _cameraZoom );
	}
}

void Graphics::moveUp() {
	if ( _cameraX<Game::getInstance()->getTerrainWidth() && _cameraY<Game::getInstance()->getTerrainHeight() ) {
		setCamera( _cameraX+SCROLL_FACTOR, _cameraY+SCROLL_FACTOR, _cameraZoom );
	}
}

void Graphics::moveRight() {
	if ( _cameraX<Game::getInstance()->getTerrainWidth() && _cameraY>0 ) {
		setCamera( _cameraX+SCROLL_FACTOR, _cameraY-SCROLL_FACTOR, _cameraZoom );
	}
}

void Graphics::moveLeft() {
	if ( _cameraX>0 && _cameraY<Game::getInstance()->getTerrainHeight()-1 ) {
		setCamera( _cameraX-SCROLL_FACTOR, _cameraY+SCROLL_FACTOR, _cameraZoom );
	}
}
