#include "Board.h"

Board::Board(int psize, int pX, int pY) : size(psize), left(pX), top(pY)
{
	pokemons = new int*[size];
	for (int i = 0; i < psize; i++)
		pokemons[i] = new int[size];
	pBoard = new Point * [psize];
	for (int i = 0; i < psize; i++)		
		pBoard[i] = new Point[psize];
	background = new string[psize * 10];
}

Board::~Board()
{
	for (int i = 0; i < size; i++)
		delete[] pBoard[i];
	delete[] pBoard,
	pBoard = nullptr;
	delete[] background;
	background = nullptr;
}

int Board::Size()
{
	return size;
}

int Board::Left()
{
	return left;
}

int Board::Top()
{
	return top;
}

int Board::getXAt(int i, int j)
{
	return pBoard[i][j].getX();
}

int Board::getYAt(int i, int j)
{
	return pBoard[i][j].getY();
}

int Board::getRAt(int x, int y)
{
	return (y - top) / 2;
}

int Board::getCAt(int x, int y)
{
	return (x - 3 - left) / 4;
}

char Board::getPokemons(int x, int y)
{
	return pBoard[getRAt(x,y)][getCAt(x,y)].getPokemons();
}

int Board::getCheckAtXY(int pX, int pY)
{
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			if (pBoard[i][j].getX() == pX && pBoard[i][j].getY() == pY)
				return pBoard[i][j].getCheck();
		}
	}
	throw "Position problem!";
}
int Board::getCheck(int x, int y)
{
	int r = getRAt(x, y);
	int c = getCAt(x, y);
	return pBoard[r][c].getCheck();
}

void Board::showBoard()
{
	if (pBoard == NULL)
		return;
	Controller::setConsoleColor(BLACK, WHITE);
	Controller::clearConsole();

	// Draw top line
	Controller::gotoXY(left + 1, top);
	putchar(201);
	for (int i = 1; i < size * 4; i++)
	{
		Sleep(5);
		if (i % 4 == 0)
			putchar(203);
		else
			putchar(205);
	}
	putchar(187);
	
	// Draw right line
	for (int i = 1; i < size * 2; i++)
	{
		Sleep(10);
		Controller::gotoXY(size * 4 + left + 1, i + top);
		if (i % 2 == 0)
			putchar(185);
		else
			putchar(186);
	}
	Controller::gotoXY(size * 4 + left + 1, size * 2 + top);
	putchar(188);
	
	// Draw bottom line
	for (int i = 1; i < size * 4; i++)
	{
		Controller::gotoXY(size * 4 + left - i + 1, size * 2 + top);
		Sleep(15);
		if (i % 4 == 0)
			putchar(202);
		else
			putchar(205);
	}
	Controller::gotoXY(left + 1, size * 2 + top);
	putchar(200);
	
	// Draw left line
	for (int i = 1; i < size * 2; i++)
	{
		Sleep(10);
		Controller::gotoXY(left + 1, size * 2 + top - i);
		if (i % 2 == 0)
			putchar(204);
		else
			putchar(186);
	}
	
	// Draw vertical lines
	for (int i = 1; i < size * 2; i++)
	{
		for (int j = 4; j < size * 4; j += 4)
		{
			if (i % 4 != 0)
			{
				Controller::gotoXY(j + left + 1, i + top);
				putchar(186);
			}
		}
		Sleep(10);
	}
	
	// Draw horizontal lines
	for (int i = 1; i < size * 4; i++)
	{
		for (int j = 2; j < size * 2; j += 2)
		{
			Controller::gotoXY(i + left + 1, j + top);
			if (i % 4 == 0)
				//putchar(197);
				putchar(206);
			else
				putchar(205);
		}
		Sleep(5);
	}
}

void Board::renderBoard() {
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			pBoard[i][j].setX(4 * j + left + 3); // x-value of boardgame
			pBoard[i][j].setY(2 * i + top + 1); // y-value of boardgame
			pBoard[i][j].setCheck(0);

			int r = pBoard[i][j].getX();
			int c = pBoard[i][j].getY();

			Controller::gotoXY(r, c);
			putchar(pBoard[i][j].getPokemons());
		}
	}
}

