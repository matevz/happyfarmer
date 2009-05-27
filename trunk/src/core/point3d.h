#ifndef POINT3D_H_
#define POINT3D_H_

class Point3d {
public:
	Point3d( int x, int y, int z );
	virtual ~Point3d();

	const int& getX() const { return _x; }
	const int& getY() const { return _y; }
	const int& getZ() const { return _z; }

	void setX( int x ) { _x = x; }
	void setY( int y ) { _y = y; }
	void setZ( int z ) { _z = z; }

private:
	int _x;
	int _y;
	int _z;
};

#endif
