/*!
	Copyright (c) 2012-2019, Matevž Jekovec, Happy Farmer development team
	All Rights Reserved. See AUTHORS for a complete list of authors.

	Licensed under the GNU GENERAL PUBLIC LICENSE. See COPYING for details.
*/

#ifndef HFDCONSASPHALTROAD_H
#define	HFDCONSASPHALTROAD_H

#include <drawable/drawable.h>

class HFConsAsphaltRoad;

class HFDConsAsphaltRoad : public HFDrawable {
public:
	HFDConsAsphaltRoad( HFConsAsphaltRoad *road );
	virtual ~HFDConsAsphaltRoad();
};

#endif