void Board::buildBoardData() {
	srand((unsigned int)time(NULL));

	bool* checkDuplicate = new bool[size * size];
	int* pos = new int[size * size];

	// Random pokemons
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j += 2) {
			pokemons[i][j] = pokemons[i][j + 1] = rand() % 26 + 'A';
		}
	}

	// Random pokemons position 
	for (int i = 0; i < size * size; i++)
		checkDuplicate[i] = 0;
	for (int i = 0; i < size * size; i++) {
		int tmp = 0;
		do {
			tmp = rand() % (size * size);
		} while (checkDuplicate[tmp]);
		checkDuplicate[tmp] = 1;
		pos[i] = tmp;
	}

	// Construct pokemons matrix
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			int r = pos[size * i + j] / size;
			int c = pos[size * i + j] % size;
			pBoard[i][j].setPokemons(pokemons[r][c]);
		}
	}

	delete[] pos;
	delete[] checkDuplicate;
}

void Board::selectedBlock(int x, int y, int color) {
	Controller::setConsoleColor(color, WHITE);
	for (int i = x - 1; i <= x + 1; i++) {
		Controller::gotoXY(i, y);
		putchar(32);
	}
	if (getCheck(x, y) != _DELETE) {
		Controller::gotoXY(x, y);
		putchar(getPokemons(x, y));
		Controller::gotoXY(x, y);
	}
	else {
		for (int i = x - 1; i <= x + 1; i++) {
			Controller::gotoXY(i, y);
			putchar(32);
		}
	}
}

void Board::unselectedBlock(int x, int y) {
	int r = getRAt(x, y);
	int c = getCAt(x, y);
	if(getCheck(x, y) != _DELETE)
		pBoard[r][c].setCheck(_NORMAL);

	Controller::setConsoleColor(BLACK, WHITE);
	for (int i = x - 1; i <= x + 1; i++) {
		Controller::gotoXY(i, y);
		putchar(32);
	}
	if (getCheck(x, y) != _DELETE) {
		Controller::gotoXY(x, y);
		putchar(getPokemons(x, y));
		Controller::gotoXY(x, y);
	}
	else {
		for (int i = x - 1; i <= x + 1; i++) {
			Controller::gotoXY(i, y);
			putchar(32);
		}
	}
}

void Board::lockBlock(int x, int y)
{
	int r = getRAt(x, y);
	int c = getCAt(x, y);
	pBoard[r][c].setCheck(_LOCK);

	Controller::setConsoleColor(RED, WHITE);
	int i = y;
	for (int j = x - 1; j <= x + 1; j++) {
		Controller::gotoXY(j, i);
		putchar(32);
	}
	Controller::gotoXY(x, y);
	putchar(getPokemons(x, y));
	Controller::gotoXY(x, y);
}

void Board::deleteBlock(int x, int y)
{
	int r = getRAt(x, y);
	int c = getCAt(x, y);
	pBoard[r][c].setCheck(_DELETE);

	Controller::setConsoleColor(BLACK, WHITE);
	for (int i = x - 1; i <= x + 1; i++) {
		Controller::gotoXY(i, y);
		putchar(32);
	}
}

void Board::drawLineI(pair<int, int>firstBlock, pair<int, int>secondBlock) {
	Controller::setConsoleColor(RED, WHITE);
	if (firstBlock.first == secondBlock.first) {
		Controller::gotoXY(firstBlock.first, firstBlock.second + 1);
		putchar(30);
		for (int i = firstBlock.second + 2; i <= secondBlock.second - 2; i++) {
			Controller::gotoXY(firstBlock.first, i);
			putchar(179);
		}
		Controller::gotoXY(secondBlock.first, secondBlock.second - 1);
		putchar(31);
		return;
	}
	//========================================================================//
	if (firstBlock.second == secondBlock.second) {
		Controller::gotoXY(firstBlock.first + 1, firstBlock.second);
		putchar(17);
		for (int i = firstBlock.first + 2; i <= secondBlock.first - 2; i++) {
			Controller::gotoXY(i, firstBlock.second);
			putchar(45);
		}
		Controller::gotoXY(secondBlock.first - 1, secondBlock.second);
		putchar(16);
		return;
	}
}

void Board::deleteLineI(pair<int, int>firstBlock, pair<int, int>secondBlock) {
	Controller::setConsoleColor(BLACK, BLACK);
	if (firstBlock.first == secondBlock.first) {
		Controller::gotoXY(firstBlock.first, firstBlock.second + 1);
		putchar(32);
		for (int i = firstBlock.second + 2; i <= secondBlock.second - 2; i++) {
			Controller::gotoXY(firstBlock.first, i);
			putchar(32);
		}
		Controller::gotoXY(secondBlock.first, secondBlock.second - 1);
		putchar(32);
		return;
	}
	//========================================================================//
	if (firstBlock.second == secondBlock.second) {
		Controller::gotoXY(firstBlock.first + 1, firstBlock.second);
		putchar(32);
		for (int i = firstBlock.first + 2; i <= secondBlock.first - 2; i++) {
			Controller::gotoXY(i, firstBlock.second);
			putchar(32);
		}
		Controller::gotoXY(secondBlock.first - 1, secondBlock.second);
		putchar(32);
		return;
	}
}

