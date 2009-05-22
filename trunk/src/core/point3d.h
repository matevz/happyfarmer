#ifndef POINT3D_H_
#define POINT3D_H_

class Point3d {
public:
	Point3d( double x, double y, double z );
	virtual ~Point3d();

	const double& getX() const { return _x; }
	const double& getY() const { return _y; }
	const double& getZ() const { return _z; }

	void setX( double x ) { _x = x; }
	void setY( double y ) { _y = y; }
	void setZ( double z ) { _z = z; }

private:
	double _x;
	double _y;
	double _z;
};

#endif
