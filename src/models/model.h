#ifndef MODEL_H_
#define MODEL_H_

#include <string>
#include <vector>

#include <GL/gl.h>
#include <GL/glu.h>

struct Vertex {
	GLfloat val[3];
};

struct Normal {
	GLfloat val[3];
};

struct TexUV {
	GLfloat val[2];
};

struct Material {
	std::string name;

	GLfloat Ka[3];
	GLfloat Kd[3];
	GLfloat Ks[3];
	GLfloat Ns;
	GLfloat Tr;
	GLfloat Ni;
	GLuint illum;
	std::string map_Kd;
};

struct Texture {
	GLuint glName;
	std::string name;
};

struct Face {
	int vertexIndex[3];
	int normalIndex[3];
	int uvIndex[3];
	int matIndex;
};

struct ObjObject {
	std::string name;
	GLuint dispList;

	std::vector<Face> faces;
};

struct ObjFile {
	std::string name;
	GLuint dispList;

	std::vector<Vertex> vertices;
	std::vector<Normal> normals;
	std::vector<TexUV> uvs;
	std::vector<ObjObject> objects;
	std::vector<Material> materials;
	std::vector<Texture> textures;
};

struct Model {
	std::string name;

	std::vector<ObjFile> objFiles;
};

#endif