void Board::drawLineL(pair<int, int>firstBlock, pair<int, int>secondBlock, pair<int, int>Lcorner) {
	Controller::setConsoleColor(RED, BLACK);
	// down-left corner
	if (Lcorner.first < secondBlock.first && Lcorner.second > firstBlock.second) {
		Controller::gotoXY(firstBlock.first, firstBlock.second + 1);
		putchar(30);
		for (int i = firstBlock.second + 2; i <= Lcorner.second - 1; i++) {
			Controller::gotoXY(firstBlock.first, i);
			putchar(179);
		}
		for (int i = Lcorner.first; i <= secondBlock.first - 2; i++) {
			Controller::gotoXY(i, secondBlock.second);
			putchar(45);
		}
		Controller::gotoXY(secondBlock.first - 1, secondBlock.second);
		putchar(16);
		return;
	}
	//========================================================================//
	// up-left corner
	if (Lcorner.first < secondBlock.first && Lcorner.second < firstBlock.second) {
		Controller::gotoXY(firstBlock.first, firstBlock.second - 1);
		putchar(31);
		for (int i = firstBlock.second - 2; i >= Lcorner.second + 1; i--) {
			Controller::gotoXY(firstBlock.first, i);
			putchar(179);
		}
		for (int i = Lcorner.first; i <= secondBlock.first - 2; i++) {
			Controller::gotoXY(i, secondBlock.second);
			putchar(45);
		}
		Controller::gotoXY(secondBlock.first - 1, secondBlock.second);
		putchar(16);
		return;
	}
	//========================================================================//
	// up-right corner
	if (Lcorner.second < secondBlock.second && Lcorner.first > firstBlock.first) {
		Controller::gotoXY(firstBlock.first + 1, firstBlock.second);
		putchar(17);
		for (int i = firstBlock.first + 2; i <= Lcorner.first; i++) {
			Controller::gotoXY(i, firstBlock.second);
			putchar(45);
		}
		for (int i = Lcorner.second + 1; i <= secondBlock.second - 2; i++) {
			Controller::gotoXY(secondBlock.first, i);
			putchar(179);
		}
		Controller::gotoXY(secondBlock.first, secondBlock.second - 1);
		putchar(31);
		return;
	}
	//========================================================================//
	// down-right corner
	if (Lcorner.second > secondBlock.second && Lcorner.first > firstBlock.first) {
		Controller::gotoXY(firstBlock.first + 1, firstBlock.second);
		putchar(17);
		for (int i = firstBlock.first + 2; i <= Lcorner.first; i++) {
			Controller::gotoXY(i, firstBlock.second);
			putchar(45);
		}
		for (int i = Lcorner.second - 1; i >= secondBlock.second + 2; i--) {
			Controller::gotoXY(secondBlock.first, i);
			putchar(179);
		}
		Controller::gotoXY(secondBlock.first, secondBlock.second + 1);
		putchar(30);
		return;
	}
}

