#include<cstring>
#include "Teacher.h"
#include"Course.h"
#include"TA.h"
#include"Template.h"


//constructors
Teacher::Teacher() : listOfCourses(nullptr), currentNumOfCourses(0), maxNumOfCourses(15), Employee(),Person() {
	listOfCourses = new Course * [maxNumOfCourses];
	for (int i = 0; i < maxNumOfCourses; i++)
		listOfCourses[i] = nullptr;
}
Teacher::Teacher(const char* _fname, const char* _lname, int _id, int _age, int _maxNumOfCourses, const char* _userName, const char* _password) : Employee(_fname, _lname, _id, _age, _userName, _password), Person(_fname, _lname, _age, _userName, _password) {
	maxNumOfCourses = _maxNumOfCourses;
	listOfCourses = new Course * [maxNumOfCourses];
	currentNumOfCourses = 0;
}
Teacher::Teacher(const Teacher& obj) : Employee(obj),Person(obj) {
	for (int i = 0; i < currentNumOfCourses; i++)
		if (listOfCourses[i] != nullptr)
			listOfCourses[i] = nullptr;
	if (listOfCourses != nullptr)
		delete[] listOfCourses;

	maxNumOfCourses = obj.maxNumOfCourses;
	currentNumOfCourses = obj.currentNumOfCourses;
	listOfCourses = new Course * [maxNumOfCourses];
	for (int i = 0; i < currentNumOfCourses; i++) {
		if (obj.listOfCourses[i] != nullptr) {
			listOfCourses[i] = obj.listOfCourses[i];
		}
	}
}

//overload insertion operator for "Teacher" class
ofstream& operator<<(ofstream& _fout, const Teacher& obj) {
	if (&obj != nullptr) {
		_fout << (Employee)obj<<", ";
		_fout << obj.maxNumOfCourses<<endl;

		_fout << obj.currentNumOfCourses << endl;

		for (int j = 0; j < obj.currentNumOfCourses; j++)
			_fout << obj.listOfCourses[j]->getCourseCode()<< endl;
	}
	return _fout;
}

//check for existence of a specific course
bool Teacher::isCourseExist(const char* courseCode) {
	for (int i = 0; i < currentNumOfCourses; i++) {
		if (listOfCourses[i] != nullptr && !strcmp(listOfCourses[i]->getCourseCode(), courseCode)) {
			return true;
		}
	}
	return false;
}

//print data of a teacher
void Teacher::print() {
	if (this != nullptr) {
		//first print data of employee
		Employee::print();
		cout << "Number Of Courses: " << currentNumOfCourses << endl;

		if (currentNumOfCourses > 0)
			cout << "Assign Courses: \n\n";
		for (int i = 0; i < currentNumOfCourses; i++) {
			if (listOfCourses[i] != nullptr) {
				cout << "\t" << i + 1 << "_\t"
					<< listOfCourses[i]->getCourseName()
					<< endl;
			}
		}
	}
}

//setters
void Teacher::setCurrentCourse(int n) { 
	try {
		if (n < 0)
			throw "Passed Size Of Current Number Of Courses Is Negative";
		else if (n >= currentNumOfCourses)
			throw "Passed Size Of Current Number Of Courses Is Greater Than Or Equal To Maximum Courses";

		//set Current number Of courses to n
		currentNumOfCourses = n;
	}
	catch (const char* message) {
		cout << "Exception throw: " << message << endl;
	}
 }
void Teacher::setMaxCourse(int n) {
	//grow maximum size of list of courses
	 listOfCourses = Template<Course>::growSize(listOfCourses, maxNumOfCourses, n);
}
bool Teacher::setCourse(Course* c) {
	if (currentNumOfCourses < maxNumOfCourses) {
		bool res = true;
		for (int i = 0; i < currentNumOfCourses; i++) {
			if (listOfCourses[i] != nullptr && !strcmp(listOfCourses[i]->getCourseCode(), c->getCourseCode())) {
				res = false;
				break;
			}
		}
		if (res) {
			listOfCourses[currentNumOfCourses++] = c;
			return true;
		}
	}
	return false;
}

//getters
int Teacher::getCurrentNumOfCourses() { return currentNumOfCourses; }
int Teacher::getMaxNumOfCourses() { return maxNumOfCourses; }
char* Teacher::getCourseCode(int index) {
	if (index >= 0 && index < currentNumOfCourses)
		return listOfCourses[index]->getCourseCode();
	return nullptr;
}
char* Teacher::getCourseName(int index) {
	if (index >= 0 && index < currentNumOfCourses)
		return listOfCourses[index]->getCourseName();
	return nullptr;
}

//Teacher's Fuctionalities
void Teacher::viewEvaluationOfAllStudents(const char* _courseCode) {
	for (int i = 0; i < currentNumOfCourses; i++) {
		if (listOfCourses[i] != nullptr && !strcmp(listOfCourses[i]->getCourseCode(), _courseCode)) {
			listOfCourses[i]->viewEvaluationOfAllStudents();
			break;
		}
	}
}
void Teacher::viewAttendance(const char* _courseCode) {
	for (int i = 0; i < currentNumOfCourses; i++) {
		if (listOfCourses[i] != nullptr && !strcmp(listOfCourses[i]->getCourseCode(), _courseCode)) {
			listOfCourses[i]->viewAttendaceOfAllStudents();
			break;
		}
	}
}

//Destructor
Teacher::~Teacher() {
	for (int i = 0; i < currentNumOfCourses; i++)
		if (listOfCourses[i] != nullptr)
			listOfCourses[i] = nullptr;
	if (listOfCourses != nullptr)
		delete[] listOfCourses;
}

