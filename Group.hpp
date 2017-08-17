#ifndef GROUP_HPP
#define GROUP_HPP

#include "Coordinate.hpp"

#include <stdio.h>
#include <vector>
using std::vector;

class Group {
public:
	Group() =default;
	Group(Coordinate member);
	Group(const Group& orig);
	//virtual ~Group();
	
	bool addMember(Coordinate newMember);
	
	bool getColor() const;
	vector<Coordinate> getMembers() const;
	int getNumberOfMembers() const;
	
	bool hasMemberAt(Coordinate& coor) const;
	
	void setColor(bool color);
private:
	vector<Coordinate> m_coordinates;
	bool m_color = false;
	
};

#endif /* GROUP_HPP */

