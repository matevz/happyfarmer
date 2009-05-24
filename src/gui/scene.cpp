#include <string>
#include "gui/scene.h"
#include "core/world.h"
#include "core/tile.h"
#include "core/point3d.h"
#include <alut.h>
#include <GL/gl.h>
#include <GL/glu.h>

Vertex v;

Scene::Scene( World *w )
 : _world(w) {
	initScene();
}

Scene::~Scene()
{
	alutExit();
}

bool Scene::initScene() {
	loadTerrain();

	alutInit(0, 0);

	setCamera( 10.0, 10.0, 10.0, 5.0, 5.0, 0.0);

	return true;
}

/*!
 * Starts the scene.
 */
void Scene::startScene() {
	startTime();
}

/*!
 * Draws the whole scene.
 */
void Scene::draw() {
	glPushMatrix();
	glTranslatef(0.0,0.0,0.0);
	glCallList(_terrain);
	glPopMatrix();
}

/*!
 * Loads the hall.
 */
void Scene::loadTerrain() {
	std::cout << "Loading terrain...";
	std::cout.flush();
	GLdouble x_m, y_m, z_m, u_m, v_m;
	_terrain = glGenLists(1);
	glNewList(_terrain,GL_COMPILE);
    glColor3f(   0.0f,  1.0f,  0.0f );
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	for (int x = 0; x < _world->getWidth(); x++) {
		for (int y = 0; y < _world->getHeight(); y++) {
			glBegin(GL_QUADS);
			//glNormal3f(0.0f, 0.0f, 1.0f);
			x_m = _world->getTile(x,y)->getPoint1()->getX();
			y_m = _world->getTile(x,y)->getPoint1()->getY();
			z_m = _world->getTile(x,y)->getPoint1()->getZ();
			u_m = 0.0f;
			v_m = 0.0f;
			//glTexCoord2d( u_m, v_m );
			glVertex3d( x_m, y_m, z_m );

			x_m = _world->getTile(x,y)->getPoint2()->getX();
			y_m = _world->getTile(x,y)->getPoint2()->getY();
			z_m = _world->getTile(x,y)->getPoint2()->getZ();
			u_m = 5.0f;
			v_m = 0.0f;
			//glTexCoord2d( u_m, v_m );
			glVertex3d( x_m, y_m, z_m );

			x_m = _world->getTile(x,y)->getPoint3()->getX();
			y_m = _world->getTile(x,y)->getPoint3()->getY();
			z_m = _world->getTile(x,y)->getPoint3()->getZ();
			u_m = 0.0f;
			v_m = 5.0f;
			//glTexCoord2d( u_m, v_m );
			glVertex3d( x_m, y_m, z_m );

			x_m = _world->getTile(x,y)->getPoint4()->getX();
			y_m = _world->getTile(x,y)->getPoint4()->getY();
			z_m = _world->getTile(x,y)->getPoint4()->getZ();
			u_m = 5.0f;
			v_m = 5.0f;
			//glTexCoord2d( u_m, v_m );
			glVertex3d( x_m, y_m, z_m );

			glEnd();
		}
	}

	glEndList();
	std::cout << "done." << std::endl;
}

void Scene::zoomIn() {
	setCamera( cameraXPos()-5, cameraYPos()-5, cameraZPos()-5, cameraXOri()-5, cameraYOri()-5, cameraZOri()-5 );
}

void Scene::zoomOut() {
	setCamera( cameraXPos()+5, cameraYPos()+5, cameraZPos()+5, cameraXOri()+5, cameraYOri()+5, cameraZOri()+5 );
}
