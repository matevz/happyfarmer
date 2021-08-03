/*!
	Copyright (c) 2012, Matevž Jekovec, Happy Farmer development team
	All Rights Reserved. See AUTHORS for a complete list of authors.

	Licensed under the GNU GENERAL PUBLIC LICENSE. See COPYING for details.
*/

#ifndef HFTILE_H
#define	HFTILE_H

#include <QList>
#include <QPoint>
#include <QString>

class HFConstruction;
class HFGame;
class HFObject;

class HFTile {
public:
	HFTile(HFGame *game, int x, int y, int z, int height[4]);
	virtual ~HFTile();
	
	const int &x() const { return _x; }
    const int &y() const { return _y; }
	const int &z() const { return _z; }
    const QPoint pos() const { return QPoint(_x, _y); }

	int *height() { return _height; }
	
	inline HFConstruction *construction() { return _construction; }
	void setConstruction( HFConstruction *cons ) { _construction = cons; }
	
	static QString heightToString(int *);
	
	HFGame *game() { return _game; }
	
	const QList<HFObject*>& objects() const { return _objects; }
	void addObject(HFObject *obj) { _objects << obj; }
	void removeObject(HFObject *obj) { _objects.removeAll(obj); }
	
private:
	int _x;
	int _y;
	int _z;
	int _height[4];
	HFGame *_game;
	
	HFConstruction *_construction;
	QList<HFObject*> _objects;
};

#endif	/* HFTERRAIN_H */

