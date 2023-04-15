#pragma once
#pragma comment(lib, "Winmm.lib")

#include <Windows.h>
#include <conio.h>
#include <vector>
#include <Random>
#include <string>

// COLOR CODE
#define BLACK 0
#define BLUE 1
#define GREEN 2
#define AQUA 3
#define RED 4
#define PURPLE 5
#define YELLOW 6
#define WHITE 7
#define GRAY 8
#define LIGHT_BLUE 9
#define LIGHT_GREEN 10
#define LIGHT_AQUA 11
#define LIGHT_RED 12
#define LIGHT_PURPLE 13
#define LIGHT_YELLOW 14
#define BRIGHT_WHITE 15

// MOVEMENT
#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_LEFT 75
#define KEY_RIGHT 77
#define KEY_ESC 27

// SOUNDTRACK
#define MOVE_SOUND 0
#define ENTER_SOUND 1
#define ERROR_SOUND 2
#define WIN_SOUND 4
#define BACKGROUND_SOUND 5
#define EFFECT_SOUND 6
using namespace std;

struct Controller {
	Controller() {};
	~Controller() {};
	static HWND consoleWindow;    //Pointer Execute Console Window
	static HANDLE consoleOutput;  //Pointer Execute Console Output
	static void setUpConsole();               //Setup the console
	static void gotoXY(int, int);			  //Move to (x, y)
	static void setAndCenterWindow();         
	static void setConsoleColor(int, int);    //Setup Color in Console
	static void setConsoleTitle();            //Setup Console Title
	static void disableMaximize();            //Disable maximize console
	static void showCursor(bool);             //Hide or show cursors
	static void setFontInfo();                //setting the font
	static void clearConsole();               //clear console
	static void disableMouseInput();          //Disable mouse
	static int getConsoleInput();             //get the command to console
	static void playSound(int);               //play the sound
}; 

int getRandomInt(int begin, int end);         //get random numbers
