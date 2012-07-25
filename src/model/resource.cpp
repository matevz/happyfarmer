/*!
	Copyright (c) 2012, Matevž Jekovec, Happy Farmer development team
	All Rights Reserved. See AUTHORS for a complete list of authors.

	Licensed under the GNU GENERAL PUBLIC LICENSE. See COPYING for details.
*/

#include <model/resource.h>

#include <QPixmap>

QStringList HFResource::TILE_HEIGHT_COMBINATIONS = QStringList() <<
		"0000" <<
		"0001" << "0010" << "0011" << "0100" << "0101" << "0110" << "0111" <<
		"1000" << "1001" << "1010" << "1011" << "1100" << "1101" << "1110" <<
		"0121" << "1012" << "2101" << "1210";
	
QHash<QString, QPixmap> HFResource::PIXMAP_GRASS = QHash<QString, QPixmap>();

// TODO: Implement priority list for checking presence of resources. For now, it's hardcoded to "data" directory. -Matevz
#undef DEFAULT_DATA_DIR
#define DEFAULT_DATA_DIR "data"

HFResource::HFResource() {
	for (QString &combination: HFResource::TILE_HEIGHT_COMBINATIONS) {
		HFResource::PIXMAP_GRASS[combination] = QPixmap(QString(DEFAULT_DATA_DIR)+"/terrain/grass/grass-"+combination+".png");
	}
}

HFResource::~HFResource() {
}

