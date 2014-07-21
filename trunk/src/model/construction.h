/*!
	Copyright (c) 2012, Matevž Jekovec, Happy Farmer development team
	All Rights Reserved. See AUTHORS for a complete list of authors.

	Licensed under the GNU GENERAL PUBLIC LICENSE. See COPYING for details.
*/

#ifndef HFCONSTRUCTION_H
#define	HFCONSTRUCTION_H

#include <QString> // _orientation

class HFTile;

class HFConstruction {
public:
	enum HFConsType {
		AsphaltRoad,
		DirtRoad,
		Tree
	};
	
	HFConstruction( HFConsType, HFTile* );
	virtual ~HFConstruction();
	
	inline HFConsType consType() { return _consType; }
	inline HFTile* tile() { return _tile; }

	QString &orientation() { return _orientation; }
	void calculateOrientation();

protected:
	HFTile *_tile;
	QString _orientation;

private:
	HFConsType _consType;
};

#endif	/* HFTERRAIN_H */

