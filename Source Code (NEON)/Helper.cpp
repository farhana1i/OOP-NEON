#include "Helper.h"
#include<fstream>

HANDLE hmPrint = GetStdHandle(STD_OUTPUT_HANDLE);

//generates random password
void Helper::generatePassword(char*& password) {
	srand(time(NULL));
	char pwd[] = "abcdefghijklmnopqrstuvwxyz1234567890ABCDEFGHIJKLMNOPQRSTUVWXYZ!@#$%&*";
	password = new char[16];
	for (int i = 0; i < 15; i++) {
		password[i] = pwd[rand() % 70];
	}
	password[15] = '\0';
}

//generates random username
void Helper::generateUserName(char*& userName) {
	srand(time(NULL));
	char uN[] = "abcdefghijklmnopqrstuvwxyz1234567890!@";
	userName = new char[11];
	for (int i = 0; i < 10; i++) {
		userName[i] = uN[rand() % 39];
	}
	userName[10] = '\0';
}

//generates random registeration ID
int Helper::generateRegisterationID() {
	srand(time(nullptr));
	int reg_num;
	return reg_num = rand() % 1000 + 1;
}

// To store number of days in all months from January to December 
const int monthDays[12] = { 31, 28, 31, 30, 31, 30,
						   31, 31, 30, 31, 30, 31 };

// This function counts number of leap years before the given date 
int Helper::countLeapYears(Date* d){
	int years = d->getYear();
	if (d->getMonth() <= 2)
		years--;
	return years / 4 - years / 100 + years / 400;
}

//return number of days between two dates
int Helper::getDifference(Date* dt1, Date* dt2){	
	long int n1 = dt1->getYear() * 365 + dt1->getDay();
	for (int i = 0; i < dt1->getMonth() - 1; i++)
		n1 += monthDays[i];

	n1 += countLeapYears(dt1);

	long int n2 = dt2->getYear() * 365 + dt2->getDay();
	for (int i = 0; i < dt2->getMonth() - 1; i++)
		n2 += monthDays[i];
	n2 += Helper::countLeapYears(dt2);

	return (n2 - n1);
}

//control cursor's position on the output(console) screen
void Helper::gotoxy(int x, int y) {
	COORD c = { x, y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
}
int Helper::wherex()
{
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
	return csbi.dwCursorPosition.X;
}
int Helper::wherey()
{
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
	return csbi.dwCursorPosition.Y;
}


//move and adjust size of output window
void Helper::adjustWindowSize()
{
	HWND console = GetConsoleWindow();
	RECT r;
	GetWindowRect(console, &r); //stores the console's current dimensions
	MoveWindow(console, 0, 0, 1500, 1000, TRUE); // 1600 width, 900 height
}



/***************************|     PRINTING FUNCTIONS        |******************/

//print 'N'
void Helper::printN(char symbol, int size, int x, int y) {
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			if (j == 0 || j == size - 1 || i == j) {
				Helper::gotoxy(x + j, y + i);
				cout << symbol;
			}
		}
		cout << endl;
	}
}

//print 'E'
void Helper::printE(char symbol, int size, int x, int y) {
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			if (i == 0 || j == 0 || i == size - 1 || i == (size - 1) / 2) {
				Helper::gotoxy(x + j, y + i);
				cout << symbol;
			}
		}
		cout << endl;
	}
}

//print 'O'
void Helper::printO(char symbol, int size, int x, int y) {

	Helper::gotoxy(x, y);
	cout << " " << symbol << symbol << symbol <<symbol<< " \n";
	for (int i = 0; i < size - 2; i++) {
		for (int j = 0; j <= size; j++) {
			if (j == 0 || j == size)
			{
				Helper::gotoxy(x + j, y + i + 1);
				cout << symbol;
			}
		}
		cout << endl;
	}
	Helper::gotoxy(x, y + size - 1);
	cout << " " << symbol << symbol << symbol << symbol << "\n";
}

//print 'P'
void Helper::printP(char symbol, int size, int x, int y) {
	for (int i = 0; i < size / 2; i++) {
		for (int j = 0; j < size; j++) {
			if ((i == 0 && j != size - 1) || j == 0 || (i == (size / 2) - 1 && j != size - 1) || (i != 0 && i != (size / 2) - 1 && j == size - 1))
			{
				Helper::gotoxy(x + j, y + i);
				cout << symbol;
			}
		}
		cout << endl;
	}


	for (int i = size / 2; i < size - 1; i++)
	{
		Helper::gotoxy(x, y + i);
		cout << symbol << endl;
	}
}

