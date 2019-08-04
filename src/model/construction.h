/*!
	Copyright (c) 2012-2019, Matevž Jekovec, Happy Farmer development team
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
		AsphaltRoad=0x10,
		DirtRoad=0x11,
	};

	const unsigned int ROAD_MASK=0x10;

	HFConstruction( HFConsType, HFTile* );
	virtual ~HFConstruction();
	
	inline const HFConsType consType() const { return _consType; }
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

