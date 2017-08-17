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
	
	bool getColor();
	vector<Coordinate> getMembers();
	vector<Coordinate> getNeighbours();
	int getNumberOfMembers();
	
	bool hasMemberAt(Coordinate coor);
	bool hasNeighbour(Coordinate potentialNeigbour);
	
	void setColor(bool color);
private:
	vector<Coordinate> m_coordinates;
	bool m_color = false;
	
};

#endif /* GROUP_HPP */

