/*!
	Copyright (c) 2012, Matevž Jekovec, Happy Farmer development team
	All Rights Reserved. See AUTHORS for a complete list of authors.

	Licensed under the GNU GENERAL PUBLIC LICENSE. See COPYING for details.
*/

#ifndef HFDOBJSHEEP_H
#define	HFDOBJSHEEP_H

#include "drawable/drawable.h"

class HFObjSheep;

class HFDObjSheep : public HFDrawable {
public:
	HFDObjSheep( HFObjSheep *s );
	virtual ~HFDObjSheep();
};

#endif