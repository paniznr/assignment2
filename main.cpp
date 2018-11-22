//
//  main.cpp
//  assignment2
//
//  Created by Paniz Najjarrezaparast on 2018-11-19.
//  Copyright © 2018 Paniz Najjarrezaparast. All rights reserved.
//

/*
 void InitializeBoard(int CMCheckersBoard[MAX_ARRAY_SIZE][MAX_ARRAY_SIZE],
 
 int numRowsInBoard);
 
 void DisplayBoard(int CMCheckersBoard[MAX_ARRAY_SIZE][MAX_ARRAY_SIZE],
 
 int numRowsInBoard);
 
 int CountJumps(int CMCheckersBoard[MAX_ARRAY_SIZE][MAX_ARRAY_SIZE],
 
 int numRowsInBoard, int player, int xLocArray[], int yLocArray[]);
 
 bool CheckList(int inArray1[], int inArray2[], int xIndex, int yIndex);
 
 int CountMove1Squares(int CMCheckersBoard[MAX_ARRAY_SIZE][MAX_ARRAY_SIZE],
 
 int numRowsInBoard, int player, int xLocArray[],  int yLocArray[]);
 
 bool IsMove1Square(int CMCheckersBoard[MAX_ARRAY_SIZE][MAX_ARRAY_SIZE],
 
 int numRowsInBoard, int player, int xLoc, int yLoc);
 
 bool IsJump(int CMCheckersBoard[MAX_ARRAY_SIZE][MAX_ARRAY_SIZE],
 
 int numRowsInBoard, int player, int xLoc, int yLoc);
 
 bool MakeMove(int CMCheckersBoard[MAX_ARRAY_SIZE][MAX_ARRAY_SIZE],
 
 int numRowsInBoard, int player, int fromSquareNum,
 
 int toSquareNum, bool &jumped);
 
 bool CheckWin(int CMCheckersBoard[MAX_ARRAY_SIZE][MAX_ARRAY_SIZE], int numRowsInBoard);
 
 */

#include <iostream>
#include <fstream>
#include <string>
using namespace std;

const int MAX_ARRAY_SIZE = 18;

const int MIN_ARRAY_SIZE = 8;

const int MAX_PIECES = 72; //might not need

const int NOPLAYER = 0;

const int WHITEWINS = 1; //might not need

const int REDWINS = 2;//might not need

const int NOONEWINS = 0;

const int WHITESOLDIER = 1;

const int WHITEMULE = 2;

const int WHITEKING = 3;

const int REDSOLDIER = 4;

const int REDMULE = 5;

const int REDKING = 6;

const int WHITEPLAYER = 1;

const int REDPLAYER = 2;




int main()
{
   
    
    char myCMCheckersBoard[MAX_ARRAY_SIZE];
    char xIndicesMove[MAX_PIECES]; //holds x index
    char yIndicesMove[MAX_PIECES]; //holds y index of location on board of a checker
                        //these are the checkers that can be moved
                        //include Soldier/Mule that can move 1 square diagonally fwd
                        //& King that can move 1 sqr diagonally fwd OR bkwd
    char xIndicesJump[MAX_PIECES];
    char yIndicesJump[MAX_PIECES];
                        //these are cheeckers that can jump one of the opponents checkers
    int numRowsInBoard=0;
    int i;
    
    
    
    for(i=0; i<4; i++)
    {
        if (i==3)
        {
            cerr<<"ERROR: Too many errors entering the size of the board.\n";
            return 2;
        }
        else
        {
            cout<<"Enter the number of squares along each edge of the board\n";
            //cin>>numRowsInBoard;
            
            if(!(cin>>numRowsInBoard))
            {

                cerr<<"ERROR: Board size is not an integer.\n";
                cerr<<"8 <= number of squares <= 18\n";
                cin.clear();
                cin.ignore();
                continue;
            }
            else if (numRowsInBoard>18)
            {
                cerr<<"ERROR: Board size too large.\n";
                cerr<<"8 <= number of squares <= 18\n";
                continue;
            }
            else if (numRowsInBoard<8)
            {
                cerr<<"ERROR: Board size too small.\n";
                cerr<<"8 <= number of squares <= 18\n";
                continue;
            }
            else if (numRowsInBoard%2==1)
            {
                cerr<<"ERROR: Board size odd.\n";
                cerr<<"8 <= number of squares <= 18\n";
                continue;
            }
            else {
                break;
            }
            
        }
    }
    return 0;
}







