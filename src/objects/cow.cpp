#include "objects/cow.h"
#include "models/modelloader.h"
#include "control/resource.h"
#include "gui/scene.h"
#include "core/terrain.h"
#include "core/tile.h"
#include "core/point.h"
#include "objects/fence.h"
#include <math.h>

GLuint Cow::_dispList = 0;

Cow::Cow( Player* p, const float& x, const float& y )
 : MovingObject( p, x, y, 0 ), _dx(0), _dy(0), _dz(0), _state(Stand) {
	if (!Cow::_dispList) {
		_dispList = ModelLoader().loadModel( Resource::locateModel("cow/cow") );
	}
}

Cow::~Cow() {
}

void Cow::draw( const unsigned long long& time ) {
    glPushMatrix();

	glTranslatef( 0.25, 0.25, 0 );
	glTranslatef( _x, _y, _z );
	if (_dx > 0 && _dy==0) {
    	glRotatef( -90.0f, 0.0, 0.0, 1.0 );
    }
    if (_dx < 0 && _dy==0) {
    	glRotatef( 90.0f, 0.0, 0.0, 1.0 );
    }
    if (_dy > 0 && _dx==0) {
    	glRotatef( 0.0f, 0.0, 0.0, 1.0 );
    }
    if (_dy < 0 && _dx==0) {
    	glRotatef( 180.0f, 0.0, 0.0, 1.0 );
    }
	if (_dx > 0 && _dy>0) {
    	glRotatef( -45.0f, 0.0, 0.0, 1.0 );
    }
    if (_dx < 0 && _dy<0) {
    	glRotatef( 135.0f, 0.0, 0.0, 1.0 );
    }
    if (_dy > 0 && _dx<0) {
    	glRotatef( 45.0f, 0.0, 0.0, 1.0 );
    }
    if (_dy < 0 && _dx>0) {
    	glRotatef( -135.0f, 0.0, 0.0, 1.0 );
    }
	glTranslatef( -0.25, -0.25, 0 );

	glCallList( Cow::_dispList );
	glPopMatrix();
}

void Cow::update( const unsigned long long& time ) {
	if (_state==Stand) {
		_state = ((rand()%50==1)?Walk:Stand);
		if (_state==Walk) {
			_dx=_dy=0;
		}
	} else if (_state==Walk) {
		if (!_dx && !_dy) {
			int dirX = (rand()%3)-1;
			int dirY = (rand()%3)-1;
			Tile *tile = Scene::getScene()->getTerrain()->getTile( (int)_x+dirX, (int)_y+dirY );
			if (tile && !tile->contains<Fence>() && !Scene::getScene()->contains<Cow>((int)_x+dirX, (int)_y+dirY)) {
				_dx = 0.05f*dirX;
				_dy = 0.05f*dirY;
				_state=Walk;
			} else {
				_state=Stand;
			}
		} else {
			_x += _dx;
			_y += _dy;
			Tile *tile = Scene::getScene()->getTerrain()->getTile( (int)_x, (int)_y );

			double tmp;
			if ((modf(_x,&tmp)>=0.94 || modf(_x,&tmp)<=0.11) && (modf(_y,&tmp)<=0.11 || modf(_y,&tmp)>=0.94)) {
				_state=Stand;
			}
		}
	}
}
