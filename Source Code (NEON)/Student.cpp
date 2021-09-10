#include<iostream>
#include "Student.h"
#include"Registeration.h"
#include"Helper.h"
using namespace std;

HANDLE hm1 = GetStdHandle(STD_OUTPUT_HANDLE);


//constructors
Student::Student() :rollNum(0), listOfRegisteration(nullptr), currentNoOfReg(0), maxNoOfReg(5), Person() {
	listOfRegisteration = new Registeration * [maxNoOfReg];
	for (int i = 0; i < maxNoOfReg; i++)
		listOfRegisteration[i] = nullptr;
	
}
Student::Student(const char* _fname, const char* _lname, int _rollNum, int age, const char* _userName, const char* _password) :Person(_fname, _lname, age, _userName, _password) {
	rollNum = _rollNum;
	maxNoOfReg = 5;
	listOfRegisteration = new Registeration * [maxNoOfReg];
	for (int i = 0; i < maxNoOfReg; i++)
		listOfRegisteration[i] = nullptr;
	currentNoOfReg = 0;
}
Student::Student(const Student& obj) :Person(obj) {
	rollNum = obj.rollNum;

	maxNoOfReg = obj.maxNoOfReg;
	currentNoOfReg = obj.currentNoOfReg;
	listOfRegisteration = new Registeration * [obj.maxNoOfReg];

	for (int i = 0; i < currentNoOfReg; i++) {
		if (obj.listOfRegisteration[i] != nullptr) {
			listOfRegisteration[i] = obj.listOfRegisteration[i];
		}
	}
}
 
//overload insertion in file operator for "Student" class
ofstream& operator<< (ofstream& _fout, Student& obj) {
	if (&obj != nullptr) {
		_fout << obj.userName << ", " << obj.password << ", " << obj.rollNum << ", " << 
			obj.name << ", " << obj.age << ", "
			<< obj.maxNoOfReg << endl;

		_fout <<obj.currentNoOfReg << endl;
		for (int j = 0; j < obj.currentNoOfReg; j++) {
			_fout << obj.getRegisterationId(j) << ", " << obj.getCourseCode(j) << ", "
				<< obj.getGPA(obj.getCourseCode(j)) << ", "<< obj.getGrade(obj.getCourseCode(j)) << ", "
				<< obj.getGT(obj.getCourseCode(j)) << ", "<< obj.getAttendance(obj.getCourseCode(j));
			
			_fout << endl;
			
			_fout << obj.getRegisteraion(j)->getYear() << " "
				<< obj.getRegisteraion(j)->getMonth() << " "
				<< obj.getRegisteraion(j)->getDay() << endl;
		}
	}
	return _fout;
}

//Student's Functionalities
bool Student::registerCourse(Registeration* r) {
	if (currentNoOfReg < maxNoOfReg) {
		bool res = true;
		for (int i = 0; i < currentNoOfReg; i++) {
			if (listOfRegisteration[i] != nullptr && !strcmp(listOfRegisteration[i]->getCourseCode(), r->getCourseCode())) {
				res = false;
				break;
			}
		}
		if (res) {
			listOfRegisteration[currentNoOfReg++] = r;
			return true;
		}
	}
	return false;
}
bool Student::unRegisterCourse(const char* _courseCode) {
	for (int i = 0; i < currentNoOfReg; i++) {
		if (listOfRegisteration[i] != nullptr && !strcmp(_courseCode, listOfRegisteration[i]->getCourseCode())) {
			if (listOfRegisteration[i] != nullptr) {
				delete listOfRegisteration[i];
			}

			for (int j = i; j < currentNoOfReg - 1; j++) {
				listOfRegisteration[j] = listOfRegisteration[j + 1];
			}
			--currentNoOfReg;
			if (listOfRegisteration[currentNoOfReg] != nullptr)
				listOfRegisteration[currentNoOfReg] = nullptr;
			return true;
		}
	}
	return false;
}
bool Student::withdrawCourse(const char* _courseCode) {
	for (int i = 0; i < currentNoOfReg; ++i) {
		if (listOfRegisteration[i] != nullptr && !strcmp(_courseCode, listOfRegisteration[i]->getCourseCode())) {
			listOfRegisteration[i]->setGrade('W');
			return true;
		}
	}
	return false;
}
bool Student::setAttendance(const char* _courseCode, float attendance) {
	for (int i = 0; i < currentNoOfReg; i++) {
		if (listOfRegisteration[i] != nullptr && !strcmp(listOfRegisteration[i]->getCourseCode(), _courseCode)) {
			listOfRegisteration[i]->setAttendance(attendance);
			return true;
		}
	}
	return false;
}
void Student::viewAttendance(const char* courseCode) {
	cout << endl << endl;
	for (int i = 0; i < currentNoOfReg; i++) {
		if (listOfRegisteration[i] != nullptr && !strcmp(listOfRegisteration[i]->getCourseCode(), courseCode)) {
			cout << "\t\t";
			SetConsoleTextAttribute(hm1, 0 | BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED | BACKGROUND_INTENSITY);
			cout << "Attendance Percentage";
			cout << "\t\t";
			SetConsoleTextAttribute(hm1, 15);
			cout << "   " << listOfRegisteration[i]->GetAttendancePer() << endl;
			break;
		}
	}
}
void Student::viewMarkSheet(const char* _courseCode) {
	for (int i = 0; i < currentNoOfReg; i++) {
		if (listOfRegisteration[i] != nullptr && !strcmp(_courseCode, listOfRegisteration[i]->getCourseCode())) {
			listOfRegisteration[i]->viewMarkSheet();
			break;
		}
	}
}


