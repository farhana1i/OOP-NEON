#include "Date.h"

//constructors
Date::Date() : year(0), month(0), day(0) {}
Date::Date(int y, int m, int d) : year(y), month(m), day(d) {}
Date::Date(const Date& obj) : year(obj.year), month(obj.month), day(obj.day) {}

//getters
int Date::getDay() { return day; }
int Date::getMonth() { return month; }
int Date::getYear() { return year; }

//overload insertion operator for "Date" class
ostream& operator<<(ostream& _cout, const Date& obj) {
	if (&obj != nullptr) {
		_cout << obj.day << "/" << obj.month << "/" << obj.year;
	}
	return _cout;
}

//Destructor
Date::~Date() {}