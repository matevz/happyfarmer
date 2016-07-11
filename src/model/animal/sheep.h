/*!
	Copyright (c) 2014, Matevž Jekovec, Happy Farmer development team
	All Rights Reserved. See AUTHORS for a complete list of authors.

	Licensed under the GNU GENERAL PUBLIC LICENSE. See COPYING for details.
*/

#ifndef HFOBJSHEEP_H
#define	HFOBJSHEEP_H

#include "model/object.h"

class HFObjSheep : public HFObject {
public:
	HFObjSheep( HFGame *game, QVector3D pos );
	virtual ~HFObjSheep();
	
	bool wakeUp(qint64 curTime);

private:
	QPointF _direction;
};

#endif	/* HFOBJSHEEP_H */

