#ifndef TA_H
#define TA_H

#include"Student.h"
#include"Teacher.h"

class TA : public Student, public Teacher {
public:

	//constructors
	TA();
	TA(const char* _fname, const char* _lname, int _age, int _rollNum, int _teacherId, int _maxNumOfCourses, const char* _userName = nullptr, const char* _password = nullptr);
	TA(const TA& obj);

	//overload insertion in file operator for "TA" class
	friend ofstream& operator<<(ofstream& _fout , const TA& obj);

	//print data of a TA
	void print();
};
#endif