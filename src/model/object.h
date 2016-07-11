/* 
 * File:   HFObject.h
 * Author: matevz
 *
 * Created on Sreda, 6 avgust 2014, 21:05
 */

#ifndef HFOBJECT_H
#define	HFOBJECT_H

class HFGame;

#include <QVector3D>

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
	
	HFObject(HFGame *game, HFObjType type, QVector3D pos);
	HFObject(const HFObject& orig);
	virtual ~HFObject();
	
	void setPos(QVector3D pos) { _pos = pos; }
	const QVector3D& pos() const { return _pos; }	
	const float x() const { return _pos.x(); }
	const float y() const { return _pos.y(); }
	const float z() const { return _pos.z(); }
	
	const HFObjType objType() const { return _type; }
	
	virtual bool wakeUp(qint64 curTime) { return false; }

protected:
	QVector3D _pos;
	HFOrientation _orientation;	
	HFGame *_game;
	
private:
	HFObjType _type;
};

typedef QList<HFObject*> HFObjectList; // hack to solve connecting signal with QList<HFObject*> argument to the slot

#endif	/* HFOBJECT_H */