void Board::deleteLineL(pair<int, int>firstBlock, pair<int, int>secondBlock, pair<int, int>Lcorner) {
	Controller::setConsoleColor(BLACK, BLACK);
	// down-left corner
	if (Lcorner.first < secondBlock.first && Lcorner.second > firstBlock.second) {
		Controller::gotoXY(firstBlock.first, firstBlock.second + 1);
		putchar(32);
		for (int i = firstBlock.second + 2; i <= Lcorner.second - 1; i++) {
			Controller::gotoXY(firstBlock.first, i);
			putchar(32);
		}
		for (int i = Lcorner.first; i <= secondBlock.first - 2; i++) {
			Controller::gotoXY(i, secondBlock.second);
			putchar(32);
		}
		Controller::gotoXY(secondBlock.first - 1, secondBlock.second);
		putchar(32);
		return;
	}
	//========================================================================//
	// up-left corner
	if (Lcorner.first < secondBlock.first && Lcorner.second < firstBlock.second) {
		Controller::gotoXY(firstBlock.first, firstBlock.second - 1);
		putchar(32);
		for (int i = firstBlock.second - 2; i >= Lcorner.second + 1; i--) {
			Controller::gotoXY(firstBlock.first, i);
			putchar(32);
		}
		for (int i = Lcorner.first; i <= secondBlock.first - 2; i++) {
			Controller::gotoXY(i, secondBlock.second);
			putchar(32);
		}
		Controller::gotoXY(secondBlock.first - 1, secondBlock.second);
		putchar(32);
		return;
	}
	//========================================================================//
	// up-right corner
	if (Lcorner.second < secondBlock.second && Lcorner.first > firstBlock.first) {
		Controller::gotoXY(firstBlock.first + 1, firstBlock.second);
		putchar(32);
		for (int i = firstBlock.first + 2; i <= Lcorner.first; i++) {
			Controller::gotoXY(i, firstBlock.second);
			putchar(32);
		}
		for (int i = Lcorner.second + 1; i <= secondBlock.second - 2; i++) {
			Controller::gotoXY(secondBlock.first, i);
			putchar(32);
		}
		Controller::gotoXY(secondBlock.first, secondBlock.second - 1);
		putchar(32);
		return;
	}
	//========================================================================//
	// down-right corner
	if (Lcorner.second > secondBlock.second && Lcorner.first > firstBlock.first) {
		Controller::gotoXY(firstBlock.first + 1, firstBlock.second);
		putchar(32);
		for (int i = firstBlock.first + 2; i <= Lcorner.first; i++) {
			Controller::gotoXY(i, firstBlock.second);
			putchar(32);
		}
		for (int i = Lcorner.second - 1; i >= secondBlock.second + 2; i--) {
			Controller::gotoXY(secondBlock.first, i);
			putchar(32);
		}
		Controller::gotoXY(secondBlock.first, secondBlock.second + 1);
		putchar(32);
		return;
	}
}

void Board::drawLineZ(pair<int, int>firstBlock, pair<int, int>secondBlock, pair<int, int>Zcorner1, pair<int, int>Zcorner2) {
	Controller::setConsoleColor(RED, BLACK);
	// down-left corner
	if (Zcorner1.first < secondBlock.first && Zcorner1.second > firstBlock.second) {
		Controller::gotoXY(firstBlock.first, firstBlock.second + 1);
		putchar(30);
		for (int i = firstBlock.second + 2; i <= Zcorner1.second - 1; i++) {
			Controller::gotoXY(firstBlock.first, i);
			putchar(179);
		}
		for (int i = Zcorner1.first; i <= Zcorner2.first; i++) {
			Controller::gotoXY(i, Zcorner1.second);
			putchar(45);
		}
		for (int i = Zcorner2.second + 1; i <= secondBlock.second - 2; i++) {
			Controller::gotoXY(secondBlock.first, i);
			putchar(179);
		}
		Controller::gotoXY(secondBlock.first, secondBlock.second - 1);
		putchar(31);
		return;
	}
	//========================================================================//
	// up-left corner
	if (Zcorner1.first > secondBlock.first && Zcorner1.second > firstBlock.second) {
		Controller::gotoXY(firstBlock.first, firstBlock.second + 1);
		putchar(30);
		for (int i = firstBlock.second + 2; i <= Zcorner1.second - 1; i++) {
			Controller::gotoXY(firstBlock.first, i);
			putchar(179);
		}	
		for (int i = Zcorner1.first; i >= Zcorner2.first; i--) {
			Controller::gotoXY(i, Zcorner1.second);
			putchar(45);
		}
		for (int i = Zcorner2.second + 1; i <= secondBlock.second - 2; i++) {
			Controller::gotoXY(secondBlock.first, i);
			putchar(179);
		}
		Controller::gotoXY(secondBlock.first, secondBlock.second - 1);
		putchar(31);
		return;
	}
	//========================================================================//
	// up-right corner
	if (Zcorner1.second < secondBlock.second && Zcorner1.first > firstBlock.first) {
		Controller::gotoXY(firstBlock.first + 1, firstBlock.second);
		putchar(17);
		for (int i = firstBlock.first + 2; i <= Zcorner1.first; i++) {
			Controller::gotoXY(i, firstBlock.second);
			putchar(45);
		}
		for (int i = Zcorner1.second + 1; i <= Zcorner2.second - 1; i++) {
			Controller::gotoXY(Zcorner1.first, i);
			putchar(179);
		}
		for (int i = Zcorner2.first; i <= secondBlock.first - 2; i++) {
			Controller::gotoXY(i, secondBlock.second);
			putchar(45);
		}
		Controller::gotoXY(secondBlock.first - 1, secondBlock.second);
		putchar(16);
		return;
	}
	//========================================================================//
	// down-right corner
	if (Zcorner1.second > secondBlock.second && Zcorner1.first > firstBlock.first) {
		Controller::gotoXY(firstBlock.first + 1, firstBlock.second);
		putchar(17);
		for (int i = firstBlock.first + 2; i <= Zcorner1.first; i++) {
			Controller::gotoXY(i, firstBlock.second);
			putchar(45);
		}
		for (int i = Zcorner1.second - 1; i >= Zcorner2.second + 1; i--) {
			Controller::gotoXY(Zcorner1.first, i);
			putchar(179);
		}
		for (int i = Zcorner2.first; i <= secondBlock.first - 2; i++) {
			Controller::gotoXY(i, secondBlock.second);
			putchar(45);
		}
		Controller::gotoXY(secondBlock.first - 1, secondBlock.second);
		putchar(16);
		return;
	}
}

