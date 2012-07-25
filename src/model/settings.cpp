/*!
	Copyright (c) 2012, Matevž Jekovec, Happy Farmer development team
	All Rights Reserved. See AUTHORS for a complete list of authors.

	Licensed under the GNU GENERAL PUBLIC LICENSE. See COPYING for details.
*/

#include <model/settings.h>

HFSettings *HFSettings::_instance = nullptr;

HFSettings::HFSettings()
 : _scrollSpeed(100) {
	HFSettings::_instance = this;
}

HFSettings::~HFSettings() {
}

