#ifndef GROUP_HPP
#define GROUP_HPP

#include "Coordinate.hpp"

#include <stdio.h>
#include <vector>
using std::vector;

class Group {
public:
	Group();
	Group(Coordinate member);
	Group(const Group& orig);
	//virtual ~Group();
	
	bool addMember(Coordinate newMember);
	
	vector<Coordinate> getMembers() const;
	vector<Coordinate> getNeighbours();
	int getNumberOfMembers();
	
	bool hasMemberAt(Coordinate coor);
	bool hasNeighbour(Coordinate potentialNeigbour);
private:
	vector<Coordinate> __members;
	
};

#endif /* GROUP_HPP */

