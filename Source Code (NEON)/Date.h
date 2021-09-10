#pragma once
#include<iostream>
using namespace std;

class Date
{
	int year;
	int month;
	int day;
public:

	//constructors
	Date();
	Date(int y, int m, int d);
	Date(const Date& obj);

	//getters
	int getDay();
	int getMonth();
	int getYear();

	//overload insertion operator for "Date" class
	friend ostream& operator<<(ostream& _cout, const Date& obj);

	//Destructor
	~Date();
};

