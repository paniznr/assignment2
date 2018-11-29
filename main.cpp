
//
//  main.cpp
//  assignment2
//
//  Created by Paniz Najjarrezaparast, Sharanjit Virdi, and Aliyah Nanji on 2018-11-28.
//  Copyright © 2018 Paniz Najjarrezaparast, Sharanjit Virdi, and Aliyah Nanji. All rights reserved.
//
#include <iostream>
#include <fstream>
#include <string>
#include<iomanip>
#include <cmath>
using namespace std;

const int MAX_ARRAY_SIZE = 18;

const int MIN_ARRAY_SIZE = 8;

const int MAX_PIECES = 72; 

const int NOPLAYER = 0;

const int WHITEWINS = 1; 

const int REDWINS = 2;

const int NOONEWINS = 0;

const int WHITESOLDIER = 1;

const int WHITEMULE = 2;

const int WHITEKING = 3;

const int REDSOLDIER = 4;

const int REDMULE = 5;

const int REDKING = 6;

const int WHITEPLAYER = 1;

const int REDPLAYER = 2;

void InitializeBoard(int CMCheckersBoard[MAX_ARRAY_SIZE][MAX_ARRAY_SIZE], int numRowsInBoard);

void DisplayBoard(int CMCheckersBoard[MAX_ARRAY_SIZE][MAX_ARRAY_SIZE], int numRowsInBoard);

int CountJumps(int CMCheckersBoard[MAX_ARRAY_SIZE][MAX_ARRAY_SIZE], int numRowsInBoard, int player, int xLocArray[], int yLocArray[]);

bool CheckList(int inArray1[], int inArray2[], int xIndex, int yIndex);

int CountMove1Squares(int CMCheckersBoard[MAX_ARRAY_SIZE][MAX_ARRAY_SIZE], int numRowsInBoard, int player, int xLocArray[], int yLocArray[]);

bool IsMove1Square(int CMCheckersBoard[MAX_ARRAY_SIZE][MAX_ARRAY_SIZE], int numRowsInBoard, int player, int xLoc, int yLoc);

bool IsJump(int CMCheckersBoard[MAX_ARRAY_SIZE][MAX_ARRAY_SIZE], int numRowsInBoard, int player, int xLoc, int yLoc);

bool MakeMove(int CMCheckersBoard[MAX_ARRAY_SIZE][MAX_ARRAY_SIZE], int numRowsInBoard, int player, int fromSquareNum, int toSquareNum, bool &jumped);

bool CheckWin(int CMCheckersBoard[MAX_ARRAY_SIZE][MAX_ARRAY_SIZE], int numRowsInBoard);




