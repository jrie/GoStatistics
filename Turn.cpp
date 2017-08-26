#include "Turn.hpp"

/**
 * This variable is static so that every instance can access this value
 */
int Turn::instances = 0;

/**
 * @brief Standard Constructor
 */
Turn::Turn()
{
	m_id = Turn::instances;
	Turn::instances++;
}

/**
 * @brief Costum Constructor
 * @param color black = false, white = true
 * @param target Coordinate of the target field
 */
Turn::Turn(bool color, Coordinate target)
{
	m_id = Turn::instances;
	Turn::instances++;
	setColor(color);
	setTarget(target);
	setInitialized();
}

/**
 * @brief Sets the color. false for black and true for white
 * @param color
 */
void Turn::setColor(bool color)
{
	m_color = color;
}

/**
 * @brief Sets the privat variables __initialized to true
 */
void Turn::setInitialized()
{
	m_initialized = true;
}

/**
 * @brief Sets the target Coordinate
 * @param target The Coordinate
 */
void Turn::setTarget(Coordinate target)
{
	m_target = target;
}

/**
 * @brief Returns if the object is fully initialized
 * @return true if the object is initialized
 */
bool Turn::isInitialized() const
{
	return m_initialized;
}

/**
 * @brief Returns if the represented turn is valid or not
 * @return true if the turn is valid
 * @deprecated This function is replaced by Board::isValid(Turn)
 */
bool Turn::isValid() const
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
	return m_color;
}

/**
 * @brief Returns the id of this turn
 * @return The id of this turn
 */
int Turn::getId() const
{
	return m_id;
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
	return m_target;
}