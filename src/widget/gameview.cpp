/*!
        Copyright (c) 2012, Matevž Jekovec, Happy farmer development team
        All Rights Reserved. See AUTHORS for a complete list of authors.

        Licensed under the GNU GENERAL PUBLIC LICENSE. See COPYING for details.
*/

#include <widget/gameview.h>

#include <QMouseEvent>
#include <QTransform>
#include <QTimer>
#include <QList>

#include <drawable/drawable.h>
#include <drawable/terrain/grass.h>
#include <model/terrain/grass.h>
#include <model/tile.h>

#include <iostream>

#include <model/settings.h>

class QGraphicsItem;

HFGameView::HFGameView(QWidget* parent)
 : QGraphicsView(parent)
{
	setMouseTracking(true);
	setZoomLevel( 3 );
	setTransformationAnchor(NoAnchor);
}

void HFGameView::mouseMoveEvent(QMouseEvent* event) {
	emit mouseMove(event);
}

void HFGameView::mousePressEvent(QMouseEvent* event) {
	emit mousePress(event);
}

void HFGameView::wheelEvent(QWheelEvent* event) {
	if ( event->delta()>0 ) {
		setZoomLevel( zoomLevel()+1 );
	} else if ( event->delta()<0 ) {
		setZoomLevel( zoomLevel()-1 );
	}
}

bool HFGameView::setZoomLevel( const int& zoomLevel ) {
	if (zoomLevel<1 || zoomLevel>3) {
		return false;
	}
	
	if (zoomLevel>_zoomLevel) {
		scale(2, 2);
	} else {
		scale(0.5, 0.5);
	}
	
	_zoomLevel = zoomLevel;
	
	return true;
}

/**
 * Returns the tile at the given mouse coordinates.
 * 
 * @param pos Cursor location
 * @return HFTile* or nullptr if no tile is present at that position.
 */
HFTile *HFGameView::tileAt( const QPoint &pos ) {
	QList<QGraphicsItem*> itemsList = items(pos);
	if (itemsList.isEmpty()) {
		return nullptr;
	} else {
		return static_cast<HFDrawable*>(itemsList.last()->parentItem())->tile();
	}
}