#include "Board.hpp"

#include <iostream>

// with this line we do not have to write std::cout and can write cout instead.
// same for endl
using namespace std;


/**
 * @brief Standard Constructor which initialized the board to a normal Go board
 * (19x19)
 */
Board::Board()
{
	setMaxX(19);
	setMaxY(19);
}

/**
 * @brief Costum Constructor which initialized the board to a board with given 
 * rows and columns
 */
Board::Board(int maxX, int maxY)
{
	setMaxX(maxX);
	setMaxY(maxY);
}

/**
 * @brief Copy Constructor
 * @param orig The instance which will be copied from
 */
Board::Board(const Board& orig)
{
	__currentColor = orig.__currentColor;
	__groups = orig.__groups;
	__initialized = orig.__initialized;
	
	__maxX = orig.__maxX;
	__maxY= orig.__maxY;
	__minX = orig.__minX;
	__minY = orig.__minY;
	
	__turnHistory = orig.__turnHistory;
}

/**
 * @brief Adds the given history of Turns to the history of Turns
 * @param turnHistory vector<Turn> which will be added to the history of Turns
 * @return true on success
 */
bool Board::addTurnHistory(vector<Turn> turnHistory)
{
	//Prealocate memory to improve performance
	__turnHistory.reserve(turnHistory.size());
	__turnHistory.insert(__turnHistory.end(), turnHistory.begin(), turnHistory.end());
	return true;
}

/**
 * @brief Apply the given Turn to the Board and recalculates the groups and so on
 * @param t The turn to be performed
 * @return true on success
 */
bool Board::applyTurn(Turn t)
{
	cout << "applyTurn(Turn) is currently not implemented" << endl;
	return false;
}

/**
 * @brief Creates a Turn from the given params and calls the real applyTurn function
 * @param color The color of the player
 * @param target The Coordinate of the target
 * @return true on success
 * @note This is an alternative signature for the other applyTurn function
 */
bool Board::applyTurn(bool color, Coordinate target)
{
	//create Turn
	Turn t(color, target);
	
	//call the function above
	return applyTurn(t);
}

/**
 * @brief Changes the current color to the opposite one
 */
void Board::changeColor()
{
	setColor(!getColor());
}

/**
 * @brief Returns the current color
 * @return current color
 */
bool Board::getColor()
{
	return __currentColor;
}

/**
 * @brief Returns all groups at the board
 * @return vector<Group> groups at the board
 */
vector<Group> Board::getGroups()
{
	return __groups;
}

/**
 * @brief Returns the groups which belong to the given color
 * @param color The color of the groups which are requested
 * @return vector<Group> groups of the given color
 */
vector<Group> Board::getGroups(bool color)
{
	vector<Group> retGroups;
	// Iterate over the __groups vector to compare the color of the Group with 
	// the requested one
	for(vector<Group>::iterator it = __groups.begin(); it != __groups.end(); ++it)
	{
		if(it->getColor() == getColor())
		{
			// Adding the Group to the end of the return vector
			retGroups.push_back(*it);
		}
	}
	
	return retGroups;
}

/**
 * @brief Returns the maximum x value
 * @return maximum x value
 */
int Board::getMaxX()
{
	return __maxX;
}

/**
 * @brief Returns the maximum y value
 * @return maximum y value
 */
int Board::getMaxY()
{
	return __maxY;
}

/**
 * @brief Returns the minimum x value
 * @return minimum x value
 */
int Board::getMinX()
{
	return __minX;
}

/**
 * @brief Returns the minimum y value
 * @return minimum y value
 */
int Board::getMinY()
{
	return __minY;
}

/**
 * @brief Returns the complete Turn history of the board
 * @return vector<Turn> turn history of the board
 */
vector<Turn> Board::getTurnHistory()
{
	return __turnHistory;
}

/**
 * @brief Returns if the Board is fully initialized
 * @return true if the Board is fully initialized
 */
bool Board::isInitialized()
{
	return __initialized;
}

/**
 * @brief Sets the current color of the board
 * @param color The new color
 */
void Board::setColor(bool color)
{
	__currentColor = color;
}

/**
 * @brief Sets the Board to status fully initialized
 */
void Board::setInitialized()
{
	__initialized = true;
}

/**
 * @brief Sets the maximum x value of the board
 * @param maxX Maximum x value
 */
void Board::setMaxX(int maxX)
{
	__maxX = maxX;
}

/**
 * @brief Sets the maximum y value of the board
 * @param maxY Maximum y value
 */
void Board::setMaxY(int maxY)
{
	__maxY = maxY;
}

/**
 * @brief Sets the minimum x value of the board
 * @param minX Minimum x value
 */
void Board::setMinX(int minX)
{
	__minX = minX;
}

/**
 * @brief Sets the minimum y value of the board
 * @param minY Minimum y value
 */
void Board::setMinY(int minY)
{
	__minY = minY;
}