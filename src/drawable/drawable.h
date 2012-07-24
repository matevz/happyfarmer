/*!
	Copyright (c) 2012, Matevž Jekovec, Happy Farmer development team
	All Rights Reserved. See AUTHORS for a complete list of authors.

	Licensed under the GNU GENERAL PUBLIC LICENSE. See COPYING for details.
*/

#ifndef HFDRAWABLE_H
#define	HFDRAWABLE_H

#include <QGraphicsItemGroup>
#include <QGraphicsPixmapItem>

class HFDrawable : public QGraphicsItemGroup {
protected:
	QGraphicsPixmapItem *_front;
	QGraphicsPixmapItem *_back;
};

#endif