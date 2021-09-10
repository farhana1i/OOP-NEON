#include<iostream>
#include "HOD.h"
using namespace std;

//constructors
HOD::HOD() : Teacher(), Person() {}
HOD::HOD(const char* _fname, const char* _lname, int _id, int _age, int _maxNumOfCourses, const char* _userName, const char* _password) : Teacher(_fname, _lname, _id, _age, _maxNumOfCourses, _userName, _password), Person(_fname, _lname, _age, _userName, _password) {}
HOD::HOD(const HOD& obj) : Teacher(obj), Person(obj) {}

