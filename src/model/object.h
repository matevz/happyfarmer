/* 
 * File:   HFObject.h
 * Author: matevz
 *
 * Created on Sreda, 6 avgust 2014, 21:05
 */

#ifndef HFOBJECT_H
#define	HFOBJECT_H

#include <QPoint>

/**
 * Movable objects like tractors, animals etc.
 * A single construction and multiple movable objects can exist on a single tile.
 */
class HFObject {
public:
	enum HFObjType {
		AnimalSheep
	};
	
	enum HFOrientation {
		W=0,
		NW=1,
		N=2,
		NE=3,
		E=4,
		SE=5,
		S=6,
		SW=7
	};
	
	HFObject(HFObjType type, QPointF pos);
	HFObject(const HFObject& orig);
	virtual ~HFObject();
	
	void setPos(QPointF pos) { _x=pos.x(); _y=pos.y(); }
	QPointF pos() { return QPointF(_x,_y); }

private:
	HFObjType _type;
	double _x, _y;
	HFOrientation _orientation;
};

#endif	/* HFOBJECT_H */

