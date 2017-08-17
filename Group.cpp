#include "Group.hpp"

#include <iostream>

// with this line we do not have to write std::cout and can write cout instead.
// same for endl
using namespace std;

#include <algorithm> //find

/**
 * @brief Standard Constructor
 */
Group::Group()
{
}

/**
 * @brief Costum Constructor which starts the group with the given member
 * @param member A Coordinate which represents the first member of the group
 */
Group::Group(Coordinate member)
{
	addMember(member);
}

/**
 * @brief Copy Constructor  which creates a new Group object with the values
 * of the given object
 * @param orig The Group object which will be copied
 */
Group::Group(const Group& orig)
{
	m_coordinates = orig.m_coordinates;
}

/**
 * @brief Adds a given Coordinate to the list of members
 * @param newMember The Coordinate which represents the new member
 * @return true if adding was successfull
 */
bool Group::addMember(Coordinate newMember)
{
	if(hasMemberAt(newMember))
	{
		return false;
	}
	
	if(hasNeighbour(newMember))
	{
		//Add newMember at the End of the vector
		m_coordinates.push_back(newMember);
		return true;
	}
	return false;
}

/**
 * @brief Return the color of the group
 * @return color of the group
 */
bool Group::getColor()
{
	return m_color;
}

/**
 * @brief Returns a vector of all members
 * @return vector<Coordinate> of all members
 */
vector<Coordinate> Group::getMembers()
{
	return m_coordinates;
}

/**
 * @brief Returns a vector of all neighbours of the group
 * @return vector<Coordnate> of all neighbours
 * @todo This function should check if all Coordinates which it gets from its members
 * are valid on the board.
 */
vector<Coordinate> Group::getNeighbours()
{
	vector<Coordinate> neighbours;
	
	// Iterate through all members
	for(vector<Coordinate>::iterator it = m_coordinates.begin(); it != m_coordinates.end(); ++it)
	{
		// Get all potential neighbours of the current member
		vector<Coordinate> possibleNeighbours = it->getNeighbours();
		
		// Check all potential neighbours
		for(vector<Coordinate>::iterator it = possibleNeighbours.begin(); it != possibleNeighbours.end(); ++it)
		{
			// If the potential neighbour is already in the vector it shall not be added
			if(std::find(neighbours.begin(), neighbours.end(), *it) == neighbours.end())
			{
				// Neighbours which are members of the group are no neighbours
				if(!hasMemberAt(*it))
				{
					neighbours.push_back(*it);
				}
			}
		}
	}
	
	return neighbours;
}

/**
 * @brief Returns the number of members of the group
 * @return Number of members
 */
int Group::getNumberOfMembers()
{
	return m_coordinates.size();
}

/**
 * @brief Checks whether the group has a member at the given Coordinate or not
 * @param coor Coordinate which could be a member
 * @return true if coor is a member of the group
 */
bool Group::hasMemberAt(Coordinate coor)
{
	///\todo check if we want to use some other datastructur which is mor effizient.
	return std::find(m_coordinates.begin(), m_coordinates.end(), coor) != m_coordinates.end();
}

/*
 * @brief Checks whether the group has a neighbour at the given Coordinate or not
 * @param potentialNeigbour Coordinate which could be a neighbour
 * @return true if potentialNeigbour is a neighbour of the group
 */
bool Group::hasNeighbour(Coordinate potentialNeigbour)
{
	///\todo Alternatively we could create a new Group (of the neighbour Coordinates) and use hasMemberAt().
	///\todo But i think we should not use it because we need a check if the member is a real member of the group
	
	vector<Coordinate> neighbours = getNeighbours();
	
	return std::find(neighbours.begin(), neighbours.end(), potentialNeigbour) != neighbours.end();
}

/**
 * @brief Sets the color of the group
 * @param color The color of the group
 */
void Group::setColor(bool color)
{
	m_color = color;
}