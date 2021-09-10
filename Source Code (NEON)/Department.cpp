#include "Department.h"
#include"Template.h"
using namespace std;

HANDLE hmD = GetStdHandle(STD_OUTPUT_HANDLE);

//constructors
Department::Department() : name(nullptr), it_manager(nullptr), Hod(nullptr), maxTeachers(30), currentTeachers(0), maxStudents(100), currentStudents(0), maxCourses(15), currentCourses(0) {
	listOfStudents = new Student * [maxStudents];
	for (int i = 0; i < maxStudents; i++)
		listOfStudents[i] = nullptr;

	listOfTeachers = new Teacher * [maxTeachers];
	for (int i = 0; i < maxTeachers; i++)
		listOfTeachers[i] = nullptr;

	listOfCourses = new Course * [maxCourses];
	for (int i = 0; i < maxCourses; i++)
		listOfCourses[i] = nullptr;
}
Department::Department(const char* _name, IT_Manager* _it_manager, HOD* _Hod, int _maxTeachers, int _maxStudents, int _maxCourses) {
	it_manager = _it_manager;
	Hod = _Hod;

	maxStudents = _maxStudents;
	listOfStudents = new Student * [maxStudents];
	for (int i = 0; i < maxStudents; i++)
		listOfStudents[i] = nullptr;
	currentStudents = 0;

	maxTeachers = _maxTeachers;
	listOfTeachers = new Teacher * [maxTeachers];
	for (int i = 0; i < maxTeachers; i++)
		listOfTeachers[i] = nullptr;
	currentTeachers = 0;

	maxCourses = _maxCourses;
	listOfCourses = new Course * [maxCourses];
	for (int i = 0; i < maxCourses; i++)
		listOfCourses[i] = nullptr;
	currentCourses = 0;

	name = new char[strlen(_name) + 1];
	strcpy_s(name, strlen(_name) + 1, _name);
}

//setters
void Department::setHOD(HOD* h) {
	if (Hod != nullptr)
		delete Hod;
	Hod = h;
}
void Department::setItManager(IT_Manager* it) {
	if (it_manager != nullptr)
		delete it_manager;
	it_manager = it;
}
void Department::setCurrentCourses(int n) { 
	try {
		if (n < 0)
			throw "Passed Size Of Current Number Of Courses Is Negative";
		else if (n >= maxCourses)
			throw "Passed Size Of Current Number Of Courses Is Greater Than Or Equal To Maximum Courses";

		//set Current number Of courses to n
		currentCourses = n;
	}
	catch (const char* message) {
		cout << "Exception throw: " << message << endl;
	} 
}
void Department::setMaxCourses(int n) { 
	//grow maximum size of list of courses
	listOfCourses = Template<Course>::growSize(listOfCourses, currentCourses, maxCourses);
}
void Department::setCurrentTeachers(int n) {
	try {
		if (n < 0)
			throw "Passed Size Of Current Number Of Teachers Is Negative";
		else if (n >= maxTeachers)
			throw "Passed Size Of Current Number Of Teachers Is Greater Than Or Equal To Maximum Courses";

		//set Current number Of teachers to n
		currentTeachers = n;
	}
	catch (const char* message) {
		cout << "Exception throw: " << message << endl;
	}
}
void Department::setMaxTeachers(int n) {
	//grow maximum size of list of teachers
	listOfTeachers = Template<Teacher>::growSize(listOfTeachers, currentTeachers, maxTeachers);
}
void Department::setCurrentStudents(int n) {
	try {
		if (n < 0)
			throw "Passed Size Of Current Number Of Studetns Is Negative";
		else if (n >= maxStudents)
			throw "Passed Size Of Current Number Of Studrnts Is Greater Than Or Equal To Maximum Courses";

		//set Current number Of students to n
		currentStudents = n;
	}
	catch (const char* message) {
		cout << "Exception throw: " << message << endl;
	}
}
void Department::setMaxStudents(int n) { 
	//grow maximum size of list of course
	listOfStudents = Template<Student>::growSize(listOfStudents, currentStudents, maxStudents);
}
void Department::setName(const char* _name) {
	if (name != nullptr)
		delete[] name;
	name = new char[strlen(_name) + 1];
	strcpy_s(name, strlen(_name) + 1, _name);
}