int main()
{


	int myCMCheckersBoard[MAX_ARRAY_SIZE][MAX_ARRAY_SIZE] = { 0 };
	int xIndicesMove[MAX_PIECES]; //holds x index
	int yIndicesMove[MAX_PIECES]; //holds y index of location on board of a checker
	//these are the checkers that can be moved
	//include Soldier/Mule that can move 1 square diagonally fwd
	//& King that can move 1 sqr diagonally fwd OR bkwd
	int xIndicesJump[MAX_PIECES];
	int yIndicesJump[MAX_PIECES];
	//char enter_key;
	//these are cheeckers that can jump one of the opponents checkers
	int numRowsInBoard = 0;
	int i;
	int turn = 0;
	int jumps;
	int moves;
	int intended_move = 0;
	int future_placement = 0;
	bool right_move = false;
	int xvalFROM;
	int yvalFROM;
	int xvalTO;
	int yvalTO;
	int xdist = 0;
	int ydist = 0;
	bool jumped = false;
	bool move_made;
	bool check_win_now;

	for (i = 0; i < 4; i++)
	{
		if (i == 3)
		{
			cerr << "ERROR: Too many errors entering the size of the board.\n";
			return 2;
		}
		else
		{
			cout << "Enter the number of squares along each edge of the board\n";

			if (!(cin >> numRowsInBoard))
			{

				cerr << "ERROR: Board size is not an integer.\n";
				cerr << "8 <= number of squares <= 18\n";
				cin.clear();
				cin.ignore();
				continue;
			}
			else if (numRowsInBoard > 18)
			{
				cerr << "ERROR: Board size too large.\n";
				cerr << "8 <= number of squares <= 18\n";
				continue;
			}
			else if (numRowsInBoard < 8)
			{
				cerr << "ERROR: Board size too small.\n";
				cerr << "8 <= number of squares <= 18\n";
				continue;
			}
			else if (numRowsInBoard % 2 == 1)
			{
				cerr << "ERROR: Board size odd.\n";
				cerr << "8 <= number of squares <= 18\n";
				continue;
			}
			else {
				break;
			}

		}
	}

	myCMCheckersBoard[numRowsInBoard][numRowsInBoard] = { 0 };

	//InitializeBoard function
	InitializeBoard(myCMCheckersBoard, numRowsInBoard);

	//displayboard function
	DisplayBoard(myCMCheckersBoard, numRowsInBoard);

	do
	{
		if (turn % 2 == 0)
			//player 1, white
		{
			turn = WHITEPLAYER;
			jumps = CountJumps(myCMCheckersBoard, numRowsInBoard, turn, xIndicesJump, yIndicesJump);
			moves = CountMove1Squares(myCMCheckersBoard, numRowsInBoard, turn, xIndicesMove, yIndicesMove);



			if (jumps == 0 && moves == 0)
			{
				cerr << "White is unable to move.\nGAME OVER, Red has won.\nEnter any character to close the game.\n";
			}
			else
			{
				cout << "White takes a turn.\n";
				

				while (right_move == false)
				{
					cout << "Enter the square number of the checker you want to move" << endl;
					cin >> intended_move;

					xvalFROM = intended_move % numRowsInBoard;
					yvalFROM = intended_move / numRowsInBoard;

					if (!intended_move)
					{
						cerr << "ERROR: You did not enter an integer" << endl
							<< "Try again" << endl;
						cin.clear();
						cin.ignore();
						continue;

					}
					else if ((intended_move >= (numRowsInBoard*numRowsInBoard)) || (intended_move < 0))
					{
						cerr << "ERROR: That square is not on the board." << endl
							<< "Try again" << endl;
						continue;
					}
					else if ((myCMCheckersBoard[xvalFROM][yvalFROM] == REDKING) || (myCMCheckersBoard[xvalFROM][yvalFROM] == REDSOLDIER) || (myCMCheckersBoard[xvalFROM][yvalFROM] == REDMULE))
					{

						cerr << "ERROR: That square contains an opponent's checker." << endl
							<< "Try again" << endl;
						continue;
					}
					else if ((myCMCheckersBoard[xvalFROM][yvalFROM] != WHITEKING) && (myCMCheckersBoard[xvalFROM][yvalFROM] != WHITEMULE) && (myCMCheckersBoard[xvalFROM][yvalFROM] != WHITESOLDIER))
					{
						
						cerr << "ERROR: That square is empty." << endl
							<< "Try again" << endl;
						continue;
					}


					else if (CheckList(xIndicesJump, yIndicesJump, xvalFROM, yvalFROM) == true)
					{
						cerr << "ERROR: You can jump with another checker, you may not move your chosen checker." << endl

							<< "You can jump using checkers on the following squares : "
							<< "Try again" << endl;
						continue;
					}
					else if (!(CheckList(xIndicesMove, yIndicesMove, xvalFROM, yvalFROM)))
					{
						cerr << "ERROR: There is no legal move for this checker." << endl
							<< "Try again" << endl;
						continue;
					}
					else
					{
						right_move = true;
					}

				}


				right_move = false;
				while (right_move == false)
				{
					cout << "Enter the square number of the square you want to move your checker to" << endl;
					cin >> future_placement;

					xvalTO = future_placement % numRowsInBoard;
					yvalTO = future_placement / numRowsInBoard;


				//	unsigned
					int absltxdist = 0;
					//unsigned 
					int absltydist = 0;

					xdist = (xvalTO - xvalFROM);

					ydist = (yvalTO - yvalFROM);


					if (!future_placement)
					{
						cerr << "you did not enter an integer" << endl
							<< "Try again" << endl;
						cin.clear();
						cin.ignore();
						continue;

					}
					else if ((future_placement >= (numRowsInBoard*numRowsInBoard)) || (future_placement < 0))
					{
						cerr << "ERROR: It is not possible to move to a square that is not on the board." << endl
							<< "Try again" << endl;
						continue;
					}


					else if (!((myCMCheckersBoard[xvalTO][yvalTO]) == NOPLAYER))
					{
						cerr << "ERROR: It is not possible to move to a square that is already occupied." << endl << "Try again" << endl;
						continue;
					}

					else if (xdist == 0)
					{
						cerr << "ERROR: Illegal move" << endl;
						cerr << "ERROR: Moving to that square is not legal, Try again." << "SET" << endl;
						continue;
					}
					else if (ydist == 0)
					{
						cerr << "ERROR: Illegal move" << endl;
						cerr << "ERROR: Moving to that square is not legal, Try again." << "GET" << endl;
						continue;
					}

					else
					{

						move_made = MakeMove(myCMCheckersBoard, numRowsInBoard, turn, intended_move, future_placement, jumped);

						DisplayBoard(myCMCheckersBoard, numRowsInBoard);

						if (move_made == false)
						{

							cerr << "ERROR: Moving to that square is not legal, Try again." << "GO" << endl;
						}
						else if (jumped == true)
						{
							if (((IsJump(myCMCheckersBoard, numRowsInBoard, turn, xvalTO, yvalTO)) == true) && ((IsMove1Square(myCMCheckersBoard, numRowsInBoard, turn, xvalTO, yvalTO)) == true))
							{
								cout << "You can jump again, Please enter the next square you wish to move your checker to" << endl;

							}
						}
						else
						{
							right_move = true;
						}

					}

				}

			}
		}
		else
		{
			turn = REDPLAYER;
			jumps = CountJumps(myCMCheckersBoard, numRowsInBoard, turn, xIndicesJump, yIndicesJump);
			moves = CountMove1Squares(myCMCheckersBoard, numRowsInBoard, turn, xIndicesMove, yIndicesMove);



			if (jumps == 0 && moves == 0)
			{
				cerr << "Red is unable to move.\nGAME OVER, White has won.\nEnter any character to close the game.\n";
			}
			else
			{
				cout << "Red takes a turn.\n";
				right_move = false;
				
				while (right_move == false)
				{
					cout << "Enter the square number of the checker you want to move" << endl;
					cin >> intended_move;

					xvalFROM = intended_move % numRowsInBoard;
					yvalFROM = intended_move / numRowsInBoard;

					if (!intended_move)
					{
						cerr << "ERROR: You did not enter an integer" << endl
							<< "Try again" << endl;
						cin.clear();
						cin.ignore();
						continue;

					}
					else if ((intended_move >= (numRowsInBoard*numRowsInBoard)) || (intended_move < 0))
					{
						cerr << "ERROR: That square is not on the board." << endl
							<< "Try again" << endl;
						continue;
					}
					else if ((myCMCheckersBoard[xvalFROM][yvalFROM] == WHITEKING) || (myCMCheckersBoard[xvalFROM][yvalFROM] == WHITESOLDIER) || (myCMCheckersBoard[xvalFROM][yvalFROM] == WHITEMULE))
					{

						cerr << "ERROR: That square contains an opponent's checker." << endl
							<< "Try again" << endl;
						continue;
					}
					else if ((myCMCheckersBoard[xvalFROM][yvalFROM] != REDKING) && (myCMCheckersBoard[xvalFROM][yvalFROM] != REDMULE) && (myCMCheckersBoard[xvalFROM][yvalFROM] != REDSOLDIER))
					{
						
						cerr << "ERROR: That square is empty." << endl
							<< "Try again" << endl;
						continue;
					}
					
					else if (CheckList(xIndicesJump, yIndicesJump, xvalFROM, yvalFROM) == true)
					{
						cerr << "ERROR: You can jump with another checker, you may not move your chosen checker." << endl

							<< "You can jump using checkers on the following squares : "
							<< "Try again" << endl;
						continue;
					}
					
					else if (CheckList(xIndicesMove, yIndicesMove, xvalFROM, yvalFROM) == false)
					{
						cerr << "ERROR: There is no legal move for this checker." << endl
							<< "Try again" << endl;
						continue;
					}
					else
					{
						right_move = true;
					}

				}


				right_move = false;
				while (right_move == false)
				{
					cout << "Enter the square number of the square you want to move your checker to" << endl;
					cin >> future_placement;

					xvalTO = future_placement % numRowsInBoard;
					yvalTO = future_placement / numRowsInBoard;


				//	unsigned
					int absltxdist = 0;
					//unsigned 
					int absltydist = 0;

					xdist = (xvalTO - xvalFROM);

					ydist = (yvalTO - yvalFROM);


					if (!future_placement)
					{
						cerr << "you did not enter an integer" << endl
							<< "Try again" << endl;
						cin.clear();
						cin.ignore();
						continue;

					}
					else if ((future_placement >= (numRowsInBoard*numRowsInBoard)) || (future_placement < 0))
					{
						cerr << "ERROR: It is not possible to move to a square that is not on the board." << endl
							<< "Try again" << endl;
						continue;
					}


					else if (!((myCMCheckersBoard[xvalTO][yvalTO]) == NOPLAYER))
					{
						cerr << "ERROR: It is not possible to move to a square that is already occupied." << endl << "Try again" << endl;
						continue;
					}

					else if (xdist == 0)
					{
						cerr << "ERROR: Illegal move" << endl;
						cerr << "ERROR: Moving to that square is not legal, Try again." << "SET" << endl;
						continue;
					}
					else if (ydist == 0)
					{
						cerr << "ERROR: Illegal move" << endl;
						cerr << "ERROR: Moving to that square is not legal, Try again." << "GET" << endl;
						continue;
					}

					else
					{

						move_made = MakeMove(myCMCheckersBoard, numRowsInBoard, turn, intended_move, future_placement, jumped);

						DisplayBoard(myCMCheckersBoard, numRowsInBoard);

						if (move_made == false)
						{

							cerr << "ERROR: Moving to that square is not legal, Try again." << "GO" << endl;
						}
						else if (jumped == true)
						{
							if (((IsJump(myCMCheckersBoard, numRowsInBoard, turn, xvalTO, yvalTO)) == true) && ((IsMove1Square(myCMCheckersBoard, numRowsInBoard, turn, xvalTO, yvalTO)) == true))
							{
								cout << "You can jump again, Please enter the next square you wish to move your checker to" << endl;

							}
						}
						else
						{
							right_move = true;
						}
					}
				}
			}
		}

		cout << "HELLO!" << endl;

		cout << turn << endl;
		check_win_now = CheckWin(myCMCheckersBoard, numRowsInBoard);
		cout << check_win_now;

	} while (check_win_now == false);

	return 0;

}








