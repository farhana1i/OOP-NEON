#ifndef DEPARTMENT_H
#define DEPARTMENT_H
#include"IT_Manager.h"
#include"HOD.h"
#include"Course.h"
#include"TA.h"
#include"Helper.h"
#include<iostream>
#include<fstream>
#include<cstring>
#include<iomanip>

class Department
{
	char* name;								//	name of a department
	IT_Manager* it_manager;					//	IT Manager in a department
	HOD* Hod;								//	HOD of a department
	
	Teacher** listOfTeachers;				//	Teachers in a department
	int maxTeachers;
	int currentTeachers;
	
	Student** listOfStudents;				//	Students in a department
	int maxStudents;
	int currentStudents;
	
	Course** listOfCourses;					//	Courses Available in a department
	int maxCourses;
	int currentCourses;

public:

	//constructors
	Department();
	Department(const char* _name, IT_Manager* _it_manager, HOD* _Hod, int _maxTeachers = 30, int _maxStudents = 100, int _maxCourses = 15);

	//add a course in list of courses
	bool addCourse(const char* courseCode, const char* courseName, TA* ta);

	//setters
	void setName(const char* _name);
	void setHOD(HOD* h);
	void setItManager(IT_Manager* it);
	void setCurrentCourses(int n);
	void setMaxCourses(int n);
	void setCurrentTeachers(int n);
	void setMaxTeachers(int n);
	void setCurrentStudents(int n);
	void setMaxStudents(int n);

	//getters
	int getCurrentCourses();
	int getMaxCourses();
	int getCurrentTeachers();
	int getMaxTeachers();
	int getCurrentStudents();
	int getMaxStudents();
	char* getName();
	char* getCourseName(int index);
	char* getCourseCode(int index);
	int getIDOfStudent(const char* _username, const char* _password);
	int getIDOfTeacher(const char* _username, const char* _password);
	Course* getCourse(const char* _courseCode);
	Student* getStudent(int rollNum);
	Teacher* getTeacher(int teacher_id);
	HOD* getHod(int Hod_id);
	TA* getTAOfACourse(const char* _courseCode);
	int getTAEmployeeId(const char* _courseCode);
	int getTAStudentId(const char* _courseCode);

	//check accounts of all entities
	bool checkHODAccount(const char* _username, const char* _password);
	bool checkItManagerAccount(const char* _username, const char* _password);
	bool checkTeacherAccount(const char* _username, const char* _password);
	bool checkStudentAccount(const char* _username, const char* _password);
	bool checkTAAccount(const char* _username, const char* _password);


	//HOD Functionalities
	bool assignCourse(int teacher_Id, const char* courseCode);
	bool registerCourse(int student_Id, const char* courseCode);
	bool unRegisterCourse(int student_Id, const char* courseCode);
	void veiwCourseGrade(const char* _courseCode);

	//IT MANAGER Functionalities
	bool createTeacherAccount(Teacher* t);
	bool createStudentAccount(Student* s);
	bool deleteTeacherAccount(int teacher_Id);
	bool deleteStudentAccount(int student_Id);
	bool changeStudentUserName(int student_Id, const char* _userName);
	bool changeStudentPassword(int student_Id, const char* _passWord);
	bool changeTeacherUserName(int teacher_Id, const char* _userName);
	bool changeTeacherPassword(int teacher_Id, const char* _passWord);

	//Teacher Functionalities
	bool manageAttendancePer(const char* _userName, int stdRollNum, float _attPer, const char* _courseCode);
	void viewAttendanceOfAllStudent(const char* userName, const char* _courseCode);
	bool assignGradeToStudent(const char* _userName, int stdRollNum, char _grade, const char* _courseCode);
	bool manageEvaluationOfAStudent(const char* _userName, int stdRollNum, float _gpa, float _gt, const char* _courseCode);
	void viewEvaluationOfAllStudents(const char* userName, const char* _courseCode);
	bool changeTA(const char* username, int std_Id, const char* courseCode);

	//Student Functionalities
	bool registerCourse(const char* _username, const char* _courseCode);
	bool unRegisterCourse(const char* _username, const char* _courseCode, char choice);
	void viewAttendance(const char* _username, const char* courseCode);
	void viewMarkSheet(const char* _username, const char* _courseCode);
	bool changePassword(const char* _username, const char* _password);

	//Teaching Assistant Functionalities
	void taViewEvaluationOfAllStudents(const char* _courseCode);
	bool taManageEvaluationOfAStudent(int stdRollNum, float _gpa, float _gt, const char* _courseCode);
	void taViewAttendanceOfAStudent(const char* _courseCode);
	bool taManageAttendancePer(int stdRollNum, float _attPer, const char* _courseCode);
	char* getCourseCodeThroghTA(const char* _userName, const char* _password);

	//	display different entities of department
	void displayStudents(int x=0, int y=0);
	void displayTeachers(int x=0, int y=0);
	void displayCourses(int x=0, int y=0);

	//Destructor
	~Department();
};

#endif