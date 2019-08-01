/*!
	Copyright (c) 2012-2019, Matevž Jekovec, Happy Farmer development team
	All Rights Reserved. See AUTHORS for a complete list of authors.

	Licensed under the GNU GENERAL PUBLIC LICENSE. See COPYING for details.
*/

#include <model/resource.h>

#include <QPixmap>
#include <QFile>

QStringList HFResource::TILE_HEIGHT_COMBINATIONS = QStringList() <<
		"0000" <<
		"0001" << "0010" << "0011" << "0100" << "0101" << "0110" << "0111" <<
		"1000" << "1001" << "1010" << "1011" << "1100" << "1101" << "1110" <<
		"0121" << "1012" << "2101" << "1210";

// possible road combinations: Tile is divided into 9 sub-tiles from top-left to bottom-right
// one denotes that the sub-tile contains road, zero that it doesn't
QStringList HFResource::ROAD_COMBINATIONS = QStringList() <<
		"010010010" << "000111000" << // straight roads
		"010111010" << // 4-way junction
		"000111010" << "010110010" << "010111000" << "010011010" << // T junctions
		"000110010" << "010110000" << "010011000" << "000011010"; // curves

QHash<QString, QPixmap> HFResource::PIXMAP_HELPER_TILE = QHash<QString, QPixmap>();
QPixmap *HFResource::PIXMAP_HELPER_DOT;
QHash<QString, QPixmap> HFResource::PIXMAP_GRASS = QHash<QString, QPixmap>();
QHash<QString, QPixmap> HFResource::PIXMAP_ROAD = QHash<QString, QPixmap>();
QHash<QString, QPixmap> HFResource::PIXMAP_SHEEP = QHash<QString, QPixmap>();

// TODO: Implement priority list for checking presence of resources. For now, it's hardcoded to "data" directory. -Matevz
#undef DEFAULT_DATA_DIR
#define DEFAULT_DATA_DIR "data"

HFResource::HFResource() {
	HFResource::PIXMAP_HELPER_DOT = new QPixmap(QString(DEFAULT_DATA_DIR)+"/helper/dot/dot.png");
	for (QString &height: HFResource::TILE_HEIGHT_COMBINATIONS) {
		HFResource::PIXMAP_GRASS[height] = QPixmap(QString(DEFAULT_DATA_DIR)+"/terrain/grass/grass-"+height+".png");
		HFResource::PIXMAP_HELPER_TILE[height] = QPixmap(QString(DEFAULT_DATA_DIR)+"/helper/tile/tile-"+height+".png");
		
		for (QString &road: HFResource::ROAD_COMBINATIONS) {
			QString name=QString(DEFAULT_DATA_DIR)+"/construction/road/asphaltroad/road-"+height+"-"+road+".png";
			if (QFile::exists(name)) {
				HFResource::PIXMAP_ROAD[height+road] = QPixmap(name);
			}
		}
	}
	
	HFResource::PIXMAP_SHEEP["0"] = QPixmap(QString(DEFAULT_DATA_DIR)+"/animal/sheep/sheep-0.png");
	HFResource::PIXMAP_SHEEP["4"] = QPixmap(QString(DEFAULT_DATA_DIR)+"/animal/sheep/sheep-4.png");
}

HFResource::~HFResource() {
}