void InitializeBoard(int CMCheckersBoard[MAX_ARRAY_SIZE][MAX_ARRAY_SIZE], int numRowsInBoard)
{
	int row; //y
	int col; //x
	for (row = 0; row < numRowsInBoard; row++)
	{
		if (row == 0) //very first row: white mules
		{
			for (col = 0; col < numRowsInBoard; col++)
			{
				if (col % 2 == 0) //even column
				{
					CMCheckersBoard[col][row] = { 0 };
				}
				else
				{

					CMCheckersBoard[col][row] = { 2 };

				}
			}
			cout << endl;
		}
		else if (row == (numRowsInBoard - 1)) //very last row: red mules
		{
			for (col = 0; col < numRowsInBoard; col++)
			{
				if (col % 2 == 0) //even arrays, odd column #
				{
					CMCheckersBoard[col][row] = { 5 };
					cout << CMCheckersBoard[col][row];
				}
				else //odd arrays, even column #
				{
					CMCheckersBoard[col][row] = { 0 };
					cout << CMCheckersBoard[col][row];
				}
			}
			cout << endl;

		}
		else if ((row == ((numRowsInBoard / 2) - 1)) || (row == (numRowsInBoard / 2)))
		{
			for (col = 0; col < numRowsInBoard; col++)
			{
				CMCheckersBoard[col][row] = { 0 };
				cout << CMCheckersBoard[col][row];
			}
			cout << endl;

		}

		else if (row > 0 && row < (numRowsInBoard - 1) && (row != (numRowsInBoard / 2) - 1) && (row != (numRowsInBoard / 2)))
			//if its not the first row, last row, or 2 middle rows:
		{
			if (row < (numRowsInBoard / 2) - 1) //white
			{
				if (row % 2 == 0)
				{
					for (col = 0; col < numRowsInBoard; col++)
					{
						if (col % 2 == 0) //even column
						{
							CMCheckersBoard[col][row] = { 0 };
							cout << CMCheckersBoard[col][row];
						}
						else
						{

							CMCheckersBoard[col][row] = { 1 };
							cout << CMCheckersBoard[col][row];
						}
					}
					cout << endl;
				}
				else
				{
					for (col = 0; col < numRowsInBoard; col++)
					{
						if (col % 2 == 0) //even column
						{
							CMCheckersBoard[col][row] = { 1 };
							cout << CMCheckersBoard[col][row];
						}
						else
						{
							CMCheckersBoard[col][row] = { 0 };
							cout << CMCheckersBoard[col][row];
						}
					}
					cout << endl;
				}
			}
			else if (row > (numRowsInBoard / 2))
			{
				if (row % 2 == 0)
				{
					for (col = 0; col < numRowsInBoard; col++)
					{
						if (col % 2 == 0) //even column
						{
							CMCheckersBoard[col][row] = { 0 };
							cout << CMCheckersBoard[col][row];
						}
						else
						{
							CMCheckersBoard[col][row] = { 4 };
							cout << CMCheckersBoard[col][row];
						}
					}
					cout << endl;

				}
				else
				{
					for (col = 0; col < numRowsInBoard; col++)
					{
						if (col % 2 == 0) //even column
						{
							CMCheckersBoard[col][row] = { 4 };
							cout << CMCheckersBoard[col][row];
						}
						else
						{
							CMCheckersBoard[col][row] = { 0 };
							cout << CMCheckersBoard[col][row];
						}
					}
					cout << endl;

				}
			}
		}
	}
}







void DisplayBoard(int CMCheckersBoard[MAX_ARRAY_SIZE][MAX_ARRAY_SIZE], int numRowsInBoard)
{
	int counter = 0;
	for (int row = 0; row < numRowsInBoard; row++)
	{
		for (int col = 0; col < numRowsInBoard; col++)
		{

			if (CMCheckersBoard[col][row] == 0)
			{
				cout << setw(4) << counter;
				counter++;
			}
			else
			{
				switch (CMCheckersBoard[col][row])
				{
				case WHITESOLDIER:
				{
					cout << setw(4) << "WS";
					counter++;
					break;
				}
				case WHITEMULE:
				{
					cout << setw(4) << "WM";
					counter++;
					break;
				}
				case WHITEKING:
				{
					cout << setw(4) << "WK";
					counter++;
					break;
				}
				case REDSOLDIER:
				{
					cout << setw(4) << "RS";
					counter++;
					break;
				}
				case REDMULE:
				{
					cout << setw(4) << "RM";
					counter++;
					break;
				}
				case REDKING:
				{
					cout << setw(4) << "RK";
					counter++;
					break;
				}
				}
			}
		}
		cout << endl;
	}
}



//IF ALL ELEMENTS IN yLocArray[] AND xLocArray[] ARE INITIALIZED TO -1, WHERE DO WE GET THE UNINITIALIZED 0 LOCATIONS FROM?

int CountJumps(int CMCheckersBoard[MAX_ARRAY_SIZE][MAX_ARRAY_SIZE], int numRowsInBoard, int player, int xLocArray[], int yLocArray[])
{
	int num_checkers_jump_allowed = 0;
	int white_player_jump = 0;
	int red_player_jump = 0;


	for (int x = 0; x < MAX_PIECES; x++)
	{
		xLocArray[x] = -1;
	}
	for (int y = 0; y < MAX_PIECES; y++)
	{
		yLocArray[y] = -1;
	}

	for (int i = 0; i < numRowsInBoard; i++)
	{
		for (int j = 0; j < numRowsInBoard; j++)
		{
			if (player == WHITEPLAYER)    //Considers the white player pieces
			{
				if (IsJump(CMCheckersBoard, numRowsInBoard, player, i, j))
				{
					white_player_jump++;

					for (int xindex = 0; xindex < MAX_PIECES; xindex++)
					{
						if (xLocArray[xindex] == -1)
						{
							xLocArray[xindex] = i;
							break;
						}
					}

					for (int yindex = 0; yindex < MAX_PIECES; yindex++)
					{
						if (yLocArray[yindex] == -1)
						{
							yLocArray[yindex] = j;
							break;
						}
					}

				}
			}

			else if (player == REDPLAYER)    //Considers the red player pieces
			{
				if (IsJump(CMCheckersBoard, numRowsInBoard, player, i, j))
				{
					red_player_jump++;

					for (int xindex = 0; xindex < MAX_PIECES; xindex++)
					{
						if (xLocArray[xindex] == -1)
						{
							xLocArray[xindex] = i;
							break;
						}
					}

					for (int yindex = 0; yindex < MAX_PIECES; yindex++)
					{
						if (yLocArray[yindex] == -1)
						{
							yLocArray[yindex] = j;
							break;
						}
					}

				}

			}
		}
	}

	if (player == 1)
	{
		num_checkers_jump_allowed = white_player_jump;
	}
	else if (player == 2)
	{
		num_checkers_jump_allowed = red_player_jump;
	}

	return num_checkers_jump_allowed;
}


bool CheckList(int inArray1[], int inArray2[], int xIndex, int yIndex)
{
	bool found = false;
	for (int i = 0; i < MAX_ARRAY_SIZE; i++)
	{
		if ((inArray1[i] == xIndex) && (inArray2[i] == yIndex))
		{
			found = true;
		}


	}
	return found;

}




int CountMove1Squares(int CMCheckersBoard[MAX_ARRAY_SIZE][MAX_ARRAY_SIZE], int numRowsInBoard, int player, int xLocArray[], int yLocArray[])
{
	bool posmove;
	//int redcheckersthatcanmove = 0;
	//int whitecheckersthatcanmove = 0;
	int checkersthatcanmove = 0;
	int xIndex = 0;
	int yIndex = 0;
	int xloccounter = 0;
	int yloccounter = 0;
	//    yLocArray[MAX_ARRAY_SIZE] = { -1 };
	//IDK IF THIS IS RIGHT
	///CHECK PLS IS IT SUPPOSED TO BE numRowsInBoard
	/// I think it should be MAX_PIECES, but I don’t know.
	//    yLocArray = { 0 };
	for (int counter = 0; counter < MAX_PIECES; counter++)
	{
		yLocArray[counter] = -1;
	}
	//    xLocArray = { 0 };
	for (int counter = 0; counter < MAX_PIECES; counter++)
	{
		xLocArray[counter] = -1;
	}
	// for white ones
	//ii. xIndex is placed in the next unused location of array
	//xLocArray and yIndex is placed in the next unused element of array yLocArray
	if (player == 1)
	{
		// for (int row = 0; row < numRowsInBoard; row++)
		for (int xIndex = 0; xIndex < numRowsInBoard; xIndex++)
		{
			for (int yIndex = 0; yIndex < numRowsInBoard; yIndex++)
			{
				if ((CMCheckersBoard[xIndex][yIndex] != 0) && 
					((CMCheckersBoard[xIndex][yIndex] == WHITEMULE) || (CMCheckersBoard[xIndex][yIndex] == WHITESOLDIER) || (CMCheckersBoard[xIndex][yIndex] == WHITEKING)))
				{
					posmove = IsMove1Square(CMCheckersBoard, numRowsInBoard, player, xIndex, yIndex);
					if (posmove)
					{
						checkersthatcanmove++;
						xLocArray[xloccounter] = xIndex;
						xloccounter++;
						yLocArray[yloccounter] = yIndex;
						yloccounter++;
					}
				}
			}
		}
	}
	//for red ones
	else if (player == 2)// I would put an else if, just to be safe about possible errors
	{
		for (int row = 0; row < numRowsInBoard; row++)
		{
			for (int col = 0; col < numRowsInBoard; col++)
			{
				if ((CMCheckersBoard[row][col] != 0) && ((CMCheckersBoard[row][col] == REDKING) ||
					CMCheckersBoard[row][col] == REDMULE) ||/*(CMCheckersBoard[row][col]==REDPLAYER)||*/
					(CMCheckersBoard[row][col] == REDSOLDIER))//and check for if its red
				{
					posmove = IsMove1Square(CMCheckersBoard, numRowsInBoard, player, row, col);
					if (posmove)
					{
						checkersthatcanmove++;
						xLocArray[xloccounter] = row;
						xloccounter++;
						yLocArray[yloccounter] = col;
						yloccounter++;
					}
				}
			}
		}
	}
	return checkersthatcanmove;
}




