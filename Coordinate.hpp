#ifndef COORDINATE_HPP
#define COORDINATE_HPP

#include <stdio.h>
#include <vector>
using std::vector;

class Coordinate {
public:
	Coordinate();
	Coordinate(int x, int y);
	Coordinate(const Coordinate& orig);
	//virtual ~Coordinate();
	
	bool operator==(const Coordinate& rCoor);
	
	Coordinate getBottomNeighbour();
	Coordinate getLeftNeighbour();
	vector<Coordinate> getNeighbours();
	Coordinate getRightNeighbour();
	Coordinate getUpperNeighbour();
	
	int getX();
	int getY();
private:
	int __x;
	int __y;
	void setX(int x);
	void setY(int y);
};

#endif /* COORDINATE_HPP */

