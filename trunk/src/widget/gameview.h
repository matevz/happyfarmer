/*!
        Copyright (c) 2012, Matevž Jekovec, Happy farmer development team
        All Rights Reserved. See AUTHORS for a complete list of authors.

        Licensed under the GNU GENERAL PUBLIC LICENSE. See COPYING for details.
*/

#ifndef GAMEVIEW_H

#define GAMEVIEW_H

#include <QGraphicsView> 
#include <QPoint>

class QTimer;
class HFTile;

class HFGameView : public QGraphicsView {
	Q_OBJECT

public:
	HFGameView( QWidget *parent = 0 );
	
	bool setZoomLevel( const int& zoomLevel );
	const int& zoomLevel() { return _zoomLevel; }

	HFTile *tileAt( const QPoint &pos );

signals:
	void mousePress( QMouseEvent* );
	void mouseMove( QMouseEvent* );

protected:
	void mousePressEvent( QMouseEvent* );
	void mouseMoveEvent( QMouseEvent* );
	void wheelEvent( QWheelEvent* );

private:
	int _zoomLevel; // 1 - most zoom out, 4 - most zoom in
};
		
#endif /* GAMEVIEW_H */ 
