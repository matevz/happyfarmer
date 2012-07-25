/*!
	Copyright (c) 2012, Matevž Jekovec, Happy Farmer development team
	All Rights Reserved. See AUTHORS for a complete list of authors.

	Licensed under the GNU GENERAL PUBLIC LICENSE. See COPYING for details.
*/

#ifndef HFSETTINGS_H
#define	HFSETTINGS_H

#include <QPixmap>
#include <QStringList>
#include <QHash>

#include <model/resource.h>

class HFSettings {
public:
	HFSettings();
	virtual ~HFSettings();
	static HFSettings *instance() { return HFSettings::_instance; }
	
	// properties
	const int& scrollSpeed() { return _scrollSpeed; }
	void setScrollSpeed(const int& scrollSpeed) { _scrollSpeed = scrollSpeed; }
	
private:
	static HFSettings *_instance;
	
	int _scrollSpeed;
};

#endif

