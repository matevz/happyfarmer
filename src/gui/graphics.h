#ifndef GRAPHICS_H_
#define GRAPHICS_H_

class SDL_Surface;

class Graphics {
public:
	// system actions
	Graphics();
	~Graphics();
	bool init();
	bool resize(int w, int h);

	inline int getWindowWidth() { return _windowWidth; }
	inline int getWindowHeight() { return _windowHeight; }

	// game actions
	double getCameraX() { return _cameraX; }
	double getCameraY() { return _cameraY; }
	double getCameraZoom() { return _cameraZoom; }
	void setCamera( double x, double y, double zoom ) { _cameraX=x; _cameraY=y; _cameraZoom=zoom; }

	void zoomIn();
	void zoomOut();
	void moveLeft();
	void moveRight();
	void moveUp();
	void moveDown();

private:
	// system properties
	SDL_Surface *_surface;
	int _windowWidth;
	int _windowHeight;
	int _bpp;
	int _videoFlags;

	static const int DEFAULT_SCREEN_WIDTH;
	static const int DEFAULT_SCREEN_HEIGHT;
	static const int DEFAULT_SCREEN_BPP;
	static const double SCROLL_FACTOR;
	static const double TERRAIN_ANGLE; // view angle in degrees
	static const double MAGNIFIER_FACTOR;

	// game properties
	double _cameraX;
	double _cameraY;
	double _cameraZoom;
};

#endif /* GRAPHICS_H_ */
