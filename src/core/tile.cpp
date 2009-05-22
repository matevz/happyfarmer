#include "core/tile.h"

Tile::Tile( int x, int y, Point3d *p1, Point3d *p2, Point3d *p3, Point3d *p4 )
 : _x(x), _y(y),
   _point1(p1), _point2(p2), _point3(p3), _point4(p4) {
}

Tile::~Tile() {
}
