/*!
	Copyright (c) 2012, Matevž Jekovec, Happy Farmer development team
	All Rights Reserved. See AUTHORS for a complete list of authors.

	Licensed under the GNU GENERAL PUBLIC LICENSE. See COPYING for details.
*/

#ifndef HFTERRAIN_H
#define	HFTERRAIN_H

class HFTile {
public:
	HFTile(int x, int y, int z, int height[4]);
	virtual ~HFTile();
	
	const int &x() const { return _x; }
	const int &y() const { return _y; }
	const int &z() const { return _z; }
	
	int *height() { return _height; }
	
private:
	int _x;
	int _y;
	int _z;
	int _height[4];
};

#endif	/* HFTERRAIN_H */

