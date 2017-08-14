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
 * @brief Returns the neighbour at the bottom side of this coordinate
 * @return Coordinate at the bottom side
 */
Coordinate Coordinate::getBottomNeighbour()
{
	Coordinate bottomNeighbour(getX(), getY() + 1);
	
	return bottomNeighbour;
}

/**
 * @brief Returns the neighbour at the left side of the coordinate
 * @return Coordinate at the left side
 */
Coordinate Coordinate::getLeftNeighbour()
{
	Coordinate leftNeighbour(getX() - 1, getY());
	
	return leftNeighbour;
}

/**
 * @brief Returns the four Coordinates which are direct neighbours
 * @return vector<Coordinate>
 * @todo This function should check if all Coordinates are valid on the board.
 */
vector<Coordinate> Coordinate::getNeighbours()
{
	vector<Coordinate> neighbours;
	
	neighbours.reserve(4); //Preallocate memory to speed up the next 4 lines.
	neighbours.push_back(getUpperNeighbour());
	neighbours.push_back(getRightNeighbour());
	neighbours.push_back(getBottomNeighbour());
	neighbours.push_back(getLeftNeighbour());
	
	return neighbours;
}

/**
 * @brief Returns the neighbour at the right side of the coordinate
 * @return Coordinate at the right side
 */
Coordinate Coordinate::getRightNeighbour()
{
	Coordinate rightNeighbour(getX() + 1, getY());
	
	return rightNeighbour;
}

/**
 * @brief Returns the neighbour at the upper side of the coordinate
 * @return Coordinate at the upper side
 */
Coordinate Coordinate::getUpperNeighbour()
{
	Coordinate upperNeighbour(getX(), getY() - 1);
	
	return upperNeighbour;
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