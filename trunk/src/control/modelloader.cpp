#include "control/modelloader.h"
#include <math.h>

obj::obj_parser ModelLoader::file;
vector<Model> ModelLoader::models;

Vertex t;
Normal n;
TexUV tuv;
Material mat;
Face l;
ObjObject o;
ObjFile of;
Model m;
Texture tex;


int objfileNo, modelNo, materialNo, objectNo, bbNo, vpNo;
int materialIndex=-1;
bool noRender=false;
bool bbox=false;
bool pos=false;


void ModelLoader::parseMtl(string s)
{

	string line;
	string word;
	ifstream ifs(s.c_str());
	istringstream ss;
	bool brk=false;
	GLfloat r,g,b ;
	int i;
	int blanklines=0;



	if( !ifs )
	{
    	std::cerr << "Error opening " << s << std::endl;
    	return;
  	}

  	while( getline(ifs,line) )
  	{

  		if(line[0]=='#') continue ; //it is a comment


  		if ( line.size() < 1 ) //blank line
  		{
  			blanklines++;

  			if( blanklines==2) //end of material
  			{
  				models[modelNo].objfiles[objfileNo].materials.push_back(mat);

  				mat.name="";
  				mat.Ka[0] = mat.Ka[1] = mat.Ka[2] = mat.Kd[0] = mat.Kd[1] = mat.Kd[2] = 0.0;
  				mat.Ks[0] = mat.Ks[1] = mat.Ks[2] = mat.Ns = mat.Ni = mat.Tr = 0.0;
  				mat.illum=0;
  				mat.map_Kd="";

  				blanklines=0;
  			}
  			continue ;
  		}

  		ss.clear();
  		ss.str(line);

  		while( (ss >> word) && (!brk) )
  		{
  			if( word=="newmtl")//we have a new material definition
  			{
  				ss >> word ;
  				brk=true;
  				//at this point, word contains the name of material

  				mat.name=word ;
  			}
  			else if (word=="Ka") //ambient rgb
			{
  				ss >> r >> g >> b ;
  				brk=true;
  				mat.Ka[0] = r;
  				mat.Ka[1] = g;
  				mat.Ka[2] = b;

			}
  			else if (word=="Kd") //diffuse rgb
			{
  				ss >> r >> g >> b ;
  				brk=true;
  				mat.Kd[0] = r;
  				mat.Kd[1] = g;
  				mat.Kd[2] = b;
			}
			else if ( word=="Ks") //specular rgb
			{
  				ss >> r >> g >> b ;
  				brk=true;
  				mat.Ks[0] = r;
  				mat.Ks[1] = g;
  				mat.Ks[2] = b;
			}
			else if (word=="Ns") //material shininess
  			{
  				ss >> r ;
  				brk=true;
  				mat.Ns = r;
  			}
  			else if (word=="Ni") //optical density
			{
  				ss >> r ;
  				brk=true;
  				mat.Ni = r;
			}
  			else if (word=="Tr" || word=="d") //alpha
  			{
  				ss >> r ;
  				brk=true;
  				mat.Tr = r;
  			}
  			else if (word=="illum") //illumination model
  			{
  				ss >> i ;
  				brk=true;
  				mat.illum = i;
  			}
  			else if (word=="map_Kd") //texture file
  			{
  				ss >> word ;
  				brk=true;
  				mat.map_Kd = word ;


  			}
  		}
  		//std::cerr << "MAT=" << word << "-" << r << "-" << g << "-" << b << std::endl;
  		brk=false;

  	}

	ifs.close();
	return;
}


void readMtlLib(string s)
{
	s = m.name.substr(0,m.name.find_last_of('/')+1).append(s);
	ModelLoader::parseMtl(s);
}


void readMaterial(string s)
{
	if(noRender)
	{
		return;
	}

	for(int i=0; i < ModelLoader::models[modelNo].objfiles[objfileNo].materials.size();++i)
	{
		if(ModelLoader::models[modelNo].objfiles[objfileNo].materials[i].name==s)
		{
			materialIndex = i;
			return;
		}
	}
}

