#ifndef COURSE_H
#define COURSE_H
#include<cstring>
#include"Registeration.h"
#include<fstream>

class TA;

class Course {
	char* courseCode;
	char* courseName;
	TA* _TA;				//Teaching Assistant of a course

	Registeration** listOfRegisteration;
	int maxNoOfReg;
	int currentNoOfReg;
public:

	//constructors
	Course();
	Course(const char* _courseName, const char* _courseCode, TA* _TA);
	Course(const Course& obj);
	
	//overload insertion in file operator for "Course" class
	friend ofstream& operator << (ofstream & _fout, const Course & obj);

	//setters
	bool setRegisteration(Registeration* r);
	void setCourseName(const char* _courseName);
	void setCourseCode(const char* _courseCode);
	void setTA(TA* _TA = nullptr);

	//getters
	char* getCourseName();
	char* getCourseCode();
	TA* getTA();
	int getTAEmployeeId();
	int getTAStudentId();
	char* getTAUsername();
	char* getTAPassword();

	//functionalities
	void viewAttendaceOfAllStudents();
	void viewEvaluationOfAllStudents();
	bool manageAttendancePer(int stdRollNum, float _attPer);
	bool assignGradesToStudents(int stdRollNum, char _grade);
	bool manageEvaluationOfAStudent(int stdRollNum, float _gpa, float _gt);
	
	//destructor
	~Course();
};
#endif