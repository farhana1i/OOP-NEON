#include<iostream>
#include"Course.h"
#include"TA.h"
using namespace std;
HANDLE HM = GetStdHandle(STD_OUTPUT_HANDLE);


//constructors
Course::Course() :courseCode(nullptr), courseName(nullptr), _TA(nullptr), listOfRegisteration(nullptr), currentNoOfReg(0), maxNoOfReg(50) {
	listOfRegisteration = new Registeration * [maxNoOfReg];
	for (int i = 0; i < currentNoOfReg; i++)
		listOfRegisteration[i] = nullptr;
}
Course::Course(const char* _courseName, const char* _courseCode, TA* _ta) {
	maxNoOfReg = 50;
	currentNoOfReg = 0;
	listOfRegisteration = new Registeration * [maxNoOfReg];

	courseName = new char[strlen(_courseName) + 1];
	strcpy_s(courseName, strlen(_courseName) + 1, _courseName);

	courseCode = new char[strlen(_courseCode) + 1];
	strcpy_s(courseCode, strlen(_courseCode) + 1, _courseCode);
	
	_TA = _ta;
}
Course::Course(const Course& obj) {
	if (&obj != this) {
		if (obj.courseName != nullptr) {
			courseName = new char[strlen(obj.courseName) + 1];
			strcpy_s(courseName, strlen(obj.courseName) + 1, obj.courseName);
		}

		if (obj.courseCode != nullptr) {
			courseCode = new char[strlen(obj.courseCode) + 1];
			strcpy_s(courseCode, strlen(obj.courseCode) + 1, obj.courseCode);
		}

		currentNoOfReg = obj.currentNoOfReg;
		maxNoOfReg = obj.maxNoOfReg;
		listOfRegisteration = new Registeration * [maxNoOfReg];
		for (int i = 0; i < maxNoOfReg; i++)
			listOfRegisteration[i] = nullptr;

		for (int i = 0; i < currentNoOfReg; i++) {
			listOfRegisteration[i] = obj.listOfRegisteration[i];
		}
		_TA = nullptr;
		if (obj._TA != nullptr)
			_TA = new TA(*obj._TA);
	}
}

//overload insertion in file operator for "Course" class
ofstream& operator << (ofstream& _fout, const Course& obj) {
	_fout << obj.courseCode << ", " << obj.courseName << ", ";
	TA* ta = obj._TA;
	if (ta == nullptr)
		_fout << "0";
	else
		_fout << "1";

	_fout << endl;
	if (ta != nullptr) {
		_fout << ta->getEmployeeId() << ", " << ta->getRollNum() << endl;
		ta = nullptr;
	}
	return _fout;
}

//setters
void Course::setTA(TA* ta) {
	this->_TA = ta;
}
bool Course::setRegisteration(Registeration* r) {
	if (this != nullptr){
		if (currentNoOfReg < maxNoOfReg) {
			listOfRegisteration[currentNoOfReg++] = r;
			return true;
		}
	}
	return false;
}
void Course::setCourseName(const char* _courseName) {
	if (courseName != nullptr)
		delete[] courseName;
	courseName = new char[strlen(_courseName) + 1];
	strcpy_s(courseName, strlen(_courseName) + 1, _courseName);
}
void Course::setCourseCode(const char* _courseCode) {
	if (courseCode != nullptr)
		delete[] courseCode;
	courseCode = new char[strlen(_courseCode) + 1];
	strcpy_s(courseCode, strlen(_courseCode) + 1, _courseCode);
}

//getters
char* Course::getTAUsername() {
	if (_TA != nullptr)
		return _TA->getUserName();
	return 0;
}
char* Course::getTAPassword() {
	if (_TA != nullptr)
		return _TA->getPassword();
	return 0;
}
char* Course::getCourseName() { 
	if(this!=nullptr)
		return courseName;
	return 0;
}
char* Course::getCourseCode() { 
	if(this!=nullptr)
		return courseCode; 
	return 0;
}
TA* Course::getTA() { 
		return _TA; 
}
int Course::getTAEmployeeId() {
	if(_TA!=nullptr)
		return _TA->getEmployeeId();
	return 0;
}
int Course::getTAStudentId() { 
	return _TA->getRollNum(); 
}

//functionalities
void Course::viewAttendaceOfAllStudents() {
	if (this != nullptr) {
		cout << "\n\n\t\t\t";
		SetConsoleTextAttribute(HM, 0 | BACKGROUND_BLUE);
		cout << "Name";
		SetConsoleTextAttribute(HM, 15);

		cout << "\t\t\t";
		SetConsoleTextAttribute(HM, 0 | BACKGROUND_BLUE);
		cout << "Attendance Percentage\n\n";
		SetConsoleTextAttribute(HM, 15);
		for (int i = 0; i < currentNoOfReg; i++)
			if (listOfRegisteration[i] != nullptr) {
				cout << "\t\t\t";
				cout << listOfRegisteration[i]->getStudentFirstName() << " " << listOfRegisteration[i]->getStudentLastName() << "\t\t   " << listOfRegisteration[i]->GetAttendancePer() << "%" << endl;
			}
	}
}
void Course::viewEvaluationOfAllStudents() {
	for (int i = 0; i < currentNoOfReg; i++) {
		if (listOfRegisteration[i] != nullptr) {
			listOfRegisteration[i]->viewMarkSheet();
			cout << endl;
		}
	}
}
bool Course::manageAttendancePer(int stdRollNum, float _attPer) {
	for (int i = 0; i < currentNoOfReg; i++) {
		if (listOfRegisteration[i] != nullptr && listOfRegisteration[i]->getRollNumOfStd() == stdRollNum) {
			listOfRegisteration[i]->setAttendance(_attPer);
			return true;
		}
	}
	return false;
}
bool Course::assignGradesToStudents(int stdRollNum, char _grade) {
	for (int i = 0; i < currentNoOfReg; i++) {
		if (listOfRegisteration[i] != nullptr && listOfRegisteration[i]->getGrade() != 'W' && listOfRegisteration[i]->getRollNumOfStd() == stdRollNum) {
			listOfRegisteration[i]->setGrade(_grade);
			return true;
		}
	}
	return false;
}
bool Course::manageEvaluationOfAStudent(int stdRollNum, float _gpa, float _gt) {
	for (int i = 0; i < currentNoOfReg; i++) {
		if (listOfRegisteration[i] != nullptr && listOfRegisteration[i]->getRollNumOfStd() == stdRollNum) {
			listOfRegisteration[i]->setGPA(_gpa);
			listOfRegisteration[i]->setGT(_gt);
			return true;
		}
	}
	return false;
}

//destructor
Course::~Course() {
	if (courseName != nullptr) {
		delete[] courseName;
	}

	if (courseCode != nullptr) {
		delete[] courseCode;
	}

	if (_TA != nullptr)
		 _TA = nullptr;

	for (int i = 0; i < currentNoOfReg; i++)
		if (listOfRegisteration[i] != nullptr)
			listOfRegisteration[i] = nullptr;
	if (listOfRegisteration != nullptr)
		delete[] listOfRegisteration;
}