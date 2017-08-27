#include "Turn.hpp"

/**
 * This variable is static so that every instance can access this value
 * It will keep track of how many instances were created to set unique ids
 */
int Turn::instances = 0;


/**
 * @brief Costum Constructor
 * @param color black = false, white = true
 * @param target Coordinate of the target field
 */
Turn::Turn(bool color, Coordinate target) : m_color(color), m_target(target), m_id(Turn::instances)
{
	//m_id = Turn::instances;
	Turn::instances++;
}

/**
 * @brief Sets the player color. false for black and true for white
 * @param color The player color
 */
void Turn::setColor(bool color)
{
	m_color = color;
}

/**
 * @brief Sets the target Coordinate. This describes the field were the stone will be placed
 * @param target The Coordinate
 */
void Turn::setTarget(Coordinate target)
{
	m_target = target;
}

/**
 * @brief Returns the player color of the stone which will be played
 * @return The player color
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
 * @return The field (Coordinate) were the stone should be placed
 */
Coordinate Turn::getTarget() const
{
	return m_target;
}

bool operator==(const Turn& lhs, const Turn& rhs)
{
	return lhs.getColor() == rhs.getColor() && lhs.getTarget() == rhs.getTarget();
}

bool operator!=(const Turn& lhs, const Turn& rhs)
{
	return not (lhs == rhs);
}

bool operator<(const Turn& lhs, const Turn& rhs)
{
	return lhs.getId() < rhs.getId();
}

bool operator>(const Turn& lhs, const Turn& rhs)
{
	return rhs < lhs;
}

bool operator<=(const Turn& lhs, const Turn& rhs)
{
	return not (lhs > rhs);
}

bool operator>=(const Turn& lhs, const Turn& rhs)
{
	return not (lhs < rhs);
}