//print 'R'
void Helper::printR(char symbol, int size, int x, int y) {
	for (int i = 0; i < size / 2; i++) {
		for (int j = 0; j < size; j++) {
			if ((i == 0 && j != size - 1) || j == 0 || (i == (size / 2) - 1 && j != size - 1) || (i != 0 && i != (size / 2) - 1 && j == size - 1))
			{
				Helper::gotoxy(x + j, y + i);
				cout << symbol;
			}
		}
		cout << endl;
	}
	for (int i = 0; i < size / 2 - 1; i++) {
		for (int j = 0; j < size; j++) {
			if (j == 0 || i == j - 3) {
				Helper::gotoxy(x + j, y + i + size / 2);
				cout << symbol;
			}
		}
		cout << endl;
	}
}

//print 'J'
void Helper::printJ(char symbol, int size, int x, int y) {
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			if (i == 0 || j == size / 2 || (j == 0 && (i == size - 1 || i == size - 2) || (j == 1 || j == (size / 2 - 1)) && i == size - 1))
			{
				Helper::gotoxy(x + j, y + i);
				cout << symbol;
			}
		}
		cout << endl;
	}
}

//print 'T'
void Helper::printT(char symbol, int size, int x, int y) {
	for (int i = 0; i < size; i++) {
		for (int j = 0; j <= size; j++) {
			if (i == 0 || j == size / 2)
			{
				Helper::gotoxy(x + j, y + i);
				cout << symbol;
			}
		}
		cout << endl;
	}
}

//print 'C'
void Helper::printC(char symbol, int size, int x, int y) {

	for (int i = 1; i < size; i++) {
		Helper::gotoxy(x + i, y);
		cout << symbol;
	}

	for (int i = 1; i < size - 1; i++) {
		for (int j = 0; j < size - 1; j++) {
			if (j == 0)
			{
				Helper::gotoxy(x + j, y + i);
				cout << symbol;
			}
		}
	}


	for (int i = 1; i < size; i++) {
		Helper::gotoxy(x + i, y + size - 1);
		cout << symbol;
	}
}

//print Spaces
void Helper::printSpaces(int x, int y, int xSize, int ySize) {
	for (int i = y; i < ySize; i++) {
		for (int j = x; j < xSize; j++) {
			Helper::gotoxy(j, i);
			cout << " ";
		}
	}
}

//print NEON-PROJECT
void Helper::printNEON(char symbol, int size, int x, int y) {
	SetConsoleTextAttribute(hmPrint, 0 | BACKGROUND_RED | BACKGROUND_GREEN);
	printSpaces(x - 3, y - 1, x + 100, y + 6);

	//print NEON
	printN(symbol, size, x, y);
	printE(symbol, size, x + 8, y);
	printO(symbol, size, x + 16, y);
	printN(symbol, size, x + 25, y);

	Helper::gotoxy(x + 33, y + 2);
	cout << " *** ";

	//Print Project
	printP(symbol, size + 1, x + 41, y);
	printR(symbol, size + 1, x + 49, y);
	printO(symbol, size, x + 58, y);
	printJ(symbol, size, x + 67, y);
	printE(symbol, size, x + 75, y);
	printC(symbol, size, x + 83, y);
	printT(symbol, size, x + 91, y);

	SetConsoleTextAttribute(hmPrint, 15);
	Helper::gotoxy(70, 14);
	cout << " by Farhan Ali.. ";

	SetConsoleTextAttribute(hmPrint, 0 | BACKGROUND_GREEN);
	Helper::gotoxy(60, 23);
	cout << setw(5) << " " << "WELCOME TO THE NEON-SYSTEM" << setw(5) << " ";

	SetConsoleTextAttribute(hmPrint, 15);
	Helper::gotoxy(64, 25);
	cout << " PLease wait for 2 second.... " << setw(5);
	Sleep(2000);

	for (int i = 0; i < 5; i++)
		cout << endl;
}

/******************			End Print Functions			*************/			