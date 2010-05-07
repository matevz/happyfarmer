#include "gui/graphics.h"
#include <osg/Group>
#include <osgText/Text>
#include <osg/Geometry>
#include "core/game.h"

#include "models/modelloader.h" // debug
#include "control/resource.h"

const int Graphics::DEFAULT_SCREEN_WIDTH = 1024;
const int Graphics::DEFAULT_SCREEN_HEIGHT = 768;
const int Graphics::DEFAULT_SCREEN_BPP = 32;
const double Graphics::SCROLL_FACTOR = 0.8;
const double Graphics::TERRAIN_ANGLE = 60.0f;
const double Graphics::MAGNIFIER_FACTOR = 256;

/*!
	\class Graphics
	Contains graphics subsystem.
*/

Graphics::Graphics() {
}

Graphics::~Graphics() {
//	SDL_Quit();
}

bool Graphics::init() {
	bool error = false;

	// construct the viewer.
	_viewer = new osgViewer::Viewer();
	_sceneNode = ModelLoader().loadModel( Resource::locateModel("cow/cow") ); //new osg::Node();

	//    SnapImage* postDrawCallback = new SnapImage("PostDrawCallback.png");
	//  viewer.getCamera()->setPostDrawCallback(postDrawCallback);
	//    viewer.addEventHandler(new SnapeImageHandler('p',postDrawCallback));

	//    SnapImage* finalDrawCallback = new SnapImage("FinalDrawCallback.png");
	//    viewer.getCamera()->setFinalDrawCallback(finalDrawCallback);
	//    viewer.addEventHandler(new SnapeImageHandler('f',finalDrawCallback));

	osg::ref_ptr<osg::Group> group = new osg::Group;

	// add the HUD subgraph.
	if (_sceneNode.valid())
		group->addChild(_sceneNode.get());
	group->addChild(createHud());

	// set the scene to render
	_viewer->setSceneData(group.get());

	return (!error);
}

osg::Camera *Graphics::createHud() {
	// create a camera to set up the projection and model view matrices, and the subgraph to draw in the HUD
	osg::Camera* camera = new osg::Camera;

	// set the projection matrix
	camera->setProjectionMatrix(osg::Matrix::ortho2D(0, 1280, 0, 1024));

	// set the view matrix
	camera->setReferenceFrame(osg::Transform::ABSOLUTE_RF);
	camera->setViewMatrix(osg::Matrix::identity());

	// only clear the depth buffer
	camera->setClearMask(GL_DEPTH_BUFFER_BIT);

	// draw subgraph after main camera view.
	camera->setRenderOrder(osg::Camera::POST_RENDER);

	// we don't want the camera to grab event focus from the viewers main camera(s).
	camera->setAllowEventFocus(false);

	// add to this camera a subgraph to render
	{
		osg::Geode* geode = new osg::Geode();

		std::string timesFont("data/fonts/LiberationSans-Regular.ttf");

		// turn lighting off for the text and disable depth test to ensure it's always ontop.
		osg::StateSet* stateset = geode->getOrCreateStateSet();
		stateset->setMode(GL_LIGHTING, osg::StateAttribute::OFF);

		osg::Vec3 position(150.0f, 800.0f, 0.0f);
		osg::Vec3 delta(0.0f, -120.0f, 0.0f);

		{
			osgText::Text* text = new osgText::Text;
			geode->addDrawable(text);

			text->setFont(timesFont);
			text->setPosition(position);
			text->setText("Welcome to happy farmer :-)");

			position += delta;
		}

		{
			osg::BoundingBox bb;
			for (unsigned int i = 0; i < geode->getNumDrawables(); ++i) {
				bb.expandBy(geode->getDrawable(i)->getBound());
			}

			osg::Geometry* geom = new osg::Geometry;

			osg::Vec3Array* vertices = new osg::Vec3Array;
			float depth = bb.zMin() - 0.1;
			vertices->push_back(osg::Vec3(bb.xMin(), bb.yMax(), depth));
			vertices->push_back(osg::Vec3(bb.xMin(), bb.yMin(), depth));
			vertices->push_back(osg::Vec3(bb.xMax(), bb.yMin(), depth));
			vertices->push_back(osg::Vec3(bb.xMax(), bb.yMax(), depth));
			geom->setVertexArray(vertices);

			osg::Vec3Array* normals = new osg::Vec3Array;
			normals->push_back(osg::Vec3(0.0f, 0.0f, 1.0f));
			geom->setNormalArray(normals);
			geom->setNormalBinding(osg::Geometry::BIND_OVERALL);

			osg::Vec4Array* colors = new osg::Vec4Array;
			colors->push_back(osg::Vec4(1.0f, 1.0, 0.8f, 0.2f));
			geom->setColorArray(colors);
			geom->setColorBinding(osg::Geometry::BIND_OVERALL);

			geom->addPrimitiveSet(new osg::DrawArrays(GL_QUADS, 0, 4));

			osg::StateSet* stateset = geom->getOrCreateStateSet();
			stateset->setMode(GL_BLEND, osg::StateAttribute::ON);
			//stateset->setAttribute(new osg::PolygonOffset(1.0f,1.0f),osg::StateAttribute::ON);
			stateset->setRenderingHint(osg::StateSet::TRANSPARENT_BIN);

			geode->addDrawable(geom);
		}

		camera->addChild(geode);
	}

	return camera;
}

bool Graphics::resize(int width, int height) {
	bool error = false;

/*	Graphics::_surface = SDL_SetVideoMode(width, height, _bpp, _videoFlags);
	if (!Graphics::_surface) {
		fprintf(stderr,
		"Could not get a surface after resize: %s\n",
		SDL_GetError());
		error = true;
	}

	// Height / width ration
	GLfloat ratio;

	// Protect against a divide by zero
	if (height == 0)
		height = 1;

	ratio = (GLfloat) width / (GLfloat) height;

	// Setup our viewport.
	glViewport(0, 0, (GLint) width, (GLint) height);

	// change to the projection matrix and set our viewing volume.
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	// Make sure we're chaning the model view and not the projection
	glMatrixMode(GL_MODELVIEW);

	// Reset The View
	glLoadIdentity();
*/
	return true;
}

void Graphics::zoomIn() {
	if (_cameraZoom<3) {
		setCamera( _cameraX, _cameraY, _cameraZoom+1 );
	}
}

void Graphics::zoomOut() {
	if (_cameraZoom>0) {
		setCamera( _cameraX, _cameraY, _cameraZoom-1 );
	}
}

void Graphics::moveDown() {
	if ( _cameraX>0 && _cameraY>0 ) {
		setCamera( _cameraX-SCROLL_FACTOR, _cameraY-SCROLL_FACTOR, _cameraZoom );
	}
}

void Graphics::moveUp() {
	if ( _cameraX<Game::getInstance()->getTerrainWidth() && _cameraY<Game::getInstance()->getTerrainHeight() ) {
		setCamera( _cameraX+SCROLL_FACTOR, _cameraY+SCROLL_FACTOR, _cameraZoom );
	}
}

void Graphics::moveRight() {
	if ( _cameraX<Game::getInstance()->getTerrainWidth() && _cameraY>0 ) {
		setCamera( _cameraX+SCROLL_FACTOR, _cameraY-SCROLL_FACTOR, _cameraZoom );
	}
}

void Graphics::moveLeft() {
	if ( _cameraX>0 && _cameraY<Game::getInstance()->getTerrainHeight()-1 ) {
		setCamera( _cameraX-SCROLL_FACTOR, _cameraY+SCROLL_FACTOR, _cameraZoom );
	}
}
