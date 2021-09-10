#ifndef PERSON_H
#define PERSON_H
#include<cstring>
#include<iostream>
#include"Helper.h"
using namespace std;

				/***************************************************/
				/*********	    	Name Class		   *********/
				/***************************************************/

class Name {
	char* fName;			//	first name
	char* lName;			//	last name
public:

	//constructors
	Name();
	Name(const char* fN, const char* lN);
	Name(const Name& obj);

	//setters
	void setFirstName(const char* fN);
	void setLastName(const char* lN);
	
	//getters
	char* getFirstName();
	char* getLastName();

	//overload assignent operator for "Name" class
	Name& operator=(const Name& obj);

	//overload insertion operator for "Name" class
	friend ostream& operator<<(ostream& _cout, const Name& obj);

	//destructor
	~Name();
};



			/***************************************************/
			/*********	    	Person Class		   *********/
			/***************************************************/

class Person {
protected:
	Name name;					//	name of a person
	int age;					//	age of a person
	char* password;
	char* userName;
public:

	//constructors
	Person();
	Person(const char* _fname, const char* _lname, int _age, const char* username=nullptr, const char* password = nullptr);
	Person(const Person& obj);
	
	//setters
	void setAge(int _age);
	void setFirstName(const char* fN);
	void changeUserName(const char* _userName);
	void changePassword(const char* _password);
	void setLastName(const char* lN);

	//getters
	int getAge();
	char* getFirstName();
	char* getLastName();
	char* getUserName();
	char* getPassword();

	//Friend Function
	friend ostream& operator<<(ostream& _cout, const Person& obj);

	//pure virtual function
	virtual void print() = 0;

	//virtual destructor
	virtual ~Person();
};

#endif