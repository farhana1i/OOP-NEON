#ifndef EMPLOYEE_H
#define EMPLOYEE_H
#include"Person.h"
#include"Registeration.h"

class Course;

class Employee : virtual public Person {
protected:
	int id;
public:

	//constructors
	Employee();
	Employee(const char* _fname, const char* _lname, int id, int _age, const char* _userName = nullptr, const char* _password = nullptr);
	Employee(const Employee& obj);
	
	//setter
	void setEmployeeId(int _id);
	
	//getter
	int getEmployeeId();

	//overload insertion in file operator for "Employee" class
	friend ofstream& operator << (ofstream& _fout, const Employee& obj);
	
	//virtual function to print data of an employee
	virtual void print();

	//destructor
	~Employee();
};

#endif