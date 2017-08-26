#include "Board.hpp"

#include <iostream>
#include <map>

// with this line we do not have to write std::cout and can write cout instead.
// same for endl
using namespace std;

#include <algorithm> //find

void Board::initPoints()
{
	m_points.insert({false, 0.5}); // Komi
	m_points.insert({true, 0});
}

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
	// Check if turn is valid
	if(!isValid(t)) ///@todo We need an implementation for that...
	{
		return false;
	}
	
	// Add Turn to Turn history
	m_turnHistory.push_back(t);
	
	// Add the new stone to the Groups
	if(applyTurnToGroups(t, m_groups) == -1)
	{
		// Could not add the stone to any Group because a Group has allready a member at the 
		// given Coordinate.
		// This should never be happend because isValid(Turn) and getNeighbours(Group)
		// would be incorrect if this happens.
		return false;
	}
	
	// ###
	// Removing catched Groups/Stones
	// ###
	
	// Check if any enemy Group was catched by the last Turn
	vector<Group> catchedGroups = getCatchedGroups(getColor(), m_groups);
	
	m_numberOfRemovedStonesLastTurn = 0;
	m_removedStonesLastTurn.clear();
	// If any Group were catched we have to remove it from the board
	if(!catchedGroups.empty())
	{
		// Save the removed Stones to check if an Atari is given for the next Turn
		// Furthermore remove the catchedGroups of the vector of Groups.
		m_removedStonesLastTurn = removeGroups(catchedGroups, m_groups);
		
		// Add points to the score of the current player
		addPoints(getColor(), m_removedStonesLastTurn.size());
		
		// Save the number of Stone were removed this Turn
		m_numberOfRemovedStonesLastTurn = m_removedStonesLastTurn.size();
	}
	
	// Change color
	changeColor();
	
	// Done.
	return true;
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
 * @brief This function adds the, by Turn spezified, Coordinate to the Group which has 
 * a neighbour at the given Coordinate. If multiple Groups has neighbours at that Coordinate 
 * these Groups will be merged into one Group. If no Group of the same color has a neighbour there, 
 * a new Group will be created with the given Coordinate.
 * @param t The Turn which describes the color and Coordinate
 * @param groups vector<Groups> all Groups which will be checked and modified
 * @return 0 if a new Group were created. 1 if the Turn could be merged into the Groups. 
 * -1 if the Turn could not be added to the vector of Groups.
 */
