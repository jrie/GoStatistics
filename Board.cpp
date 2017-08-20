#include "Board.hpp"

#include <iostream>

// with this line we do not have to write std::cout and can write cout instead.
// same for endl
using namespace std;

#include <algorithm> //find

/**
 * @brief Adds the given history of Turns to the history of Turns
 * @param turnHistory vector<Turn> which will be added to the history of Turns
 * @return true on success
 */
bool Board::addTurnHistory(vector<Turn> turnHistory)
{
	//Prealocate memory to improve performance
	m_turnHistory.reserve(turnHistory.size());
	m_turnHistory.insert(m_turnHistory.end(), turnHistory.begin(), turnHistory.end());
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
	
	// Check if turn is valid
	///@todo We need an implementation for that...
	
	// Add Turn to Turn history
	
	
	// Check if Turn::target Coordinate is neighbour of an existing Group and add it 
	// to those. Else create a new Group
	
	
	// Remove stones from enemy 
	// ... and ...
	// Calculate current sum for removed stones
	
	
	// Done.
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
	return m_currentColor;
}

/**
 * @brief Returns all groups at the board
 * @return vector<Group> groups at the board
 */
vector<Group> Board::getGroups()
{
	return m_groups;
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
	for(vector<Group>::iterator it = m_groups.begin(); it != m_groups.end(); ++it)
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
	return m_maxX;
}

/**
 * @brief Returns the maximum y value
 * @return maximum y value
 */
int Board::getMaxY()
{
	return m_maxY;
}

/**
 * @brief Returns the minimum x value
 * @return minimum x value
 */
int Board::getMinX()
{
	return m_minX;
}

/**
 * @brief Returns the minimum y value
 * @return minimum y value
 */
int Board::getMinY()
{
	return m_minY;
}

/**
 * @brief Returns the complete Turn history of the board
 * @return vector<Turn> turn history of the board
 */
vector<Turn> Board::getTurnHistory()
{
	return m_turnHistory;
}

/**
 * @brief Returns if the Board is fully initialized
 * @return true if the Board is fully initialized
 */
bool Board::isInitialized()
{
	return m_initialized;
}

/**
 * @brief Sets the current color of the board
 * @param color The new color
 */
void Board::setColor(bool color)
{
	m_currentColor = color;
}

/**
 * @brief Sets the Board to status fully initialized
 */
void Board::setInitialized()
{
	m_initialized = true;
}

/**
 * @brief Sets the maximum x value of the board
 * @param maxX Maximum x value
 */
void Board::setMaxX(int maxX)
{
	m_maxX = maxX;
}

/**
 * @brief Sets the maximum y value of the board
 * @param maxY Maximum y value
 */
void Board::setMaxY(int maxY)
{
	m_maxY = maxY;
}

/**
 * @brief Sets the minimum x value of the board
 * @param minX Minimum x value
 */
void Board::setMinX(int minX)
{
	m_minX = minX;
}

/**
 * @brief Sets the minimum y value of the board
 * @param minY Minimum y value
 */
void Board::setMinY(int minY)
{
	m_minY = minY;
}

/**
 * @brief Returns the four Coordinates which are direct neighbours to the given
 * Coordinate. Returns less Coordinates if there would be neighbours outside of
 * the board
 * @param coor The Coordinate in the center
 * @return vector<Coordinate>
 */
vector<Coordinate> Board::getNeighbours(const Coordinate& coor)
{
	vector<Coordinate> neighbours;
	
	//top
	if(coor.y() > getMinY())
	{
		neighbours.push_back(Coordinate(coor.x(), coor.y() - 1));
	}
	
	//right
	if(coor.x() < getMaxX())
	{
		neighbours.push_back(Coordinate(coor.x() + 1, coor.y()));
	}
	
	//bottom
	if(coor.y() < getMaxY())
	{
		neighbours.push_back(Coordinate(coor.x(), coor.y() + 1));
	}
	
	//left
	if(coor.x() > getMinX())
	{
		neighbours.push_back(Coordinate(coor.x() - 1, coor.y()));
	}
	
	return neighbours;
}


/**
 * @brief Returns a vector of all neighbours of the group
 * @param g The Group which edges will be checked for neighbours
 * @return vector<Coordnate> of all neighbours
 */
vector<Coordinate> Board::getNeighbours(const Group& g)
{
	vector<Coordinate> neighbours;
	
	vector<Coordinate> g_members = g.getMembers();
	
	// Iterate through all members of the group
	for(vector<Coordinate>::iterator it = g_members.begin(); it != g_members.end(); ++it)
	{
		// Get all potential neighbours of the current member (Coordinate)
		vector<Coordinate> possibleNeighbours = getNeighbours(*it);
		
		// Check all potential neighbours
		for(vector<Coordinate>::iterator it = possibleNeighbours.begin(); it != possibleNeighbours.end(); ++it)
		{
			// If the potential neighbour is already in the vector it shall not be added
			if(std::find(neighbours.begin(), neighbours.end(), *it) == neighbours.end())
			{
				// Neighbours which are members of the group are no neighbours
				if(!g.hasMemberAt(*it))
				{
					neighbours.push_back(*it);
				}
			}
		}
	}
	
	return neighbours;
}

/**
 * @brief Checks if a given Coordinate is valid.
 * @param coor Coordinate to be checked
 * @return true if Coordinate is laying on the board
 */
bool Board::isValid(const Coordinate& coor)
{
	return (coor.x() <= getMaxX() && coor.x() >= getMinX() &&
			coor.y() <= getMaxY() && coor.y() >= getMinY());
}

/**
 * @brief Checks if a given Group is valid.
 * @note A Group is valid if all members are valid
 * @param g Group to be checked
 * @return  true if the Group is valid
 */
bool Board::isValid(const Group& g)
{
	vector<Coordinate> g_members = g.getMembers();
	for(vector<Coordinate>::iterator it = g_members.begin(); it != g_members.end(); ++it)
	{
		if(!isValid(*it))
		{
			return false;
		}
	}
	
	///@todo maybe we should also check if the Group only consists of members which
	/// are all neighbours (are connected to another member)
	
	// ...
	
	return true;
}

/**
 * @brief
 * @param t
 * @return 
 * @todo We need an implementation here...
 */
bool Board::isValid(const Turn& t)
{
	cout << "isValid(Turn) is currently not implemented" << endl;
	return true;
}