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

bool Board::addTurnHistory(vector<Turn> turnHistory)
{
	//Prealocate memory to improve performance
	__turnHistory.reserve(turnHistory.size());
	__turnHistory.insert(__turnHistory.end(), turnHistory.begin(), turnHistory.end());
	return true;
}

bool Board::applyTurn(Turn t)
{
	cout << "applyTurn(Turn) is currently not implemented" << endl;
	return false;
}

bool Board::applyTurn(bool color, Coordinate target)
{
	//create Turn
	Turn t(color, target);
	
	//call the function above
	return applyTurn(t);
}

void Board::changeColor()
{
	setColor(!getColor());
}

bool Board::getColor()
{
	return __currentColor;
}

vector<Group> Board::getGroups()
{
	return __groups;
}

int Board::getMaxX()
{
	return __maxX;
}

int Board::getMaxY()
{
	return __maxY;
}

int Board::getMinX()
{
	return __minX;
}

int Board::getMinY()
{
	return __minY;
}

vector<Turn> Board::getTurnHistory()
{
	return __turnHistory;
}

bool Board::isInitialized()
{
	return __initialized;
}

void Board::setColor(bool color)
{
	__currentColor = color;
}

void Board::setInitialized()
{
	__initialized = true;
}

void Board::setMaxX(int maxX)
{
	__maxX = maxX;
}

void Board::setMaxY(int maxY)
{
	__maxY = maxY;
}

void Board::setMinX(int minX)
{
	__minX = minX;
}

void Board::setMinY(int minY)
{
	__minY = minY;
}