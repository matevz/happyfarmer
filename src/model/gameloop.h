/*!
	Copyright (c) 2016, Matevž Jekovec, Happy Farmer development team
	All Rights Reserved. See AUTHORS for a complete list of authors.

	Licensed under the GNU GENERAL PUBLIC LICENSE. See COPYING for details.
*/

#ifndef HFGAMELOOP_H
#define	HFGAMELOOP_H

#include <QMultiMap>
#include <QThread>
#include <QMutex>

#include "model/object.h"

class HFGame;

class HFGameLoop : public QThread {
	Q_OBJECT
	void run();
	
public:
	HFGameLoop(HFGame *g);
	virtual ~HFGameLoop();
	
	void wakeUpObjectAfter(HFObject *obj, qint64 t);
	
	static const int SLEEP_TIME_IN_MSECS;
	
signals:
	void objectsUpdated(HFObjectList objects);

private:
	HFGame *_game;
	
	// priority queue of objects to be waken up at specific game time (ie. priority)
	QMultiMap<qint64, HFObject*> _objectQueue;
	
	QMultiMap<qint64, HFObject*> _objectQueueBuffer;
	QMutex _objectQueueBufferMutex;
};

#endif	/* HFGAMELOOP_H */

