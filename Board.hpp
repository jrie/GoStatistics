#ifndef BOARD_HPP
#define BOARD_HPP

#include "Group.hpp"
#include "Coordinate.hpp"
#include "Turn.hpp"

#include <vector>

class Board {
public:
	Board() : m_maxX(19), m_maxY(19) {};
	Board(int maxX, int maxY) : m_maxX(maxX), m_maxY(maxY) {};
	
	bool addTurnHistory(std::vector<Turn> turnHistory);
	
	bool applyTurn(Turn t);
	bool applyTurn(bool color, Coordinate target);
	
	void changeColor();
	
	bool getColor();
	std::vector<Group> getGroups();
	std::vector<Group> getGroups(bool color);
	int getMaxX();
	int getMaxY();
	int getMinX();
	int getMinY();
	
	std::vector<Turn> getTurnHistory();
	
	void setColor(bool color);
	void setMaxX(int maxX);
	void setMaxY(int maxY);
	void setMinX(int minX);
	void setMinY(int minY);
	
	std::vector<Coordinate> getNeighbours(const Coordinate& coor);
	std::vector<Coordinate> getNeighbours(const Group& g);
	
	
	bool isValid(const Coordinate& coor);
	bool isValid(const Group& g);
	bool isValid(const Turn& t);
	
private:
	bool m_currentColor;
	
	std::vector<Group> m_groups;
	
	bool m_initialized;
	bool isInitialized();
	
	int m_maxX;
	int m_maxY;
	int m_minX = 1;
	int m_minY = 1;
	
	void setInitialized();
	
	std::vector<Turn> m_turnHistory;
	
};

#endif /* BOARD_HPP */

