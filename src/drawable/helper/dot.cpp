/*!
	Copyright (c) 2019, Matevž Jekovec, Happy Farmer development team
	All Rights Reserved. See AUTHORS for a complete list of authors.

	Licensed under the GNU GENERAL PUBLIC LICENSE. See COPYING for details.
*/

#include <drawable/helper/dot.h>
#include <model/resource.h>
#include <model/tile.h>

#include <QDebug>

#include "model/game.h"

HFDHelperDot::HFDHelperDot( HFTile *tile )
 : HFDrawable(tile) {
	qDebug() << "new helperDot!\n";
	_back = new QGraphicsPixmapItem(*HFResource::PIXMAP_HELPER_DOT, this);
}

HFDHelperDot::~HFDHelperDot() {

}
