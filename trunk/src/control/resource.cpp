#include <fstream>
#include <iostream> //debug
#include <SDL_image.h>
#include "control/resource.h"

#ifdef WINDOWS32
const char Resource::DELIMITER = '\\';
#else
const char Resource::DELIMITER = '/';
#endif

using namespace std;

/*!
	Finds the correct path of the given resource file.
	Resources are usually textures, sounds, models and other data files.

	Use forward slashes for directory delimiters.

	This function first searches in the following order:
	1) current working directory,
	2) src/ directory

	Function returns empty string, if none found.
*/
string Resource::locateResource( string relPath ) {
	string path = relPath;
	ifstream stream;

	stream.open((path=fixDelimiters(relPath)).c_str());
	if (stream.is_open()) {
		return path;
	}

	stream.open((path=fixDelimiters(string("src/")+relPath)).c_str());
	if (stream.is_open()) {
		return path;
	}

	std::cerr << "Resource::locateResource(): Unable to find " + relPath << std::endl;
	return "";
}

/*!
	This function replaces any forward slash delimiters with the back-slashed
	delimiters;
 */
string Resource::fixDelimiters( string path ) {
#ifdef WINDOWS32
	for ( int i=0; (i=path.find('/',i)) != npos; i++ ) {
		path.replace( i, 1, DELIMITER );
	}
#endif

	return path;
}

/*!
	Loads the PNG file into SDL_Surface structure.
	Note: This function requires SDL_Image library.

	User needs to delete the returned surface, once used.
 */
SDL_Surface *Resource::loadPng( string path ) {
	SDL_RWops *rwop = SDL_RWFromFile(path.c_str(), "rb");
	SDL_Surface *image = IMG_LoadPNG_RW(rwop);
	if(!image) {
	    std::cerr << "Resource::loadPng(): Error loading " << path << ", error " << IMG_GetError();
	}

	delete rwop;

	return image;
}
