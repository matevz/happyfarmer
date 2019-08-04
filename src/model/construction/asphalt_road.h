/*!
	Copyright (c) 2012-2019, Matevž Jekovec, Happy Farmer development team
	All Rights Reserved. See AUTHORS for a complete list of authors.

	Licensed under the GNU GENERAL PUBLIC LICENSE. See COPYING for details.
*/

#ifndef HF_CONS_ASPHALT_ROAD_H
#define	HF_CONS_ASPHALT_ROAD_H

#include "model/construction.h"

class HFConsAsphaltRoad : public HFConstruction {
public:
	HFConsAsphaltRoad( HFTile* );
	virtual ~HFConsAsphaltRoad();
};

#endif
