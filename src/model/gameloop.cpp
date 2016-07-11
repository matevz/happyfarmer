/*!
	Copyright (c) 2016, Matevž Jekovec, Happy Farmer development team
	All Rights Reserved. See AUTHORS for a complete list of authors.

	Licensed under the GNU GENERAL PUBLIC LICENSE. See COPYING for details.
*/

#include "model/gameloop.h"
#include "model/game.h"
#include "model/object.h"

#include <iostream>

const int HFGameLoop::SLEEP_TIME_IN_MSECS = 30;

HFGameLoop::HFGameLoop(HFGame *g) : QThread(),
 _game(g) {
	
}

HFGameLoop::~HFGameLoop() {
}

/*!
	Wakes up the object obj after t milliseconds of game time.
*/
void HFGameLoop::wakeUpObjectAfter(HFObject *obj, qint64 t) {
	_objectQueue.insertMulti(t+_game->dateTime().toMSecsSinceEpoch(), obj);
}

void HFGameLoop::run() {
	while (true) {
		_game->addMSecs(60*1000);
		qint64 newTime = _game->dateTime().toMSecsSinceEpoch();
		HFObjectList updatedObjs;
		
		while (!_objectQueue.isEmpty() && _objectQueue.firstKey()<newTime) {
			HFObject* obj = _objectQueue.take(_objectQueue.firstKey());
			if (obj->wakeUp(newTime)) {
				updatedObjs << obj;
			}
		}

		if (updatedObjs.size()) {
			emit(objectsUpdated(updatedObjs));
		}

		QThread::msleep(SLEEP_TIME_IN_MSECS);
	}
}