#include<iostream>
#include"Registeration.h"
#include"Course.h"
using namespace std;
HANDLE hm = GetStdHandle(STD_OUTPUT_HANDLE);

int Registeration::numOfRegisterations = 0;

//constructors
Registeration::Registeration() :reg_Num(0), std(nullptr), subject(nullptr), gpa(0.0), gt(0.0), attendance_Percentage(0.0), grade('_') {
	time_t now = time(0);
	tm* ltm = new tm;
	localtime_s(ltm, &now);

	int year = 1900 + ltm->tm_year;
	int month = 1 + ltm->tm_mon;
	int day = ltm->tm_mday;
	if (ltm != nullptr)
		delete ltm;
	date = new Date(year, month, day);

	numOfRegisterations++;
}
Registeration::Registeration(int reg_Num, Student* s, Course* c, int y, int m, int d) : gpa(0.0), gt(0.0), attendance_Percentage(0.0), grade('_') {
	this->reg_Num = reg_Num;
		std = s;
		subject = c;
		if (y == 0) {
			time_t now = time(0);
			tm* ltm = new tm;
			localtime_s(ltm, &now);

			y = 1900 + ltm->tm_year;
			m = 1 + ltm->tm_mon;
			d = ltm->tm_mday;
			if (ltm != nullptr)
				delete ltm;
		}
		date = new Date(y, m, d);
		numOfRegisterations++;
}
Registeration::Registeration(const Registeration& obj) {
	date = new Date(*obj.date);
	gt = obj.gt;
	gpa = obj.gpa;
	grade = obj.grade;
	attendance_Percentage = obj.attendance_Percentage;
	this->reg_Num = obj.reg_Num;
	if (obj.std != nullptr)
		std = new Student(*obj.std);
	else
		std = nullptr;
	
	if (obj.subject != nullptr)
		subject = new Course(*obj.subject);
	else
		subject = nullptr;
	numOfRegisterations++;
}

//getters
Date* Registeration::getDate() { return date; }
int Registeration::getDay() { return date->getDay(); }
int Registeration::getMonth() { return date->getMonth(); }
int Registeration::getYear() { return date->getYear(); }
float Registeration::getGPA() {
	if (this != nullptr)
		return gpa;
	return 0.0;
}
int Registeration::getRollNumOfStd() {
	if (this != nullptr)
		return std->getRollNum();
	return 0;
}
int Registeration::getRegNum() {
	if (this != nullptr)
		return reg_Num;
	return 0;
}
char Registeration::getGrade() {
	if (this != nullptr)
		return grade;
	return 0;
}
float Registeration::getGT() {
	if (this != nullptr)
		return gt;
	return 0;
}
float Registeration::GetAttendancePer() {
	if (this != nullptr)
		return attendance_Percentage;
	return 0;
}
char* Registeration::getStudentFirstName() { return std->getFirstName(); }
char* Registeration::getStudentLastName() { return std->getLastName(); }
char* Registeration::getCourseName() { return subject->getCourseName(); }
char* Registeration::getCourseCode() { return subject->getCourseCode(); }

//setters
void Registeration::setGPA(float _gpa) { gpa = _gpa; }
void Registeration::setGT(float _gt) { gt = _gt; }
void Registeration::setGrade(char g) { grade = g; }
void Registeration::setAttendance(float attendance_Percentage) { this->attendance_Percentage = attendance_Percentage; }
void Registeration::setStudent(Student* s) {
	if (std != s) {
		if (std != nullptr)
			std = nullptr;
		std = s;
	}
}

//view marks of a student of register course
void Registeration::viewMarkSheet() {
	if (this != nullptr) {
		cout << "\t\t";
		SetConsoleTextAttribute(hm, 0 | BACKGROUND_BLUE);
		cout << "Name";
		SetConsoleTextAttribute(hm, 15);
		cout << "   " << std->getFirstName() << " " << std->getLastName() << "\n\n";

		cout << "\t\t";
		SetConsoleTextAttribute(hm, 0 | BACKGROUND_BLUE);
		cout << "Course Details";
		SetConsoleTextAttribute(hm, 15);
		cout << "   " << subject->getCourseName() << "(" << subject->getCourseCode() << ")" << "\n\n";

		cout << "\t\t";
		SetConsoleTextAttribute(hm, 0 | BACKGROUND_BLUE);
		cout << "MARK SHEET" << "\n\n";

		cout << "\t\t\t\t";
		SetConsoleTextAttribute(hm, 0 | BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED | BACKGROUND_INTENSITY);
		cout << "Grand Total";
		SetConsoleTextAttribute(hm, 15);
		cout << "   " << gt << "%" << "\n\n";

		cout << "\t\t\t\t";
		SetConsoleTextAttribute(hm, 0 | BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED | BACKGROUND_INTENSITY);
		cout << "GPA";
		SetConsoleTextAttribute(hm, 15);
		cout << "   " << gpa << "\n\n";

		cout << "\t\t\t\t";
		SetConsoleTextAttribute(hm, 0 | BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED | BACKGROUND_INTENSITY);
		cout << "Grade";
		SetConsoleTextAttribute(hm, 15);
		cout << "   " << grade << "\n\n";
	}
}

//destructor
Registeration::~Registeration() {
	if (subject != nullptr)
		subject = nullptr;

	if (std != nullptr)
		std = nullptr;

	if (date != nullptr)
		delete date;
	--numOfRegisterations;
}