//getters
int Department::getCurrentCourses() { return currentCourses; }
int Department::getMaxCourses() { return maxCourses; }
int Department::getCurrentTeachers() { return  currentTeachers; }
int Department::getMaxTeachers() { return maxTeachers; }
int Department::getCurrentStudents() { return currentStudents; }
int Department::getMaxStudents() { return maxStudents; }
char* Department::getName() { return name; }
char* Department::getCourseName(int index) {
	try {
		if (index < 0)
			throw "Index is negative";
		else if (index >= currentCourses)
			throw "Index is out of bound";

		return listOfCourses[index]->getCourseName();
	}
	catch (const char* message) {
		cout << "Exception throw: " << message << endl;
	}
	return nullptr;
}
char* Department::getCourseCode(int index) {
	try {
		if (index < 0)
			throw "Index is negative";
		else if (index >= currentCourses)
			throw "Index is out of bound";

		return listOfCourses[index]->getCourseCode();
	}
	catch (const char* message) {
		cout << "Exception throw: " << message << endl;
	}
	return nullptr;
}
Course* Department::getCourse(const char* _courseCode) {
	for (int i = 0; i < currentCourses; i++) {
		if (listOfCourses[i] != nullptr && !strcmp(listOfCourses[i]->getCourseCode(), _courseCode))
			return listOfCourses[i];
	}
	return nullptr;
}
Student* Department::getStudent(int rollNum) {
	for (int i = 0; i < currentStudents; i++) {
		if (listOfStudents[i] != nullptr && listOfStudents[i]->getRollNum() == rollNum)
			return listOfStudents[i];
	}
	return nullptr;
}
Teacher* Department::getTeacher(int teacher_id) {
	for (int i = 0; i < currentTeachers; i++) {
		if (listOfTeachers[i] != nullptr && listOfTeachers[i]->getEmployeeId() == teacher_id)
			return listOfTeachers[i];
	}
	return nullptr;
}
HOD* Department::getHod(int Hod_id) {
	if (Hod != nullptr && Hod->getEmployeeId() == Hod_id)
		return Hod;
	return nullptr;
}
TA* Department::getTAOfACourse(const char* _courseCode) {
	for (int i = 0; i < currentCourses; i++) {
		if (listOfCourses[i] != nullptr && !strcmp(listOfCourses[i]->getCourseCode(), _courseCode))
			return listOfCourses[i]->getTA();
	}
	return nullptr;
}
int Department::getTAEmployeeId(const char* _courseCode) {
	for (int i = 0; i < currentCourses; i++) {
		if (listOfCourses[i] != nullptr && !strcmp(listOfCourses[i]->getCourseCode(), _courseCode)) {
			return listOfCourses[i]->getTAEmployeeId();
		}
	}
	return 0;
}
int Department::getTAStudentId(const char* _courseCode) {
	for (int i = 0; i < currentCourses; i++) {
		if (listOfCourses[i] != nullptr && !strcmp(listOfCourses[i]->getCourseCode(), _courseCode)) {
			return listOfCourses[i]->getTAStudentId();
		}
	}
	return 0;
}
char* Department::getCourseCodeThroghTA(const char* _username, const char* _password) {
	for (int i = 0; i < currentCourses; i++) {
		if (listOfCourses[i] != nullptr && listOfCourses[i]->getTA() != nullptr) {
			if (!strcmp(listOfCourses[i]->getTAUsername(), _username) && !strcmp(listOfCourses[i]->getTAPassword(), _password)) {
				return listOfCourses[i]->getCourseCode();
			}
		}
	}
	return 0;
}
int Department::getIDOfStudent(const char* _username, const char* _password) {
	for (int i = 0; i < currentStudents; i++) {
		if (listOfStudents[i] != nullptr) {
			if (!strcmp(listOfStudents[i]->getUserName(), _username) && !strcmp(listOfStudents[i]->getPassword(), _password))
				return listOfStudents[i]->getRollNum();
		}
	}
	return 0;
}
int Department::getIDOfTeacher(const char* _username, const char* _password) {
	if (Hod != nullptr) {
		if (!strcmp(Hod->getUserName(), _username) && !strcmp(Hod->getPassword(), _password))
			return Hod->getEmployeeId();
	}
	for (int i = 0; i < currentTeachers; i++) {
		if (listOfTeachers[i] != nullptr) {
			if (!strcmp(listOfTeachers[i]->getUserName(), _username) && !strcmp(listOfTeachers[i]->getPassword(), _password))
				return listOfTeachers[i]->getEmployeeId();
		}
	}
	return 0;
}

//add a course in list of courses
bool Department::addCourse(const char* courseCode, const char* courseName, TA* ta) {
	if (currentCourses < maxCourses) {
		listOfCourses[currentCourses++] = new Course(courseName, courseCode, ta);
		return true;
	}
	return false;
}

//check accounts of all entities
bool Department::checkHODAccount(const char* _username, const char* _password) {
	if (Hod != nullptr) {
		if (!strcmp(Hod->getUserName(), _username) && !strcmp(Hod->getPassword(), _password))
			return true;
	}
	return false;
}
bool Department::checkItManagerAccount(const char* _username, const char* _password) {
	if (it_manager != nullptr) {
		if (!strcmp(it_manager->getUserName(), _username) && !strcmp(it_manager->getPassword(), _password))
			return true;
	}
	return false;
}
bool Department::checkTeacherAccount(const char* _username, const char* _password) {

	if (checkHODAccount(_username, _password))
		return true;

	for (int i = 0; i < currentTeachers; i++) {
		if (listOfTeachers[i] != nullptr) {
			if (!strcmp(listOfTeachers[i]->getUserName(), _username) && !strcmp(listOfTeachers[i]->getPassword(), _password))
				return true;
		}
	}
	return false;
}
bool Department::checkStudentAccount(const char* _username, const char* _password) {
	for (int i = 0; i < currentStudents; i++){
		if (listOfStudents[i] != nullptr) {
			if (!strcmp(listOfStudents[i]->getUserName(), _username) && !strcmp(listOfStudents[i]->getPassword(), _password))
				return true;
		}
	}
	return false;
}
bool Department::checkTAAccount(const char* _username, const char* _password) {
	for (int i = 0; i < currentCourses; i++) {
		if (listOfCourses[i] != nullptr ) {
			if (listOfCourses[i]->getTA() != nullptr && !strcmp(listOfCourses[i]->getTAUsername(), _username) && !strcmp(listOfCourses[i]->getTAPassword(), _password)) {
				return true;
			}
		}
	}
	return false;
}