int Board::applyTurnToGroups(const Turn& t, vector<Group>& groups)
{
	int ret = 0;
	
	// Check if Turn::target Coordinate is neighbour of an existing Group and 
	// add it to those. Else create a new Group
	vector<Group*> neighbourGroups;
	for(vector<Group>::iterator it = groups.begin(); it != groups.end(); ++it)
	{
		// The Group and the Coordinate have to have the same color
		if(t.getColor() != it->getColor())
		{
			// If the color is not equal we should check the next Group
			continue;
		}
		
		if(isNeighbour(t.getTarget(), *it))
		{
			// Temporary save of a pointer to the group which the coordinate is a neigbour of
			neighbourGroups.push_back(&*it);
		}
	}
	// If the Coordinate is a neighbour of one Group add it to it.
	if(neighbourGroups.size() > 0)
	{
		if(not (*neighbourGroups.begin())->addMember(t.getTarget()))
		{
			ret = -1;
		}
		else
		{
			ret = 1;
			// If there are more than one Group which has neighbourhood to the Coordinate
			// we can merge those Groups
			if(neighbourGroups.size() > 1)
			{
				for(vector<Group*>::iterator it = neighbourGroups.begin() + 1; it != neighbourGroups.end(); ++it)
				{
					(*neighbourGroups.begin())->merge(**it);
				}

				// Removing every Group which has been merged from the m_groups vector
				// Note: begin() + 1
				for(vector<Group*>::iterator it = neighbourGroups.begin() + 1; it != neighbourGroups.end(); ++it)
				{
					vector<Group>::iterator toRemove = std::find(groups.begin(), groups.end(), **it);

					groups.erase(toRemove);
				}
			}
		}
	}
	else // else we should create a new Group
	{
		Group newGroup(t.getTarget());
		newGroup.setColor(t.getColor());
		groups.push_back(newGroup);
	}
	
	return ret;
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
 * @brief Returns all Coordinates which are in the vector of Groups
 * @param groups Vector of all Groups which provide the Coordinates
 * @return vector<Coordinate> of all members of all Groups
 */
std::vector<Coordinate> Board::getCoordinates(const std::vector<Group>& groups)
{
	vector<Coordinate> allCoordinates;
	
	for(vector<Group>::const_iterator it = groups.begin(); it != groups.end(); ++it)
	{
		vector<Coordinate> coordinatesOfGroup = it->getMembers();
		allCoordinates.insert(allCoordinates.end(), coordinatesOfGroup.begin(), coordinatesOfGroup.end());
	}
	
	return allCoordinates;
}

/**
 * @brief Returns the catched Groups which are surounded by stones of "color"
 * @param color The color of the friendly Groups
 * @param groups vector<Group> of all Groups which should be considered
 * @return vector<Group> of all catched Groups
 */
vector<Group> Board::getCatchedGroups(const bool color, const vector<Group>& groups)
{
	// Extract the Groups by color
	vector<Group> enemyGroups = getGroups(!color, groups);
	vector<Group> friendGroups = getGroups(color, groups);
	
	// Generate a vector of all own stones
	vector<Coordinate> friendStones = getCoordinates(friendGroups);
	
	// Check if any enemy Group was catched by the last Turn
	vector<Group> catchedGroups;
	for(vector<Group>::const_iterator it = enemyGroups.begin(); it != enemyGroups.end(); ++it)
	{
		vector<Coordinate> groupNeighbours = getNeighbours(*it);
		bool hasFreedoms = false;
		for(vector<Coordinate>::const_iterator it2 = groupNeighbours.begin(); it2 != groupNeighbours.end(); ++it2)
		{
			if(std::find(friendStones.begin(), friendStones.end(), *it2) != friendStones.end())
			{
				continue;
			}
			else
			{
				hasFreedoms = true;
				break;
			}
		}
		if(!hasFreedoms)
		{
			catchedGroups.push_back(*it);
		}
	}
	
	return catchedGroups;
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
	return getGroups(color, m_groups);
}

/**
 * @brief Returns the groups which belong to the given color and are members of
 * the given groupList
 * @param color The color of the groups which are requested
 * @param groupList The vector of Groups which shall be considered
 * @return vector<Group> groups of the given color
 */
vector<Group> Board::getGroups(bool color, const vector<Group>& groupList)
{
	vector<Group> retGroups;
	// Iterate over the m_groups vector to compare the color of the Group with 
	// the requested one
	for(vector<Group>::const_iterator it = groupList.begin(); it != groupList.end(); ++it)
	{
		if(it->getColor() == color)
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
 * @brief This function will remove the given Groups from the given vector of Groups
 * @param groupsToRemove vector of Groups which will be removed
 * @param groups Th vector of Groups from which the given Groups should be removed
 * @return vector<Coordinate> of all Coordinates which were removed
 */
vector<Coordinate> Board::removeGroups(const std::vector<Group>& groupsToRemove, std::vector<Group>& groups)
{
	vector<Coordinate> removedStones;
	if(!groupsToRemove.empty())
	{
		// We need to add some points to the player and remove the catched Group(s)
		for(vector<Group>::const_iterator it = groupsToRemove.begin(); it != groupsToRemove.end(); ++it)
		{
			// Removing that Group from Group Vector
			vector<Group>::iterator toRemove = std::find(groups.begin(), groups.end(), *it);
			if(toRemove != groups.end())
			{
				vector<Coordinate> memberCoordinates = it->getMembers();
				removedStones.insert(removedStones.end(), memberCoordinates.begin(), memberCoordinates.end());
				groups.erase(toRemove);
			}
		}
	}
	
	return removedStones;
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
 * @brief Returns all stones which are placed on the board
 * @return vector<Coordinate> all stones on the board
 * @deprecated Were replaced by getCoordinates(vector<Group>)
 */
vector<Coordinate> Board::getAllStones()
{
	vector<Coordinate> stones;
	for(vector<Group>::iterator it = m_groups.begin(); it != m_groups.end(); ++it)
	{
		vector<Coordinate> stonesFromGroup = it->getMembers();
		stones.insert(stones.end(), stonesFromGroup.begin(), stonesFromGroup.end());
	}
	
	return stones;
}

/**
 * @brief Returns whether a Coordinate on the board is free or a stone is already placed on it
 * @param coor The Coordinate to be checked
 * @return true if no other stone was placed on the Coordinate
 */
bool Board::isFree(const Coordinate& coor)
{
	vector<Coordinate> allStones = getCoordinates(m_groups);
	
	return std::find(allStones.begin(), allStones.end(), coor) == allStones.end();
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
	
	// Checking if all members of the Group are neighbours of each other
	// So that all members are connected to each other
	for(vector<Coordinate>::iterator it = g_members.begin(); it != g_members.end(); ++it)
	{
		vector<Coordinate> neighbours = getNeighbours(*it);
		
		for(vector<Coordinate>::iterator it2 = neighbours.begin(); it2 != neighbours.end(); ++it2)
		{
			if(g.hasMemberAt(*it2))
			{
				continue;
			}
			return false;
		}
	}
	
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
	// ###
	// Check if the Turn color is the same as the current Board color
	// ###
	if(t.getColor() != getColor())
	{
		// A player is not allowed to move twice
		cout << "DEBUG - Invalid Turn: " << "Not the correct color" << endl;
		return false;
	}
	
	// ###
	// Check if the target Coordinate is valid 
	// ###
	if(!isValid(t.getTarget()))
	{
		// The Coordinate is not valid
		
		cout << "DEBUG - Invalid Turn: " << "Invalid Coordinate" << endl;
		return false;
	}
	
	// ###
	// Check if the target Coordinate is a free field on the board
	// ###
	if(!isFree(t.getTarget()))
	{
		// The Coordinate is not a free field
		
		cout << "DEBUG - Invalid Turn: " << "Target not free" << endl;
		return false;
	}
	
	// ###
	// Check if we do not kill a friendly group
	// ###
	
	// Deep copy the group List to not modify the real one!
	// The cast forces a deep copy of the vector
	vector<Group> tmp_Groups = (const vector<Group>) m_groups;
	
	// Adding Turn::target Coordinate to the groups
	// Add the new stone to the Groups
	if(applyTurnToGroups(t, tmp_Groups) == -1)
	{
		// Could not add the stone to any Group because a Group has allready a member at the 
		// given Coordinate.
		// isFree() failed!
		return false;
	}
	
	// First we have to check if we catch any other group...
	
	// Check if any enemy Group was catched by the last Turn
	vector<Group> catchedGroups = getCatchedGroups(getColor(), tmp_Groups);
	
	// If any Group were catched we have to remove it from the board
	removeGroups(catchedGroups, tmp_Groups);
	
	// Check if any own Group was catched by the Turn
	catchedGroups = getCatchedGroups(!getColor(), tmp_Groups);
	
	// If any Group were catched we have to remove it from the board
	if(!catchedGroups.empty())
	{
		// A friendly Group was catched so we would kill a friendly Group by
		// processing this Turn.
		
		cout << "DEBUG - Invalid Turn: " << "Friendly group was catched" << endl;
		return false;
	}
	
	// ###
	// Check if we do not place a stone at a field where an atari was one turn before
	// ###
	// If exactly one stone was removed last Turn we have to check if we want to place it again (Atari)
	if(m_numberOfRemovedStonesLastTurn == 1)
	{
		if(std::find(m_removedStonesLastTurn.begin(), m_removedStonesLastTurn.end(), t.getTarget()) != m_removedStonesLastTurn.end())
		{
			// The stone which should be placed is the same as was removed before
			
			cout << "DEBUG - Invalid Turn: " << "Atari rule" << endl;
			return false;
		}
	}
	
	return true;
}

/**
 * @brief Checks if the to given Coordinates are neighbours of each other
 * @param coorToCheck The Coordinate which could be a neighbour of the second one
 * @param coor The Coordinate which will provide the neighbours
 * @return true if the two coordinates are neighbours
 */
bool Board::isNeighbour(const Coordinate& coorToCheck, const Coordinate& coor)
{
	vector<Coordinate> neighbours = getNeighbours(coor);
	
	for(vector<Coordinate>::iterator it = neighbours.begin(); it != neighbours.end(); ++it)
	{
		if(*it == coorToCheck)
		{
			return true;
		}
	}
	return false;
}

/**
 * @brief Checks if the to given Coordinate is a neighbour of the given Group
 * @param coorToCheck The Coordinate which could be a neighbour of the Group
 * @param g The Group which will provide the neighbours
 * @return true if the Coordinate is a neighbour of the Group
 */
bool Board::isNeighbour(const Coordinate& coorToCheck, const Group& g)
{
	vector<Coordinate> neighbours = getNeighbours(g);
	for(vector<Coordinate>::iterator it = neighbours.begin(); it != neighbours.end(); ++it)
	{
		if(*it == coorToCheck)
		{
			return true;
		}
	}
	return false;
}

void Board::addPoints(bool color, float points)
{
	m_points[color] += points;
}

float Board::getPoints(bool color)
{
	return m_points[color];
}

void Board::showField(int type)
{
	switch(type)
	{
			// Output with cout in the console
		case 0:
		{
			char blackStone = 'x';
			char whiteStone = 'o';
			char freeField = '-';

			map<Coordinate, bool> field;
			vector<Group> whiteGroups = getGroups(true, m_groups);
			vector<Group> blackGroups = getGroups(false, m_groups);
			
			vector<Coordinate> whiteStones = getCoordinates(whiteGroups);
			vector<Coordinate> blackStones = getCoordinates(blackGroups);
			
			for(vector<Coordinate>::iterator it = whiteStones.begin(); it != whiteStones.end(); ++it)
			{
				field[*it] = true;
			}
			for(vector<Coordinate>::iterator it = blackStones.begin(); it != blackStones.end(); ++it)
			{
				field[*it] = false;
			}

//			cout << "DEBUG - Field has " << field.size() << " members!" << endl;
//			for(auto it = field.begin(); it != field.end(); ++it)
//			{
//				cout << "DEBUG - " << it->first.x() << "x" << it->first.y() << " is " << it->second << endl;
//			}
			
			cout << "The current field is shown below." << endl;

			
			
			for(unsigned int row = getMaxY(); row >= getMinY(); row--)
			{
				cout << row;
				if(row <= 9)
				{
					cout << " ";
				}
				cout << " | ";
				
				for(unsigned int col = getMinX(); col <= getMaxX(); col++)
				{
					Coordinate currentField(col, row);
					if(field.find(currentField) != field.end())
					{
						// There is a stone on the field.
						if(field[currentField])
						{
							// white
							cout << whiteStone << ' ';
						}
						else
						{
							// black
							cout << blackStone << ' ';
						}
					}
					else
					{
						// no stone
						cout << freeField << ' ';
					}
				}
				cout << endl;
			}
			string columns = "abcdefghjklmnopqrst";

			cout << "    ";
			if(getMaxY() > 9)
			{
				cout << " ";
			}
			
			for(unsigned int col = getMinX(); col <= getMaxX(); col++)
			{

				cout << columns.at(col - 1) << ' ';
			}
			cout << endl;

			break;
		}
		default:
		{
			cout << "This type is not implemented now (showField(" << type << "))." << endl;
			break;
		}
	}
}