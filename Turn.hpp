#ifndef TURN_HPP
#define TURN_HPP

#include "Coordinate.hpp"

class Turn {
public:
	Turn();
	Turn(bool color, Coordinate target);
	Turn(const Turn& orig);
	
	bool isInitialized();
	bool isValid();
	
	bool getColor();
	int getId();
	Coordinate getTarget();
	
	
	static int instances;
	
	
private:
	void setColor(bool color);
	void setTarget(Coordinate target);
	void setInitialized();
	
	bool __color = false;
	int __id = -1;
	bool __initialized;
	Coordinate __target;
};

#endif /* TURN_HPP */