//HOD Functionalities
bool Department::assignCourse(int teacher_Id, const char* courseCode) {
	if (Hod != nullptr && Hod->getEmployeeId() == teacher_Id) {
		for (int j = 0; j < currentCourses; j++) {
			if (listOfCourses[j] != nullptr && strcmp(listOfCourses[j]->getCourseCode(), courseCode) == 0) {
				return Hod->setCourse(listOfCourses[j]);
			}
		}
	}
	for (int i = 0; i < currentTeachers; i++) {
		if (listOfTeachers[i] != nullptr && listOfTeachers[i]->getEmployeeId() == teacher_Id) {
			for (int j = 0; j < currentCourses; j++) {
				if (listOfCourses[j] != nullptr && strcmp(listOfCourses[j]->getCourseCode(), courseCode) == 0) {
					return listOfTeachers[i]->setCourse(listOfCourses[j]);
				}
			}
		}
	}
	return false;
}
bool Department::registerCourse(int student_Id, const char* courseCode) {
	for (int i = 0; i < currentStudents; i++) {
		if (listOfStudents[i] != nullptr && listOfStudents[i]->getRollNum() == student_Id) {
			for (int j = 0; j < currentCourses; j++) {
				if (listOfCourses[j] != nullptr && !strcmp(listOfCourses[j]->getCourseCode(), courseCode)) {
					int reg_num = Helper::generateRegisterationID();
					Registeration* newReg = new Registeration(reg_num, listOfStudents[i], listOfCourses[j]);
					bool res = listOfStudents[i]->registerCourse(newReg);

					if (newReg != nullptr)
						newReg = nullptr;
					return res;
				}
			}
		}
	}
	return false;
}
bool Department::unRegisterCourse(int student_Id, const char* courseCode) {
	for (int i = 0; i < currentStudents; i++) {
		if (listOfStudents[i] != nullptr && listOfStudents[i]->getRollNum() == student_Id) {
			return listOfStudents[i]->unRegisterCourse(courseCode);
		}
	}
	return false;
}
void Department::veiwCourseGrade(const char* courseCode) {
	cout << endl << endl << endl;
	for (int i = 0; i < currentCourses; i++) {
		if (listOfCourses[i] != nullptr && !strcmp(listOfCourses[i]->getCourseCode(), courseCode))
			listOfCourses[i]->viewEvaluationOfAllStudents();
	}
}

//template function to delete an account from a 2D list
template<class Type>
void deleteAccount(Type** _studentList, int index, int& current_size) {
	try {
		if (index < 0)
			throw "Index Is Negative";
		else if (index >= current_size)
			throw "Index Is Greater Than Or Equal To Size";

		if (_studentList[index] != nullptr)
			delete _studentList[index];

		for (int i = index; i < current_size - 1; i++) {
			_studentList[i] = _studentList[i + 1];
		}
		--current_size;
		_studentList[current_size] = nullptr;
	}
	catch (const char* message) {
		cout << "Exception throw: " << message << endl;
	}
}

//IT_MANAGER Functionalities
bool Department::createTeacherAccount(Teacher* t) {
	if (currentTeachers < maxTeachers) {
		listOfTeachers[currentTeachers++] = t;
		return true;
	}
	return false;
}
bool Department::createStudentAccount(Student* s) {
	if (currentStudents < maxStudents) {
		listOfStudents[currentStudents] = s;
		currentStudents++;
		return true;
	}
	return false;
}
bool Department::deleteTeacherAccount(int teacher_Id) {
	for (int i = 0; i < currentTeachers; i++) {
		if (listOfTeachers[i] != nullptr && listOfTeachers[i]->getEmployeeId() == teacher_Id) {
			deleteAccount(listOfTeachers, i, currentTeachers);
			return true;
		}
	}
	return false;
}
bool Department::deleteStudentAccount(int student_Id) {
	//delete students
	for (int i = 0; i < currentStudents; i++) {
		if (listOfStudents[i] != nullptr && listOfStudents[i]->getRollNum() == student_Id) {
			deleteAccount(listOfStudents, i, currentStudents);
			return true;
		}
	}
	return false;
}


