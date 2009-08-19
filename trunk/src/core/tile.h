#ifndef TILE_H_
#define TILE_H_

#include <vector>

class Point3d;
class StationaryObject;

class Tile {
public:
	Tile( int x, int y, Point3d *p1, Point3d *p2, Point3d *p3, Point3d *p4 );
	virtual ~Tile();

	const std::vector<StationaryObject*>& getObjectList() { return _objectList; }
	void addObject( StationaryObject* o, bool rebuildNeighbors=true );
	bool removeObject( StationaryObject* o, bool rebuildNeighbors=true );
	void rebuild();

	template<class T>
	bool contains() {
		for (unsigned int i=0; i<_objectList.size(); i++) {
			if (dynamic_cast<T*>(_objectList[i])) {
				return true;
			}
		}

		return false;
	}

	int getX() { return _x; }
	int getY() { return _y; }

	Point3d* getPoint1() { return _point1; }
	void     setPoint1( Point3d *p ) { _point1 = p; }
	Point3d* getPoint2() { return _point2; }
	void     setPoint2( Point3d *p ) { _point1 = p; }
	Point3d* getPoint3() { return _point3; }
	void     setPoint3( Point3d *p ) { _point1 = p; }
	Point3d* getPoint4() { return _point4; }
	void     setPoint4( Point3d *p ) { _point1 = p; }

private:
	int _x; // top-left corner
	int _y;

	/////////////
	// Terrain //
	/////////////
	Point3d *_point1; // bottom
	Point3d *_point2; // right
	Point3d *_point3; // top
	Point3d *_point4; // left

	////////////////////////
	// Non-moving objects //
	////////////////////////
	std::vector<StationaryObject*> _objectList;
};

#endif
