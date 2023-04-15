#pragma once
#include "Console.h"
#include "Point.h"
#include <iostream>
#include <fstream>
#include <ctime>
#include <vector>
#include <algorithm>
#include <string>

using namespace std;


struct Board
{
	int size;						//Board Size
	int left, top;					//Board Coordinate 
	Point** pBoard;					//Array Board
	int** pokemons;
	string* background;

	Board(int, int, int);			
	~Board();

	int Size();					//Return Size 
	int Left();					//Return Left coordinate
	int Top();					//Return Top coordinate
	int getXAt(int, int);			//Return x coordinate at block
	int getYAt(int, int);			//Return y coordinate at block
	int getCheckAtXY(int, int);
	int getRAt(int, int);			//Return the coordinate of the row
	int getCAt(int, int);			//Return the coordinate of the column
	char getPokemons(int, int);
	int getCheck(int, int);

	void showBoard();
	void renderBoard();
	void buildBoardData();

	void selectedBlock(int, int, int);
	void unselectedBlock(int, int);
	
	void lockBlock(int, int);
	void deleteBlock(int, int);

	void drawLineI(pair<int, int>, pair<int, int>);
	void deleteLineI(pair<int, int>, pair<int, int>);
	void drawLineL(pair<int, int>, pair<int, int>, pair<int, int>);
	void deleteLineL(pair<int, int>, pair<int, int>, pair<int, int>);
	void drawLineZ(pair<int, int>, pair<int, int>, pair<int, int>, pair<int, int>);
	void deleteLineZ(pair<int, int>, pair<int, int>, pair<int, int>, pair<int, int>);
	void drawLineU(pair<int, int>, pair<int, int>, pair<int, int>, pair<int, int>);
	void deleteLineU(pair<int, int>, pair<int, int>, pair<int, int>, pair<int, int>);
};