bool Department::changeStudentUserName(int student_Id, const char* _userName) {
	for (int i = 0; i < currentStudents; i++) {
		if (listOfStudents[i] != nullptr && listOfStudents[i]->getRollNum() == student_Id) {
			listOfStudents[i]->changeUserName(_userName);
			return true;
		}
	}

	return false;
}
bool Department::changeStudentPassword(int student_Id, const char* _password) {
	for (int i = 0; i < currentStudents; i++) {
		if (listOfStudents[i] != nullptr && listOfStudents[i]->getRollNum() == student_Id) {
			listOfStudents[i]->changePassword(_password);
			return true;
		}
	}
	return false;
}
bool Department::changeTeacherUserName(int teacher_Id, const char* _userName) {
	if (Hod != nullptr && Hod->getEmployeeId() == teacher_Id) {
		Hod->changeUserName(_userName);
		return true;
	}

	for (int i = 0; i < currentTeachers; i++) {
		if (listOfTeachers[i] != nullptr && listOfTeachers[i]->getEmployeeId() == teacher_Id) {
			listOfTeachers[i]->changeUserName(_userName);
			return true;
		}
	}
	return false;
}
bool Department::changeTeacherPassword(int teacher_Id, const char* _password) {
	if (Hod != nullptr && Hod->getEmployeeId() == teacher_Id) {
		Hod->changePassword(_password);
		return true;
	}

	for (int i = 0; i < currentTeachers; i++) {
		if (listOfTeachers[i] != nullptr && listOfTeachers[i]->getEmployeeId() == teacher_Id) {
			listOfTeachers[i]->changePassword(_password);
			return true;
		}
	}

	return false;
}

//Teacher Functionalities
bool Department::manageAttendancePer(const char* _userName, int stdRollNum, float _attPer, const char* _courseCode) {
	bool res = false;
	for (int i = 0; i < currentTeachers; i++) {
		if (listOfTeachers[i] != nullptr && !strcmp(listOfTeachers[i]->getUserName(), _userName))
			res = listOfTeachers[i]->isCourseExist(_courseCode);
	}

	if (res) {
		for (int i = 0; i < currentStudents; i++) {
			if (listOfStudents[i] != nullptr && listOfStudents[i]->getRollNum() == stdRollNum) {
				return listOfStudents[i]->setAttendance(_courseCode, _attPer);
			}
		}
	}
	return false;
}
void Department::viewAttendanceOfAllStudent(const char* userName, const char* _courseCode) {
	for (int h = 0; h < currentTeachers; h++) {
		if (listOfTeachers[h] != nullptr && !strcmp(listOfTeachers[h]->getUserName(), userName)) {
			listOfTeachers[h]->viewAttendance(_courseCode);
		}
	}
}
bool Department::assignGradeToStudent(const char* _userName, int stdRollNum, char _grade, const char* _courseCode) {
	bool res = false;
	for (int i = 0; i < currentTeachers; i++) {
		if (listOfTeachers[i] != nullptr && !strcmp(listOfTeachers[i]->getUserName(), _userName))
			res = listOfTeachers[i]->isCourseExist(_courseCode);
	}

	if (res) {
		for (int i = 0; i < currentStudents; i++) {
			if (listOfStudents[i] != nullptr && listOfStudents[i]->getRollNum() == stdRollNum) {
				listOfStudents[i]->setGrade(_courseCode, _grade);
				return true;
			}
		}
	}
	return false;
}
bool Department::manageEvaluationOfAStudent(const char* _userName, int stdRollNum, float _gpa, float _gt, const char* _courseCode) {
	bool res = false;
	for (int i = 0; i < currentTeachers; i++) {
		if (listOfTeachers[i] != nullptr && !strcmp(listOfTeachers[i]->getUserName(), _userName))
			res = listOfTeachers[i]->isCourseExist(_courseCode);
	}

	if (res) {
		for (int i = 0; i < currentStudents; i++) {
			if (listOfStudents[i] != nullptr && listOfStudents[i]->getRollNum() == stdRollNum) {
				bool res1 = listOfStudents[i]->setGPA(_courseCode, _gpa);
				bool res2 = listOfStudents[i]->setGT(_courseCode, _gt);
				return res1 && res2;
			}
		}
	}
	return false;
}
void Department::viewEvaluationOfAllStudents(const char* userName, const char* _courseCode) {
	cout << endl << endl<<endl;
	for (int h = 0; h < currentTeachers; h++) {
		if(listOfTeachers[h]!=nullptr && !strcmp(listOfTeachers[h]->getUserName(),userName)){
			listOfTeachers[h]->viewEvaluationOfAllStudents(_courseCode);
			cout << endl;
		}
	}
}
bool Department::changeTA(const char* username, int std_Id, const char* courseCode) {
	for (int i = 0; i < currentTeachers; i++) {
		if (listOfTeachers[i] != nullptr && !strcmp(listOfTeachers[i]->getUserName(), username)) {
			for (int j = 0; j < currentStudents; j++) {
				if (listOfStudents[j] != nullptr && listOfStudents[j]->getRollNum() == std_Id) {
					bool res1 = listOfTeachers[i]->isCourseExist(courseCode);
					
					//Check if TA is already exist
					for (int i = 0; i < currentCourses; i++) {
						if (listOfCourses[i] != nullptr && listOfCourses[i]->getTAStudentId() == std_Id) {
							listOfCourses[i]->setTA();
						}
					}


					if (res1) {
						TA* ta = new TA(listOfStudents[j]->getFirstName(), 
							listOfStudents[j]->getLastName(),
							listOfStudents[j]->getAge(),
							listOfStudents[j]->getRollNum(),
							Helper::generateRegisterationID(),
							5);

						ta->changePassword(listOfStudents[j]->getPassword());
						ta->changeUserName(listOfStudents[j]->getUserName());
				
						for (int k = 0; k < listOfStudents[j]->getCurrentNoOfReg(); k++) {
							ta->registerCourse(listOfStudents[j]->getRegisteraion(k));
						}
						
						//delete student
						deleteStudentAccount(listOfStudents[j]->getRollNum());

						//set TA 
						for (int m = 0; m < currentCourses; m++) {
							if (listOfCourses[m] != nullptr && !strcmp(listOfCourses[m]->getCourseCode(), courseCode)) {
								listOfCourses[m]->setTA(ta);
							}
						}
						
						// add TA in list of students
						createStudentAccount(ta);
						
						if (ta != nullptr)
							ta = nullptr;
						return true;
					}
				}
			}
		}
	}
	return false;
}

