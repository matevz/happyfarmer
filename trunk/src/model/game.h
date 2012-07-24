/*!
	Copyright (c) 2012, Matevž Jekovec, Happy Farmer development team
	All Rights Reserved. See AUTHORS for a complete list of authors.

	Licensed under the GNU GENERAL PUBLIC LICENSE. See COPYING for details.
*/

#ifndef HFGAME_H
#define	HFGAME_H

class HFTerrain;

class HFGame {
public:
	HFGame(int w, int h);
	virtual ~HFGame();
	
	HFTerrain *terrainAt(int x, int y);
	
	inline const int width() const { return _width; }
	inline const int height() const { return _height; }
	
private:
	void init();
	
	int _width;
	int _height;
	HFTerrain **_terrain;
	
};

#endif	/* HFGAME_H */