void readVertex(obj::float_type x, obj::float_type y, obj::float_type z)
{
	t.val[0]=x;
	t.val[1]=y;
	t.val[2]=z;

	ModelLoader::models[modelNo].objfiles[objfileNo].vertices.push_back(t);

	if(bbox)
	{
		ModelLoader::models[modelNo].objfiles[objfileNo].bboxes[bbNo].vertices.push_back(t);
	}
	else if(pos)
	{
		ModelLoader::models[modelNo].objfiles[objfileNo].positions[vpNo].vertices.push_back(t);
	}

}

void readNormal(obj::float_type x, obj::float_type y, obj::float_type z)
{
	n.val[0]=x;
	n.val[1]=y;
	n.val[2]=z;
	ModelLoader::models[modelNo].objfiles[objfileNo].normals.push_back(n);
}

void readUV(obj::float_type u, obj::float_type v)
{
	tuv.val[0]=u;
	tuv.val[1]=v;
	ModelLoader::models[modelNo].objfiles[objfileNo].uvs.push_back(tuv);
}

void readObject(string s)
{
	if ( (s.find("bbox",0) == 0) )
	{
		//std::cerr << "OBJFILE=" << ModelLoader::models[modelNo].objfiles[objfileNo].name << " BSIZE=" << bbNo << std::endl;
		bbox=true;
		pos=false;
		noRender=true;

		BoundingBox bb;
		bb.name=s;
		ModelLoader::models[modelNo].objfiles[objfileNo].bboxes.push_back(bb);
		bbNo = ModelLoader::models[modelNo].objfiles[objfileNo].bboxes.size()-1;
		return;
	}
	else if (s.find("position",0) == 0)
	{
		pos=true;
		bbox=false;
		noRender=true;

		VectorPos vp;
		vp.name=s;
		ModelLoader::models[modelNo].objfiles[objfileNo].positions.push_back(vp);
		vpNo = ModelLoader::models[modelNo].objfiles[objfileNo].positions.size()-1;
		return;
	}

	bbox=pos=noRender=false;

	o.name = s;
	o.displist = -1;
	o.faces.clear();

	ModelLoader::models[modelNo].objfiles[objfileNo].objects.push_back(o);
	objectNo = ModelLoader::models[modelNo].objfiles[objfileNo].objects.size()-1;
}

void readFace3(int ind1, int ind2, int ind3)
{
	if(noRender)
		return;

		l.vertexIndex[0] = ind1 - 1 ;
		l.vertexIndex[1] = ind2 - 1 ;
		l.vertexIndex[2] = ind3 - 1 ;

		l.normalIndex[0] = -1;
		l.normalIndex[1] = -1;
		l.normalIndex[2] = -1;

		l.uvIndex[0] = -1;
		l.uvIndex[1] = -1;
		l.uvIndex[2] = -1;

		l.matIndex = materialIndex ;

		ModelLoader::models[modelNo].objfiles[objfileNo].objects[objectNo].faces.push_back(l);
}

void readFace(std::tr1::tuple <int,int,int> t1, std::tr1::tuple <int,int,int> t2, std::tr1::tuple <int,int,int> t3)
{
	if(noRender)
		return;

		l.vertexIndex[0] = (std::tr1::get<0>(t1))-1;
		l.vertexIndex[1] = (std::tr1::get<0>(t2))-1;
		l.vertexIndex[2] = (std::tr1::get<0>(t3))-1;

		l.normalIndex[0] = (std::tr1::get<2>(t1))-1;
		l.normalIndex[1] = (std::tr1::get<2>(t2))-1;
		l.normalIndex[2] = (std::tr1::get<2>(t3))-1;

		l.uvIndex[0] = (std::tr1::get<1>(t1))-1;
		l.uvIndex[1] = (std::tr1::get<1>(t2))-1;
		l.uvIndex[2] = (std::tr1::get<1>(t3))-1;

		l.matIndex = materialIndex ;

		ModelLoader::models[modelNo].objfiles[objfileNo].objects[objectNo].faces.push_back(l);

}