//Student Functionalities
bool Department::registerCourse(const char* _username, const char* _courseCode) {
	for (int i = 0; i < currentStudents; i++) {
		if (listOfStudents[i] != nullptr && !strcmp(listOfStudents[i]->getUserName(), _username)) {
			for (int j = 0; j < currentCourses; j++) {
				if (listOfCourses[j] != nullptr && strcmp(listOfCourses[j]->getCourseCode(), _courseCode) == 0)
				{
					int reg_num = Helper::generateRegisterationID();
					Registeration* newReg = new Registeration(reg_num, listOfStudents[i], listOfCourses[j]);
					bool res = listOfStudents[i]->registerCourse(newReg);

					if (newReg != nullptr)
						newReg = nullptr;
					return res;
				}
			}
		}
	}
	return false;
}
bool Department::unRegisterCourse(const char* _username, const char* _courseCode, char choice) {
	//To find current date
	time_t now = time(0);
	tm* ltm = new tm;
	localtime_s(ltm, &now);

	Date* date = new Date(1900 + ltm->tm_year, 1 + ltm->tm_mon, ltm->tm_mday);
	if (ltm != nullptr)
		delete ltm;

	int diff = 0;
	for (int i = 0; i < currentStudents; i++) {
		if (listOfStudents[i] != nullptr && !strcmp(listOfStudents[i]->getUserName(), _username)) {
			for (int j = 0; j < listOfStudents[i]->getCurrentNoOfReg(); j++) {
				if (!strcmp(listOfStudents[i]->getRegisteraion(j)->getCourseCode(), _courseCode)) {
					diff = Helper::getDifference(listOfStudents[i]->getRegisteraion(j)->getDate(),date);
				}
			}


			//unregister a course within 10 days of registeration
			if (choice == '2') {
				if (diff < 10) {
					bool res = listOfStudents[i]->unRegisterCourse(_courseCode);
					if (res)
						return true;
				}
			}

			//Withdraw a course within last 2-weeks of semester	(HINT:  I assume that a semester is longing for almost 5 months = 150 days almost)
			else if(choice == '3'){
				if (diff >= 136 && diff <= 150) {
					bool res = listOfStudents[i]->withdrawCourse(_courseCode);
					if (res)
						return true;
				}
			}
		}
	}
	if (date != nullptr)
		delete date;
	return false;
}
void Department::viewAttendance(const char* _username, const char* courseCode) {
	for (int i = 0; i < currentStudents; i++) {
		if (listOfStudents[i] != nullptr && !strcmp(listOfStudents[i]->getUserName(), _username)) {
			listOfStudents[i]->viewAttendance(courseCode);
		}
	}
}
void Department::viewMarkSheet(const char* _username, const char* _courseCode) {
	cout << endl << endl << endl;
	for (int i = 0; i < currentStudents; i++) {
		if (listOfStudents[i] != nullptr && !strcmp(listOfStudents[i]->getUserName(), _username)) {
			listOfStudents[i]->viewMarkSheet(_courseCode);
		}
	}
}
bool Department::changePassword(const char* _username, const char* _password) {
	for (int i = 0; i < currentStudents; i++) {
		if (listOfStudents[i] != nullptr && !strcmp(listOfStudents[i]->getUserName(), _username)) {
			listOfStudents[i]->changePassword(_password);
			return true;
		}
	}
	return false;
}

