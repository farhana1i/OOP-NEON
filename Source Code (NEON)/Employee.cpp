#include<iostream>
#include "Employee.h"
#include"Department.h"
#include"Course.h"
#include"Helper.h"
using namespace std;

//constructors
Employee::Employee() :id(0), Person() {}
Employee::Employee(const char* _fname, const char* _lname, int _id, int _age, const char* _userName, const char* _password) : Person(_fname, _lname, _age, _userName, _password) {
	id = _id;
}
Employee::Employee(const Employee& obj) :Person(obj) {
	id = obj.id;
}

//overload insertion in file operator for "Employee" class
ofstream& operator << (ofstream& _fout, const Employee& obj) {
	if (&obj != nullptr) {
		_fout << obj.userName << ", " << obj.password << ", "
			<< obj.id << ", " << obj.name << ", " << obj.age;
	}
	return _fout;
}

//setter
void Employee::setEmployeeId(int _id) { id = _id; }

//getter
int Employee::getEmployeeId() { return id; }

//print data of an employye
void Employee::print() {
	if (this != nullptr) {
		cout << "Name: " << name << endl;
		cout << "Age: " << age << endl;
		cout << "Employee ID: " << id << endl;
	}
}

//Destructor
Employee::~Employee() {}
