#include <AL/alut.h>
#include "gui/sound.h"

Sound::Sound() {
	init();
}

Sound::~Sound() {
	alutExit();
}

/*!
	Initializes audio subsystem.
*/
bool Sound::init() {
	bool error = false;

	if (!alutInit(0, 0)) {
		error = true;
	}

	return (!error);
}