//Teaching Assistant Functionalities
void Department::taViewEvaluationOfAllStudents(const char* _courseCode) {
	cout << endl << endl << endl;
	for (int h = 0; h < currentCourses; h++) {
		if (listOfCourses[h] != nullptr && !strcmp(listOfCourses[h]->getCourseCode(), _courseCode)) {
			listOfCourses[h]->viewEvaluationOfAllStudents();
		}
	}
}
bool Department::taManageEvaluationOfAStudent(int stdRollNum, float _gpa, float _gt, const char* _courseCode) {
	for (int i = 0; i < currentStudents; i++) {
		if (listOfStudents[i] != nullptr && listOfStudents[i]->getRollNum() == stdRollNum) {
			bool res1 = listOfStudents[i]->setGPA(_courseCode, _gpa);
			bool res2 = listOfStudents[i]->setGT(_courseCode, _gt);
			return res1 && res2;
		}
	}

	return false;
}
void Department::taViewAttendanceOfAStudent(const char* _courseCode) {
	cout << endl << endl;
	for (int h = 0; h < currentCourses; h++) {
		if (listOfCourses[h] != nullptr && !strcmp(listOfCourses[h]->getCourseCode(), _courseCode)) {
			listOfCourses[h]->viewAttendaceOfAllStudents();
		}
	}
}
bool Department::taManageAttendancePer(int stdRollNum, float _attPer, const char* _courseCode) {
	for (int i = 0; i < currentStudents; i++) {
		if (listOfStudents[i] != nullptr && listOfStudents[i]->getRollNum() == stdRollNum) {
			return listOfStudents[i]->setAttendance(_courseCode, _attPer);
		}
	}
	return false;
}

