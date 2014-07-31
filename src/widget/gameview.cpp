/*!
        Copyright (c) 2012, Matevž Jekovec, Happy farmer development team
        All Rights Reserved. See AUTHORS for a complete list of authors.

        Licensed under the GNU GENERAL PUBLIC LICENSE. See COPYING for details.
*/

#include "widget/gameview.h"

#include <QMouseEvent>
#include <QTransform>
#include <QTimer>
#include <QList>

#include "drawable/drawable.h"
#include "drawable/terrain/grass.h"
#include "model/terrain/grass.h"
#include "model/tile.h"
#include "control/drawablectl.h"

#include <iostream>

#include "model/settings.h"

#include "gameview.h"

class QGraphicsItem;

HFGameView::HFGameView(QWidget* parent)
 : QGraphicsView(parent),
   _drawableCtl( nullptr )
{
	setMouseTracking(true);
	setZoomLevel( 3 );
	setTransformationAnchor(NoAnchor);
}

void HFGameView::mouseMoveEvent(QMouseEvent* event) {
	float TRANSLATE_WEIGHT=6.0/_zoomLevel;
	if (event->buttons()&Qt::RightButton) {
		translate( (event->x()-_lastMovePos.x())*TRANSLATE_WEIGHT, (event->y()-_lastMovePos.y())*TRANSLATE_WEIGHT );
	}
	
	if (_drawableCtl->selectionMode()==HFDrawableCtl::HorizontalVertical) {
		HFTile *t = tileAt( event->pos() );
		if (t) {
			QRect sa = _drawableCtl->selectionArea();
			if (event->buttons()&Qt::LeftButton) {
				if (qAbs(_drawableCtl->selectionArea().x() - t->x())>qAbs(_drawableCtl->selectionArea().y() - t->y())) {
					// horizontal selection
					sa.setWidth( t->x()-sa.x()+1 );
					sa.setHeight( 1 );
				} else {
					// vertical selection
					sa.setWidth( 1 );
					sa.setHeight( t->y()-sa.y()+1 );
				}
			} else {
				sa = QRect( t->x(), t->y(), 1, 1 );
			}
			if (_drawableCtl->selectionArea()!=sa) {
				_drawableCtl->setSelectionArea( sa );
//				std::cout << "HFGameView::mouseMoveEvent(): x: " << sa.x() << " y: " << sa.y() << " r: " << sa.right() << " b: " << sa.bottom() << std::endl;
				_drawableCtl->updateHelpers();
			}
		}
	}

	
	_lastMovePos = event->pos();
	emit mouseMove(event);
}

void HFGameView::mousePressEvent(QMouseEvent* event) {
	_lastMovePos = event->pos();
	
	emit mousePress(event);
}

void HFGameView::mouseReleaseEvent(QMouseEvent* event) {
	emit mouseRelease(event);
	
	if (event->button()==Qt::LeftButton) {
		HFTile *t = tileAt( event->pos() );
		_drawableCtl->setSelectionArea( QRect( t->x(), t->y(), 1, 1 ) );
		_drawableCtl->updateHelpers();
	}
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
