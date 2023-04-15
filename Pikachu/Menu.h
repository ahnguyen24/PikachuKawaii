#pragma once
#include <iostream>
#include <string>
#include <unordered_map>
#include "Console.h"
#include "Game.h"
#include <random>
#include <fstream>

#define _EASY 10
#define _MEDIUM 8


using namespace std;

struct Menu
{
	static bool exitGame;									//Exit the game
	static int current_option;								
	const static string options[8];							//Option names
	static void mainScreen();								
	static void mainMenu();									
	static void playMenu();									//Menu play
	static void leaderBoard();								//Load file leaderboard
	static void helpScreen();								
	static void exitScreen();								
	static void playEasy();									
	static void playMedium();								
	static void printLogo();								//Print the logo to the console
	static void goBack() {}									
	static void printOptionsBoard();						//print the options
	static void printRectangle(int, int, int, int);			//print the rectangle
	static void changeOption(bool, bool);					//change the options
};

struct Player {
	string playerName;
	string playerID;
	string className;
	int score;
	string mode;
};