//Display Functions
void Department::displayStudents(int x, int y){
	if (this != nullptr) {
		SetConsoleTextAttribute(hmD, 0 | BACKGROUND_BLUE);
		Helper::gotoxy(60, 2);
		cout << setw(40) << "";
		Helper::gotoxy(60, 3);
		cout << setw(12) << " " << "List Of Students" << setw(12) << " ";
		Helper::gotoxy(60, 4);
		cout << setw(40) << "";
		SetConsoleTextAttribute(hmD, 15);

		
		SetConsoleTextAttribute(hmD, 0 | BACKGROUND_BLUE | BACKGROUND_RED | BACKGROUND_INTENSITY);
		Helper::gotoxy(x + 5, 9 + y);
		cout << " ID ";
		SetConsoleTextAttribute(hmD, 15);

		SetConsoleTextAttribute(hmD, 0 | BACKGROUND_BLUE | BACKGROUND_RED | BACKGROUND_INTENSITY);
		Helper::gotoxy(x + 15, 9 + y);
		cout << " Name ";
		SetConsoleTextAttribute(hmD, 15);

		SetConsoleTextAttribute(hmD, 0 | BACKGROUND_BLUE | BACKGROUND_RED | BACKGROUND_INTENSITY);
		Helper::gotoxy(x + 35, 9 + y);
		cout << " Age ";
		SetConsoleTextAttribute(hmD, 15);

		SetConsoleTextAttribute(hmD, 0 | BACKGROUND_BLUE | BACKGROUND_RED | BACKGROUND_INTENSITY);
		Helper::gotoxy(x + 45, 9 + y);
		cout << " Courses ";
		SetConsoleTextAttribute(hmD, 15);


		for (int i = 0; i < currentStudents; i++) {
			if (listOfStudents[i] != nullptr) {
				SetConsoleTextAttribute(hmD, 0 | BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED | BACKGROUND_INTENSITY);
				Helper::gotoxy(x + 5, (2*i)+12 + y);
				cout << " " << listOfStudents[i]->getRollNum() << " ";
				SetConsoleTextAttribute(hmD, 15);

				SetConsoleTextAttribute(hmD, 0 | BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED | BACKGROUND_INTENSITY);
				Helper::gotoxy(x + 15, (2 * i) + 12 + y);
				cout << " " << listOfStudents[i]->getFirstName() << " " << listOfStudents[i]->getLastName() << " ";
				SetConsoleTextAttribute(hmD, 15);

				SetConsoleTextAttribute(hmD, 0 | BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED | BACKGROUND_INTENSITY);
				Helper::gotoxy(x + 35, (2 * i) + 12 + y);
				cout << " " << listOfStudents[i]->getAge() << " ";
				SetConsoleTextAttribute(hmD, 15);

				SetConsoleTextAttribute(hmD, 0 | BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED | BACKGROUND_INTENSITY);
				Helper::gotoxy(x + 48, (2 * i) + 12 + y);
				cout <<" "<< listOfStudents[i]->getCurrentNoOfReg() << " ";
				SetConsoleTextAttribute(hmD, 15);
			}
		}
		cout << endl << endl << endl;
	}
}
void Department::displayTeachers(int x, int y){
	if (this != nullptr) {
		SetConsoleTextAttribute(hmD, 0 | BACKGROUND_BLUE);
		Helper::gotoxy(60, 2);
		cout << setw(40) << "";
		Helper::gotoxy(60, 3);
		cout << setw(12) << " " << "List Of Teachers" << setw(12) << " ";
		Helper::gotoxy(60, 4);
		cout << setw(40) << "";
		SetConsoleTextAttribute(hmD, 15);


		SetConsoleTextAttribute(hmD, 0 | BACKGROUND_BLUE | BACKGROUND_RED | BACKGROUND_INTENSITY);
		Helper::gotoxy(x + 5, y + 9);
		cout << " ID ";
		SetConsoleTextAttribute(hmD, 15);

		SetConsoleTextAttribute(hmD, 0 | BACKGROUND_BLUE | BACKGROUND_RED | BACKGROUND_INTENSITY);
		Helper::gotoxy(x + 15, y + 9);
		cout << " Name ";
		SetConsoleTextAttribute(hmD, 15);

		SetConsoleTextAttribute(hmD, 0 | BACKGROUND_BLUE | BACKGROUND_RED | BACKGROUND_INTENSITY);
		Helper::gotoxy(x + 35, y + 9);
		cout << " Age ";
		SetConsoleTextAttribute(hmD, 15);

		SetConsoleTextAttribute(hmD, 0 | BACKGROUND_BLUE | BACKGROUND_RED | BACKGROUND_INTENSITY);
		Helper::gotoxy(x + 45, y + 9);
		cout << " Courses ";
		SetConsoleTextAttribute(hmD, 15);

		//display hod
		if (Hod != nullptr) {
			SetConsoleTextAttribute(hmD, 0 | BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED | BACKGROUND_INTENSITY);
			Helper::gotoxy(x + 5, y + 11);
			cout << " " << Hod->getEmployeeId() << " ";
			SetConsoleTextAttribute(hmD, 15);

			SetConsoleTextAttribute(hmD, 0 | BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED | BACKGROUND_INTENSITY);
			Helper::gotoxy(x + 15, y + 11);
			cout << " " << Hod->getFirstName() << " " << Hod->getLastName() << " ";
			SetConsoleTextAttribute(hmD, 15);

			SetConsoleTextAttribute(hmD, 0 | BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED | BACKGROUND_INTENSITY);
			Helper::gotoxy(x + 35, y + 11);
			cout << " " << Hod->getAge() << " ";
			SetConsoleTextAttribute(hmD, 15);

			SetConsoleTextAttribute(hmD, 0 | BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED | BACKGROUND_INTENSITY);
			Helper::gotoxy(x + 48, y + 11);
			cout << " " << Hod->getCurrentNumOfCourses() << " ";
			SetConsoleTextAttribute(hmD, 15);
		}

		//display all teachers
		for (int i = 0; i < currentTeachers; i++) {
			if (listOfTeachers[i] != nullptr) {
				SetConsoleTextAttribute(hmD, 0 | BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED | BACKGROUND_INTENSITY);
				Helper::gotoxy(x + 5, (2 * i) + 13 + y);
				cout << " " << listOfTeachers[i]->getEmployeeId() << " ";
				SetConsoleTextAttribute(hmD, 15);

				SetConsoleTextAttribute(hmD, 0 | BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED | BACKGROUND_INTENSITY);
				Helper::gotoxy(x + 15, (2 * i) + 13 + y);
				cout << " " << listOfTeachers[i]->getFirstName() << " " << listOfTeachers[i]->getLastName() << " ";
				SetConsoleTextAttribute(hmD, 15);

				SetConsoleTextAttribute(hmD, 0 | BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED | BACKGROUND_INTENSITY);
				Helper::gotoxy(x + 35, (2 * i) + 13 + y);
				cout << " " << listOfTeachers[i]->getAge() << " ";
				SetConsoleTextAttribute(hmD, 15);

				SetConsoleTextAttribute(hmD, 0 | BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED | BACKGROUND_INTENSITY);
				Helper::gotoxy(x + 48, (2 * i) + 13 + y);
				cout << " " << listOfTeachers[i]->getCurrentNumOfCourses() << " ";
				SetConsoleTextAttribute(hmD, 15);
			}
		}
		cout << endl << endl << endl;
	}
}
void Department::displayCourses(int x, int y){
	system("cls");

	if (this != nullptr) {
		SetConsoleTextAttribute(hmD, 0 | BACKGROUND_BLUE);
		Helper::gotoxy(60, 2);
		cout << setw(40) << "";
		Helper::gotoxy(60, 3);
		cout << setw(12) << " " << "List Of Courses" << setw(13) << " ";
		Helper::gotoxy(60, 4);
		cout << setw(40) << "";
		SetConsoleTextAttribute(hmD, 15);


		SetConsoleTextAttribute(hmD, 0 | BACKGROUND_BLUE | BACKGROUND_RED | BACKGROUND_INTENSITY);
		Helper::gotoxy(5, 9);
		cout << " Code ";
		SetConsoleTextAttribute(hmD, 15);

		SetConsoleTextAttribute(hmD, 0 | BACKGROUND_BLUE | BACKGROUND_RED | BACKGROUND_INTENSITY);
		Helper::gotoxy(20, 9);
		cout << " Course Name ";
		SetConsoleTextAttribute(hmD, 15);

		SetConsoleTextAttribute(hmD, 0 | BACKGROUND_BLUE | BACKGROUND_RED | BACKGROUND_INTENSITY);
		Helper::gotoxy(60, 9);
		cout << " Teaching Ass. ";
		SetConsoleTextAttribute(hmD, 15);

		//display courses of a department 
		for (int i = 0; i < currentCourses; i++) {
			if (listOfCourses[i] != nullptr) {
				SetConsoleTextAttribute(hmD, 0 | BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED | BACKGROUND_INTENSITY);
				Helper::gotoxy(5, (2 * i) + 12);
				cout << " " << listOfCourses[i]->getCourseCode() << " ";
				SetConsoleTextAttribute(hmD, 15);

				SetConsoleTextAttribute(hmD, 0 | BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED | BACKGROUND_INTENSITY);
				Helper::gotoxy(20, (2 * i) + 12);
				cout << " " << listOfCourses[i]->getCourseName() << " ";
				SetConsoleTextAttribute(hmD, 15);

				//get current position of curser along x-axis
				int wx = Helper::wherex();
				for (int j = wx; j < 48; j++) {
					SetConsoleTextAttribute(hmD, 0 | BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED | BACKGROUND_INTENSITY);
					Helper::gotoxy(j, (2*i) + 12);
					cout << setw(1) << " ";
				}

				if (listOfCourses[i]->getTA() != nullptr) {
					SetConsoleTextAttribute(hmD, 0 | BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED | BACKGROUND_INTENSITY);
					Helper::gotoxy(60, (2 * i) + 12);

					cout << " " << listOfCourses[i]->getTA()->getFirstName()
						<< " " << listOfCourses[i]->getTA()->getLastName() << " ";
				}
				else {
					SetConsoleTextAttribute(hmD, 0 | BACKGROUND_RED);
					Helper::gotoxy(60, (2 * i) + 12);
					cout << " No TA! ";

				}
				SetConsoleTextAttribute(hmD, 15);
			}
		}
		cout << endl << endl << endl;
	}
}

