/*!
	Copyright (c) 2012, Matevž Jekovec, Happy Farmer development team
	All Rights Reserved. See AUTHORS for a complete list of authors.

	Licensed under the GNU GENERAL PUBLIC LICENSE. See COPYING for details.
*/

#ifndef HFDTERRGRASS_H
#define	HFDTERRGRASS_H

#include <drawable/drawable.h>

class HFTerrGrass;

class HFDTerrGrass : public HFDrawable {
public:
	HFDTerrGrass( HFTerrGrass *grass );
	virtual ~HFDTerrGrass();
	
	HFTerrGrass *grass() { return _grass; }
	
private:
	HFTerrGrass *_grass;	
};

#endif