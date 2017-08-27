#ifndef TURN_HPP
#define TURN_HPP

#include "Coordinate.hpp"

class Turn {
public:
	Turn(bool color, Coordinate target);
	
	bool getColor() const;
	int getId() const;
	Coordinate getTarget() const;
	
	void setColor(bool color);
	void setTarget(Coordinate target);
	
	// keeps track of how many instances were created
	static int instances;
private:
	bool m_color = false;
	int m_id = -1;
	Coordinate m_target;
};

bool operator==(const Turn& lhs, const Turn& rhs);
bool operator!=(const Turn& lhs, const Turn& rhs);
bool operator<(const Turn& lhs, const Turn& rhs);
bool operator>(const Turn& lhs, const Turn& rhs);
bool operator<=(const Turn& lhs, const Turn& rhs);
bool operator>=(const Turn& lhs, const Turn& rhs);

#endif /* TURN_HPP */

