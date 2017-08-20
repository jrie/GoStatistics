#ifndef GROUP_HPP
#define GROUP_HPP

#include "Coordinate.hpp"

#include <vector>

class Group {
public:
	Group() =default;
	Group(Coordinate member);
	
	bool addMember(Coordinate newMember);
	
	bool getColor() const;
	std::vector<Coordinate> getMembers() const;
	int getNumberOfMembers() const;
	
	bool hasMemberAt(const Coordinate& coor) const;
	
	unsigned int merge(const Group& g);
	
	void setColor(bool color);
private:
	std::vector<Coordinate> m_coordinates;
	bool m_color = false;
	
};

inline bool operator==(const Group& lhs, const Group& rhs)
{
	return lhs.getColor() == rhs.getColor() && lhs.getMembers() == rhs.getMembers();
}

inline bool operator!=(const Group& lhs, const Group& rhs)
{
	return not (lhs == rhs);
}

#endif /* GROUP_HPP */