//getters
Registeration* Student::getRegisteraion(int index) {
	if (index >= 0 && index < maxNoOfReg) {
		return listOfRegisteration[index];
	}
	return 0;
}
char* Student::getCourseCode(int index) {
	try {
		if (index < 0)
			throw "Index Is Negative";
		else if (index >= maxNoOfReg)
			throw "Index Is Greater Than Or Equal To Size";

		return listOfRegisteration[index]->getCourseCode();
	}
	catch (const char* message) {
		cout << "Exception throw: " << message << endl;
	}
	return 0;
}
char* Student::getCourseName(int index) {
	try {
		if (index < 0)
			throw "Index Is Negative";
		else if (index >= maxNoOfReg)
			throw "Index Is Greater Than Or Equal To Size";

		return listOfRegisteration[index]->getCourseName();
	}
	catch (const char* message) {
		cout << "Exception throw: " << message << endl;
	}
	return 0;
}
int Student::getRollNumOfStd(int index) {
	try {
		if (index < 0)
			throw "Index Is Negative";
		else if (index >= maxNoOfReg)
			throw "Index Is Greater Than Or Equal To Size";

		return listOfRegisteration[index]->getRollNumOfStd();
	}
	catch (const char* message) {
		cout << "Exception throw: " << message << endl;
	}
	return 0;
}
float Student::getGPA(const char* _courseCode) {
	for (int i = 0; i < currentNoOfReg; i++) {
		if (listOfRegisteration[i] != nullptr && !strcmp(_courseCode, listOfRegisteration[i]->getCourseCode()))
			return  listOfRegisteration[i]->getGPA();
	}
	return 0.0;
}
float Student::getGT(const char* _courseCode) {
	for (int i = 0; i < currentNoOfReg; i++) {
		if (listOfRegisteration[i] != nullptr && !strcmp(_courseCode, listOfRegisteration[i]->getCourseCode()))
			return  listOfRegisteration[i]->getGT();
	}
	return 0.0;
}
float Student::getAttendance(const char* _courseCode) {
	for (int i = 0; i < currentNoOfReg; i++) {
		if (listOfRegisteration[i] != nullptr && !strcmp(_courseCode, listOfRegisteration[i]->getCourseCode()))
			return listOfRegisteration[i]->GetAttendancePer();
	}
	return 0.0;
}
char Student::getGrade(const char* _courseCode) {
	for (int i = 0; i < currentNoOfReg; i++) {
		if (listOfRegisteration[i] != nullptr && !strcmp(_courseCode, listOfRegisteration[i]->getCourseCode()))
			return listOfRegisteration[i]->getGrade();
	}
	return 0;
}
int Student::getRollNum() {
	if (this != nullptr)
		return rollNum;
	return 0;
}
int Student::getCurrentNoOfReg() {
	if (this != nullptr)
		return currentNoOfReg;
	return 0;
}
int Student::getMaxReg() {
	if (this != nullptr)
		return maxNoOfReg;
	return 0;
}
int Student::getRegisterationId(int index) {
	try {
		if (index < 0)
			throw "Index Is Negative";
		else if (index >= maxNoOfReg)
			throw "Index Is Greater Than Or Equal To Size";

		return listOfRegisteration[index]->getRegNum();
	}
	catch (const char* message) {
		cout << "Exception throw: " << message << endl;
	}
	return 0;
}


//setters
void Student::setRollNum(int n) {
	rollNum = n;
}
bool Student::setGrade(const char* _courseCode, char ch) {
	for (int i = 0; i < currentNoOfReg; i++) {
		if (listOfRegisteration[i] != nullptr && !strcmp(listOfRegisteration[i]->getCourseCode(), _courseCode)) {
			listOfRegisteration[i]->setGrade(ch);
			return true;
		}
	}
	return false;
}
bool Student::setGT(const char* _courseCode, float _gt) {
	for (int i = 0; i < currentNoOfReg; i++) {
		if (listOfRegisteration[i] != nullptr && !strcmp(listOfRegisteration[i]->getCourseCode(), _courseCode)) {
			listOfRegisteration[i]->setGT(_gt);
			return true;
		}
	}
	return false;
}
bool Student::setGPA(const char* _courseCode, float _gpa) {
	for (int i = 0; i < currentNoOfReg; i++) {
		if (listOfRegisteration[i] != nullptr && !strcmp(listOfRegisteration[i]->getCourseCode(), _courseCode)) {
			listOfRegisteration[i]->setGPA(_gpa);
			return true;
		}
	}
	return false;
}

//check that a given course is register or not
bool Student::isCourseExist(const char* _courseCode) {
	for (int i = 0; i < currentNoOfReg; i++) {
		if (listOfRegisteration[i] != nullptr && !strcmp(listOfRegisteration[i]->getCourseCode(), _courseCode))
			return true;
	}
	return false;
}

//print data of a student
void Student::print() {
	if (this != nullptr) {
		cout << "Name: " << name << endl;
		cout << "Age: " << age << endl;
		cout << "Roll Num: " << rollNum << endl;
		cout << "Registerations: " << currentNoOfReg << endl;

		if (currentNoOfReg > 0)
			cout << "Register Courses: \n\n";

		for (int i = 0; i < currentNoOfReg; i++)
			if (listOfRegisteration[i] != nullptr) {
				cout << "\t" << i + 1 << "_\t"
					<< listOfRegisteration[i]->getCourseName()
					<< endl;
			}
	}
}

//Destructor
Student::~Student() {
	for (int i = 0; i < currentNoOfReg; i++)
		if (listOfRegisteration[i] != nullptr)
			listOfRegisteration[i] = nullptr;
	if (listOfRegisteration != nullptr)
		delete[] listOfRegisteration;
}