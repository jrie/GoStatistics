#include <iostream>

#include "Coordinate.hpp"
#include "Turn.hpp"
//#include "Group.hpp"
#include "Board.hpp"

#include <algorithm>
#include <string> 

using namespace std;

/*
 * 
 */
int main(int argc, char** argv)
{
	cout << "Welcome to GoStatistics" << endl;
	
	string blackPlayer = "first player";
	string whitePlayer = "second player";
	
	
	// Output instructions...
	// ...
	
	cout << "The " << blackPlayer << " is black." << endl;
	cout << "The " << whitePlayer << " is white." << endl;
	
	Board b(19, 19);
	
	string cols = "abcdefghjklmnopqrst"; // no i !
	
	string input;
	
	while(input != "exit")
	{
		if(b.getColor())
		{
			// white
			cout << "Make your move " << whitePlayer << " (white)." << endl;
		}
		else
		{
			// black
			cout << "Make your move " << blackPlayer << " (black)." << endl;
		}
		
		cin >> input;
		
		if(input == "exit")
		{
			cout << "Good bye!" << endl;
			break;
		}
		else if(input == "show")
		{
			b.showField();
			continue;
		}
		else if(input.size() == 2)
		{
			// to lower case
			std::transform(input.begin(), input.end(), input.begin(), ::tolower);
			
			int pos = cols.find(input.at(0), 0);
			if(pos != cols.npos)
			{
				if(isdigit(input.at(1)))
				{
					Coordinate coor(pos + 1, input.at(1));
					
					if(b.applyTurn(b.getColor(), coor))
					{
						// Successfull
						cout << "Your move has been applied." << endl;
						continue;
					}
					else
					{
						cout << "ApplyTurn invalid" << endl;
					}
				}
				else
				{
					cout << "Cannot find row" << endl;
				}
			}
			else
			{
				cout << "Cannot find column" << endl;
			}
		}
		else if(input == "show")
		{
			
		}
		
		cout << "Your input is invalid. Please try again." << endl;
		
	}
	
	return 0;
}

