#include "models/modelloaderparser.h"
#include <iostream> // debug
#include <sstream>

using namespace std;


ModelLoaderParser::ModelLoaderParser()
 : ObjParser( ObjParser::TRIANGULATE_FACES ), _model(0), _materialIndex(-1), _objFileNo(0), _objectNo(-1) {
}

ModelLoaderParser::ModelLoaderParser( Model* m, int objFileNo )
 : ObjParser( ObjParser::TRIANGULATE_FACES ), _model(m), _materialIndex(-1), _objFileNo(objFileNo), _objectNo(-1) {
}

ModelLoaderParser::~ModelLoaderParser() {
}

void ModelLoaderParser::geometric_vertex(const float& x, const float& y, const float& z) {
	Vertex t;
	t.val[0]=x;
	t.val[1]=y;
	t.val[2]=z;
	std::cout << "added vertx" << std::endl;
	_model->objFiles[_objFileNo].vertices.push_back(t);
}

void ModelLoaderParser::vertex_normal(const float& x, const float& y, const float& z) {
	Normal n;
	n.val[0]=x;
	n.val[1]=y;
	n.val[2]=z;
	_model->objFiles[_objFileNo].normals.push_back(n);
}

void ModelLoaderParser::texture_vertex(const float& u, const float& v) {
	TexUV tuv;
	tuv.val[0]=u;
	tuv.val[1]=v;
	_model->objFiles[_objFileNo].uvs.push_back(tuv);
}

void ModelLoaderParser::object_name(const std::string& s) {
	ObjObject o;
	o.name = s;
	o.dispList = -1;
	o.faces.clear();

	_model->objFiles[_objFileNo].objects.push_back(o);
	_objectNo = _model->objFiles[_objFileNo].objects.size()-1;
}

void ModelLoaderParser::material_library(const std::string& s) {
	std::string s2 = _model->name.substr(0,_model->name.find_last_of('/')+1).append(s);
	parseMtl(s2);
}

void ModelLoaderParser::material_name(const std::string& s) {
	for(int i=0; i < _model->objFiles[_objFileNo].materials.size();++i) {
		if(_model->objFiles[_objFileNo].materials[i].name==s)
		{
			_materialIndex = i;
			return;
		}
	}
}

void ModelLoaderParser::triangular_face_geometric_vertices(const int& ind1, const int& ind2, const int& ind3) {
	Face l;

	l.vertexIndex[0] = ind1 - 1 ;
	l.vertexIndex[1] = ind2 - 1 ;
	l.vertexIndex[2] = ind3 - 1 ;

	l.normalIndex[0] = -1;
	l.normalIndex[1] = -1;
	l.normalIndex[2] = -1;

	l.uvIndex[0] = -1;
	l.uvIndex[1] = -1;
	l.uvIndex[2] = -1;

	l.matIndex = _materialIndex;

	std::cout << "added face1" << std::endl;
	_model->objFiles[_objFileNo].objects[_objectNo].faces.push_back(l);
}

void ModelLoaderParser::triangular_face_geometric_vertices_texture_vertices_vertex_normals(const int& t11, const int& t12, const int& t13, const int& t21, const int& t22, const int& t23, const int& t31, const int& t32, const int& t33) {
	Face l;

	l.vertexIndex[0] = t11-1;
	l.vertexIndex[1] = t21-1;
	l.vertexIndex[2] = t31-1;

	l.normalIndex[0] = t13-1;
	l.normalIndex[1] = t23-1;
	l.normalIndex[2] = t33-1;

	l.uvIndex[0] = t12-1;
	l.uvIndex[1] = t22-1;
	l.uvIndex[2] = t32-1;

	l.matIndex = _materialIndex ;

	std::cout << "added face2" << std::endl;
	_model->objFiles[_objFileNo].objects[_objectNo].faces.push_back(l);
}

/*! Variant without the texture UVs */
void ModelLoaderParser::triangular_face_geometric_vertices_vertex_normals(const int& t11, const int& t12, const int& t21, const int& t22, const int& t31, const int& t32) {
	Face l;

	l.vertexIndex[0] = t11-1;
	l.vertexIndex[1] = t21-1;
	l.vertexIndex[2] = t31-1;

	l.normalIndex[0] = t12-1;
	l.normalIndex[1] = t22-1;
	l.normalIndex[2] = t32-1;

	l.uvIndex[0] = -1;
	l.uvIndex[1] = -1;
	l.uvIndex[2] = -1;

	l.matIndex = _materialIndex ;

	std::cout << "added face3" << std::endl;
	_model->objFiles[_objFileNo].objects[_objectNo].faces.push_back(l);
}

/*!
 * Parses the .mtl file.
 */
void ModelLoaderParser::parseMtl(std::string filename) {
	string line;
	string word;
	ifstream ifs(filename.c_str());
	istringstream ss;
	bool brk=false;
	GLfloat r,g,b ;
	int i;
	int blanklines=0;

	if( !ifs ) {
    	std::cerr << "Error opening " << filename << std::endl;
    	return;
  	}

  	while( getline(ifs,line) ) {
  		if(line[0]=='#') continue ; //it is a comment

  		if ( line.size() < 1 ) //blank line
  		{
  			blanklines++;

  			if( blanklines==2) //end of material
  			{
  				_model->objFiles[_objFileNo].materials.push_back(_mat);

  				_mat.name="";
  				_mat.Ka[0] = _mat.Ka[1] = _mat.Ka[2] = _mat.Kd[0] = _mat.Kd[1] = _mat.Kd[2] = 0.0;
  				_mat.Ks[0] = _mat.Ks[1] = _mat.Ks[2] = _mat.Ns = _mat.Ni = _mat.Tr = 0.0;
  				_mat.illum=0;
  				_mat.map_Kd="";

  				blanklines=0;
  			}
  			continue ;
  		}

  		ss.clear();
  		ss.str(line);

  		while( (ss >> word) && (!brk) ) {
  			if( word=="newmtl")//we have a new material definition
  			{
  				ss >> word ;
  				brk=true;
  				//at this point, word contains the name of material

  				_mat.name=word ;
  			}
  			else if (word=="Ka") //ambient rgb
			{
  				ss >> r >> g >> b ;
  				brk=true;
  				_mat.Ka[0] = r;
  				_mat.Ka[1] = g;
  				_mat.Ka[2] = b;

			}
  			else if (word=="Kd") //diffuse rgb
			{
  				ss >> r >> g >> b ;
  				brk=true;
  				_mat.Kd[0] = r;
  				_mat.Kd[1] = g;
  				_mat.Kd[2] = b;
			}
			else if ( word=="Ks") //specular rgb
			{
  				ss >> r >> g >> b ;
  				brk=true;
  				_mat.Ks[0] = r;
  				_mat.Ks[1] = g;
  				_mat.Ks[2] = b;
			}
			else if (word=="Ns") //material shininess
  			{
  				ss >> r ;
  				brk=true;
  				_mat.Ns = r;
  			}
  			else if (word=="Ni") //optical density
			{
  				ss >> r ;
  				brk=true;
  				_mat.Ni = r;
			}
  			else if (word=="Tr" || word=="d") //alpha
  			{
  				ss >> r ;
  				brk=true;
  				_mat.Tr = r;
  			}
  			else if (word=="illum") //illumination model
  			{
  				ss >> i ;
  				brk=true;
  				_mat.illum = i;
  			}
  			else if (word=="map_Kd") //texture file
  			{
  				ss >> word ;
  				brk=true;
  				_mat.map_Kd = word ;
  			}
  		}
  		brk=false;
  	}

	ifs.close();
	return;
}
