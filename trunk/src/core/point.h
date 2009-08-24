#ifndef POINT_H_
#define POINT_H_

struct Point3d {
	Point3d( float xx, float yy, float zz ) : x(xx), y(yy), z(zz) {}
	Point3d() : x(0), y(0), z(0) {}

	float x;
	float y;
	float z;
};

struct Point2d {
	Point2d( float xx, float yy ) : x(xx), y(yy) {}
	Point2d() : x(0), y(0) {}

	float x;
	float y;
};

#endif
