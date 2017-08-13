#include "Group.hpp"

#include <algorithm> //find

Group::Group()
{
}

Group::Group(Coordinate member)
{
	addMember(member);
}

Group::Group(const Group& orig)
{
	vector<Coordinate> members = orig.getMembers();
	for(vector<Coordinate>::iterator it = members.begin(); it != members.end(); ++it)
	{
		this->addMember(*it);
	}
}

Group::~Group()
{
}

bool Group::addMember(Coordinate newMember)
{
	if(hasMemberAt(newMember))
	{
		return false;
	}
	
	if(hasNeighbour(newMember))
	{
		__members.push_back(newMember);
		return true;
	}
	return false;
}

vector<Coordinate> Group::getMembers() const
{
	return __members;
}

vector<Coordinate> Group::getNeighbours()
{
	///\todo Implement this function.
	vector<Coordinate> neighbours;
	
	return neighbours;
}

int Group::getNumberOfMembers()
{
	return __members.size();
}

bool Group::hasMemberAt(Coordinate coor)
{
	///\todo check if we want to use some other datastructur which is mor effizient.
	return std::find(__members.begin(), __members.end(), coor) != __members.end();
}

bool Group::hasNeighbour(Coordinate potentialNeigbour)
{
	///\todo Alternatively we could create a new Group (of the neighbour Coordinates) and use hasMemberAt().
	///\todo But i think we should not use it because we need a check if the member is a real member of the group
	
	vector<Coordinate> neighbours = getNeighbours();
	
	return std::find(neighbours.begin(), neighbours.end(), potentialNeigbour) != neighbours.end();
}