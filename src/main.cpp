#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "gui/mainwin.h"

int main( int argc, char *argv[] ) {
	MainWin *mainWin = new MainWin();
	mainWin->show();

	return 0;
}
