//day 4, 14 Sep 2021
#include <iostream>
#include <Windows.h>
#include <time.h>
using namespace std;
void direction(char[14][35], int[4], int[4], char[4], int);
void clearScreen();
void check(char[14][35], int[4], int[4], int[4], int, char[4], int, int);
time_t start;
void startScreen()
{
	cout << "Use A S D W to navigate\nDiamonds will make you invulnerable to the ghosts for 5 seconds\n";
	cout << "Game ends when you consume all of the pellets\nYou only get one life\n";
	Sleep(3500);
	system("CLS");
}
void colorChange(int col)
{
	HANDLE  hConsole;
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, col);
}
void display(char arena[14][35], int x[4], int y[4], int inc[4], int c, char ghost[4])
{
	static time_t start_time = 0;
	static char pacman = 17;
	static int x1 = 17, y1 = 12, incx = 0, incy = 0, points = 0, t = 0, col;
	if (GetKeyState('A') & 0x8000) { incx = -1, incy = 0, pacman = 17; }
	if (GetKeyState('D') & 0x8000) { incx = 1, incy = 0, pacman = 16; }
	if (GetKeyState('W') & 0x8000) { incy = -1, incx = 0, pacman = 30; }
	if (GetKeyState('S') & 0x8000) { incy = 1, incx = 0, pacman = 31; }
	if (arena[y1 + incy][x1 + incx] != 004 && arena[y1 + incy][x1 + incx] != ' ' && arena[y1 + incy][x1 + incx] != '*') { incx = 0, incy = 0; }
	if (arena[y1 + incy][x1 + incx] == '*') { points += 10; }
	if (arena[y1 + incy][x1 + incx] == 004) { points += 200; start_time = time(0), t = 0; }
	t = time(0) - start_time;
	if (t >= 6) { start_time = 0, t = 7; }
	arena[y1][x1] = ' ';
	y1 += incy, x1 += incx;
	arena[y1][x1] = pacman;
	colorChange(15);
	cout << "Points: " << points << endl;
	for (int i = 0; i < 14; i++)
	{
		for (int j = 0; j < 35; j++)
		{
			if (arena[i][j] == '*' || arena[i][j] == 004) { col = 14; }
			else if (arena[i][j] == ghost[0] || arena[i][j] == ghost[1] || arena[i][j] == ghost[2] || arena[i][j] == ghost[3]) { if (t == 7) { col = 4; } else { col = 11; } }
			else if (arena[i][j] == 16 || arena[i][j] == 17 || arena[i][j] == 30 || arena[i][j] == 31) { col = 2; }
			else { col = 1; }
			colorChange(col);
			cout << arena[i][j] << ' ';
		}
		cout << endl;
	}
	Sleep(200);
	clearScreen();
	c = 0;
	check(arena, x, y, inc, c, ghost, t, points);
}
void clearScreen()
{
	COORD cursorPosition;
	cursorPosition.X = 0;
	cursorPosition.Y = 0;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), cursorPosition);
}
void endGame(int points)
{
	cout << "Points: " << points << endl << "Time taken: " << time(0) - start << " seconds" << endl;
	exit(1);
}
void check(char arena[14][35], int x[4], int y[4], int inc[4], int c, char ghost[4], int t, int points)
{
	static char temp[4] = { ' ', ' ', ' ', ' ' }, temp1 = ' '; int count = 0, gCount = 0;
	for (int i = 0; i < 14; i++)
	{
		for (int j = 0; j < 35; j++)
		{
			if (arena[i][j] == '*' || arena[i][j] == 004) { count++; }
		}
	}
	if (count == 0) { system("CLS"); colorChange(15); cout << "You Win!\n"; endGame(points); }
	if (temp[c] != 21 && temp[c] != 232 && temp[c] != 233 && temp[c] != 235)
	{
		try { temp1 = temp[c]; }
		catch (...) { temp1 = ' '; }
	}
	if (t < 7 && (temp1 == 16 || temp1 == 17 || temp1 == 30 || temp1 == 31)) { temp1 = ' '; }
	arena[y[c]][x[c]] = temp1;
	if ((arena[y[c] + inc[c]][x[c]] == 16 || arena[y[c] + inc[c]][x[c]] == 17 || arena[y[c] + inc[c]][x[c]] == 30 || arena[y[c] + inc[c]][x[c]] == 31 || arena[y[c]][x[c] + inc[c]] == 16 || arena[y[c]][x[c] + inc[c]] == 17 || arena[y[c]][x[c] + inc[c]] == 30 || arena[y[c]][x[c] + inc[c]] == 31) && (t == 7)) { system("CLS"); colorChange(15); cout << "Game over. You Lose!\n";  endGame(points); }
	bool v = (arena[y[c] + inc[c]][x[c]] == ' ' || arena[y[c] + inc[c]][x[c]] == '*' || arena[y[c] + inc[c]][x[c]] == 004 || arena[y[c] + inc[c]][x[c]] == 21 || arena[y[c] + inc[c]][x[c]] == 232 || arena[y[c] + inc[c]][x[c]] == 233 || arena[y[c] + inc[c]][x[c]] == 235 || arena[y[c] + inc[c]][x[c]] == 16 || arena[y[c] + inc[c]][x[c]] == 17 || arena[y[c] + inc[c]][x[c]] == 30 || arena[y[c] + inc[c]][x[c]] == 31);
	bool h = (arena[y[c]][x[c] + inc[c]] == ' ' || arena[y[c]][x[c] + inc[c]] == '*' || arena[y[c]][x[c] + inc[c]] == 004 || arena[y[c]][x[c] + inc[c]] == 21 || arena[y[c]][x[c] + inc[c]] == 232 || arena[y[c]][x[c] + inc[c]] == 233 || arena[y[c]][x[c] + inc[c]] == 235 || arena[y[c]][x[c] + inc[c]] == 16 || arena[y[c]][x[c] + inc[c]] == 17 || arena[y[c]][x[c] + inc[c]] == 30 || arena[y[c]][x[c] + inc[c]] == 31);
	if (v && h)
	{
		int z = rand() % 2;
		if (z == 0) { goto vertical; }
		else { goto horizontal; }
	}
	else if (v)
	{
	vertical:
		temp[c] = arena[y[c] + inc[c]][x[c]];
		arena[y[c] + inc[c]][x[c]] = ghost[c];
		y[c] = y[c] + inc[c];
	}
	else if (h)
	{
	horizontal:
		temp[c] = arena[y[c]][x[c] + inc[c]];
		arena[y[c]][x[c] + inc[c]] = ghost[c];
		x[c] = x[c] + inc[c];
	}
	else
	{
		direction(arena, x, y, ghost, c);
	}
	if (c < 3)
	{
		c++;
		check(arena, x, y, inc, c, ghost, t, points);
	}
	else { display(arena, x, y, inc, c, ghost); }
}
void direction(char arena[14][35], int x[4], int y[4], char ghost[4], int c)
{
	int dir[2] = { -1,1 };
	static int inc[4] = { dir[rand() % 2], dir[rand() % 2], dir[rand() % 2], dir[rand() % 2] }, t = 7, points = 0;
	inc[c] = dir[rand() % 2];
	check(arena, x, y, inc, c, ghost, t, points);
}
void main()
{
	start = time(0);
	startScreen();
	srand(time(0));
	char arena[14][35] = { {218,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,194,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,191},		//0
								 {179,'*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*',179,'*','*','*','*','*','*','*','*','*','*','*','*','*','*',004,179},		//1
								 {179,004,196,196,'*',218,196,196,191,'*',196,196,196,196,'*',196,196,196,217,'*',196,196,196,196,196,'*',218,191,'*',196,196,'*',196,'*',179},		//2
								 {179,'*','*','*','*',195,196,196,217,'*','*','*','*','*',004,'*','*','*','*','*',' ',' ',' ',' ',' ','*',179,179,'*','*','*','*','*','*',179},		//3
								 {195,196,196,191,'*',179,'*','*','*','*',218,196,196,191,'*',218,196,196,191,'*',179,' ',' ',' ',179,'*',179,179,'*',218,196,196,191,'*',179},		//4
								 {195,196,196,217,'*',179,'*',218,191,'*',179,' ',' ',179,'*',179,' ',' ',179,'*',179,' ',' ',' ',179,'*',179,179,'*',195,196,196,217,'*',179},		//5
								 {179,004,'*','*','*',179,004,179,179,'*',179,' ',' ',179,'*',179,' ',' ',179,'*',179,' ',' ',' ',179,'*',179,179,'*',179,'*','*','*','*',179},		//6
								 {195,196,196,191,'*',192,196,193,217,'*',192,196,196,217,'*',192,196,196,217,'*',192,196,196,196,217,'*',179,179,'*',179,'*',218,191,'*',179},		//7
								 {179,' ',' ',179,'*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*',004,179,179,'*',179,004,179,179,'*',179},		//8
								 {195,196,196,217,'*',196,196,196,196,004,196,196,'*',196,'*',196,196,196,196,196,194,196,196,'*',179,'*',192,217,'*',192,196,193,217,'*',179},		//9
								 {179,'*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*',179,'*','*','*',179,'*','*','*','*','*','*','*','*','*',179},		//10
								 {179,'*',196,196,196,'*',196,196,196,196,196,'*',196,196,196,196,196,'*',179,'*',179,'*',179,'*',192,196,196,196,196,'*',196,196,196,'*',179},		//11
								 {179,004,'*','*','*','*','*','*','*','*','*','*','*','*','*','*','*',' ',179,004,'*','*',179,'*','*','*','*','*','*','*','*','*','*',004,179},		//12
								 {192,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,193,196,196,196,193,196,196,196,196,196,196,196,196,196,196,196,217} };	//13
								//0		1   2	3	4	5	6	7	8	9  10  11  12  13  14  15  16  17  18  19  20  21  22  23  24  25  26  27  28  29  30  31  32  33  34 
	char ghost[4] = { 21, 232, 233, 235 };
	int x[4] = { 21,22,23,21 }, y[4] = { 5,5,5,3 };
	for (int i = 0; i < 4; i++)
	{
		arena[y[i]][x[i]] = ghost[i];
	}
	int c = 0;
	direction(arena, x, y, ghost, c);
}