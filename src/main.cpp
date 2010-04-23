#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "core/engine.h"

int main( int argc, char *argv[] ) {
	Engine *engine = new Engine();
	engine->start();

	return 0;
}
