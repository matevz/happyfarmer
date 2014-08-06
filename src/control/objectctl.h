/*!
	Copyright (c) 2012, Matevž Jekovec, Happy Farmer development team
	All Rights Reserved. See AUTHORS for a complete list of authors.

	Licensed under the GNU GENERAL PUBLIC LICENSE. See COPYING for details.
*/

#ifndef HFOBJECTCTL_H
#define	HFOBJECTCTL_H

#include <QRect>
#include <QList>
#include "model/object.h"

class HFTile;
class HFGame;

class HFObjectCtl {
public:
	HFObjectCtl(HFGame *g);
	virtual ~HFObjectCtl();
	HFObject *place(HFObject::HFObjType type, HFTile *tile);
	
private:
	bool check(HFObject::HFObjType type, HFTile *tile);
	
	HFGame *_game;
};

#endif