void Board::deleteLineZ(pair<int, int>firstBlock, pair<int, int>secondBlock, pair<int, int>Zcorner1, pair<int, int>Zcorner2) {
	Controller::setConsoleColor(BLACK, BLACK);
	// down-left corner
	if (Zcorner1.first < secondBlock.first && Zcorner1.second > firstBlock.second) {
		Controller::gotoXY(firstBlock.first, firstBlock.second + 1);
		putchar(32);
		for (int i = firstBlock.second + 2; i <= Zcorner1.second - 1; i++) {
			Controller::gotoXY(firstBlock.first, i);
			putchar(32);
		}
		for (int i = Zcorner1.first; i <= Zcorner2.first; i++) {
			Controller::gotoXY(i, Zcorner1.second);
			putchar(32);
		}
		for (int i = Zcorner2.second + 1; i <= secondBlock.second - 2; i++) {
			Controller::gotoXY(secondBlock.first, i);
			putchar(32);
		}
		Controller::gotoXY(secondBlock.first, secondBlock.second - 1);
		putchar(32);
		return;
	}
	//========================================================================//
	// up-left corner
	if (Zcorner1.first > secondBlock.first && Zcorner1.second > firstBlock.second) {
		Controller::gotoXY(firstBlock.first, firstBlock.second + 1);
		putchar(32);
		for (int i = firstBlock.second + 2; i <= Zcorner1.second - 1; i++) {
			Controller::gotoXY(firstBlock.first, i);
			putchar(32);
		}
		for (int i = Zcorner1.first; i >= Zcorner2.first; i--) {
			Controller::gotoXY(i, Zcorner1.second);
			putchar(32);
		}
		for (int i = Zcorner2.second + 1; i <= secondBlock.second - 2; i++) {
			Controller::gotoXY(secondBlock.first, i);
			putchar(32);
		}
		Controller::gotoXY(secondBlock.first, secondBlock.second - 1);
		putchar(32);
		return;
	}
	//========================================================================//
	// up-right corner
	if (Zcorner1.second < secondBlock.second && Zcorner1.first > firstBlock.first) {
		Controller::gotoXY(firstBlock.first + 1, firstBlock.second);
		putchar(32);
		for (int i = firstBlock.first + 2; i <= Zcorner1.first; i++) {
			Controller::gotoXY(i, firstBlock.second);
			putchar(32);
		}
		for (int i = Zcorner1.second + 1; i <= Zcorner2.second - 1; i++) {
			Controller::gotoXY(Zcorner1.first, i);
			putchar(32);
		}
		for (int i = Zcorner2.first; i <= secondBlock.first - 2; i++) {
			Controller::gotoXY(i, secondBlock.second);
			putchar(32);
		}
		Controller::gotoXY(secondBlock.first - 1, secondBlock.second);
		putchar(32);
		return;
	}
	//========================================================================//
	// down-right corner
	if (Zcorner1.second > secondBlock.second && Zcorner1.first > firstBlock.first) {
		Controller::gotoXY(firstBlock.first + 1, firstBlock.second);
		putchar(32);
		for (int i = firstBlock.first + 2; i <= Zcorner1.first; i++) {
			Controller::gotoXY(i, firstBlock.second);
			putchar(32);
		}
		for (int i = Zcorner1.second - 1; i >= Zcorner2.second + 1; i--) {
			Controller::gotoXY(Zcorner1.first, i);
			putchar(32);
		}
		for (int i = Zcorner2.first; i <= secondBlock.first - 2; i++) {
			Controller::gotoXY(i, secondBlock.second);
			putchar(32);
		}
		Controller::gotoXY(secondBlock.first - 1, secondBlock.second);
		putchar(32);
		return;
	}
}

