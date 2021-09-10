#ifndef REGISTERATION_H
#define REGISTERATION_H
#include"Student.h"
#include"Date.h"
class Course;

class Registeration
{
	int reg_Num;						//	registeration number
	float gpa;							//	gpa of a student of register course
	Student* std;						//	register student
	Course* subject;					//	register course
	float attendance_Percentage;		//	attendance of a student of register course
	float gt;							//	gt of a student	of register course
	char grade;							//	grade of a student of register course
	Date* date;							//	actual date of registeration

	static int numOfRegisterations;		//	static variable to keep
										//	count of number of registerations
public:

	//constructors
	Registeration();
	Registeration(int reg_Num, Student* s, Course* c, int y = 0, int m = 0, int d = 0);
	Registeration(const Registeration& obj);
		
	//setters
	void setGPA(float _gpa);
	void setGT(float _gt);
	void setAttendance(float attendance_Percentage);
	void setGrade(char g);
	void setStudent(Student* s);

	//getters
	char getGrade();
	float getGT();
	float GetAttendancePer();
	float getGPA();
	int getRegNum();
	int getRollNumOfStd();
	int getDay();
	int getMonth();
	int getYear();
	Date* getDate();
	char* getStudentFirstName();
	char* getStudentLastName();
	char* getCourseName();
	char* getCourseCode();
	
	//view marks of a student of register course
	void viewMarkSheet();

	//destructors
	~Registeration();
};

#endif