#ifndef POINT3D_H_
#define POINT3D_H_

class Point3d {
public:
	Point3d( const float& x, const float& y, const float& z );
	virtual ~Point3d();

	const float& getX() const { return _x; }
	const float& getY() const { return _y; }
	const float& getZ() const { return _z; }

	void setX( const float& x ) { _x = x; }
	void setY( const float& y ) { _y = y; }
	void setZ( const float& z ) { _z = z; }

private:
	float _x;
	float _y;
	float _z;
};

#endif
