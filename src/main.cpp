#include <iostream>

#include "Coordinate.hpp"
#include "Turn.hpp"
//#include "Group.hpp"
#include "Board.hpp"

#include <algorithm>
#include <string> 

using namespace std;

bool isInteger(const std::string& s)
{
	std::string::const_iterator it = s.begin();
	while(it != s.end() && std::isdigit(*it)) ++it;
	return !s.empty() && it == s.end();
}


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
	cout << "Type \"exit\" and the programm will stop" << endl;
	cout << "Type \"show\" and the playground will be displayed" << endl;
	cout << "To type a field for your stone you have to enter column first followed by " << endl
		 << "the row. For example h7 or t16" << endl << endl;
	
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
		else if(input.size() == 2 || input.size() == 3)
		{
			// to lower case
			std::transform(input.begin(), input.end(), input.begin(), ::tolower);
			
			int pos = cols.find(input.at(0), 0);
			if(pos != cols.npos)
			{
				string digit = input.substr(1);
				if(isInteger(digit))
				{
//					cout << "DEBUG - " << "Number is " << digit << endl;
//					cout << "DEBUG - " << "Column is " << pos + 1 << endl;
					Coordinate coor(pos + 1, std::stoul(digit));
					
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

