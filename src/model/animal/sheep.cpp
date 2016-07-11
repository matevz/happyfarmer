/*!
	Copyright (c) 2012, Matevž Jekovec, Happy Farmer development team
	All Rights Reserved. See AUTHORS for a complete list of authors.

	Licensed under the GNU GENERAL PUBLIC LICENSE. See COPYING for details.
*/

#include "model/animal/sheep.h"

#include "model/game.h"
#include "model/tile.h"

HFObjSheep::HFObjSheep( HFGame *game, QVector3D pos )
 : HFObject( game, AnimalSheep, pos ) {
	_game->gameLoop().wakeUpObjectAfter(this, 100);	
}

HFObjSheep::~HFObjSheep() {
}

bool HFObjSheep::wakeUp(qint64 t) {
	if ((((int)(_pos.x()*10) % 10) == 0) && (((int)(_pos.y()*10) % 10) == 0)) {
		_direction.setX( ((qrand()%100<99)?0:(qrand()%2==0)?-0.1:0.1) );
		_direction.setY( ((qrand()%100<99)?0:(qrand()%2==0)?-0.1:0.1) );
	}
	
	HFTile *tile = _game->tileAt(_pos);
	
	_pos.setX( _pos.x()+_direction.x() );
	_pos.setY( _pos.y()+_direction.y() );

	HFTile *newTile = _game->tileAt(_pos);

	if (tile!=newTile) {
		if (!newTile || newTile->objects().size()) {
			_direction *= -1;
			_pos.setX( _pos.x()+_direction.x() );
			_pos.setY( _pos.y()+_direction.y() );
		} else {
			tile->removeObject(this);
			newTile->addObject(this);
		}
	}
	
	_game->gameLoop().wakeUpObjectAfter(this, 70000+(qrand()%24000));
	return true;
}