bool IsMove1Square(int CMCheckersBoard[MAX_ARRAY_SIZE][MAX_ARRAY_SIZE], int numRowsInBoard, int player, int xLoc, int yLoc)
{
	bool possible_move = false;
	const int empty_space = 0;

	if (player == 1) //Considers the white player pieces
	{
		if (((CMCheckersBoard[xLoc][yLoc]) == WHITEKING) || ((CMCheckersBoard[xLoc][yLoc]) == WHITEMULE) || ((CMCheckersBoard[xLoc][yLoc]) == WHITESOLDIER))
		{
			if ((CMCheckersBoard[xLoc + 1][yLoc + 1]) == empty_space)
			{
				possible_move = true;
			}

			if ((CMCheckersBoard[xLoc + 1][yLoc - 1]) == empty_space)
			{
				possible_move = true;
			}

			if (yLoc == (numRowsInBoard - 1))
			{
				if ((CMCheckersBoard[xLoc + 1][0]) == empty_space)
				{
					possible_move = true;
				}
			}

			if (yLoc == 0)
			{
				if ((CMCheckersBoard[xLoc + 1][numRowsInBoard - 1]) == empty_space)
				{
					possible_move = true;
				}
			}
		}

		if ((CMCheckersBoard[xLoc][yLoc]) == WHITEKING)
		{
			if ((CMCheckersBoard[xLoc - 1][yLoc - 1]) == empty_space)
			{
				possible_move = true;
			}

			if ((CMCheckersBoard[xLoc - 1][yLoc + 1]) == empty_space)
			{
				possible_move = true;
			}

			if (yLoc == (numRowsInBoard - 1))
			{
				if ((CMCheckersBoard[xLoc - 1][0]) == empty_space)
				{
					possible_move = true;
				}
			}

			if (yLoc == 0)
			{
				if ((CMCheckersBoard[xLoc - 1][numRowsInBoard - 1]) == empty_space)
				{
					possible_move = true;
				}
			}
		}
	}


	else if (player == 2) //Considering the red pieces
	{
		if (((CMCheckersBoard[xLoc][yLoc]) == REDKING) || ((CMCheckersBoard[xLoc][yLoc]) == REDMULE) || ((CMCheckersBoard[xLoc][yLoc]) == REDSOLDIER))
		{
			if ((CMCheckersBoard[xLoc - 1][yLoc - 1]) == empty_space)
			{
				possible_move = true;
			}

			if ((CMCheckersBoard[xLoc - 1][yLoc + 1]) == empty_space)
			{
				possible_move = true;
			}

			if (yLoc == (numRowsInBoard - 1))
			{
				if ((CMCheckersBoard[xLoc - 1][0]) == empty_space)
				{
					possible_move = true;
				}
			}

			if (yLoc == 0)
			{
				if ((CMCheckersBoard[xLoc - 1][numRowsInBoard - 1]) == empty_space)
				{
					possible_move = true;
				}
			}
		}

		if ((CMCheckersBoard[xLoc][yLoc]) == REDKING)
		{
			if ((CMCheckersBoard[xLoc + 1][yLoc - 1]) == empty_space)
			{
				possible_move = true;
			}

			if ((CMCheckersBoard[xLoc + 1][yLoc + 1]) == empty_space)
			{
				possible_move = true;
			}

			if (yLoc == (numRowsInBoard - 1))
			{
				if ((CMCheckersBoard[xLoc + 1][0]) == empty_space)
				{
					possible_move = true;
				}
			}

			if (yLoc == 0)
			{
				if ((CMCheckersBoard[xLoc + 1][numRowsInBoard - 1]) == empty_space)
				{
					possible_move = true;
				}
			}
		}
	}

	return possible_move;
}


