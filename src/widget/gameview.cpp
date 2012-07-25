/*!
        Copyright (c) 2012, Matevž Jekovec, Happy farmer development team
        All Rights Reserved. See AUTHORS for a complete list of authors.

        Licensed under the GNU GENERAL PUBLIC LICENSE. See COPYING for details.
*/

#include <widget/gameview.h>

#include <QMouseEvent>
#include <QTransform>
#include <QTimer>

#include <drawable/terrain/grass.h>
#include <model/terrain/grass.h>

#include <iostream>

#include "model/settings.h"

HFGameView::HFGameView(QWidget* parent)
 : QGraphicsView(parent),
   _scrollTimer( nullptr ), _hScrollDirection(0), _vScrollDirection(0) {
	setMouseTracking(true);
	setZoomLevel( 3 );
	setTransformationAnchor(NoAnchor);
}

void HFGameView::setScrollable(const bool& scrollable) {
	if (_scrollTimer) {
		_scrollTimer->stop();
		delete _scrollTimer;
		_scrollTimer = nullptr;
	}
	
	if (scrollable) {
		_scrollTimer = new QTimer(this);
		_scrollTimer->setInterval(40);
		_scrollTimer->setSingleShot(false);
		connect(_scrollTimer, SIGNAL(timeout()), this, SLOT(onScrollTimerTimeout()));
		
		_scrollTimer->start();
	}
}

void HFGameView::onScrollTimerTimeout() {
	if (_hScrollDirection || _vScrollDirection) {
		translate( _hScrollDirection*HFSettings::instance()->scrollSpeed(), _vScrollDirection*HFSettings::instance()->scrollSpeed() );
		std::cout << transform().m31() << std::endl;
	}
}

void HFGameView::mouseMoveEvent(QMouseEvent* event) {
	if (event->x()<50) {
		_hScrollDirection = 1;
	} else if (event->x() > geometry().width()-50) {
		_hScrollDirection = -1;
	} else {
		_hScrollDirection = 0;
	}
	
	if (event->y()<50) {
		_vScrollDirection = 1;
	} else if (event->y() > geometry().height()-50) {
		_vScrollDirection = -1;
	} else {
		_vScrollDirection = 0;
	}
	
	if (itemAt(event->pos())) {
//		std::cout << dynamic_cast<HFDTerrGrass*>(itemAt(event->pos())->parentItem())->grass()->x() << " "
//				  << dynamic_cast<HFDTerrGrass*>(itemAt(event->pos())->parentItem())->grass()->y() << std::endl;
	}
}

void HFGameView::leaveEvent( QEvent* event ) {
	_hScrollDirection = 0;
	_vScrollDirection = 0;
}

void HFGameView::mousePressEvent(QMouseEvent* event) {

}

void HFGameView::wheelEvent(QWheelEvent* event) {
	if ( event->delta()>0 ) {
		setZoomLevel( zoomLevel()+1 );
	} else if ( event->delta()<0 ) {
		setZoomLevel( zoomLevel()-1 );
	}
}

bool HFGameView::setZoomLevel( const int& zoomLevel ) {
	if (zoomLevel<0 || zoomLevel>4) {
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
