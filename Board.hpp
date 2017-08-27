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
	
	int applyTurnToGroups(const Turn& t, std::vector<Group>& groups);
	
	void changeColor();
	
	std::vector<Group> getCatchedGroups(const bool color, const std::vector<Group>& groups);
	
	bool getColor();
	std::vector<Coordinate> getCoordinates(const std::vector<Group>& groups);
	
	std::vector<Group> getGroups();
	std::vector<Group> getGroups(bool color);
	std::vector<Group> getGroups(bool color, const std::vector<Group>& groupList);
	int getMaxX();
	int getMaxY();
	int getMinX();
	int getMinY();
	
	float getPoints(bool color);
	
	std::vector<Turn> getTurnHistory();
	
	std::vector<Coordinate> removeGroups(const std::vector<Group>& groupsToRemove, std::vector<Group>& groups);
	
	void setColor(bool color);
	void setMaxX(int maxX);
	void setMaxY(int maxY);
	void setMinX(int minX);
	void setMinY(int minY);
	
	std::vector<Coordinate> getNeighbours(const Coordinate& coor);
	std::vector<Coordinate> getNeighbours(const Group& g);
	
	std::vector<Coordinate> getAllStones();
	bool isFree(const Coordinate& coor);
	bool isFree(const Coordinate& coor, const std::vector<Group>& groups);
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
	unsigned int m_numberOfRemovedStonesLastTurn = 0;
	std::vector<Coordinate> m_removedStonesLastTurn;
	
	void setInitialized();
	
	std::vector<Turn> m_turnHistory;
	
};

#endif /* BOARD_HPP */