bool IsJump(int CMCheckersBoard[MAX_ARRAY_SIZE][MAX_ARRAY_SIZE], int numRowsInBoard, int player, int xLoc, int yLoc)
{
	int mule;
	int soldier;
	int king;
	int enemyMule;
	int enemySoldier;
	int enemyKing;

	if (player == WHITEPLAYER)
	{
		mule = WHITEMULE;
		soldier = WHITESOLDIER;
		king = WHITEKING;
		enemyMule = REDMULE;
		enemySoldier = REDSOLDIER;
		enemyKing = REDKING;


		if (CMCheckersBoard[yLoc][xLoc] == mule || CMCheckersBoard[xLoc][yLoc] == soldier || CMCheckersBoard[xLoc][yLoc] == king)
		{
			if (xLoc == (numRowsInBoard - 1) && (CMCheckersBoard[yLoc + 1][0] == enemyMule || CMCheckersBoard[yLoc + 1][0] == enemySoldier || CMCheckersBoard[yLoc + 1][0] == enemyKing)) //if it's the last in row index, there are different cases bc of cylinder
			{
				//last in row moving RIGHT (in index)
				//moving left in WHITE perspective
				//SPECIAL
				if (CMCheckersBoard[yLoc + 2][1] == 0)
				{
					return true;
				}
			}
			//second last in row moving RIGHT
			//moving left in WHITE perspective
			//SPECIAL
			else if (xLoc == (numRowsInBoard - 2) && (CMCheckersBoard[yLoc + 1][xLoc + 1] == enemyMule || CMCheckersBoard[yLoc + 1][xLoc + 1] == enemySoldier || CMCheckersBoard[yLoc + 1][xLoc + 1] == enemyKing))
			{
				if (CMCheckersBoard[yLoc + 2][0] == 0)
				{
					return true;
				}
			}
			//first in row moving LEFT(in index)
			//moving right in WHITE perspective
			//SPECIAL
			else if (xLoc == 0 && (CMCheckersBoard[yLoc + 1][numRowsInBoard - 1] == enemyMule || CMCheckersBoard[yLoc + 1][numRowsInBoard - 1] == enemySoldier || CMCheckersBoard[yLoc + 1][numRowsInBoard - 1] == enemyKing))
			{
				if (CMCheckersBoard[yLoc + 2][numRowsInBoard - 2] == 0)
				{
					return true;
				}
			}
			//second in row moving LEFT(in index)
			//moving right in WHITE perspective
			//SPECIAL
			else if (xLoc == 1 && (CMCheckersBoard[yLoc + 1][xLoc - 1] == enemyMule || CMCheckersBoard[yLoc + 1][xLoc - 1] == enemySoldier || CMCheckersBoard[yLoc + 1][xLoc - 1] == enemyKing))
			{
				if (CMCheckersBoard[yLoc + 2][numRowsInBoard - 1] == 0)
				{
					return true;
				}
			}
			//GENERAL moving right(in index)
			//moving left in WHITE perspective
			else if (CMCheckersBoard[yLoc + 1][xLoc + 1] == enemyMule || CMCheckersBoard[yLoc + 1][xLoc + 1] == enemySoldier || CMCheckersBoard[yLoc + 1][xLoc + 1] == enemyKing)
			{

				if (CMCheckersBoard[yLoc + 2][xLoc + 2] == 0)
				{
					return true;
				}
			}
			//GENERAL moving left(in index)
			//moving right in WHITE perspective
			else if (CMCheckersBoard[yLoc + 1][xLoc - 1] == enemyMule || CMCheckersBoard[yLoc + 1][xLoc - 1] == enemySoldier || CMCheckersBoard[yLoc + 1][xLoc - 1] == enemyKing)
			{
				if (CMCheckersBoard[yLoc + 2][xLoc - 2] == 0)
				{
					return true;
				}
			}
			else if (CMCheckersBoard[xLoc][yLoc] == king)
			{
				//KING CASES
				//*********************************************************
				//
				//
				if (xLoc == (numRowsInBoard - 1) && (CMCheckersBoard[yLoc - 1][0] == enemyMule || CMCheckersBoard[yLoc - 1][0] == enemySoldier || CMCheckersBoard[yLoc - 1][0] == enemyKing)) //if it's the last in row, there are different cases moving to right bc of cylinder
				{
					//last in row moving RIGHT(in index)
					//moving left in WHITE perspective
					//SPECIAL
					if (CMCheckersBoard[yLoc - 2][1] == 0)
					{
						return true;
					}
				}
				//second last in row moving RIGHT(in index)
				//moving left in WHITE perspective
				//SPECIAL
				else if (xLoc == (numRowsInBoard - 2) && (CMCheckersBoard[yLoc - 1][xLoc + 1] == enemyMule || CMCheckersBoard[yLoc - 1][xLoc + 1] == enemySoldier || CMCheckersBoard[yLoc - 1][xLoc + 1] == enemyKing))
				{
					if (CMCheckersBoard[yLoc - 2][0] == 0)
					{
						return true;
					}
				}
				//first in row moving LEFT(in index)
				//moving right in WHITE perspective
				//SPECIAL
				else if (xLoc == 0 && (CMCheckersBoard[yLoc - 1][numRowsInBoard - 1] == enemyMule || CMCheckersBoard[yLoc - 1][numRowsInBoard - 1] == enemySoldier || CMCheckersBoard[yLoc - 1][numRowsInBoard - 1] == enemyKing))
				{
					if (CMCheckersBoard[yLoc - 2][numRowsInBoard - 2] == 0)
					{
						return true;
					}
				}
				//second in row moving LEFT(in index)
				//moving right in WHITE perspective
				//SPECIAL
				else if (xLoc == 1 && (CMCheckersBoard[yLoc - 1][xLoc - 1] == enemyMule || CMCheckersBoard[yLoc - 1][xLoc - 1] == enemySoldier || CMCheckersBoard[yLoc - 1][xLoc - 1] == enemyKing))
				{
					if (CMCheckersBoard[yLoc - 2][numRowsInBoard - 1] == 0)
					{
						return true;
					}
				}
				//GENERAL moving right(in index)
				//moving left in WHITE perspective
				else if (CMCheckersBoard[yLoc - 1][xLoc + 1] == enemyMule || CMCheckersBoard[yLoc - 1][xLoc + 1] == enemySoldier || CMCheckersBoard[yLoc - 1][xLoc + 1] == enemyKing)
				{

					if (CMCheckersBoard[yLoc - 2][xLoc + 2] == 0)
					{
						return true;
					}
				}
				//GENERAL moving left(in index)
				//moving right in WHITE perspective
				else if (CMCheckersBoard[yLoc - 1][xLoc - 1] == enemyMule || CMCheckersBoard[yLoc - 1][xLoc - 1] == enemySoldier || CMCheckersBoard[yLoc - 1][xLoc - 1] == enemyKing)
				{
					if (CMCheckersBoard[yLoc - 2][xLoc - 2] == 0)
					{
						return true;
					}
				}
			}
			else
			{
				return false;
			}
		}
	}
	else if (player == REDPLAYER)
	{
		mule = REDMULE;
		soldier = REDSOLDIER;
		king = REDKING;
		enemyMule = WHITEMULE;
		enemySoldier = WHITESOLDIER;
		enemyKing = WHITEKING;

		if (CMCheckersBoard[yLoc][xLoc] == mule || CMCheckersBoard[xLoc][yLoc] == soldier || CMCheckersBoard[xLoc][yLoc] == king)
		{
			//last in row moving RIGHT
			//SPECIAL
			if (xLoc == (numRowsInBoard - 1) && (CMCheckersBoard[yLoc - 1][0] == enemyMule || CMCheckersBoard[yLoc - 1][0] == enemySoldier || CMCheckersBoard[yLoc - 1][0] == enemyKing)) //if it's the last in row, there are different cases moving to right bc of cylinder
			{
				if (CMCheckersBoard[yLoc - 2][1] == 0)
				{
					return true;
				}
			}
			//second last in row moving RIGHT
			//SPECIAL
			else if (xLoc == (numRowsInBoard - 2) && (CMCheckersBoard[yLoc - 1][xLoc + 1] == enemyMule || CMCheckersBoard[yLoc - 1][xLoc + 1] == enemySoldier || CMCheckersBoard[yLoc - 1][xLoc + 1] == enemyKing))
			{
				if (CMCheckersBoard[yLoc - 2][0] == 0)
				{
					return true;
				}
			}
			//first in row moving LEFT
			//SPECIAL
			else if (xLoc == 0 && (CMCheckersBoard[yLoc - 1][numRowsInBoard - 1] == enemyMule || CMCheckersBoard[yLoc - 1][numRowsInBoard - 1] == enemySoldier || CMCheckersBoard[yLoc - 1][numRowsInBoard - 1] == enemyKing))
			{
				if (CMCheckersBoard[yLoc - 2][numRowsInBoard - 2] == 0)
				{
					return true;
				}
			}
			//second in row moving LEFT
			//SPECIAL
			else if (xLoc == 1 && (CMCheckersBoard[yLoc - 1][xLoc - 1] == enemyMule || CMCheckersBoard[yLoc - 1][xLoc - 1] == enemySoldier || CMCheckersBoard[yLoc - 1][xLoc - 1] == enemyKing))
			{
				if (CMCheckersBoard[yLoc - 2][numRowsInBoard - 1] == 0)
				{
					return true;
				}
			}
			//GENERAL moving right
			else if (CMCheckersBoard[yLoc - 1][xLoc + 1] == enemyMule || CMCheckersBoard[yLoc - 1][xLoc + 1] == enemySoldier || CMCheckersBoard[yLoc - 1][xLoc + 1] == enemyKing)
			{

				if (CMCheckersBoard[yLoc - 2][xLoc + 2] == 0)
				{
					return true;
				}
			}
			//GENERAL moving left
			else if (CMCheckersBoard[yLoc - 1][xLoc - 1] == enemyMule || CMCheckersBoard[yLoc - 1][xLoc - 1] == enemySoldier || CMCheckersBoard[yLoc - 1][xLoc - 1] == enemyKing)
			{
				if (CMCheckersBoard[yLoc - 2][xLoc - 2] == 0)
				{
					return true;
				}
			}
			//KING CASE
			//*****************************
			//
			//
			else if (CMCheckersBoard[xLoc][yLoc] == king)
			{
				//last in row moving RIGHT
				//SPECIAL
				if (xLoc == (numRowsInBoard - 1) && (CMCheckersBoard[yLoc + 1][0] == enemyMule || CMCheckersBoard[yLoc + 1][0] == enemySoldier || CMCheckersBoard[yLoc + 1][0] == enemyKing)) //if it's the last in row, there are different cases moving to right bc of cylinder
				{
					if (CMCheckersBoard[yLoc + 2][1] == 0)
					{
						return true;
					}
				}
				//second last in row moving RIGHT
				//SPECIAL
				else if (xLoc == (numRowsInBoard - 2) && (CMCheckersBoard[yLoc + 1][xLoc + 1] == enemyMule || CMCheckersBoard[yLoc + 1][xLoc + 1] == enemySoldier || CMCheckersBoard[yLoc + 1][xLoc + 1] == enemyKing))
				{
					if (CMCheckersBoard[yLoc + 2][0] == 0)
					{
						return true;
					}
				}
				//first in row moving LEFT
				//SPECIAL
				else if (xLoc == 0 && (CMCheckersBoard[yLoc + 1][numRowsInBoard - 1] == enemyMule || CMCheckersBoard[yLoc + 1][numRowsInBoard - 1] == enemySoldier || CMCheckersBoard[yLoc + 1][numRowsInBoard - 1] == enemyKing))
				{
					if (CMCheckersBoard[yLoc + 2][numRowsInBoard - 2] == 0)
					{
						return true;
					}
				}
				//second in row moving LEFT
				//SPECIAL
				else if (xLoc == 1 && (CMCheckersBoard[yLoc + 1][xLoc - 1] == enemyMule || CMCheckersBoard[yLoc + 1][xLoc - 1] == enemySoldier || CMCheckersBoard[yLoc + 1][xLoc - 1] == enemyKing))
				{
					if (CMCheckersBoard[yLoc + 2][numRowsInBoard - 1] == 0)
					{
						return true;
					}
				}
				//GENERAL moving right
				else if (CMCheckersBoard[yLoc + 1][xLoc + 1] == enemyMule || CMCheckersBoard[yLoc + 1][xLoc + 1] == enemySoldier || CMCheckersBoard[yLoc + 1][xLoc + 1] == enemyKing)
				{

					if (CMCheckersBoard[yLoc + 2][xLoc + 2] == 0)
					{
						return true;
					}
				}
				//GENERAL moving left
				else if (CMCheckersBoard[yLoc + 1][xLoc - 1] == enemyMule || CMCheckersBoard[yLoc + 1][xLoc - 1] == enemySoldier || CMCheckersBoard[yLoc + 1][xLoc - 1] == enemyKing)
				{
					if (CMCheckersBoard[yLoc + 2][xLoc - 2] == 0)
					{
						return true;
					}
				}
			}
		}
		else
		{
			return false;
		}
	}

	return false;

}



