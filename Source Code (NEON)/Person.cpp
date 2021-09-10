#include "Person.h"

		/***************************************************/
		/*********	    	Name Class		       *********/
		/***************************************************/

//constructors
Name::Name() :fName(nullptr), lName(nullptr) {}
Name::Name(const char* fN, const char* lN) {
	fName = new char[strlen(fN) + 1];
	strcpy_s(fName, strlen(fN) + 1, fN);

	lName = new char[strlen(lN) + 1];
	strcpy_s(lName, strlen(lN) + 1, lN);
}
Name::Name(const Name& obj) {
	if (obj.fName != nullptr) {
		fName = new char[strlen(obj.fName) + 1];
		strcpy_s(fName, strlen(obj.fName) + 1, obj.fName);
	}
	else
		fName = nullptr;

	if (obj.lName != nullptr) {
		lName = new char[strlen(obj.lName) + 1];
		strcpy_s(lName, strlen(obj.lName) + 1, obj.lName);
	}
	else
		lName = nullptr;
}

//overload assignment operator for "Name" class
Name& Name::operator=(const Name& obj) {
	if (this != &obj) {
		if (fName != nullptr)
			delete[] fName;
		if (obj.fName != nullptr) {
			fName = new char[strlen(obj.fName) + 1];
			strcpy_s(fName, strlen(obj.fName) + 1, obj.fName);
		}

		if (lName != nullptr)
			delete[] lName;

		if (obj.lName != nullptr) {
			lName = new char[strlen(obj.lName) + 1];
			strcpy_s(lName, strlen(obj.lName) + 1, obj.lName);
		}
	}
	return *this;
}

//overload insertion operator for "Name" class
ostream& operator<<(ostream& _cout, const Name& obj) {
	if (&obj != nullptr) {
		_cout << obj.fName << " " << obj.lName;
	}
	return _cout;
}

//setters
void Name::setFirstName(const char* fN) {
	if (fName != nullptr)
		delete[] fName;

	if (fN != nullptr) {
		fName = new char[strlen(fN) + 1];
		strcpy_s(fName, strlen(fN) + 1, fN);
	}
}
void Name::setLastName(const char* lN) {
	if (lName != nullptr)
		delete[] lName;

	if (lN != nullptr) {
		lName = new char[strlen(lN) + 1];
		strcpy_s(lName, strlen(lN) + 1, lN);
	}
}

//getters
char* Name::getFirstName() { return fName; }
char* Name::getLastName() { return lName; }

//destructors
Name::~Name() {
	if (fName != nullptr)
		delete[] fName;
	if (lName != nullptr)
		delete[] lName;
}



		/***************************************************/
		/*********	    	Person Class		   *********/
		/***************************************************/

//constructors
Person::Person() : age(0) {
	Helper::generateUserName(userName);
	Helper::generatePassword(password);
}
Person::Person(const char* _fname, const char* _lname, int _age, const char* _userName, const char* _password) : name(_fname, _lname), age(_age) {
	if (_userName == nullptr)
		Helper::generateUserName(userName);
	else {
		userName = new char[strlen(_userName) + 1];
		strcpy_s(userName, strlen(_userName) + 1, _userName);
	}

	if (_password == nullptr)
		Helper::generatePassword(password);
	else {
		password = new char[strlen(_password) + 1];
		strcpy_s(password, strlen(_password) + 1, _password);
	}
}
Person::Person(const Person& obj) : name(obj.name) {
	age = obj.age;
	if (obj.userName != nullptr) {
		userName = new char[strlen(obj.userName) + 1];
		strcpy_s(userName, strlen(obj.userName) + 1, obj.userName);
	}
	else
		userName = nullptr;

	if (obj.password != nullptr) {
		password = new char[strlen(obj.password) + 1];
		strcpy_s(password, strlen(obj.password) + 1, obj.password);
	}
	else
		password = nullptr;
}


//setters
void Person::changeUserName(const char* _userName) {
	if (userName != nullptr)
		delete[] userName;
	if (_userName != nullptr) {
		userName = new char[strlen(_userName) + 1];
		strcpy_s(userName, strlen(_userName) + 1, _userName);
	}
}
void Person::changePassword(const char* _password) {
	if (password != nullptr)
		delete[] password;
	if (_password != nullptr) {
		password = new char[strlen(_password) + 1];
		strcpy_s(password, strlen(_password) + 1, _password);
	}
}
void Person::setAge(int _age) { age = _age; }
void Person::setFirstName(const char* fN) { name.setFirstName(fN); }
void Person::setLastName(const char* lN) { name.setLastName(lN); }

//getters
char* Person::getUserName() {
	if (this != nullptr)
		return userName;
	return 0;
}
char* Person::getPassword() {
	if (this != nullptr)
		return password;
	return 0;
}
int Person::getAge() { return age; }
char* Person::getFirstName() { return name.getFirstName(); }
char* Person::getLastName() { return name.getLastName(); }

//overload << operator for person class
ostream& operator<<(ostream& _cout, const Person& obj) {
	if (&obj != nullptr) {
		cout<<"Name: " << obj.name<<endl;
		cout << "Age: " << obj.age<<endl;
	}
	return _cout;
}

//Destructors
Person::~Person() {
	if (userName != nullptr)
		delete[] userName;
	if (password != nullptr)
		delete[] password;
}