#ifndef COORDINATE_HPP
#define COORDINATE_HPP

class Coordinate {
public:
	Coordinate(int x, int y);
	Coordinate(const Coordinate& orig);
	//virtual ~Coordinate();
	
	int getX();
	int getY();
private:
	int __x;
	int __y;
	void setX(int x);
	void setY(int y);
};

#endif /* COORDINATE_HPP */

