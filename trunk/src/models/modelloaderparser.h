#ifndef MODELLOADERPARSER_H_
#define MODELLOADERPARSER_H_

#include "models/model.h"
#include "models/objparser.h"

class ModelLoaderParser: public ObjParser {
public:
	ModelLoaderParser();
	ModelLoaderParser( Model* model, int objFileNo );
	virtual ~ModelLoaderParser();

	void geometric_vertex(const float&, const float&, const float&);
	void vertex_normal(const float&, const float&, const float&);
	void texture_vertex(const float&, const float&);
	void object_name(const std::string&);
	void material_library(const std::string&);
	void material_name(const std::string&);
	void triangular_face_geometric_vertices_texture_vertices_vertex_normals(const int&, const int&, const int&, const int&, const int&, const int&, const int&, const int&, const int&);
	void triangular_face_geometric_vertices_vertex_normals(const int&, const int&, const int&, const int&, const int&, const int&);
	void triangular_face_geometric_vertices(const int&, const int&, const int&);

	void parseMtl(std::string filename);

private:
	Model *_model; // model being imported

	/////////////////////////
	// Temporary variables //
	/////////////////////////
	Material _mat;

	int _objFileNo, _objectNo;
	int _materialIndex;
};

#endif /* MODELLOADERPARSER_H_ */
