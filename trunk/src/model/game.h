/*!
	Copyright (c) 2012, Matevž Jekovec, Happy Farmer development team
	All Rights Reserved. See AUTHORS for a complete list of authors.

	Licensed under the GNU GENERAL PUBLIC LICENSE. See COPYING for details.
*/

#ifndef HFGAME_H
#define	HFGAME_H

class HFTile;

class HFGame {
public:
	HFGame(int w, int h);
	virtual ~HFGame();
	
	HFTile *tileAt(int x, int y);
	
	inline const int width() const { return _width; }
	inline const int height() const { return _height; }
	
private:
	void init();
	
	void genRndGame();
	
	int _width;
	int _height;
	HFTile **_tiles;
	
};

#endif	/* HFGAME_H */

