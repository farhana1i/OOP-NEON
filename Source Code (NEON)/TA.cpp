#include "TA.h"
#include"Course.h"

//constructors
TA::TA() : Student(), Teacher(), Person() {}
TA::TA(const char* _fname, const char* _lname, int _age, int _rollNum, int _teacherId, int _maxNumOfCourse, const char* _userName, const char* _password) : Student(_fname, _lname, _rollNum, _age, _userName, _password), Teacher(_fname, _lname, _teacherId, _age, _maxNumOfCourse, _userName, _password), Person(_fname, _lname, _age, _userName, _password) {}
TA::TA(const TA& obj) : Student(obj), Teacher(obj), Person(obj) {}

//print data of a TA
void TA::print() {
	if (this != nullptr) {
		Student::print();
		cout << "Employee ID: " << id << endl;

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

//overload insertion in file operator for "TA" class
ofstream& operator<<(ofstream& _fout, const TA& obj) {
	if (&obj != nullptr) {
		_fout << (Employee)obj<<", ";
		_fout << obj.maxNumOfCourses << endl;

		_fout << obj.currentNumOfCourses << endl;

		for (int j = 0; j < obj.currentNumOfCourses; j++)
			_fout << obj.listOfCourses[j]->getCourseCode() << endl;
	}
	return _fout;
}