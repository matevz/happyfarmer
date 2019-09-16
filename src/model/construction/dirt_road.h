/*!
	Copyright (c) 2019, Matevž Jekovec, Happy Farmer development team
	All Rights Reserved. See AUTHORS for a complete list of authors.

	Licensed under the GNU GENERAL PUBLIC LICENSE. See COPYING for details.
*/

#ifndef HF_CONS_DIRT_ROAD_H
#define	HF_CONS_DIRT_ROAD_H

#include "model/construction.h"

class HFConsDirtRoad : public HFConstruction {
public:
	HFConsDirtRoad( HFTile* );
	virtual ~HFConsDirtRoad();
};

#endif
