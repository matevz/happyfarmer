/*!
        Copyright (c) 2012, Matevž Jekovec, Happy farmer development team
        All Rights Reserved. See AUTHORS for a complete list of authors.

        Licensed under the GNU GENERAL PUBLIC LICENSE. See COPYING for details.
*/

#ifndef GAMEVIEW_H

#define GAMEVIEW_H

#include <QGraphicsView> 

class HFGameView : public QGraphicsView {
	Q_OBJECT

public:
	HFGameView( QWidget *parent = 0 );

protected:
	void mousePressEvent( QMouseEvent * event );
	void mouseMoveEvent( QMouseEvent * event );
};
		
#endif /* GAMEVIEW_H */ 
