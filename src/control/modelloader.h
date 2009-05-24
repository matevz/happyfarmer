#ifndef modelLOADER_H_
#define modelLOADER_H_

#include <GL/gl.h>
#include <GL/glu.h>
#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <tr1/tuple>
#include "libobj/obj.hpp"
#include "libobj/obj_parser.hpp"

using namespace std;

void readVertex(obj::float_type x, obj::float_type y, obj::float_type z);
void readNormal(obj::float_type x, obj::float_type y, obj::float_type z);
void readUV(obj::float_type u, obj::float_type v);
void readObject(string s);
void readFace(std::tr1::tuple <int,int,int>, std::tr1::tuple <int,int,int>, std::tr1::tuple <int,int,int>);
void readFace2(std::tr1::tuple <int,int> t1, std::tr1::tuple <int,int> t2, std::tr1::tuple <int,int> t3);
void readFace3(int ind1, int ind2, int ind3);


struct Vertex
{
	GLfloat val[3];
} ;

struct VectorPos
{
	string name;
	vector<Vertex> vertices;
} ;

struct Normal
{
	GLfloat val[3];
} ;

struct TexUV
{
	GLfloat val[2];
} ;

struct Material
{
	string name ;

	GLfloat Ka[3] ;
	GLfloat Kd[3] ;
	GLfloat Ks[3] ;
	GLfloat Ns ;
	GLfloat Tr ;
	GLfloat Ni ;
	GLuint illum ;
	string map_Kd;

};

struct Texture
{
	GLuint glName ;
	string name ;
};

struct BoundingBox
{
	string name;

	vector<Vertex> vertices;
};

struct Face
{
	int vertexIndex[3];
	int normalIndex[3];
	int uvIndex[3];
	int matIndex;
} ;

struct ObjObject
{
	string name;
	GLuint displist;

	vector<Face> faces ;
} ;

struct ObjFile
{
	string name;
	GLuint displist;

	vector<Vertex> vertices ;
	vector<Normal> normals ;
	vector<TexUV> uvs ;
	vector<ObjObject> objects ;
	vector<Material> materials ;
	vector<Texture> textures ;

	vector<BoundingBox> bboxes ;
	vector<VectorPos> positions;
} ;

struct Model
{
	string name ;

	vector<ObjFile> objfiles ;
} ;

class ModelLoader
{
public:
	static GLuint loadModel( string modelname, string objectname="", int frame=-1 );

	static VectorPos getPos( string, string, int frame=-1 ) ;
	static vector<BoundingBox> getBoundingBox( string, VectorPos , int frame=-1) ;


	//void renderModel(GLfloat x, GLfloat y, GLfloat z, GLfloat angle);

	static string genFilenameFromFrame( string filename, int frame );
	static void parseMtl(string s);

	static vector<Model> models ;
	//void applyTexture(Lib3dsMesh *mesh);

private:
	static obj::obj_parser file;
};

#endif /*modelLOADER_H_*/
