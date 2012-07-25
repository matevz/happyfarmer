/*!
	Copyright (c) 2012, Matevž Jekovec, Happy Farmer development team
	All Rights Reserved. See AUTHORS for a complete list of authors.

	Licensed under the GNU GENERAL PUBLIC LICENSE. See COPYING for details.
*/

#ifndef HFTERRGRASS_H
#define	HFTERRGRASS_H

#include <model/tile.h>

class HFTerrGrass : public HFTile {
public:
	HFTerrGrass(int x, int y, int z, int height[4]);
	virtual ~HFTerrGrass();
private:

};

#endif	/* HFTERRGRASS_H */

