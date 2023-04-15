#pragma once

#define _NORMAL 0
#define _LOCK 1
#define _DELETE -1

struct Point
{
	int _x = 0;					
	int _y = 0;					
	int _check = 0;			//0: NORMAL, 1: LOCK, -1: DELETE
	char _pokemon = ' ';
	Point();			//initialize
	Point(int, int, int, char);	//initialize

	int getX();			//get the x coordinate
	int getY();			//get the y coordinate
	int getCheck();		//get the pokemons

	void setX(int);		//set the x coordinate
	void setY(int);		//set the y coordinate
	void setCheck(int);	//set the pokemons

	char getPokemons();
	void setPokemons(char);

};