/*!
        Copyright (c) 2012, Matevž Jekovec, Happy farmer development team
        All Rights Reserved. See AUTHORS for a complete list of authors.

        Licensed under the GNU GENERAL PUBLIC LICENSE. See COPYING for details.
*/

#include <widget/gameview.h>

#include <QMouseEvent>

#include "drawable/terrain/grass.h"

#include <iostream>

HFGameView::HFGameView(QWidget* parent)
 : QGraphicsView(parent) {
	setMouseTracking(true);
}

void HFGameView::mouseMoveEvent(QMouseEvent* event) {
	if (itemAt(event->pos())) {
		std::cout << dynamic_cast<QGraphicsItem*>(itemAt(event->pos()))->parentItem()->x()/128 << " "
				  << dynamic_cast<QGraphicsItem*>(itemAt(event->pos()))->parentItem()->y()/64 << std::endl;
	}
}

void HFGameView::mousePressEvent(QMouseEvent* event) {
	
}
