#ifndef GROUP_HPP
#define GROUP_HPP

#include "Coordinate.hpp"

#include <stdio.h>
#include <vector>

class Group {
public:
	Group() =default;
	Group(Coordinate member);
	
	bool addMember(Coordinate newMember);
	
	bool getColor() const;
	std::vector<Coordinate> getMembers() const;
	int getNumberOfMembers() const;
	
	bool hasMemberAt(Coordinate& coor) const;
	
	void setColor(bool color);
private:
	std::vector<Coordinate> m_coordinates;
	bool m_color = false;
	
};

#endif /* GROUP_HPP */

