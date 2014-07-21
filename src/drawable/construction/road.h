/*!
	Copyright (c) 2012, Matevž Jekovec, Happy Farmer development team
	All Rights Reserved. See AUTHORS for a complete list of authors.

	Licensed under the GNU GENERAL PUBLIC LICENSE. See COPYING for details.
*/

#ifndef HFDCONSROAD_H
#define	HFDCONSROAD_H

#include <drawable/drawable.h>

class HFConsRoad;

class HFDConsRoad : public HFDrawable {
public:
	HFDConsRoad( HFConsRoad *road );
	virtual ~HFDConsRoad();
};

#endif