//variant without texture UVs
void readFace2(std::tr1::tuple <int,int> t1, std::tr1::tuple <int,int> t2, std::tr1::tuple <int,int> t3)
{
	if(noRender)
		return;

		l.vertexIndex[0] = (std::tr1::get<0>(t1))-1;
		l.vertexIndex[1] = (std::tr1::get<0>(t2))-1;
		l.vertexIndex[2] = (std::tr1::get<0>(t3))-1;

		l.normalIndex[0] = (std::tr1::get<1>(t1))-1;
		l.normalIndex[1] = (std::tr1::get<1>(t2))-1;
		l.normalIndex[2] = (std::tr1::get<1>(t3))-1;

		l.uvIndex[0] = -1;
		l.uvIndex[1] = -1;
		l.uvIndex[2] = -1;

		l.matIndex = materialIndex ;

		ModelLoader::models[modelNo].objfiles[objfileNo].objects[objectNo].faces.push_back(l);
}

/*!
 * Generates a correct filename from the base name + frame number.
 * This is the format Blender uses for exporting an animation to multiple
 * .obj files.
 */
string ModelLoader::genFilenameFromFrame( string modelname, int frame ) {
	if (frame > 999999) // frame number should be smaller than one million
		return modelname;

	if(frame==-1)
	{
		modelname += ".obj";
		return modelname ;
	}

	char appendedNumber[7];
	for (int i=0; i<6; i++) appendedNumber[i]='0';
	appendedNumber[6]='\0';

	char number[7];
	sprintf( number, "%i", frame );

	for (unsigned int i=0; i<strlen(number); i++) {
		appendedNumber[6-i-1] = number[strlen(number)-i-1];
	}

	modelname += "_";
	modelname += appendedNumber;
	modelname += ".obj";

	return modelname;
}


/*!
 * Loads an object named \a objectname from a file \a filename and a frame number \a frame
 * and returns the index of the generated display list.
 */