//Destructor
Department::~Department() {
	//for writing in a file
	ofstream fout;
	fout.open("data.txt", ios::app);
	if (fout.fail())
		cout << "Fail to open file\n";
	else {
		if (name != nullptr)
			fout << name << endl;

		//Courses in a department
		fout << currentCourses << endl;
		for (int i = 0; i < currentCourses; i++) {
			if (listOfCourses[i] != nullptr) {
				fout<<(*listOfCourses[i]);
			}
		}

		//IT_Manager of a department
		if (it_manager != nullptr){
			fout <<*it_manager;
			fout << endl;
		}

		//count TAs of courses available in a department
		int count = 0;
		for (int m = 0; m < currentCourses; m++) {
			if (listOfCourses[m]->getTA() != nullptr)
				++count;
		}

		//HOD of a department
		fout << currentTeachers + count + 1 << endl;
		if (Hod != nullptr)
			fout << *Hod;

		//Teachers in a department 
		for (int i = 0; i < currentTeachers; i++) {
			if (listOfTeachers[i] != nullptr) {
				fout<<*listOfTeachers[i];
			}
		}

		//TA (Teacher's component)
		for (int i = 0; i < currentCourses; i++) {
			if (listOfCourses[i] != nullptr) {
				TA* ta = listOfCourses[i]->getTA();
				if (ta != nullptr) {
					fout << *ta;
				}
				if (ta != nullptr)
					ta = nullptr;
			}
		}

		//Students in a department
		fout << currentStudents << endl;
		for (int i = 0; i < currentStudents; i++) {
			if (listOfStudents[i] != nullptr) {
				fout<<*listOfStudents[i];
			}
		}
	}


	if (name != nullptr)
		delete[] name;

	if (it_manager != nullptr)
		delete it_manager;

	if (Hod != nullptr)
		delete Hod ;


	//Teachers
	for (int i = 0; i < currentTeachers; i++)
		if (listOfTeachers[i] != nullptr)
			delete listOfTeachers[i];
	if (listOfTeachers != nullptr)
		delete[] listOfTeachers;


	//Registerations
	for (int m = 0; m < currentStudents; m++) {
		for (int n = 0; n < listOfStudents[m]->getCurrentNoOfReg(); n++) {
			if (listOfStudents[m] != nullptr && listOfStudents[m]->getRegisteraion(n) != nullptr)
				delete listOfStudents[m]->getRegisteraion(n);
		}
	}

	//Students
	for (int i = 0; i < currentStudents; i++)
		if (listOfStudents[i] != nullptr)
			delete listOfStudents[i];
	if (listOfStudents != nullptr)
		delete[] listOfStudents;


	//Courses
	for (int i = 0; i < currentCourses; i++)
		if (listOfCourses[i] != nullptr)
			delete listOfCourses[i];
	if (listOfCourses != nullptr)
		delete[] listOfCourses;
}

