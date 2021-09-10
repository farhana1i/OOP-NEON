#ifndef UNIVERSITY_H
#define UNIVERSITY_H

#include<iostream>
#include<iomanip>
#include<conio.h>
#include<cstring>
#include"Department.h"
#include"Exceptions.h"

using namespace std;


class University{
	char* name;											//	name of a university
	Department** listOfDepartments;						//	list of departments in a university
	int maxDepartment;
	int currentDepartment;

public:

	//constructors
	University();
	University(const char* _name, int _maxDepartment);

	//add department in a university
	bool addDepartment(const char* dep_name, IT_Manager* _it_manager, HOD* _Hod, int _maxTeachers, int _maxStudents, int _maxCourses);
	
	//setters
	void setName(const char* _name);
	void setMaxDepartment(int n);
	void setCurrentDepartment(int n);

	//getters
	char* getName();
	int getMaxDepartment();
	int getCurrentDepartment();

	//Login System
	void LoginControl();
	int loginMode(const char* dep, int i);
	int HODLogin(int i);
	int itManagerLogin(const char* dep, int i);
	int teacherLogin(int i, const char* username, const char* _password);
	int studentLogin(int i, const char* username, int std_ID);
	int taLogin(int i, const char* username, const char* courseCode);
	
	//loads data from a file
	void loadData();

	//prints functionalities of different entities
	void printDepartmentName();
	void printChoice();
	void printHODChoice();
	void printITManagerChoice();
	void printIT_SubChoice();
	void printTeacherChoice();
	void printStudentChoice();
	void printTAChoice();
	void printInstructions();
	void printNonRegCourses(int index, char choice, int ID);
	void printEntity(int index, char choice);

	//print detail of available courses
	void printCourses(int index, char choice, int ID = 0);

	//gets user choice
	int getChoice(char mode, int total_buttons);
	
	//destructor
	~University();
};

#endif