GLuint ModelLoader::loadModel( string modelname, string objectname, int frame )
{
	GLuint dlist;
	int rvalue=-1;
	string filename ;
	objfileNo=-1;
	modelNo=-1;
	objectNo=-1;

	filename = genFilenameFromFrame( modelname, frame );

	//check if we already have model in models vector
	for(int i=0;i<models.size();++i)
	{
		if(models[i].name==modelname)
		{
			modelNo = i;
			break;
		}
	}

	//checking if we have the right frame (objfile)
	if (modelNo > -1)
	{
		for(int i=0;i<models[modelNo].objfiles.size();++i)
		{
			if (models[modelNo].objfiles[i].name==filename)
			{
				objfileNo = i ;
				break;
			}
		}
	}

	//if we already have this model at this frame in memory, we find display list for the right object and return it
	if ( (modelNo > -1) && (objfileNo > -1) )
	{
		if(objectname.empty())
		{
			return models[modelNo].objfiles[objfileNo].displist ;
		}

		for(int i=0; i < models[modelNo].objfiles[objfileNo].objects.size() ; ++i)
		{
			if ( models[modelNo].objfiles[objfileNo].objects[i].name.find( objectname, 0 ) == 0 )
			{
				return models[modelNo].objfiles[objfileNo].objects[i].displist ;
			}
		}
	}

	if ( modelNo == -1)//we create new model
	{
		m.name = modelname;
		m.objfiles.clear();
		models.push_back(m);
		modelNo = models.size()-1;
	}

	//if we have reached this part of loadModel, we must create new objfile.
	of.name = filename;
	of.displist = 999999;
	of.objects.clear();
	of.vertices.clear();
	of.normals.clear();
	of.uvs.clear();
	of.materials.clear();
	of.textures.clear();
	of.bboxes.clear();
	of.positions.clear();

	models[modelNo].objfiles.push_back(of);
	objfileNo = models[modelNo].objfiles.size()-1 ;

	file = obj::obj_parser(2);

	file.geometric_vertex_callback(readVertex);
	file.vertex_normal_callback(readNormal);
	file.texture_vertex_callback(readUV);
	file.object_name_callback(readObject);
	file.material_library_callback(readMtlLib);
	file.material_name_callback(readMaterial);
	file.face_callbacks(readFace3,0,readFace2,readFace,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0);

	file = file.parse(filename);

	//we create display lists for all objects of this model at this frame
	dlist = glGenLists( models[modelNo].objfiles[objfileNo].objects.size() );

	int lightside = GL_FRONT;
	bool hasUVs = (models[modelNo].objfiles[objfileNo].uvs.size() > 0) ? true : false ;
	SDL_Surface * textureImage ;
	GLuint texIndex ;

	//load all the texture for all objects and faces of current objfile

	for(int j=0; j < models[modelNo].objfiles[objfileNo].materials.size() ; ++j)
	{
		if ( ! models[modelNo].objfiles[objfileNo].materials[j].map_Kd.empty() )
		{
			tex.name = models[modelNo].objfiles[objfileNo].materials[j].map_Kd ;
			textureImage = IMG_Load( m.name.substr(0,m.name.find_last_of('/')+1).append( models[modelNo].objfiles[objfileNo].materials[j].map_Kd ).c_str() ) ;

			glGenTextures(1, &(tex.glName)); // allocate memory for one texture
			models[modelNo].objfiles[objfileNo].textures.push_back(tex); // add the index of our newly created texture to textureIndices

			glBindTexture(GL_TEXTURE_2D, tex.glName); // use our newest texture

			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); // give the best result for texture magnification
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); //give the best result for texture minification
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
			gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGB, textureImage->w , textureImage->h, GL_RGB, GL_UNSIGNED_BYTE, textureImage->pixels); // genereate MipMap levels for our texture

			SDL_FreeSurface(textureImage);
		}
	}

	//create display lists for all objects of current objfile

	for(int j=0; j < models[modelNo].objfiles[objfileNo].objects.size() ; ++j)
	{

		glNewList(dlist,GL_COMPILE);
		glDisable(GL_TEXTURE_2D);
		for(unsigned int i=0; i < models[modelNo].objfiles[objfileNo].objects[j].faces.size() ; i++)
		{

				if(i==0)
				{
					glMaterialfv(lightside, GL_AMBIENT, models[modelNo].objfiles[objfileNo].materials[ models[modelNo].objfiles[objfileNo].objects[j].faces[i].matIndex ].Ka );
					glMaterialfv(lightside, GL_DIFFUSE, models[modelNo].objfiles[objfileNo].materials[ models[modelNo].objfiles[objfileNo].objects[j].faces[i].matIndex ].Kd );
					glMaterialfv(lightside, GL_SPECULAR, models[modelNo].objfiles[objfileNo].materials[ models[modelNo].objfiles[objfileNo].objects[j].faces[i].matIndex ].Ks );
					glMaterialf(lightside, GL_SHININESS, models[modelNo].objfiles[objfileNo].materials[ models[modelNo].objfiles[objfileNo].objects[j].faces[i].matIndex ].Ns );

					if ( ! models[modelNo].objfiles[objfileNo].materials[ models[modelNo].objfiles[objfileNo].objects[j].faces[i].matIndex ].map_Kd.empty() )
					{
						for(int k=0; k < models[modelNo].objfiles[objfileNo].textures.size(); ++k)
						{
							if ( models[modelNo].objfiles[objfileNo].textures[k].name == models[modelNo].objfiles[objfileNo].materials[ models[modelNo].objfiles[objfileNo].objects[j].faces[i].matIndex ].map_Kd)
							{
								texIndex = k;
								k = models[modelNo].objfiles[objfileNo].textures.size() ;
							}
						}
						glBindTexture(GL_TEXTURE_2D, models[modelNo].objfiles[objfileNo].textures[texIndex].glName ) ;
						glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
						glEnable(GL_TEXTURE_2D);
					}
				}
				else if ( models[modelNo].objfiles[objfileNo].objects[j].faces[i].matIndex != models[modelNo].objfiles[objfileNo].objects[j].faces[i-1].matIndex )
				{
					glDisable(GL_TEXTURE_2D);

					glMaterialfv(lightside, GL_AMBIENT, models[modelNo].objfiles[objfileNo].materials[ models[modelNo].objfiles[objfileNo].objects[j].faces[i].matIndex ].Ka );
					glMaterialfv(lightside, GL_DIFFUSE, models[modelNo].objfiles[objfileNo].materials[ models[modelNo].objfiles[objfileNo].objects[j].faces[i].matIndex ].Kd );
					glMaterialfv(lightside, GL_SPECULAR, models[modelNo].objfiles[objfileNo].materials[ models[modelNo].objfiles[objfileNo].objects[j].faces[i].matIndex ].Ks );
					glMaterialf(lightside, GL_SHININESS, models[modelNo].objfiles[objfileNo].materials[ models[modelNo].objfiles[objfileNo].objects[j].faces[i].matIndex ].Ns );

					if ( ! models[modelNo].objfiles[objfileNo].materials[ models[modelNo].objfiles[objfileNo].objects[j].faces[i].matIndex ].map_Kd.empty() )
					{
						for(int k=0; k < models[modelNo].objfiles[objfileNo].textures.size(); ++k)
						{
							if ( models[modelNo].objfiles[objfileNo].textures[k].name == models[modelNo].objfiles[objfileNo].materials[ models[modelNo].objfiles[objfileNo].objects[j].faces[i].matIndex ].map_Kd)
							{
								texIndex = k;
								k = models[modelNo].objfiles[objfileNo].textures.size() ;
							}
						}
						glBindTexture(GL_TEXTURE_2D, models[modelNo].objfiles[objfileNo].textures[texIndex].glName ) ;
						glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
						glEnable(GL_TEXTURE_2D);
					}
				}

				if (hasUVs) // if we have texture coordinates
				{

					glBegin(GL_TRIANGLES);

					glNormal3fv( models[modelNo].objfiles[objfileNo].normals[models[modelNo].objfiles[objfileNo].objects[j].faces[i].normalIndex[0]].val  );
					glTexCoord2fv( models[modelNo].objfiles[objfileNo].uvs[ models[modelNo].objfiles[objfileNo].objects[j].faces[i].uvIndex[0] ].val ) ;
					glVertex3fv( models[modelNo].objfiles[objfileNo].vertices[models[modelNo].objfiles[objfileNo].objects[j].faces[i].vertexIndex[0]].val );

					glNormal3fv( models[modelNo].objfiles[objfileNo].normals[models[modelNo].objfiles[objfileNo].objects[j].faces[i].normalIndex[1]].val );
					glTexCoord2fv( models[modelNo].objfiles[objfileNo].uvs[ models[modelNo].objfiles[objfileNo].objects[j].faces[i].uvIndex[1] ].val ) ;
					glVertex3fv( models[modelNo].objfiles[objfileNo].vertices[models[modelNo].objfiles[objfileNo].objects[j].faces[i].vertexIndex[1]].val );

					glNormal3fv( models[modelNo].objfiles[objfileNo].normals[models[modelNo].objfiles[objfileNo].objects[j].faces[i].normalIndex[2]].val );
					glTexCoord2fv( models[modelNo].objfiles[objfileNo].uvs[ models[modelNo].objfiles[objfileNo].objects[j].faces[i].uvIndex[2] ].val ) ;
					glVertex3fv( models[modelNo].objfiles[objfileNo].vertices[models[modelNo].objfiles[objfileNo].objects[j].faces[i].vertexIndex[2]].val );

  					glEnd();
				}
				else // without texture coordinates
				{
					glBegin(GL_TRIANGLES);

					glNormal3fv( models[modelNo].objfiles[objfileNo].normals[models[modelNo].objfiles[objfileNo].objects[j].faces[i].normalIndex[0]].val  );
					glVertex3fv( models[modelNo].objfiles[objfileNo].vertices[models[modelNo].objfiles[objfileNo].objects[j].faces[i].vertexIndex[0]].val );

					glNormal3fv( models[modelNo].objfiles[objfileNo].normals[models[modelNo].objfiles[objfileNo].objects[j].faces[i].normalIndex[1]].val );
					glVertex3fv( models[modelNo].objfiles[objfileNo].vertices[models[modelNo].objfiles[objfileNo].objects[j].faces[i].vertexIndex[1]].val );

					glNormal3fv( models[modelNo].objfiles[objfileNo].normals[models[modelNo].objfiles[objfileNo].objects[j].faces[i].normalIndex[2]].val );
					glVertex3fv( models[modelNo].objfiles[objfileNo].vertices[models[modelNo].objfiles[objfileNo].objects[j].faces[i].vertexIndex[2]].val );

  					glEnd();
				}
		}
		glEndList();

		models[modelNo].objfiles[objfileNo].objects[j].displist = dlist;

		if ( (!objectname.empty()) && (models[modelNo].objfiles[objfileNo].objects[j].name.find( objectname, 0 ) == 0 ) )
			rvalue = dlist;

		dlist++;
	}

	//when objectname is empty
	if ( objectname.empty() )
	{
		rvalue = glGenLists(1);
		glNewList(rvalue,GL_COMPILE);

		for(int i=0; i < models[modelNo].objfiles[objfileNo].objects.size(); ++i)
		{
			glCallList(models[modelNo].objfiles[objfileNo].objects[i].displist) ;
		}
		glEndList();

		models[modelNo].objfiles[objfileNo].displist = rvalue;
	}

	//return the list we wanted
	return (rvalue > -1) ? rvalue : 999999;
}

