#include "Coordinate.hpp"

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

int Coordinate::getX()
{
	return __x;
}

int Coordinate::getY()
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