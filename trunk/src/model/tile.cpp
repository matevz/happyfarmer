/*!
	Copyright (c) 2012, Matevž Jekovec, Happy Farmer development team
	All Rights Reserved. See AUTHORS for a complete list of authors.

	Licensed under the GNU GENERAL PUBLIC LICENSE. See COPYING for details.
*/

#include <model/tile.h>

HFTile::HFTile(int x, int y, int z, int height[4])
 : _x(x), _y(y), _z(z) {
	for (int i=0; i<4; i++) {
		_height[i] = height[i];
	}
}


HFTile::~HFTile() {
}

