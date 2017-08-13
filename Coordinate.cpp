#include "Coordinate.hpp"

Coordinate::Coordinate()
{
	setX(0);
	setY(0);
}

Coordinate::Coordinate(int x, int y)
{
	setX(x);
	setY(y);
}

Coordinate::Coordinate(const Coordinate& orig)
{
	this->setX(orig.getX());
	this->setY(orig.getY());
}

bool Coordinate::operator==(const Coordinate& rCoor)
{
	return (getX() == rCoor.getX() && getY() == rCoor.getY());
}

int Coordinate::getX() const
{
	return __x;
}

int Coordinate::getY() const
{
	return __y;
}

void Coordinate::setX(int x)
{
	__x = x;
}

void Coordinate::setY(int y)
{
	__y = y;
}