#include "models/modelloader.h"
#include <math.h>

using namespace std;

vector<Model*> ModelLoader::_models;

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
GLuint ModelLoader::loadModel( string modelname, string objectname, int frame ) {
	GLuint dlist;
	int rvalue=-1;
	string filename = genFilenameFromFrame( modelname, frame );
	int modelNo = -1;
	int objFileNo = 0;

	//check if we already have model in models vector
	for (int i=0;i<_models.size();++i) {
		if(_models[i]->name==modelname) {
			modelNo = i;
			break;
		}
	}

	//checking if we have the right frame (objfile)
	if (modelNo > -1) {
		for(int i=0;i<_models[modelNo]->objFiles.size();++i) {
			if (_models[modelNo]->objFiles[i].name==filename) {
				objFileNo = i ;
				break;
			}
		}
	}

	//if we already have this model at this frame in memory, we find display list for the right object and return it
	if ( (modelNo > -1) && (objFileNo > -1) ) {
		if(objectname.empty()) {
			return _models[modelNo]->objFiles[objFileNo].dispList ;
		}

		for(int i=0; i < _models[modelNo]->objFiles[objFileNo].objects.size() ; ++i) {
			if ( _models[modelNo]->objFiles[objFileNo].objects[i].name.find( objectname, 0 ) == 0 ) {
				return _models[modelNo]->objFiles[objFileNo].objects[i].dispList ;
			}
		}
	}

	Model *m = 0;
	if ( modelNo == -1) { //we create new model
		m = new Model;
		m->name = modelname;
		m->objFiles.clear();
		_models.push_back(m);
		modelNo = _models.size()-1;
	}

	//if we have reached this part of loadModel, we must create new objfile.
	_of.name = filename;
	_of.dispList = 999999;
	_of.objects.clear();
	_of.vertices.clear();
	_of.normals.clear();
	_of.uvs.clear();
	_of.materials.clear();
	_of.textures.clear();

	m->objFiles.push_back(_of);
	objFileNo = m->objFiles.size()-1 ;

	_file = ModelLoaderParser( m, objFileNo );

	_file.parse(filename);

	// we create display lists for all objects of this model at this frame
	dlist = glGenLists( m->objFiles[objFileNo].objects.size() );

	int lightside = GL_FRONT;
	bool hasUVs = (m->objFiles[objFileNo].uvs.size() > 0) ? true : false ;
	Texture tex;
	SDL_Surface * textureImage ;
	GLuint texIndex ;

	// load all the textures for all objects and faces of current objfile
	for(int j=0; j < m->objFiles[objFileNo].materials.size() ; j++) {
		if ( ! m->objFiles[objFileNo].materials[j].map_Kd.empty() ) {
			tex.name = m->objFiles[objFileNo].materials[j].map_Kd;
			SDL_RWops *rwop = SDL_RWFromFile( m->name.substr(0,m->name.find_last_of('/')+1).append( m->objFiles[objFileNo].materials[j].map_Kd ).c_str() , "rb");
			textureImage = IMG_LoadPNG_RW(rwop);
			delete rwop;
			if(!textureImage) {
			    std::cerr << "Resource::loadPng(): Error loading " << m->name.substr(0,m->name.find_last_of('/')+1).append( m->objFiles[objFileNo].materials[j].map_Kd ).c_str() << ", error " << IMG_GetError();
			    continue;
			}

			glGenTextures(1, &(tex.glName)); // allocate memory for one texture
			glBindTexture(GL_TEXTURE_2D, tex.glName); // use our newest texture
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, textureImage->w, textureImage->h, 0, GL_RGBA, GL_UNSIGNED_BYTE, textureImage->pixels );
			m->objFiles[objFileNo].textures.push_back(tex); // add the index of our newly created texture to textureIndices
		    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST );
		    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST );

			SDL_FreeSurface(textureImage);
		}
	}

	// create display lists for all objects of the current objfile

	for(int j=0; j < m->objFiles[objFileNo].objects.size() ; j++) {
		glNewList(dlist,GL_COMPILE);
		glDisable(GL_TEXTURE_2D);
		for(unsigned int i=0; i < m->objFiles[objFileNo].objects[j].faces.size() ; i++) {
			// introduce new material
			if (i==0 || m->objFiles[objFileNo].objects[j].faces[i].matIndex != m->objFiles[objFileNo].objects[j].faces[i-1].matIndex) {
				// material changed from the previous face
				if (i!=0 && m->objFiles[objFileNo].objects[j].faces[i].matIndex != m->objFiles[objFileNo].objects[j].faces[i-1].matIndex) {
					glDisable(GL_TEXTURE_2D);
				}

				if ( ! m->objFiles[objFileNo].materials[ m->objFiles[objFileNo].objects[j].faces[i].matIndex ].map_Kd.empty() ) {
					for(int k=0; k < m->objFiles[objFileNo].textures.size(); ++k) {
						if ( m->objFiles[objFileNo].textures[k].name == m->objFiles[objFileNo].materials[ m->objFiles[objFileNo].objects[j].faces[i].matIndex ].map_Kd) {
							texIndex = k;
							k = m->objFiles[objFileNo].textures.size() ;
						}
					}
//					glMaterialfv(lightside, GL_AMBIENT, m->objFiles[objFileNo].materials[ m->objFiles[objFileNo].objects[j].faces[i].matIndex ].Ka );
//					glMaterialfv(lightside, GL_DIFFUSE, m->objFiles[objFileNo].materials[ m->objFiles[objFileNo].objects[j].faces[i].matIndex ].Kd );
//					glMaterialfv(lightside, GL_SPECULAR, m->objFiles[objFileNo].materials[ m->objFiles[objFileNo].objects[j].faces[i].matIndex ].Ks );
//					glMaterialf(lightside, GL_SHININESS, m->objFiles[objFileNo].materials[ m->objFiles[objFileNo].objects[j].faces[i].matIndex ].Ns );
					glColor3f( 1.0, 1.0, 1.0 );

					glBindTexture(GL_TEXTURE_2D, m->objFiles[objFileNo].textures[texIndex].glName ) ;
					glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
					glEnable(GL_TEXTURE_2D);
				} else {
					glColor3f( m->objFiles[objFileNo].materials[ m->objFiles[objFileNo].objects[j].faces[i].matIndex ].Kd[0],
							m->objFiles[objFileNo].materials[ m->objFiles[objFileNo].objects[j].faces[i].matIndex ].Kd[1],
							m->objFiles[objFileNo].materials[ m->objFiles[objFileNo].objects[j].faces[i].matIndex ].Kd[2] );
				}
			}

			// texture coordinates
			if (hasUVs) {
				glBegin(GL_TRIANGLES);

				glNormal3fv( m->objFiles[objFileNo].normals[m->objFiles[objFileNo].objects[j].faces[i].normalIndex[0]].val  );
				glTexCoord2fv( m->objFiles[objFileNo].uvs[ m->objFiles[objFileNo].objects[j].faces[i].uvIndex[0] ].val ) ;
				glVertex3fv( m->objFiles[objFileNo].vertices[m->objFiles[objFileNo].objects[j].faces[i].vertexIndex[0]].val );

				glNormal3fv( m->objFiles[objFileNo].normals[m->objFiles[objFileNo].objects[j].faces[i].normalIndex[1]].val );
				glTexCoord2fv( m->objFiles[objFileNo].uvs[ m->objFiles[objFileNo].objects[j].faces[i].uvIndex[1] ].val ) ;
				glVertex3fv( m->objFiles[objFileNo].vertices[m->objFiles[objFileNo].objects[j].faces[i].vertexIndex[1]].val );

				glNormal3fv( m->objFiles[objFileNo].normals[m->objFiles[objFileNo].objects[j].faces[i].normalIndex[2]].val );
				glTexCoord2fv( m->objFiles[objFileNo].uvs[ m->objFiles[objFileNo].objects[j].faces[i].uvIndex[2] ].val ) ;
				glVertex3fv( m->objFiles[objFileNo].vertices[m->objFiles[objFileNo].objects[j].faces[i].vertexIndex[2]].val );

				glEnd();
			} else { // no texture coordinates
				glBegin(GL_TRIANGLES);

				glNormal3fv( m->objFiles[objFileNo].normals[m->objFiles[objFileNo].objects[j].faces[i].normalIndex[0]].val  );
				glVertex3fv( m->objFiles[objFileNo].vertices[m->objFiles[objFileNo].objects[j].faces[i].vertexIndex[0]].val );

				glNormal3fv( m->objFiles[objFileNo].normals[m->objFiles[objFileNo].objects[j].faces[i].normalIndex[1]].val );
				glVertex3fv( m->objFiles[objFileNo].vertices[m->objFiles[objFileNo].objects[j].faces[i].vertexIndex[1]].val );

				glNormal3fv( m->objFiles[objFileNo].normals[m->objFiles[objFileNo].objects[j].faces[i].normalIndex[2]].val );
				glVertex3fv( m->objFiles[objFileNo].vertices[m->objFiles[objFileNo].objects[j].faces[i].vertexIndex[2]].val );

				glEnd();
			}
		}
		glEndList();

		m->objFiles[objFileNo].objects[j].dispList = dlist;

		if ( (!objectname.empty()) && (m->objFiles[objFileNo].objects[j].name.find( objectname, 0 ) == 0 ) )
			rvalue = dlist;

		dlist++;
	}

	// when objectname is empty
	if ( objectname.empty() ) {
		rvalue = glGenLists(1);
		glNewList(rvalue,GL_COMPILE);

		for(int i=0; i < m->objFiles[objFileNo].objects.size(); i++) {
			glCallList(m->objFiles[objFileNo].objects[i].dispList) ;
		}
		glEndList();

		m->objFiles[objFileNo].dispList = rvalue;
	}

	//return the list we wanted
	if (rvalue > -1) {
		return rvalue;
	} else {
		std::cerr << "ModelLoader::loadModel error: Display list not generated." << std::endl;
		return 999999;
	}
}
