#ifndef IT_MANAGER_H
#define IT_MANAGER_H
#include"Teacher.h"

class IT_Manager : public Employee {
public:

	//constructors
	IT_Manager();
	IT_Manager(const char* _fname, const char* _lname, int _id, int _age, const char* _userName = nullptr, const char* _password = nullptr);
	IT_Manager(const IT_Manager& obj);
};

#endif