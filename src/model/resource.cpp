/*!
	Copyright (c) 2012, Matevž Jekovec, Happy Farmer development team
	All Rights Reserved. See AUTHORS for a complete list of authors.

	Licensed under the GNU GENERAL PUBLIC LICENSE. See COPYING for details.
*/

#include <model/resource.h>

#include <QPixmap>

QPixmap *HFResource::PIXMAP_GRASS_256 = nullptr;

// TODO: Implement priority list for checking presence of resources. For now, it's hardcoded to "data" directory. -Matevz
#undef DEFAULT_DATA_DIR
#define DEFAULT_DATA_DIR "data"

HFResource::HFResource() {
	HFResource::PIXMAP_GRASS_256 = new QPixmap(QString(DEFAULT_DATA_DIR)+"/terrain/grass/grass256.png");
}

HFResource::~HFResource() {
}

