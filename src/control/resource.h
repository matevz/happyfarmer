#ifndef RESOURCE_H_
#define RESOURCE_H_
#include <string>

struct SDL_Surface;

class Resource {
public:
	static std::string locateResource( std::string relPath );
	static SDL_Surface *loadPng( std::string path );

private:
	static const char DELIMITER;
	static std::string fixDelimiters( std::string path );
};

#endif /* RESOURCE_H_ */
