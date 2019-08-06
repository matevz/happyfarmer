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

#include "model/object.h"

class HFDHelperTile;

class HFDrawableCtl : public QObject {
	Q_OBJECT

public:
	enum SelectionMode {
		None=0,
		Horizontal,
		Vertical,
		HorizontalVertical,
		Rectangular,
		Fixed,
		Dot,
	};
	
	static const QRect NO_SELECTION;

	HFDrawableCtl();
	virtual ~HFDrawableCtl();
	
	void rebuildScene( HFGame* );
	void rebuildTile( HFTile*, bool rebuildAdjacentTiles );
	
	inline QGraphicsScene *scene() { return &_scene; }
	
	void updateHelpers();

	SelectionMode selectionMode() const { return _selectionMode; }
	void setSelectionMode(SelectionMode m) { _selectionMode = m; }

	const QRect& selectionTileArea() const { return _selectionTileArea; }
	void setSelectionTileArea(const QRect& s) { _selectionTileArea = s; }

	const QRect& selectionDotArea() const { return _selectionDotArea; }
	void setSelectionDotArea(const QRect& s) { _selectionDotArea = s; }

private slots:
	void on_objects_updated(HFObjectList objs);
	
private:
	HFGame *_game;

	// Scene //
	///////////
	QGraphicsScene _scene;
	QHash<HFTile*, HFDrawable*> _drawableTiles;     // drawable tiles and constructions
	QHash<HFObject*, HFDrawable*> _drawableObjects; // drawable objects
	
	// Helpers //
	/////////////
	// selection helpers drawn?
	SelectionMode _selectionMode;
	// selected area of tiles
	QRect _selectionTileArea;
	// selected area of dots
	QRect _selectionDotArea;

	// drawable white rectangles/dots instances
	QList<HFDrawable*> _selectionHelpers;

};

#endif

