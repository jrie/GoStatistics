#include "Turn.hpp"
#include "Coordinate.hpp"

int Turn::instances = 0;

Turn::Turn()
{
	__id = Turn::instances;
	Turn::instances++;
}

Turn::Turn(bool color, Coordinate target)
{
	__id = Turn::instances;
	Turn::instances++;
	setColor(color);
	setTarget(target);
	setInitialized();
}

Turn::Turn(const Turn& orig)
{
	this->setColor(orig.getColor());
	this->setTarget(orig.getTarget());
	this->__id = orig.getId();
	this->__initialized = orig.isInitialized();
}

void Turn::setColor(bool color) {
	__color = color;
}

void Turn::setInitialized()
{
	__initialized = true;
}

void Turn::setTarget(Coordinate target)
{
	__target = target;
}

bool Turn::isInitialized()
{
	return __initialized;
}

bool Turn::isValid()
{
	if(!isInitialized())
		return false;
	
	///\todo Implement validation check
	return true;
}

bool Turn::getColor()
{
	return __color;
}

int Turn::getId()
{
	return __id;
}

Coordinate Turn::getTarget()
{
	if(!isInitialized())
	{
		///\todo Do we want to use own Exception instances or any other error handler?
		///\todo I start with this one.
		throw "Turn is not fully initialized. No target coordinate is available.";
	}
	return __target;
}