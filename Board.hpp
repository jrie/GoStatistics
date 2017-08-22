#ifndef BOARD_HPP
#define BOARD_HPP

#include "Group.hpp"
#include "Coordinate.hpp"
#include "Turn.hpp"

#include <vector>
#include <map>

class Board {
public:
	Board() : m_maxX(19), m_maxY(19), m_currentColor(false) {
		initPoints();
	};
	Board(int maxX, int maxY) : m_maxX(maxX), m_maxY(maxY), m_currentColor(false) {
		initPoints();
	};
	
	void initPoints();
	
	bool addTurnHistory(std::vector<Turn> turnHistory);
	
	void addPoints(bool color, float points);
	
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
	
	float getPoints(bool color);
	
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
	
	bool isNeighbour(const Coordinate& coorToCheck, const Coordinate& coor);
	bool isNeighbour(const Coordinate& coorToCheck, const Group& g);
	
	void showField(int type = 0);
	
private:
	bool m_currentColor;
	
	std::vector<Group> m_groups;
	
	bool m_initialized;
	bool isInitialized();
	
	int m_maxX;
	int m_maxY;
	int m_minX = 1;
	int m_minY = 1;
	
	std::map<bool, float> m_points;
	
	void setInitialized();
	
	std::vector<Turn> m_turnHistory;
	
};

#endif /* BOARD_HPP */

