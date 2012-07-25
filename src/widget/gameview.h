/*!
        Copyright (c) 2012, Matevž Jekovec, Happy farmer development team
        All Rights Reserved. See AUTHORS for a complete list of authors.

        Licensed under the GNU GENERAL PUBLIC LICENSE. See COPYING for details.
*/

#ifndef GAMEVIEW_H

#define GAMEVIEW_H

#include <QGraphicsView> 

class QTimer;

class HFGameView : public QGraphicsView {
	Q_OBJECT

public:
	HFGameView( QWidget *parent = 0 );
	
	bool setZoomLevel( const int& zoomLevel );
	const int& zoomLevel() { return _zoomLevel; }

	void setScrollable( const bool& scrollable );
	bool isScrollable() { return _scrollTimer; }
	
protected:
	void mousePressEvent( QMouseEvent* );
	void mouseMoveEvent( QMouseEvent* );
	void leaveEvent( QEvent* );
	void wheelEvent( QWheelEvent* );

protected slots:
	void onScrollTimerTimeout();

private:
	QTimer *_scrollTimer; // timer for scrolling when mouse cursor reaches widget border, default NULL
	
	int _zoomLevel; // 1 - most zoom out, 4 - most zoom in
	int _hScrollDirection; // current horizontal scroll direction: -1 left, 1 right, 0 none
	int _vScrollDirection; // current vertical scroll direction: -1 up, 1 down, 0 none
};
		
#endif /* GAMEVIEW_H */ 
