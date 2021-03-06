/*!
	Copyright (c) 2012-2019, Matevž Jekovec, Happy Farmer development team
	All Rights Reserved. See AUTHORS for a complete list of authors.

	Licensed under the GNU GENERAL PUBLIC LICENSE. See COPYING for details.
*/

#ifndef HFRESOURCE_H
#define	HFRESOURCE_H

#include <QPixmap>
#include <QStringList>
#include <QHash>

class HFResource {
public:
	HFResource();
	virtual ~HFResource();

	static QStringList TILE_HEIGHT_COMBINATIONS;
	static QStringList ROAD_COMBINATIONS;
	
	// pixmaps
	static QHash<QString, QPixmap> PIXMAP_HELPER_TILE;
	static QPixmap *PIXMAP_HELPER_DOT;
	static QHash<QString, QPixmap> PIXMAP_GRASS;
	static QHash<QString, QPixmap> PIXMAP_ASPHALT_ROAD;
	static QHash<QString, QPixmap> PIXMAP_DIRT_ROAD;
	static QHash<QString, QPixmap> PIXMAP_SHEEP;
};

#endif

