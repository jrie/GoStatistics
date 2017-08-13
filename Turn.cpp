#include "Turn.hpp"
#include "Coordinate.hpp"

/**
 * This variable is static so that every instance can access this value
 */
int Turn::instances = 0;

/**
 * @brief Standard Constructor
 */
Turn::Turn()
{
	__id = Turn::instances;
	Turn::instances++;
}

/**
 * @brief Costum Constructor
 * @param color black = false, white = true
 * @param target Coordinate of the target field
 */
Turn::Turn(bool color, Coordinate target)
{
	__id = Turn::instances;
	Turn::instances++;
	setColor(color);
	setTarget(target);
	setInitialized();
}

/**
 * @brief Copy Constructor which creates a new Turn object with the values
 * of the given object
 * @param orig The Turn object which will be copied
 */
Turn::Turn(const Turn& orig)
{
	this->setColor(orig.getColor());
	//errorhandling because this functin can throw an exception..
	this->setTarget(orig.getTarget());
	this->__id = orig.getId();
	this->__initialized = orig.isInitialized();
}

/**
 * @brief Sets the color. false for black and true for white
 * @param color
 */
void Turn::setColor(bool color) {
	__color = color;
}

/**
 * @brief Sets the privat variables __initialized to true
 */
void Turn::setInitialized()
{
	__initialized = true;
}

/**
 * @brief Sets the target Coordinate
 * @param target The Coordinate
 */
void Turn::setTarget(Coordinate target)
{
	__target = target;
}

/**
 * @brief Returns if the object is fully initialized
 * @return true if the object is initialized
 */
bool Turn::isInitialized() const
{
	return __initialized;
}

/**
 * @brief Returns if the represented turn is valid or not
 * @return true if the turn is valid
 * @todo We need to implement a validation check!
 */
bool Turn::isValid()
{
	if(!isInitialized())
		return false;
	
	///\todo Implement validation check
	return true;
}

/**
 * @brief Returns the color of the Stone which will be played
 * @return The color
 */
bool Turn::getColor() const
{
	return __color;
}

/**
 * @brief Returns the id of this turn
 * @return The id of this turn
 */
int Turn::getId() const
{
	return __id;
}

/**
 * @brief Returns the target Coordinate
 * @return The target Coordinate
 * @throws Exception if the object is not fully initialized
 */
Coordinate Turn::getTarget() const
{
	if(!isInitialized())
	{
		///\todo Do we want to use own Exception instances or any other error handler?
		///\todo I start with this one.
		throw "Turn is not fully initialized. No target coordinate is available.";
	}
	return __target;
}