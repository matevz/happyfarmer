/*!
	Copyright (c) 2014, Matevž Jekovec, Happy Farmer development team
	All Rights Reserved. See AUTHORS for a complete list of authors.

	Licensed under the GNU GENERAL PUBLIC LICENSE. See COPYING for details.
*/

#ifndef HFDHELPERTILE_H
#define	HFDHELPERTILE_H

#include <drawable/drawable.h>

class HFDHelperTile : public HFDrawable {
public:
	HFDHelperTile( HFTile *tile );
	virtual ~HFDHelperTile();
};

#endif