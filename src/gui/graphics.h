/*Contains the "physical" appearance of objects as well as drawing methods*/
#ifndef GRAPHICS_H_
#define GRAPHICS_H_

#include <SDL/SDL.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include "core/world.h"
#include "core/tile.h"

class Graphics {
public:
	Graphics(World *gameWorld);
	~Graphics();
	void init();
	void resize();
	void draw();

private:
	GLuint terrain = glGenLists(1);
	SDL_Surface *surface = 0;
	int _screen_width = 1024;
	int _screen_height = 768;
	int _bpp = 32;
	int videoFlags = 0;
	void genTerrain();
	World *world;

};

#endif /* GRAPHICS_H_ */
