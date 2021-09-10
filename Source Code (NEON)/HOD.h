#ifndef HOD_H
#define HOD_H
#include"Teacher.h"

class HOD : public Teacher {
public:

	//constructors
	HOD();
	HOD(const char* _fname, const char* _lname, int _id, int _age, int _maxNumOfCourses, const char* _userName = nullptr, const char* _password = nullptr);
	HOD(const HOD& obj);

};
#endif