#ifndef MODELLOADER_H_
#define MODELLOADER_H_

#include <GL/gl.h>
#include <GL/glu.h>
#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <tr1/tuple>

#include "models/modelloaderparser.h"
#include "models/model.h"

class ModelLoader {
public:
	GLuint loadModel( std::string modelname, std::string objectname="", int frame=-1 );
	std::string genFilenameFromFrame( std::string filename, int frame );

	static std::vector<Model*>& modelList() { return _models; }
private:
	static std::vector<Model*> _models;

	ModelLoaderParser _file;
	ObjFile _of;
};

#endif /*modelLOADER_H_*/