void Board::drawLineU(pair<int, int>firstBlock, pair<int, int>secondBlock, pair<int, int>Ucorner1, pair<int, int>Ucorner2) {
	Controller::setConsoleColor(RED, BLACK);
	//========================================================================//
	if (Ucorner1.first < firstBlock.first && Ucorner1.second < secondBlock.second) {
		for (int i = Ucorner1.first; i <= firstBlock.first - 2; i++) {
			Controller::gotoXY(i, firstBlock.second);
			putchar(45);
		}
		Controller::gotoXY(firstBlock.first - 1, firstBlock.second);
		putchar(16);
		for (int i = Ucorner1.second + 1; i <= Ucorner2.second - 1; i++) {
			Controller::gotoXY(Ucorner1.first, i);
			putchar(179);
		}
		for (int i = Ucorner2.first; i <= secondBlock.first - 2; i++) {
			Controller::gotoXY(i, secondBlock.second);
			putchar(45);
		}
		Controller::gotoXY(secondBlock.first - 1, secondBlock.second);
		putchar(16);
		return;
	}
	if (Ucorner1.first < firstBlock.first && Ucorner1.second > secondBlock.second) {
		for (int i = Ucorner1.first; i <= firstBlock.first - 2; i++) {
			Controller::gotoXY(i, firstBlock.second);
			putchar(45);
		}
		Controller::gotoXY(firstBlock.first - 1, firstBlock.second);
		putchar(16);
		for (int i = Ucorner1.second - 1; i >= Ucorner2.second + 1; i--) {
			Controller::gotoXY(Ucorner1.first, i);
			putchar(179);
		}
		for (int i = Ucorner2.first; i <= secondBlock.first - 2; i++) {
			Controller::gotoXY(i, secondBlock.second);
			putchar(45);
		}
		Controller::gotoXY(secondBlock.first - 1, secondBlock.second);
		putchar(16);
		return;
	}
	//========================================================================//
	if(Ucorner1.first > firstBlock.first && Ucorner1.second < secondBlock.second) {
		for (int i = Ucorner1.first; i >= firstBlock.first + 2; i--) {
			Controller::gotoXY(i, firstBlock.second);
			putchar(45);
		}
		Controller::gotoXY(firstBlock.first + 1, firstBlock.second);
		putchar(17);
		for (int i = Ucorner1.second + 1; i <= Ucorner2.second - 1; i++) {
			Controller::gotoXY(Ucorner1.first, i);
			putchar(179);
		}
		for (int i = Ucorner2.first; i >= secondBlock.first + 2; i--) {
			Controller::gotoXY(i, secondBlock.second);
			putchar(45);
		}
		Controller::gotoXY(secondBlock.first + 1, secondBlock.second);
		putchar(17);
		return;
	}
	if (Ucorner1.first > firstBlock.first && Ucorner1.second > secondBlock.second) {
		for (int i = Ucorner1.first; i >= firstBlock.first + 2; i--) {
			Controller::gotoXY(i, firstBlock.second);
			putchar(45);
		}
		Controller::gotoXY(firstBlock.first + 1, firstBlock.second);
		putchar(17);
		for (int i = Ucorner1.second - 1; i >= Ucorner2.second + 1; i++) {
			Controller::gotoXY(Ucorner1.first, i);
			putchar(179);
		}
		for (int i = Ucorner2.first; i >= secondBlock.first + 2; i--) {
			Controller::gotoXY(i, secondBlock.second);
			putchar(45);
		}
		Controller::gotoXY(secondBlock.first + 1, secondBlock.second);
		putchar(17);
		return;
	}
	//========================================================================//
	if (Ucorner1.second < firstBlock.second && Ucorner1.first < secondBlock.first) {
		for (int i = Ucorner1.second + 1; i <= firstBlock.second - 2; i++) {
			Controller::gotoXY(firstBlock.first, i);
			putchar(179);
		}
		Controller::gotoXY(firstBlock.first, firstBlock.second - 1);
		putchar(31);
		for (int i = Ucorner1.first; i <= Ucorner2.first; i++) {
			Controller::gotoXY(i, Ucorner1.second);
			putchar(45);
		}
		for (int i = Ucorner2.second + 1; i <= secondBlock.second - 2; i++) {
			Controller::gotoXY(secondBlock.first, i);
			putchar(179);
		}
		Controller::gotoXY(secondBlock.first, secondBlock.second - 1);
		putchar(31);
		return;
	}
	if (Ucorner1.second < firstBlock.second && Ucorner1.first > secondBlock.first) {
		for (int i = Ucorner1.second + 1; i <= firstBlock.second - 2; i++) {
			Controller::gotoXY(firstBlock.first, i);
			putchar(179);
		}
		Controller::gotoXY(firstBlock.first, firstBlock.second - 1);
		putchar(31);
		for (int i = Ucorner1.first; i >= Ucorner2.first; i--) {
			Controller::gotoXY(i, Ucorner1.second);
			putchar(45);
		}
		for (int i = Ucorner2.second + 1; i <= secondBlock.second - 2; i++) {
			Controller::gotoXY(secondBlock.first, i);
			putchar(179);
		}
		Controller::gotoXY(secondBlock.first, secondBlock.second - 1);
		putchar(31);
		return;
	}
	//========================================================================//
	if (Ucorner1.second > firstBlock.second && Ucorner1.first < secondBlock.first) {
		for (int i = Ucorner1.second - 1; i >= firstBlock.second + 2; i--) {
			Controller::gotoXY(firstBlock.first, i);
			putchar(179);
		}
		Controller::gotoXY(firstBlock.first, firstBlock.second + 1);
		putchar(30);
		for (int i = Ucorner1.first; i <= Ucorner2.first; i++) {
			Controller::gotoXY(i, Ucorner1.second);
			putchar(45);
		}
		for (int i = Ucorner2.second - 1; i >= secondBlock.second + 2; i--) {
			Controller::gotoXY(secondBlock.first, i);
			putchar(179);
		}
		Controller::gotoXY(secondBlock.first, secondBlock.second + 1);
		putchar(30);
		return;
	}
	if (Ucorner1.second > firstBlock.second && Ucorner1.first > secondBlock.first) {
		for (int i = Ucorner1.second - 1; i >= firstBlock.second + 2; i--) {
			Controller::gotoXY(firstBlock.first, i);
			putchar(179);
		}
		Controller::gotoXY(firstBlock.first, firstBlock.second + 1);
		putchar(30);
		for (int i = Ucorner1.first; i >= Ucorner2.first; i--) {
			Controller::gotoXY(i, Ucorner1.second);
			putchar(45);
		}
		for (int i = Ucorner2.second - 1; i >= secondBlock.second + 2; i--) {
			Controller::gotoXY(secondBlock.first, i);
			putchar(179);
		}
		Controller::gotoXY(secondBlock.first, secondBlock.second + 1);
		putchar(30);
		return;
	}
}

