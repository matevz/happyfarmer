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
	};
	
	static const QRect NO_SELECTION;

	HFDrawableCtl();
	virtual ~HFDrawableCtl();
	
	void rebuildScene( HFGame* );
	void rebuildTile( HFTile*, bool rebuildAdjacentTiles );
	
	inline QGraphicsScene *scene() { return &_scene; }
	
	void setSelectionMode( const SelectionMode& sm ) { _selectionMode = sm; }
	const SelectionMode& selectionMode() { return _selectionMode; }
	
	void setSelectionArea( const QRect& s ) { _selectionArea = s; }
	const QRect& selectionArea() { return _selectionArea; }

	void updateHelpers();

private slots:
	void on_objects_updated(HFObjectList objs);
	
private:
	QGraphicsScene _scene;
	QHash<HFTile*, HFDrawable*> _drawableTiles;     // drawable tiles and constructions
	QHash<HFObject*, HFDrawable*> _drawableObjects; // drawable objects
	
	HFGame *_game;
	QList<HFDHelperTile*> _selectionHelpers; // white rectangles
	SelectionMode _selectionMode; // selection helpers drawn?
	QRect _selectionArea; // selected rectangular area of tiles
};

#endif

