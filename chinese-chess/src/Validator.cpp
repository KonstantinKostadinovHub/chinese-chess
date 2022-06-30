#include "Validator.h"

bool canMove(int2 coor)
{
	return false;
}

bool isNumber(string data)
{
	for (int i = 0; i < data.length(); i++)
	{
		if (!isdigit(data[i]))
		{
			return false;
		}
	}

	return true;
}

//*
//* give all the squares that are unavailable after we places a queen
//*/
//vector<int2> giveAvailableMoves(int2 coor, int rows, int colls)
//{
//	vector<int2> unavailableMoves; // return at the end of the function
//	
//	// king moves
//	
//	// curr place
//	unavailableMoves.push_back(coor);
//		
//	for (int i = 0; i < 8; i++)
//	{
//		int2 buff = coor + directions[i];
//		if (inGrid(buff, rows, colls))
//		{
//			unavailableMoves.push_back(buff);
//		}
//	}
//	
//	// now is time for the bishop and rook moves
//	for (int i = 0; i < 8; i++)
//	{
//		lineMoves(coor, rows, colls, i, unavailableMoves);
//	}
//
//	return unavailableMoves;
//}


/*
* check if the move belongs to the grid
* @param coor - the move we want to check
* @param ROLLS - rows
* @param COLLS - colls
*/
bool inGrid(int2 coor, int ROWS, int COLLS)
{
	if (coor.x < 0 || coor.x >= ROWS || coor.y < 0 || coor.y >= COLLS)
	{
		return false;
	}
	return true;
}