void Board::deleteLineU(pair<int, int>firstBlock, pair<int, int>secondBlock, pair<int, int>Ucorner1, pair<int, int>Ucorner2) {
	Controller::setConsoleColor(BLACK, BLACK);
	//========================================================================//
	if (Ucorner1.first < firstBlock.first && Ucorner1.second < secondBlock.second) {
		for (int i = Ucorner1.first; i <= firstBlock.first - 2; i++) {
			Controller::gotoXY(i, firstBlock.second);
			putchar(32);
		}
		Controller::gotoXY(firstBlock.first - 1, firstBlock.second);
		putchar(32);
		for (int i = Ucorner1.second + 1; i <= Ucorner2.second - 1; i++) {
			Controller::gotoXY(Ucorner1.first, i);
			putchar(32);
		}
		for (int i = Ucorner2.first; i <= secondBlock.first - 2; i++) {
			Controller::gotoXY(i, secondBlock.second);
			putchar(32);
		}
		Controller::gotoXY(secondBlock.first - 1, secondBlock.second);
		putchar(32);
		return;
	}
	if (Ucorner1.first < firstBlock.first && Ucorner1.second > secondBlock.second) {
		for (int i = Ucorner1.first; i <= firstBlock.first - 2; i++) {
			Controller::gotoXY(i, firstBlock.second);
			putchar(32);
		}
		Controller::gotoXY(firstBlock.first - 1, firstBlock.second);
		putchar(32);
		for (int i = Ucorner1.second - 1; i >= Ucorner2.second + 1; i--) {
			Controller::gotoXY(Ucorner1.first, i);
			putchar(32);
		}
		for (int i = Ucorner2.first; i <= secondBlock.first - 2; i++) {
			Controller::gotoXY(i, secondBlock.second);
			putchar(32);
		}
		Controller::gotoXY(secondBlock.first - 1, secondBlock.second);
		putchar(32);
		return;
	}
	//========================================================================//
	if (Ucorner1.first > firstBlock.first && Ucorner1.second < secondBlock.second) {
		for (int i = Ucorner1.first; i >= firstBlock.first + 2; i--) {
			Controller::gotoXY(i, firstBlock.second);
			putchar(32);
		}
		Controller::gotoXY(firstBlock.first + 1, firstBlock.second);
		putchar(32);
		for (int i = Ucorner1.second + 1; i <= Ucorner2.second - 1; i++) {
			Controller::gotoXY(Ucorner1.first, i);
			putchar(32);
		}
		for (int i = Ucorner2.first; i >= secondBlock.first + 2; i--) {
			Controller::gotoXY(i, secondBlock.second);
			putchar(32);
		}
		Controller::gotoXY(secondBlock.first + 1, secondBlock.second);
		putchar(32);
		return;
	}
	if (Ucorner1.first > firstBlock.first && Ucorner1.second > secondBlock.second) {
		for (int i = Ucorner1.first; i >= firstBlock.first + 2; i--) {
			Controller::gotoXY(i, firstBlock.second);
			putchar(32);
		}
		Controller::gotoXY(firstBlock.first + 1, firstBlock.second);
		putchar(32);
		for (int i = Ucorner1.second - 1; i >= Ucorner2.second + 1; i++) {
			Controller::gotoXY(Ucorner1.first, i);
			putchar(32);
		}
		for (int i = Ucorner2.first; i >= secondBlock.first + 2; i--) {
			Controller::gotoXY(i, secondBlock.second);
			putchar(32);
		}
		Controller::gotoXY(secondBlock.first + 1, secondBlock.second);
		putchar(32);
		return;
	}
	//========================================================================//
	if (Ucorner1.second < firstBlock.second && Ucorner1.first < secondBlock.first) {
		for (int i = Ucorner1.second + 1; i <= firstBlock.second - 2; i++) {
			Controller::gotoXY(firstBlock.first, i);
			putchar(32);
		}
		Controller::gotoXY(firstBlock.first, firstBlock.second - 1);
		putchar(32);
		for (int i = Ucorner1.first; i <= Ucorner2.first; i++) {
			Controller::gotoXY(i, Ucorner1.second);
			putchar(32);
		}
		for (int i = Ucorner2.second + 1; i <= secondBlock.second - 2; i++) {
			Controller::gotoXY(secondBlock.first, i);
			putchar(32);
		}
		Controller::gotoXY(secondBlock.first, secondBlock.second - 1);
		putchar(32);
		return;
	}
	if (Ucorner1.second < firstBlock.second && Ucorner1.first > secondBlock.first) {
		for (int i = Ucorner1.second + 1; i <= firstBlock.second - 2; i++) {
			Controller::gotoXY(firstBlock.first, i);
			putchar(32);
		}
		Controller::gotoXY(firstBlock.first, firstBlock.second - 1);
		putchar(32);
		for (int i = Ucorner1.first; i >= Ucorner2.first; i--) {
			Controller::gotoXY(i, Ucorner1.second);
			putchar(32);
		}
		for (int i = Ucorner2.second + 1; i <= secondBlock.second - 2; i++) {
			Controller::gotoXY(secondBlock.first, i);
			putchar(32);
		}
		Controller::gotoXY(secondBlock.first, secondBlock.second - 1);
		putchar(32);
		return;
	}
	//========================================================================//
	if (Ucorner1.second > firstBlock.second && Ucorner1.first < secondBlock.first) {
		for (int i = Ucorner1.second - 1; i >= firstBlock.second + 2; i--) {
			Controller::gotoXY(firstBlock.first, i);
			putchar(32);
		}
		Controller::gotoXY(firstBlock.first, firstBlock.second + 1);
		putchar(32);
		for (int i = Ucorner1.first; i <= Ucorner2.first; i++) {
			Controller::gotoXY(i, Ucorner1.second);
			putchar(32);
		}
		for (int i = Ucorner2.second - 1; i >= secondBlock.second + 2; i--) {
			Controller::gotoXY(secondBlock.first, i);
			putchar(32);
		}
		Controller::gotoXY(secondBlock.first, secondBlock.second + 1);
		putchar(32);
		return;
	}
	if (Ucorner1.second > firstBlock.second && Ucorner1.first > secondBlock.first) {
		for (int i = Ucorner1.second - 1; i >= firstBlock.second + 2; i--) {
			Controller::gotoXY(firstBlock.first, i);
			putchar(32);
		}
		Controller::gotoXY(firstBlock.first, firstBlock.second + 1);
		putchar(32);
		for (int i = Ucorner1.first; i >= Ucorner2.first; i--) {
			Controller::gotoXY(i, Ucorner1.second);
			putchar(32);
		}
		for (int i = Ucorner2.second - 1; i >= secondBlock.second + 2; i--) {
			Controller::gotoXY(secondBlock.first, i);
			putchar(32);
		}
		Controller::gotoXY(secondBlock.first, secondBlock.second + 1);
		putchar(32);
		return;
	}
}
