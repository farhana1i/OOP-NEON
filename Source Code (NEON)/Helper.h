#ifndef HELPER_H
#define HELPER_H
#include<iostream>
#include<time.h>
#include"Date.h"
#include<Windows.h>
#include<iomanip>
using namespace std;


class Helper {
public:

	//generates random password
	static void generatePassword(char*& password);
	
	//generates random username
	static void generateUserName(char*& userName);
	
	//generates random registeration ID
	static int generateRegisterationID();
	
	//calculates number of days between two dates
	static int getDifference(Date* dt1, Date* dt2);

	//counts number of leap years before the given date
	static int countLeapYears(Date* d);
	
	//controls cursor's position on the output(console) screen
	static void gotoxy(int x, int y);
	static int wherex();
	static int wherey();

	//move and adjust size of output window
	static void adjustWindowSize();

	//print spaces
	static void printSpaces(int x, int y, int xSize, int ySize);
	//print 'N'
	static void printN(char symbol, int size = 5, int x = 0, int y = 0);
	//print 'E'
	static void printE(char symbol, int size = 5, int x = 0, int y = 0);
	//print 'O'
	static void printO(char symbol, int size = 5, int x = 0, int y = 0);
	//print 'P'
	static void printP(char symbol, int size = 5, int x = 0, int y = 0);
	//print 'R'
	static void printR(char symbol, int size = 5, int x = 0, int y = 0);
	//print 'J'
	static void printJ(char symbol, int size = 5, int x = 0, int y = 0);
	//print 'T'
	static void printT(char symbol, int size = 5, int x = 0, int y = 0);
	//print 'C'
	static void printC(char symbol, int size = 5, int x = 0, int y = 0);
	//print NEON-Project
	static void printNEON(char symbol, int size = 5, int x = 0, int y = 0);
};

#endif