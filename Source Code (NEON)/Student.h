#ifndef STUDENT_H
#define STUDENT_H
#include"Person.h"
#include<fstream>
class Registeration;

class Student : virtual public Person {
	int rollNum;
	Registeration** listOfRegisteration;
	int maxNoOfReg;
	int currentNoOfReg;

public:
	
	//constructors
	Student();
	Student(const char* _fname, const char* _lname, int _rollNum, int age, const char* _userName = nullptr, const char* _password = nullptr);
	Student(const Student& obj);
	
	//overload insertion in file operator for "Student" class
	friend ofstream& operator<< (ofstream& _fout, Student& obj);
	
	//Student's Functionalities
	bool registerCourse(Registeration* r);
	bool unRegisterCourse(const char* _courseCode);
	bool withdrawCourse(const char* _courseCode);
	void viewAttendance(const char* courseCode);
	void viewMarkSheet(const char* _courseCode);


	//setters
	bool setGrade(const char* _userName, char ch);
	bool setGT(const char* _userName, float _gt);
	bool setGPA(const char* _userName, float _gpa);
	bool setAttendance(const char* _courseCode, float attendance);
	void setRollNum(int n);
	
	//getters
	float getGPA(const char* _courseCode);
	float getGT(const char* _courseCode);
	float getAttendance(const char* _courseCode);
	char getGrade(const char* _courseCode);
	int getRollNum();
	int getCurrentNoOfReg();
	int getMaxReg();
	int getRegisterationId(int index);
	char* getCourseCode(int index);
	char* getCourseName(int index);
	int getRollNumOfStd(int index);
	Registeration* getRegisteraion(int index);
	
	//check that a given course is register or not
	bool isCourseExist(const char* courseCode);

	//virtiual function to print data of a student
	virtual void print();

	//destructor
	~Student();
};

#endif