#ifndef COORDINATE_HPP
#define COORDINATE_HPP

class Coordinate {
public:
	Coordinate();
	Coordinate(int x, int y);
	Coordinate(const Coordinate& orig);
	//virtual ~Coordinate();
	
	bool operator==(const Coordinate& rCoor);
	
	int getX();
	int getY();
private:
	int __x;
	int __y;
	void setX(int x);
	void setY(int y);
};

#endif /* COORDINATE_HPP */

