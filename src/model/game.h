/*!
	Copyright (c) 2012, Matevž Jekovec, Happy Farmer development team
	All Rights Reserved. See AUTHORS for a complete list of authors.

	Licensed under the GNU GENERAL PUBLIC LICENSE. See COPYING for details.
*/

#ifndef HFGAME_H
#define	HFGAME_H

#include "model/gameloop.h"

#include <QPointF>
#include <QVector3D>
#include <QDateTime>

class HFTile;

class HFGame {
public:
	enum HFGameSpeed {
		Pause = 0,
		Slow = 1,
		Normal = 2,
		Fast = 3,
		Ultra = 4
	};
	
	HFGame(int w, int h, QDateTime dateTime = QDateTime());
	virtual ~HFGame();
	void start();
	void end();
	
	HFTile *tileAt(int x, int y);
	HFTile *tileAt(QPointF pos);
	HFTile *tileAt(QVector3D pos);
	
	const int width() const { return _width; }
	const int height() const { return _height; }
	
	const HFGameSpeed speed() const { return _speed; }
	void setSpeed(const HFGameSpeed& s) { _speed = s; }
	
	const QDateTime& dateTime() const { return _dateTime; }
	void addMSecs(qint64 msecs) { _dateTime = _dateTime.addMSecs(msecs); }
	
	HFGameLoop& gameLoop() { return _gameLoop; }
	
private:
	void init();
	
	void genRndGame();
	
	HFGameSpeed _speed;
	QDateTime  _dateTime; // current game date and time
	HFGameLoop _gameLoop;
	
	int _width;
	int _height;
	HFTile **_tiles;
	
};

#endif	/* HFGAME_H */

