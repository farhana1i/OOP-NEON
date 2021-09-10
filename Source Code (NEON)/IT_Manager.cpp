#include "IT_Manager.h"

//constructors
IT_Manager::IT_Manager() : Employee(), Person() {}
IT_Manager::IT_Manager(const char* _fname, const char* _lname, int _id, int _age, const char* _userName, const char* _password) : Employee(_fname, _lname, _id, _age, _userName, _password), Person(_fname, _lname, _age, _userName, _password) {}
IT_Manager::IT_Manager(const IT_Manager& obj) : Employee(obj), Person(obj) {}

