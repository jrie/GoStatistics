#ifndef TURN_HPP
#define TURN_HPP

#include "Coordinate.hpp"

class Turn {
public:
	Turn();
	Turn(bool color, Coordinate target);
	Turn(const Turn& orig);
	
	bool isInitialized() const;
	bool isValid() const;
	
	bool getColor() const;
	int getId() const;
	Coordinate getTarget() const;
	
	
	static int instances;
	
	
private:
	void setColor(bool color);
	void setTarget(Coordinate target);
	void setInitialized();
	
	bool m_color = false;
	int m_id = -1;
	bool m_initialized;
	Coordinate m_target;
};

#endif /* TURN_HPP */

