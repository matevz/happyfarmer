/*!
	Copyright (c) 2012, Matevž Jekovec, Happy Farmer development team
	All Rights Reserved. See AUTHORS for a complete list of authors.

	Licensed under the GNU GENERAL PUBLIC LICENSE. See COPYING for details.
*/

#ifndef HFTILE_H
#define	HFTILE_H

#include <QString>

class HFConstruction;
class HFGame;

class HFTile {
public:
	HFTile(HFGame *game, int x, int y, int z, int height[4]);
	virtual ~HFTile();
	
	const int &x() const { return _x; }
	const int &y() const { return _y; }
	const int &z() const { return _z; }
	
	int *height() { return _height; }
	
	inline HFConstruction *construction() { return _construction; }
	void setConstruction( HFConstruction *cons ) { _construction = cons; }
	
	static QString heightToString(int *);
	
	HFGame *game() { return _game; }
	
private:
	int _x;
	int _y;
	int _z;
	int _height[4];
	HFGame *_game;
	
	HFConstruction *_construction;
};

#endif	/* HFTERRAIN_H */