bool MakeMove(int CMCheckersBoard[MAX_ARRAY_SIZE][MAX_ARRAY_SIZE], int numRowsInBoard, int player, int fromSquareNum, int toSquareNum, bool &jumped)
{
	int xvalTO = 0;
	int yvalTO = 0;
	int xvalFROM = 0;
	int yvalFROM = 0;
	int xdist = 0;
	int ydist = 0;
	//unsigned int absltxdist = 0;
	int absltxdist = 0;
	int absltydist = 0;
	//unsigned int absltydist = 0;
	string bob = "hello its me";
	xvalTO = toSquareNum % numRowsInBoard;
	yvalTO = toSquareNum / numRowsInBoard;
	xvalFROM = fromSquareNum % numRowsInBoard;
	yvalFROM = fromSquareNum / numRowsInBoard;
	//cout << xvalFROM << endl << yvalFROM << endl;

	bool flag = true;

	//ALL X ARE COLUMNS AND ALL Y ARE ROWS

	xdist = (xvalTO - xvalFROM);
	if (xdist < 0)
	{
		absltxdist = (xdist*-1);
	}
	else
	{
		absltxdist = xdist;
	}

	ydist = (yvalTO - yvalFROM);
	if (ydist < 0)
	{
		absltydist = (ydist*-1);
	}
	else
	{
		absltydist = ydist;
	}
	cout << absltxdist << endl << absltydist << endl;
	//if (!IsJump(CMCheckersBoard, numRowsInBoard, player, xvalFROM, yvalFROM))
	//{
	// //it cant jump
	//}
	//if (!IsMove1Square (CMCheckersBoard, numRowsInBoard, player, xvalFROM, yvalFROM))
	//{
	// //it cant move
	//}
	//cross-board move
	//last or first



	//JUST MOVING
	if (numRowsInBoard - 1 == absltxdist && absltydist == 1) //ACROSS WHOLE ROW AND JUST ONE ROW DOWN
	{
		if (CMCheckersBoard[xvalFROM][yvalFROM] == WHITESOLDIER)
		{
			if (CMCheckersBoard[xvalTO][yvalTO] == 0)
			{
				CMCheckersBoard[xvalFROM][yvalFROM] = 0;
				CMCheckersBoard[xvalTO][yvalTO] = WHITESOLDIER;
				flag = true;
			}

		}
		else if (CMCheckersBoard[xvalFROM][yvalFROM] == WHITEMULE)
		{
			if (CMCheckersBoard[xvalTO][yvalTO] == 0)
			{
				CMCheckersBoard[xvalFROM][yvalFROM] = 0;
				CMCheckersBoard[xvalTO][yvalTO] = WHITEMULE;
				flag = true;
			}

		}
		else if (CMCheckersBoard[xvalFROM][yvalFROM] == WHITEKING)
		{
			if (CMCheckersBoard[xvalTO][yvalTO] == 0)
			{
				CMCheckersBoard[xvalFROM][yvalFROM] = 0;
				CMCheckersBoard[xvalTO][yvalTO] = WHITEKING;
				flag = true;
			}

		}
		else if (CMCheckersBoard[xvalFROM][yvalFROM] == REDSOLDIER)
		{
			if (CMCheckersBoard[xvalTO][yvalTO] == 0)
			{
				CMCheckersBoard[xvalFROM][yvalFROM] = 0;
				CMCheckersBoard[xvalTO][yvalTO] = REDSOLDIER;
				flag = true;
			}
		}
		else if (CMCheckersBoard[xvalFROM][yvalFROM] == REDMULE)
		{
			if (CMCheckersBoard[xvalTO][yvalTO] == 0)
			{
				CMCheckersBoard[xvalFROM][yvalFROM] = 0;
				CMCheckersBoard[xvalTO][yvalTO] = REDMULE;
				flag = true;
			}
		}
		else if (CMCheckersBoard[xvalFROM][yvalFROM] == REDKING)
		{
			if (CMCheckersBoard[xvalTO][yvalTO] == 0)
			{
				CMCheckersBoard[xvalFROM][yvalFROM] = 0;
				CMCheckersBoard[xvalTO][yvalTO] = REDKING;
				flag = true;
			}
		}


	}

	//JUST JUMPING
	else if (numRowsInBoard - 2 == absltxdist && absltydist == 2)
	{
		//cross board jump
		//check if middle is empty
		if ((xvalTO == 0) && (ydist > 0))
		{
			//yvalFROM++;
			if (CMCheckersBoard[numRowsInBoard - 1][yvalFROM + 1] == 0)
			{
				//middle is empty
				cout << "Error: Illegal move" << endl << "A" << endl;
				return false;
			}
			//if it didnt make it into that  if, then it was just incremented and decremented so its like nothing even happened so its okay
			//yvalFROM--;

			//actually move the stuff
			else
			{

				CMCheckersBoard[xvalTO][yvalTO] = CMCheckersBoard[xvalFROM][yvalFROM];
				CMCheckersBoard[xvalFROM][yvalFROM] = 0;
				//yvalFROM++;
				CMCheckersBoard[numRowsInBoard - 1][yvalFROM + 1] = 0;
				//yvalFROM--;
				jumped = true;
				flag = true;
			}

		}

		//cross board jump
		//gotta check if middle is empty
		else if ((xvalTO == 0) && (ydist < 0))
		{
			//yvalFROM--;
			if (CMCheckersBoard[numRowsInBoard - 1][yvalFROM + 1] == 0)
			{
				//middle is empty
				cout << "Error: Illegal move" << endl << "B" << endl;
				return false;
			}
			//yvalFROM++;
			else
			{
				//actually move the stuff
				CMCheckersBoard[xvalTO][yvalTO] = CMCheckersBoard[xvalFROM][yvalFROM];
				CMCheckersBoard[xvalFROM][yvalFROM] = 0;
				//yvalFROM--;
				CMCheckersBoard[numRowsInBoard - 1][yvalFROM - 1] = 0;
				//yvalFROM++;
				jumped = true;
				flag = true;
			}


		}

		//cross board jump
		//gotta check if middle is empty
		else if ((xvalTO == 1) && (ydist > 0))
		{
			//yvalFROM++;
			if (CMCheckersBoard[0][yvalFROM + 1] == 0)
			{
				//middle is empty
				cout << "Error: Illegal move" << endl << "C" << endl;
				return false;
			}
			//yvalFROM--;
			else
			{
				//actually move the stuff
				CMCheckersBoard[xvalTO][yvalTO] = CMCheckersBoard[xvalFROM][yvalFROM];
				CMCheckersBoard[xvalFROM][yvalFROM] = 0;
				//yvalFROM++;
				CMCheckersBoard[0][yvalFROM + 1] = 0;
				//yvalFROM--;
				jumped = true;
				flag = true;
			}

		}
		//cross board jump
		//gotta check if middle is empty
		else if ((xvalTO == 1) && (ydist < 0))
		{
			//yvalFROM--;
			if (CMCheckersBoard[0][yvalFROM - 1] == 0)
			{
				//middle is empty
				cout << "Error: Illegal move" << endl << "D" << endl;
				return false;
			}
			//yvalFROM++;

			else
			{
				//actually move the stuff
				CMCheckersBoard[xvalTO][yvalTO] = CMCheckersBoard[xvalFROM][yvalFROM];
				CMCheckersBoard[xvalFROM][yvalFROM] = 0;
				//yvalFROM--;
				CMCheckersBoard[0][yvalFROM - 1] = 0;
				//yvalFROM++;
				jumped = true;
				flag = true;
			}

		}

		//cross board jump
		//gotta check if middle is empty
		else if ((xvalTO == (numRowsInBoard - 1)) && (ydist > 0))
		{
			//yvalFROM++;
			if (CMCheckersBoard[0][yvalFROM + 1] == 0)
			{
				//middle is empty
				cout << "Error: Illegal move" << endl << "E" << endl;
				return false;
			}
			//yvalFROM--;
			else
			{
				//actually move the stuff
				CMCheckersBoard[xvalTO][yvalTO] = CMCheckersBoard[xvalFROM][yvalFROM];
				CMCheckersBoard[xvalFROM][yvalFROM] = 0;
				//yvalFROM++;
				CMCheckersBoard[0][yvalFROM + 1] = 0;
				//yvalFROM--;
				jumped = true;
				flag = true;
			}

		}
		//cross board jump
		//gotta check if middle is empty
		else if ((xvalTO == (numRowsInBoard - 1)) && (ydist < 0))
		{
			//yvalFROM--;
			if (CMCheckersBoard[0][yvalFROM - 1] == 0)
			{
				//middle is empty
				cout << "Error: Illegal move" << endl << "F" << endl;
				return false;
			}
			//yvalFROM++;
			else
			{
				//actually move the stuff
				CMCheckersBoard[xvalTO][yvalTO] = CMCheckersBoard[xvalFROM][yvalFROM];
				CMCheckersBoard[xvalFROM][yvalFROM] = 0;
				//yvalFROM--;
				CMCheckersBoard[0][yvalFROM - 1] = 0;
				//yvalFROM++;
				jumped = true;
				flag = true;
			}

		}
		//cross board jump
		//gotta check if middle is empty
		else if ((xvalTO == (numRowsInBoard - 2) && (ydist > 0)))
		{
			//yvalFROM++;
			if (CMCheckersBoard[numRowsInBoard - 1][yvalFROM + 1] == 0)
			{
				//middle is empty
				cout << "Error: Illegal move" << endl << "G" << endl;
				return false;
			}
			//yvalFROM--;
			else
			{
				//actually move the stuff
				CMCheckersBoard[xvalTO][yvalTO] = CMCheckersBoard[xvalFROM][yvalFROM];
				CMCheckersBoard[xvalFROM][yvalFROM] = 0;
				//yvalFROM++;
				CMCheckersBoard[0][yvalFROM + 1] = 0;
				//yvalFROM--;
				jumped = true;
				flag = true;
			}

		}
		//cross board jump
		//gotta check if middle is empty
		else if ((xvalTO == (numRowsInBoard - 2) && (ydist < 0)))
		{
			//yvalFROM--;
			if (CMCheckersBoard[numRowsInBoard - 1][yvalFROM - 1] == 0)
			{
				//middle is empty
				cout << "Error: Illegal move" << endl << "H" << endl;
				return false;
			}
			//yvalFROM++;
			else
			{
				//actually move the stuff
				CMCheckersBoard[xvalTO][yvalTO] = CMCheckersBoard[xvalFROM][yvalFROM];
				CMCheckersBoard[xvalFROM][yvalFROM] = 0;
				//yvalFROM--;
				CMCheckersBoard[numRowsInBoard - 1][yvalFROM - 1] = 0;
				//yvalFROM++;
				jumped = true;
				flag = true;
			}

		}
	}
	else if (absltxdist > 2 || absltydist > 2)
		//SHOULD THIS BE else if (absltxdist>2 && absltydist>2)
		//OR POSSIBLY else if (absltdist>2)
		//if it moved too many
	{
		cout << "Error: Illegal move" << endl << "I" << endl;
		return false;
	}









	///COMBINE THE IF STATEMENTS INTO ELSE IF!!!


	else if (absltxdist == 2 && absltydist == 2)
	{
		//jump
		//to see if middle is empty
		if (xdist < 0)
		{
			//xvalFROM++;
			if (ydist > 0)//changed sign
			{
				//yvalFROM++;
				if (CMCheckersBoard[xvalFROM - 1][yvalFROM + 1] == 0)
				{
					cout << "Error: Illegal move" << endl << "J" << endl;
					return false;
				}
				//yvalFROM--;
			}
			//xvalFROM--;
		}
		if (xdist < 0)
		{
			//xvalFROM++;
			if (ydist < 0)//changed sign
			{
				//yvalFROM--;
				if (CMCheckersBoard[xvalFROM - 1][yvalFROM - 1] == 0)
				{
					cout << "Error: Illegal move" << endl << "K" << endl;
					return false;
				}
				//yvalFROM++;
			}
			//xvalFROM--;
		}
		if (xdist > 0)
		{
			//xvalFROM--;
			if (ydist < 0)//changed sign
			{
				//yvalFROM--;
				if (CMCheckersBoard[xvalFROM + 1][yvalFROM - 1] == 0)
				{
					cout << "Error: Illegal move" << endl << "L" << endl;
					return false;
				}
				//yvalFROM++;
			}
			//xvalFROM++;
		}
		if (xdist > 0)
		{
			//xvalFROM--;
			if (ydist > 0)//changed sign
			{
				//yvalFROM++;
				if (CMCheckersBoard[xvalFROM - +1][yvalFROM + 1] == 0)
				{
					cout << "Error: Illegal move" << endl << "M" << endl;
					return false;
				}
				//yvalFROM--;
			}
			//xvalFROM++;
		}
	}






	//if it is moving in the wrong direction
	//NOTE: I CHANGED THE DIRECTION OF THE YDIST
	else if (player == 1 && ydist < 0 && ((CMCheckersBoard[xvalFROM][yvalFROM] == WHITEMULE) || (CMCheckersBoard[xvalFROM][yvalFROM] == WHITESOLDIER)))
	{
		//changed sign of y
		cout << "Error: Illegal move" << endl << "N" << endl;
		return false;
	}


	//if it is moving in the wrong direction
	//NOTE: I CHANGED THE DIRECTION OF THE YDIST
	else if (player == 2 && ydist > 0 && (CMCheckersBoard[xvalFROM][yvalFROM] == REDMULE) || (CMCheckersBoard[xvalFROM][yvalFROM] == REDSOLDIER))
	{
		//changed sign of y
		cout << "Error: Illegal move" << endl << "O" << endl;
		return false;
	}


	else if ((absltxdist == 1) && (absltydist == 1))
	{
		//moved diagonally 1
		if (CMCheckersBoard[xvalFROM][yvalFROM] == WHITESOLDIER)
		{
			if (CMCheckersBoard[xvalTO][yvalTO] == 0)
			{
				CMCheckersBoard[xvalFROM][yvalFROM] = 0;
				CMCheckersBoard[xvalTO][yvalTO] = WHITESOLDIER;
				flag = true;
			}

		}
		else if (CMCheckersBoard[xvalFROM][yvalFROM] == WHITEMULE)
		{
			if (CMCheckersBoard[xvalTO][yvalTO] == 0)
			{
				CMCheckersBoard[xvalFROM][yvalFROM] = 0;
				CMCheckersBoard[xvalTO][yvalTO] = WHITEMULE;
				flag = true;
			}

		}
		else if (CMCheckersBoard[xvalFROM][yvalFROM] == WHITEKING)
		{
			if (CMCheckersBoard[xvalTO][yvalTO] == 0)
			{
				CMCheckersBoard[xvalFROM][yvalFROM] = 0;
				CMCheckersBoard[xvalTO][yvalTO] = WHITEKING;
				flag = true;
			}

		}
		else if (CMCheckersBoard[xvalFROM][yvalFROM] == REDSOLDIER)
		{
			if (CMCheckersBoard[xvalTO][yvalTO] == 0)
			{
				CMCheckersBoard[xvalFROM][yvalFROM] = 0;
				CMCheckersBoard[xvalTO][yvalTO] = REDSOLDIER;
				flag = true;
			}
		}
		else if (CMCheckersBoard[xvalFROM][yvalFROM] == REDMULE)
		{
			if (CMCheckersBoard[xvalTO][yvalTO] == 0)
			{
				CMCheckersBoard[xvalFROM][yvalFROM] = 0;
				CMCheckersBoard[xvalTO][yvalTO] = REDMULE;
				flag = true;
			}
		}
		else if (CMCheckersBoard[xvalFROM][yvalFROM] == REDKING)
		{
			if (CMCheckersBoard[xvalTO][yvalTO] == 0)
			{
				CMCheckersBoard[xvalFROM][yvalFROM] = 0;
				CMCheckersBoard[xvalTO][yvalTO] = REDKING;
				flag = true;
			}
		}

		/*
		if (CMCheckersBoard[xvalFROM][yvalFROM] == WHITESOLDIER)
		{
			CMCheckersBoard[xvalFROM][yvalFROM] = 0;
			CMCheckersBoard[xvalTO][yvalTO] = WHITESOLDIER;
		}
		else if (CMCheckersBoard[xvalFROM][yvalFROM] == WHITEMULE)
		{
			CMCheckersBoard[xvalFROM][yvalFROM] = 0;
			CMCheckersBoard[xvalTO][yvalTO] = WHITEMULE;
		}
		else if (CMCheckersBoard[xvalFROM][yvalFROM] == REDSOLDIER)
		{
			CMCheckersBoard[xvalFROM][yvalFROM] = 0;
			CMCheckersBoard[xvalTO][yvalTO] = REDSOLDIER;
		}
		else if (CMCheckersBoard[xvalFROM][yvalFROM] == REDMULE)
		{
			CMCheckersBoard[xvalFROM][yvalFROM] = 0;
			CMCheckersBoard[xvalTO][yvalTO] = REDMULE;
		}*/
	}
	else if (absltxdist == 2 && absltydist == 2)
	{
		//moved diagonally 2 (jump)
		CMCheckersBoard[xvalTO][yvalTO] = CMCheckersBoard[xvalFROM][yvalFROM];
		CMCheckersBoard[xvalFROM][yvalFROM] = 0;


		if (xdist < 0)
		{
			//xvalFROM++;
			if (ydist > 0)
				//changed sign of y
			{
				//yvalFROM++;
				CMCheckersBoard[xvalFROM - 1][yvalFROM + 1] = 0;
				//yvalFROM--;
			}
			//xvalFROM--;
			jumped = true;
		}

		else if (xdist < 0)
		{
			//xvalFROM++;
			if (ydist < 0)
			{
				//yvalFROM--;
				CMCheckersBoard[xvalFROM - 1][yvalFROM - 1] = 0;
				//yvalFROM++;
			}
			//xvalFROM--;
			jumped = true;
		}

		else if (xdist > 0)
		{
			//xvalFROM--;
			if (ydist < 0)
			{
				//yvalFROM--;
				CMCheckersBoard[xvalFROM + 1][yvalFROM - 1] = 0;
				//yvalFROM++;
			}
			//xvalFROM++;
			jumped = true;
		}

		else if (xdist > 0)
		{
			//xvalFROM--;
			if (ydist > 0)
			{
				//yvalFROM++;
				CMCheckersBoard[xvalFROM + 1][yvalFROM + 1] = 0;
				//yvalFROM--;
			}
			//xvalFROM++;
			jumped = true;
		}
		flag = true;
	}

	//AFTER MOVING IT
	if ((CMCheckersBoard[xvalTO][yvalTO] == REDMULE) && (yvalTO == 0))
	{
		CMCheckersBoard[xvalTO][yvalTO] = REDKING;
		cout << "Red has created a Mule King,  White wins the game\n";
		cout << "Enter any character to terminate the game then press the enter key\nThe program will terminate after the player presses the enter key.";
		cin >> bob;
		exit(0);
	}
	if (((CMCheckersBoard[xvalTO][yvalTO] == REDSOLDIER) && (yvalTO == 0)))
	{
		CMCheckersBoard[xvalTO][yvalTO] = REDKING;
		return true;
	}
	if ((CMCheckersBoard[xvalTO][yvalTO] == WHITEMULE) && (yvalTO == (numRowsInBoard - 1)))
	{
		CMCheckersBoard[xvalTO][yvalTO] = WHITEKING;
		cout << "White has created a Mule King,  Red wins the game\n";
		cout << "Enter any character to terminate the game then press the enter key\nThe program will terminate after the player presses the enter key.";
		cin >> bob;
		exit(0);
	}
	if (((CMCheckersBoard[xvalTO][yvalTO] == WHITESOLDIER) && (yvalTO == 0)))
	{
		CMCheckersBoard[xvalTO][yvalTO] = WHITEKING;
		return true;
	}

	if (jumped == true)
	{
		cout << "NICE!" << endl;
		return flag;
	}
	return flag;
}









