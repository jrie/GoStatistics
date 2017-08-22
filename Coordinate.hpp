#ifndef COORDINATE_HPP
#define COORDINATE_HPP

class Coordinate {
public:
	Coordinate() = default;

	Coordinate(int x, int y) : m_x(x), m_y(y) {}

	int x() const
	{
		return m_x;
	}

	int y() const
	{
		return m_y;
	}

private:
	int m_x = 0;
	int m_y = 0;
};

inline bool operator==(const Coordinate& lhs, const Coordinate& rhs)
{
	return lhs.x() == rhs.x() && lhs.y() == rhs.y();
}

inline bool operator!=(const Coordinate& lhs, const Coordinate& rhs)
{
	return not (lhs == rhs);
}

inline bool operator<(const Coordinate& lhs, const Coordinate& rhs)
{
	if(lhs.y() == rhs.y())
	{
		return lhs.x() < rhs.x();
	}
	else
	{
		return lhs.y() < rhs.y();
	}
}

inline bool operator>(const Coordinate& lhs, const Coordinate& rhs)
{
	return rhs < lhs;
}

inline bool operator<=(const Coordinate& lhs, const Coordinate& rhs)
{
	return not (lhs > rhs);
}

inline bool operator>=(const Coordinate& lhs, const Coordinate& rhs)
{
	return not (lhs < rhs);
}

#endif /* COORDINATE_HPP */

