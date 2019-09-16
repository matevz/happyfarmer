/*!
	Copyright (c) 2019, Matevž Jekovec, Happy Farmer development team
	All Rights Reserved. See AUTHORS for a complete list of authors.

	Licensed under the GNU GENERAL PUBLIC LICENSE. See COPYING for details.
*/

#ifndef HFDCONSDIRTROAD_H
#define	HFDCONSDIRTROAD_H

#include <drawable/drawable.h>

class HFConsDirtRoad;

class HFDConsDirtRoad : public HFDrawable {
public:
	HFDConsDirtRoad( HFConsDirtRoad *road );
	virtual ~HFDConsDirtRoad();
};

#endif