bool CheckWin(int CMCheckersBoard[MAX_ARRAY_SIZE][MAX_ARRAY_SIZE], int numRowsInBoard)
{
	bool win = false;
	int red_mules = 0;
	int white_mules = 0;
	int empty_spaces = 0;
	int red_soldiers_or_king = 0;
	int white_soldier_or_king = 0;

	for (int i = 0; i < numRowsInBoard; i++)
	{
		for (int j = 0; j < numRowsInBoard; j++)
		{
			if (((CMCheckersBoard[i][j]) == WHITESOLDIER) || ((CMCheckersBoard[i][j]) == WHITEKING))
			{
				white_soldier_or_king++;
			}
			else if (((CMCheckersBoard[i][j]) == REDSOLDIER) || ((CMCheckersBoard[i][j]) == REDKING))
			{
				red_soldiers_or_king++;
			}
			else if ((CMCheckersBoard[i][j]) == WHITEMULE)
			{
				white_mules++;
			}
			else if ((CMCheckersBoard[i][j]) == REDMULE)
			{
				red_mules++;
			}
			else
			{
				empty_spaces++;
			}
		}
	}

	if (red_mules == 0)
	{
		cout << "The Red Player has won the game by losing all of the Red Mules" << endl;
		win = true;
	}
	else if (white_mules == 0)
	{
		cout << "The White Player has won the game by losing all of the White Mules" << endl;
		win = true;
	}
	else if (red_soldiers_or_king == 0)
	{
		cout << "The White Player has won by capturing all of the red players soldiers and kings" << endl;
		win = true;
	}
	else if (white_soldier_or_king == 0)
	{
		cout << "The Red Player has won by capturing all of the white players soldiers and kings" << endl;
		win = true;
	}

	return win;
}




//0 1 2 3 4 5 6 7 8 9 10 11 12
// 10 11 12 13 4 5 6 7 8 9 10 11 12