/*!
 * Returns the position of the given object.
 * This is usually called when querying the positions of a specific
 * performer, if the scene defines his position.
 */
VectorPos ModelLoader::getPos( string modelname, string objectname, int frame )
{
	modelNo=-1;
	objfileNo=-1 ;
	VectorPos vp;

	string filename = genFilenameFromFrame( modelname, frame );

	for(int i=0;i<models.size();++i)
	{
		if(models[i].name==modelname)
		{
			modelNo = i;
			break;
		}
	}

	if(modelNo == -1)
	{
		std::cerr << "Napaka v ModelLoader::getPos - nepredvidljivi rezultati sledijo!" << std::endl ;
		return vp;
	}

	for(int i=0;i<models[modelNo].objfiles.size();++i)
	{
		if (models[modelNo].objfiles[i].name==filename)
		{
			objfileNo = i ;
			break;
		}
	}

	if(objfileNo==-1)
	{
		std::cerr << "Napaka v ModelLoader::getPos - nepredvidljivi rezultati sledijo!" << std::endl ;
		return vp;
	}


	for(int i=0; i < models[modelNo].objfiles[objfileNo].positions.size() ; ++i)
	{
		if ( models[modelNo].objfiles[objfileNo].positions[i].name.find( objectname, 0 ) == 0 )
		{
			return models[modelNo].objfiles[objfileNo].positions[i] ;
		}
	}
	std::cerr << "Napaka v ModelLoader::getPos - nepredvidljivi rezultati sledijo!" << std::endl ;
	return vp ;
}

