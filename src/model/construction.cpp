/*!
	Copyright (c) 2012, Matevž Jekovec, Happy Farmer development team
	All Rights Reserved. See AUTHORS for a complete list of authors.

	Licensed under the GNU GENERAL PUBLIC LICENSE. See COPYING for details.
*/

#include <model/construction.h>
#include <model/tile.h>
#include <model/game.h>

#include <iostream>

HFConstruction::HFConstruction( HFConstruction::HFConsType type, HFTile *tile )
 : _consType( type ), _tile(tile) {
}


HFConstruction::~HFConstruction() {
}

void HFConstruction::calculateOrientation() {
	_orientation.clear();
	
	// heights 0011 and 1100 are always roads 000111000
	QString hStr = HFTile::heightToString(_tile->height());
	if (hStr=="0011" || hStr=="1100") {
		_orientation = "000111000";
	} else
	if (hStr=="0110" || hStr=="1001") {
		_orientation = "010010010";
	} else {
		HFTile *t;
		
		_orientation += "0";
		if ((t=_tile->game()->tileAt( _tile->x()+1, _tile->y() )) &&
			t->construction() &&
			t->construction()->consType()&HFConstruction::ROAD_MASK &&
			(t->construction()->consType()&HFConstruction::ROAD_MASK)==(consType()&HFConstruction::ROAD_MASK)
		   ) {
			_orientation += "1";
		} else {
			_orientation += "0";
		}
		_orientation += "0";
		
		if ((t=_tile->game()->tileAt( _tile->x(), _tile->y()-1 )) &&
			t->construction() &&
			t->construction()->consType()&HFConstruction::ROAD_MASK &&
			(t->construction()->consType()&HFConstruction::ROAD_MASK)==(consType()&HFConstruction::ROAD_MASK)
		   ) {
			_orientation += "1";
		} else {
			_orientation += "0";
		}
		_orientation += "1";
		if ((t=_tile->game()->tileAt( _tile->x(), _tile->y()+1 )) &&
			t->construction() &&
			t->construction()->consType()&HFConstruction::ROAD_MASK &&
			(t->construction()->consType()&HFConstruction::ROAD_MASK)==(consType()&HFConstruction::ROAD_MASK)
		   ) {
			_orientation += "1";
		} else {
			_orientation += "0";
		}
		
		_orientation += "0";
		if ((t=_tile->game()->tileAt( _tile->x()-1, _tile->y() )) &&
			t->construction() &&
			t->construction()->consType()&HFConstruction::ROAD_MASK &&
			(t->construction()->consType()&HFConstruction::ROAD_MASK)==(consType()&HFConstruction::ROAD_MASK)
		   ) {
			_orientation += "1";
		} else {
			_orientation += "0";
		}
		_orientation += "0";
	}
	
	if (_orientation=="010010000" || _orientation=="000010010") {
		_orientation="010010010";
	}
	if (_orientation=="000110000" || _orientation=="000011000") {
		_orientation="000111000";
	}
	if (_orientation=="000010000") { // default
		_orientation = "010010010";
	}
}
