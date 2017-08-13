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
	__members = orig.__members;
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
		__members.push_back(newMember);
		return true;
	}
	return false;
}

/**
 * @brief Returns a vector of all members
 * @return vector<Coordinate> of all members
 */
vector<Coordinate> Group::getMembers()
{
	return __members;
}

/**
 * @brief Returns a vector of all neighbours of the group
 * @return vector<Coordnate> of all neighbours
 * @todo this function is currently not implemented
 */
vector<Coordinate> Group::getNeighbours()
{
	///\todo Implement this function.
	vector<Coordinate> neighbours;
	
	cout << "getNeighbours is currently not implemented" << endl;
	return neighbours;
}

/**
 * @brief Returns the number of members of the group
 * @return Number of members
 */
int Group::getNumberOfMembers()
{
	return __members.size();
}

/**
 * @brief Checks whether the group has a member at the given Coordinate or not
 * @param coor Coordinate which could be a member
 * @return true if coor is a member of the group
 */
bool Group::hasMemberAt(Coordinate coor)
{
	///\todo check if we want to use some other datastructur which is mor effizient.
	return std::find(__members.begin(), __members.end(), coor) != __members.end();
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