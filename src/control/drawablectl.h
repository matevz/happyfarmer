/*!
	Copyright (c) 2012, Matevž Jekovec, Happy Farmer development team
	All Rights Reserved. See AUTHORS for a complete list of authors.

	Licensed under the GNU GENERAL PUBLIC LICENSE. See COPYING for details.
*/

#ifndef HFDRAWABLECTL_H
#define	HFDRAWABLECTL_H

class HFMainWin;
class HFTile;
class HFGame;
class HFDrawable;

#include <QGraphicsScene>
#include <QHash>

class HFDrawableCtl {
public:
	HFDrawableCtl();
	virtual ~HFDrawableCtl();
	
	void rebuildTerrain( HFGame* );
	void rebuildTile( HFTile*, bool rebuildAdjacentTiles );
	
	inline QGraphicsScene *scene() { return &_scene; }
	
private:
	QGraphicsScene _scene;
	QHash<HFTile*, HFDrawable*> _drawableTiles; // drawable tiles and constructions
};

#endif