vector<BoundingBox> ModelLoader::getBoundingBox(string modelname, VectorPos vp, int frame)
{
	string filename = genFilenameFromFrame( modelname, frame );
	BoundingBox bb;
	vector<BoundingBox> bbs ;
	Vertex vmin, vmax;
	GLfloat angle;
	GLfloat temp;

	for(int i=0;i<models.size();++i)
	{
		if(models[i].name==modelname)
		{
			modelNo = i;
			break;
		}
	}

	if(modelNo == -1)
	{
		std::cerr << "Napaka v ModelLoader::getBoundingBox - nepredvidljivi rezultati sledijo!" << std::endl ;
		return bbs;
	}

	for(int i=0;i<models[modelNo].objfiles.size();++i)
	{
		if (models[modelNo].objfiles[i].name==filename)
		{
			objfileNo = i ;
			break;
		}
	}

	if(objfileNo==-1)
	{
		std::cerr << "Napaka v ModelLoader::getBoundingBox - nepredvidljivi rezultati sledijo!" << std::endl ;
		return bbs;
	}

	if( vp.name.empty() )
	{
		for(int i=0; i < models[modelNo].objfiles[objfileNo].bboxes.size() ; ++i)
		{
			bb = models[modelNo].objfiles[objfileNo].bboxes[i];

			//calculate and save xmin, xmax, ymin, ymax, zmin, zmax
			vmin.val[0] = bb.vertices[0].val[0];
			vmin.val[1] = bb.vertices[0].val[1];
			vmin.val[2] = bb.vertices[0].val[2];

			vmax.val[0] = bb.vertices[0].val[0];
			vmax.val[1] = bb.vertices[0].val[1];
			vmax.val[2] = bb.vertices[0].val[2];

			for(int i=1; i < bb.vertices.size();++i)
			{
				if(bb.vertices[i].val[0] > vmax.val[0])
					vmax.val[0] = bb.vertices[i].val[0] ;
				if(bb.vertices[i].val[1] > vmax.val[1])
					vmax.val[1] = bb.vertices[i].val[1] ;
				if(bb.vertices[i].val[2] > vmax.val[2])
					vmax.val[2] = bb.vertices[i].val[2] ;

				if(bb.vertices[i].val[0] < vmin.val[0])
					vmin.val[0] = bb.vertices[i].val[0] ;
				if(bb.vertices[i].val[1] < vmin.val[1])
					vmin.val[1] = bb.vertices[i].val[1] ;
				if(bb.vertices[i].val[2] < vmin.val[2])
					vmin.val[2] = bb.vertices[i].val[2] ;
			}
			bb.vertices.push_back(vmin);
			bb.vertices.push_back(vmax);

			bbs.push_back(bb);
		}

		return bbs ;
	}

	for(int i=0; i < models[modelNo].objfiles[objfileNo].bboxes.size() ; ++i)
	{
		bb = models[modelNo].objfiles[objfileNo].bboxes[i];

		angle = 4.71238898 - atan( (vp.vertices[1].val[1]-vp.vertices[0].val[1]) / (vp.vertices[1].val[0]-vp.vertices[0].val[0])) ;

		for(int j=0; j < bb.vertices.size();++j)
		{
			temp = bb.vertices[j].val[0] ;
			bb.vertices[j].val[0] = cos(angle)*temp + sin(angle)*bb.vertices[j].val[1];
			bb.vertices[j].val[1] = -sin(angle)*temp + cos(angle)*bb.vertices[j].val[1];
		}

		//translate x,y,z
		for(int j=0; j < bb.vertices.size();++j)
		{
			bb.vertices[j].val[0] += vp.vertices[0].val[0] ;
			bb.vertices[j].val[1] += vp.vertices[0].val[1] ;
			bb.vertices[j].val[2] += vp.vertices[0].val[2] ;
		}

		//calculate and save xmin, xmax, ymin, ymax, zmin, zmax
		vmin.val[0] = bb.vertices[0].val[0];
		vmin.val[1] = bb.vertices[0].val[1];
		vmin.val[2] = bb.vertices[0].val[2];

		vmax.val[0] = bb.vertices[0].val[0];
		vmax.val[1] = bb.vertices[0].val[1];
		vmax.val[2] = bb.vertices[0].val[2];

		for(int i=1; i < bb.vertices.size();++i)
		{
			if(bb.vertices[i].val[0] > vmax.val[0])
				vmax.val[0] = bb.vertices[i].val[0] ;
			if(bb.vertices[i].val[1] > vmax.val[1])
				vmax.val[1] = bb.vertices[i].val[1] ;
			if(bb.vertices[i].val[2] > vmax.val[2])
				vmax.val[2] = bb.vertices[i].val[2] ;

			if(bb.vertices[i].val[0] < vmin.val[0])
				vmin.val[0] = bb.vertices[i].val[0] ;
			if(bb.vertices[i].val[1] < vmin.val[1])
				vmin.val[1] = bb.vertices[i].val[1] ;
			if(bb.vertices[i].val[2] < vmin.val[2])
				vmin.val[2] = bb.vertices[i].val[2] ;
		}
		bb.vertices.push_back(vmin);
		bb.vertices.push_back(vmax);

		bbs.push_back(bb);
	}


	return bbs;
}
