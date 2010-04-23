#include <stdlib.h>
#include <math.h>
#include <iostream>

#include "core/terrain.h"
#include "core/tile.h"
#include "core/point.h"
#include "gui/mainwin.h"
#include "gui/graphics.h"
#include "gui/sound.h"

#include "objects/tractor.h"

MainWin::MainWin()
 : _loop(true), _scene(0), _mouseX(50), _mouseY(50) {
}

MainWin::~MainWin() {
}

void MainWin::show() {

}
