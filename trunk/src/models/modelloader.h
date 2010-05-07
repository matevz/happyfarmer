#ifndef MODELLOADER_H_
#define MODELLOADER_H_

#include <osg/Node>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

class ModelLoader {
public:
	osg::Node* loadModel( std::string modelname, std::string objectname="", int frame=-1 );
	std::string genFilenameFromFrame( std::string filename, int frame );

private:
};

#endif /*modelLOADER_H_*/
