#ifndef TEACHER_H
#define TEACHER_H
#include"Employee.h"

class Course;
class TA;

class Teacher : public Employee {
protected:
	Course** listOfCourses;
	int maxNumOfCourses;
	int currentNumOfCourses;
public:

	//constructors
	Teacher();
	Teacher(const char* _fname, const char* _lname, int _id, int _age, int _maxNumOfCourses, const char* _userName = nullptr, const char* _password = nullptr);
	Teacher(const Teacher& obj);
	
	//overload insertion in file operator for "Teacher" class
	friend ofstream& operator<<(ofstream& _fout, const Teacher& obj);

	//setters
	void setMaxCourse(int n);
	void setCurrentCourse(int n);
	bool setCourse(Course* c);
	
	//getters
	int getCurrentNumOfCourses();
	int getMaxNumOfCourses();
	char* getCourseCode(int index);
	char* getCourseName(int index);

	//check for existence of a specific course
	bool isCourseExist(const char* courseCode);
	
	//print data of a teacher
	void print();

	//Teacher's Functionalities
	void viewAttendance(const char* _courseCode);
	void viewEvaluationOfAllStudents(const char* _courseCode);
	
	//Destructors
	~Teacher();
};

#endif
