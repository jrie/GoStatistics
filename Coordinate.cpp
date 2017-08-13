#include "Coordinate.hpp"

/**
 * @brief Standard Constructor which initialize the object with x=y=0
 */
Coordinate::Coordinate()
{
	setX(0);
	setY(0);
}

/**
 * @brief Costum Constructor which initialize the object with the given values
 * @param x The x coordinate
 * @param y The y coordinate
 */
Coordinate::Coordinate(int x, int y)
{
	setX(x);
	setY(y);
}

/**
 * @brief Copy Constructor which creates a new Coordinate object with the values
 * of the given object
 * @param orig The Coordinate object which will be copied
 */
Coordinate::Coordinate(const Coordinate& orig)
{
	setX(orig.__x);
	setY(orig.__y);
}

/**
 * @brief Operator == which is called when a Coordinate object is compared to
 * another one.
 * @param rCoor The Coordinate object to which this one is compared to
 * @return true if the objects are equal
 */
bool Coordinate::operator==(const Coordinate& rCoor)
{
	return (__x == rCoor.__x && 
			__y == rCoor.__y);
}

/**
 * @brief Returns the X coordinate
 * @note This function has to be const to be called on a const object
 * @return the x coordinate
 */
int Coordinate::getX()
{
	return __x;
}

/**
 * @brief Returns the Y coordinate
 * @note This function has to be const to be called on a const object
 * @return the y coordinate
 */
int Coordinate::getY()
{
	return __y;
}

/**
 * @brief Sets the x coordinate
 * @param x The x coordinate
 */
void Coordinate::setX(int x)
{
	__x = x;
}

/**
 * @brief Sets the y coordinate
 * @param x The y coordinate
 */
void Coordinate::setY(int y)
{
	__y = y;
}