#ifndef OBJ_OBJ_PARSER_HPP_INCLUDED
#define OBJ_OBJ_PARSER_HPP_INCLUDED

#include <fstream>
#include <istream>
#include <string>

class ObjParser {
public:
  enum ParseType{
    PARSE_BLANK_LINES_AS_COMMENT = 1 << 0,
    TRIANGULATE_FACES = 1 << 1,
    TRANSLATE_NEGATIVE_INDICES = 1 << 2
  };

  ObjParser(int flags = 0);
  virtual ~ObjParser();
  bool parse(std::istream& istream);
  bool parse(const std::string& filename);

  virtual void info(const int&, const std::string&) {}
  virtual void warning(const int&, const std::string&) {}
  virtual void error(const int&, const std::string&) {}
  virtual void geometric_vertex(const float&, const float&, const float&) {}
  virtual void texture_vertex(const float&, const float&) {}
  virtual void vertex_normal(const float&, const float&, const float&) {}
  virtual void group_name(const std::string&) {}
  virtual void smoothing_group(const int&) {}
  virtual void object_name(const std::string&) {}
  virtual void material_library(const std::string&) {}
  virtual void material_name(const std::string&) {}
  virtual void comment(const std::string&) {}

  virtual void triangular_face_geometric_vertices(const int&, const int&, const int&) {}
  virtual void triangular_face_geometric_vertices_texture_vertices(const int&, const int&, const int&, const int&, const int&, const int&) {}
  virtual void triangular_face_geometric_vertices_vertex_normals(const int&, const int&, const int&, const int&, const int&, const int&) {}
  virtual void triangular_face_geometric_vertices_texture_vertices_vertex_normals(const int&, const int&, const int&, const int&, const int&, const int&, const int&, const int&, const int&) {}
  virtual void quadrilateral_face_geometric_vertices(const int&, const int&, const int&, const int&) {}
  virtual void quadrilateral_face_geometric_vertices_texture_vertices(const int&, const int&, const int&, const int&, const int&, const int&, const int&, const int&) {}
  virtual void quadrilateral_face_geometric_vertices_vertex_normals(const int&, const int&, const int&, const int&, const int&, const int&, const int&, const int&) {}
  virtual void quadrilateral_face_geometric_vertices_texture_vertices_vertex_normals(const int&, const int&, const int&, const int&, const int&, const int&, const int&, const int&, const int&, const int&, const int&, const int&) {}
  virtual void polygonal_face_geometric_vertices_begin(const int&, const int&, const int&) {}
  virtual void polygonal_face_geometric_vertices_vertex(const int&) {}
  virtual void polygonal_face_geometric_vertices_end() {}
  virtual void polygonal_face_geometric_vertices_texture_vertices_begin(const int&, const int&, const int&, const int&, const int&, const int&) {}
  virtual void polygonal_face_geometric_vertices_texture_vertices_vertex(const int&, const int&) {}
  virtual void polygonal_face_geometric_vertices_texture_vertices_end() {}
  virtual void polygonal_face_geometric_vertices_vertex_normals_begin(const int&, const int&, const int&, const int&, const int&, const int&) {}
  virtual void polygonal_face_geometric_vertices_vertex_normals_vertex(const int&, const int&) {}
  virtual void polygonal_face_geometric_vertices_vertex_normals_end() {}
  virtual void polygonal_face_geometric_vertices_texture_vertices_vertex_normals_begin(const int&, const int&, const int&, const int&, const int&, const int&, const int&, const int&, const int&) {}
  virtual void polygonal_face_geometric_vertices_texture_vertices_vertex_normals_vertex(const int&, const int&, const int&) {}
  virtual void polygonal_face_geometric_vertices_texture_vertices_vertex_normals_end() {}

private:
  int flags_;
};

#endif // OBJ_OBJ_PARSER_HPP_INCLUDED
