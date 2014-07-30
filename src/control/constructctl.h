/*!
	Copyright (c) 2012, Matevž Jekovec, Happy Farmer development team
	All Rights Reserved. See AUTHORS for a complete list of authors.

	Licensed under the GNU GENERAL PUBLIC LICENSE. See COPYING for details.
*/

#ifndef HFCONSTRUCTCTL_H
#define	HFCONSTRUCTCTL_H

#include <QRect>
#include <QList>
#include "model/construction.h"

class HFTile;
class HFGame;

class HFConstructCtl {
public:
	HFConstructCtl(HFGame *g);
	virtual ~HFConstructCtl();
	QList<HFTile*> place(HFConstruction::HFConsType type, const QRect& area);
	
private:
	bool check(HFConstruction::HFConsType type, HFTile *tile);
	bool place(HFConstruction::HFConsType type, HFTile *tile);
	
	HFGame *_game;
};

#endif

