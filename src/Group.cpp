#include "Group.hpp"

#include <algorithm> //find

/**
 * @brief Costum Constructor which starts the group with the given member
 * @param member A Coordinate which represents the first member of the group
 */
Group::Group(Coordinate member)
{
	addMember(member);
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
	
//	if(hasNeighbour(newMember))
//	{
		//Add newMember at the End of the vector
		m_coordinates.push_back(newMember);
		return true;
//	}
//	return false;
}

/**
 * @brief Return the player color of the group
 * @return player color of the group
 */
bool Group::getColor() const
{
	return m_color;
}

/**
 * @brief Returns a vector of all members
 * @return vector<Coordinate> of all members
 */
std::vector<Coordinate> Group::getMembers() const
{
	return m_coordinates;
}

/**
 * @brief Returns the number of members of the group
 * @return Number of members
 */
int Group::getNumberOfMembers() const
{
	return m_coordinates.size();
}

/**
 * @brief Checks whether the group has a member at the given Coordinate or not
 * @param coor Coordinate which could be a member
 * @return true if coor is a member of the group
 */
bool Group::hasMemberAt(const Coordinate& coor) const
{
	///\todo check if we want to use some other datastructur which is mor effizient.
	return std::find(m_coordinates.begin(), m_coordinates.end(), coor) != m_coordinates.end();
}

/**
 * @brief Merges two groups by copying the given Group into this one.
 * @param g Group which will be merged into this Group
 * @return Number of merged members
 */
unsigned int Group::merge(const Group& g)
{
	unsigned int i = 0;
	for(const auto& coor : g.m_coordinates)
	{
		if(addMember(coor))
		{
			i++;
		}
	}
	
	return i;
}

/**
 * @brief Sets the player color of the group
 * @param color The player color of the group
 */
void Group::setColor(bool color)
{
	m_color = color;
}