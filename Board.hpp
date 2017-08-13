#ifndef BOARD_HPP
#define BOARD_HPP

#include "Group.hpp"
#include "Coordinate.hpp"
#include "Turn.hpp"

#include <stdio.h>
#include <vector>
using std::vector;

class Board {
public:
	Board();
	Board(int maxX, int maxY);
	Board(const Board& orig);
	//virtual ~Board();
	
	bool addTurnHistory(vector<Turn> turnHistory);
	
	bool applyTurn(Turn t);
	bool applyTurn(bool color, Coordinate target);
	
	void changeColor();
	
	bool getColor();
	vector<Group> getGroups();
	int getMaxX();
	int getMaxY();
	int getMinX();
	int getMinY();
	
	vector<Turn> getTurnHistory();
	
	void setColor(bool color);
	void setMaxX(int maxX);
	void setMaxY(int maxY);
	void setMinX(int minX);
	void setMinY(int minY);
	
private:
	bool __currentColor;
	
	vector<Group> __groups;
	
	bool __initialized;
	bool isInitialized();
	
	int __maxX;
	int __maxY;
	int __minX = 1;
	int __minY = 1;
	
	void setInitialized();
	
	vector<Turn> __turnHistory;
	
};

#endif /* BOARD_HPP */

