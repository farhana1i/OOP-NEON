#include "University.h"
#include<ios>
#include<limits>
#include<fstream>

HANDLE hM = GetStdHandle(STD_OUTPUT_HANDLE);

//Constructors
University::University() {
	name = nullptr;
	maxDepartment = 10;
	currentDepartment = 0;
	listOfDepartments = new Department * [maxDepartment];

	for (int i = 0; i < maxDepartment; i++)
		listOfDepartments[i] = nullptr;
}
University::University(const char* _name, int _maxDepartment) {
	name = new char[strlen(_name) + 1];
	strcpy_s(name, strlen(_name) + 1, _name);

	maxDepartment = _maxDepartment;
	listOfDepartments = new Department * [maxDepartment];
	currentDepartment = 0;
}

//add department in a university
bool University::addDepartment(const char* dep_name, IT_Manager* it_manager, HOD* Hod, int maxTeachers, int maxStudents, int maxCourses) {
	if (currentDepartment < maxDepartment) {
		listOfDepartments[currentDepartment++] = new Department(dep_name, it_manager, Hod, maxTeachers, maxStudents, maxCourses);
		return true;
	}
	return false;
}

//setters
void University::setName(const char* _name) {
	if (name != nullptr)
		delete[] name;
	name = new char[strlen(_name) + 1];
	strcpy_s(name, strlen(_name) + 1, _name);
}
void University::setMaxDepartment(int n) { maxDepartment = n; }
void University::setCurrentDepartment(int n) { currentDepartment = n; }

//getters
char* University::getName() { return name; }
int University::getMaxDepartment() { return maxDepartment; }
int University::getCurrentDepartment() { return currentDepartment; }

//Destructors
University::~University() {
	ofstream fout;
	fout.open("data.txt", ios::out);
	
	//write in a file
	fout << name << endl;
	fout << currentDepartment << endl;

	//delete departments of a university
	for (int i = 0; i < currentDepartment; i++)
		if (listOfDepartments[i] != nullptr)
			delete listOfDepartments[i];
	if (listOfDepartments != nullptr)
		delete[] listOfDepartments;

	//delete name of a university
	if (name != nullptr)
		delete[] name;
}

//display students
void University::printEntity(int index, char choice) {
	SetConsoleTextAttribute(hM, 0 | BACKGROUND_GREEN | BACKGROUND_RED);
	Helper::gotoxy(80, 9);
	cout << setw(40) << "";
	Helper::gotoxy(80, 10);
	if (choice == 't')
		cout << setw(11) << " " << "Available Teachers" << setw(11) << " ";
	else
		cout << setw(11) << " " << "Available Students" << setw(11) << " ";
	Helper::gotoxy(80, 11);
	cout << setw(40) << "";
	SetConsoleTextAttribute(hM, 15);


	if (choice == 't') {
		listOfDepartments[index]->displayTeachers(100, 5);
	}
	else
		listOfDepartments[index]->displayStudents(100, 5);
}

//Login modes of all entities
int University::HODLogin(int i) {
	system("CLS");
	char choice;
	choice = getChoice('1', 8) + 48;
	system("CLS");
	if (choice == '1') {
		
		//display teachers
		printEntity(i, 't');
		
		int teacher_id;
		SetConsoleTextAttribute(hM, 0 | BACKGROUND_BLUE);
		Helper::gotoxy(10, 10);
		cout << "Enter Teacher ID";
		SetConsoleTextAttribute(hM, 15);
		cout << ": ";
		Helper::gotoxy(29, 10);
		cin.get();
		Helper::gotoxy(29, 10);
		cin >> teacher_id;
		Helper::gotoxy(29, 10);
		cin.ignore(cin.rdbuf()->in_avail());

		system("cls");

		//print course details
		printNonRegCourses(i, 't' , teacher_id);

		SetConsoleTextAttribute(hM, 0 | BACKGROUND_BLUE);
		Helper::gotoxy(10, 12);
		char courseCode[20];
		cout << "Enter Course Code";
		SetConsoleTextAttribute(hM, 15);
		cout << ": ";
		Helper::gotoxy(29, 12);
		cin >> courseCode;
		Helper::gotoxy(29, 12);
		cin.ignore(cin.rdbuf()->in_avail());

		bool res = listOfDepartments[i]->assignCourse(teacher_id, courseCode);
		if (res) {
			Helper::gotoxy(35, 15);
			SetConsoleTextAttribute(hM, 0 | BACKGROUND_GREEN);
			cout << "Assign Course Successfully\n";
			SetConsoleTextAttribute(hM, 15);
		}
		else {
			Helper::gotoxy(35, 15);
			SetConsoleTextAttribute(hM, 0 | BACKGROUND_RED);
			cout << "Fail To Assign Course\n";
			SetConsoleTextAttribute(hM, 15);
		}
	}

	else if (choice == '2' || choice == '3') {
		
		//print student
		printEntity(i, 's');

		int student_id;
		SetConsoleTextAttribute(hM, 0 | BACKGROUND_BLUE);
		Helper::gotoxy(10, 10);
		cout << "Enter Student ID";
		SetConsoleTextAttribute(hM, 15);
		cout << ": ";
		Helper::gotoxy(29, 10);
		cin.get();
		Helper::gotoxy(29, 10);
		cin.ignore(cin.rdbuf()->in_avail());
		Helper::gotoxy(29, 10);
		cin >> student_id;
		Helper::gotoxy(29, 10);
		cin.ignore(cin.rdbuf()->in_avail());

		system("cls");

		//print course details
		if (choice == '2')
			printNonRegCourses(i, 's', student_id);
		else if (choice == '3')
			printCourses(i, '1', student_id);

		SetConsoleTextAttribute(hM, 0 | BACKGROUND_BLUE);
		Helper::gotoxy(10, 12);
		char courseCode[20];
		cout << "Enter Course Code";
		SetConsoleTextAttribute(hM, 15);
		cout << ": ";
		Helper::gotoxy(29, 12);
		cin >> courseCode;
		Helper::gotoxy(29, 12);
		cin.ignore(cin.rdbuf()->in_avail());

		if (choice == '2') {
			bool res = listOfDepartments[i]->registerCourse(student_id, courseCode);
			if (res) {
				Helper::gotoxy(35, 15);
				SetConsoleTextAttribute(hM, 0 | BACKGROUND_GREEN);
				cout << "Register Course Successfully\n";
				SetConsoleTextAttribute(hM, 15);
			}
			else {
				Helper::gotoxy(35, 15);
				SetConsoleTextAttribute(hM, 0 | BACKGROUND_RED);
				cout << "Fail To Register Course\n";
				SetConsoleTextAttribute(hM, 15);
			}
		}
		else {
			bool res = listOfDepartments[i]->unRegisterCourse(student_id, courseCode);
			if (res) {
				Helper::gotoxy(35, 15);
				SetConsoleTextAttribute(hM, 0 | BACKGROUND_GREEN);
				cout << "UnRegister Course Successfully\n";
				SetConsoleTextAttribute(hM, 15);
			}
			else {
				Helper::gotoxy(35, 15);
				SetConsoleTextAttribute(hM, 0 | BACKGROUND_RED);
				cout << "Fail To UnRegister Course\n";
				SetConsoleTextAttribute(hM, 15);
			}
		}
	}

	else if (choice == '4') {
		//print course details
		printCourses(i, '0');

		SetConsoleTextAttribute(hM, 0 | BACKGROUND_BLUE);
		Helper::gotoxy(10, 10);
		char courseCode[20];
		cout << "Enter Course Code";
		SetConsoleTextAttribute(hM, 15);
		cout << ": ";
		Helper::gotoxy(29, 10);
		cin.get();
		Helper::gotoxy(29, 10);
		cin.ignore(cin.rdbuf()->in_avail());
		Helper::gotoxy(29, 10);
		cin >> courseCode;
		Helper::gotoxy(29, 10);
		cin.ignore(cin.rdbuf()->in_avail());
		listOfDepartments[i]->veiwCourseGrade(courseCode);
	}

	else if (choice == '5') {
		system("CLS");
		listOfDepartments[i]->displayStudents();
	}

	else if (choice == '6') {
		system("CLS");
		listOfDepartments[i]->displayTeachers();
	}

	else if (choice == '7') {
		system("CLS");
		listOfDepartments[i]->displayCourses();
	}

	else if (choice == '8') {
		Sleep(150);
		return 6;
	}

	system("pause");
	Sleep(100);
	HODLogin(i);
}
int University::itManagerLogin(const char* dep, int i) {
	system("CLS");
	char choice;
	choice = getChoice('2', 9) + 48;
	system("CLS");
	if (choice == '1' || choice == '3') {
		char firstName[50];
		char lastName[50];

		Sleep(50);
		SetConsoleTextAttribute(hM, 0 | BACKGROUND_BLUE);
		Helper::gotoxy(10, 10);
		cout << "Enter First Name";
		SetConsoleTextAttribute(hM, 15);
		cout << ": ";
		Helper::gotoxy(29, 10);
		cin.get();
		Helper::gotoxy(29, 10);
		cin.ignore(cin.rdbuf()->in_avail());
		Helper::gotoxy(29, 10);
		cin >> firstName;
		Helper::gotoxy(29, 10);
		cin.ignore(cin.rdbuf()->in_avail());

		SetConsoleTextAttribute(hM, 0 | BACKGROUND_BLUE);
		Helper::gotoxy(10, 12);
		cout << "Enter Last Name";
		SetConsoleTextAttribute(hM, 15);
		cout << ": ";
		Helper::gotoxy(28, 12);
		cin >> lastName;
		Helper::gotoxy(28, 12);
		cin.ignore(cin.rdbuf()->in_avail());

		int age;
		SetConsoleTextAttribute(hM, 0 | BACKGROUND_BLUE);
		Helper::gotoxy(10, 14);
		cout << "Enter Age";
		SetConsoleTextAttribute(hM, 15);
		cout << ": ";
		Helper::gotoxy(23, 14);
		cin >> age;
		Helper::gotoxy(23, 14);
		cin.ignore(cin.rdbuf()->in_avail());

		if (choice == '1') {
			int teacher_id;
			SetConsoleTextAttribute(hM, 0 | BACKGROUND_BLUE);
			Helper::gotoxy(10, 16);
			cout << "Enter Teacher ID";
			SetConsoleTextAttribute(hM, 15);
			cout << ": ";
			Helper::gotoxy(29, 16);
			cin >> teacher_id;
			Helper::gotoxy(29, 16);
			cin.ignore(cin.rdbuf()->in_avail());

			SetConsoleTextAttribute(hM, 0 | BACKGROUND_BLUE);
			Helper::gotoxy(10, 18);
			int maxCourse;
			cout << "Enter Maximum Course";
			SetConsoleTextAttribute(hM, 15);
			cout << ": ";
			Helper::gotoxy(33, 18);
			cin >> maxCourse;
			Helper::gotoxy(33, 18);
			cin.ignore(cin.rdbuf()->in_avail());

			Teacher* newTeacher = new Teacher(firstName, lastName, teacher_id, age, maxCourse);
			bool res = listOfDepartments[i]->createTeacherAccount(newTeacher);
			if (newTeacher != nullptr)
				newTeacher = nullptr;
			if (res) {
				Helper::gotoxy(35, 23);
				SetConsoleTextAttribute(hM, 0 | BACKGROUND_GREEN);
				cout << "Account is created\n";
				SetConsoleTextAttribute(hM, 15);
			}

			else {
				Helper::gotoxy(35, 23);
				SetConsoleTextAttribute(hM, 0 | BACKGROUND_RED);
				cout << "Fail to create Account\n";
				SetConsoleTextAttribute(hM, 15);
			}
		}
		else {
			int student_id;
			SetConsoleTextAttribute(hM, 0 | BACKGROUND_BLUE);
			Helper::gotoxy(10, 16);
			cout << "Enter Student ID";
			SetConsoleTextAttribute(hM, 15);
			cout << ": ";
			Helper::gotoxy(29, 16);
			cin >> student_id;
			Helper::gotoxy(29, 16);
			cin.ignore(cin.rdbuf()->in_avail());


			Student* newStudent = new Student(firstName, lastName, student_id, age);
			bool res = listOfDepartments[i]->createStudentAccount(newStudent);
			if (newStudent != nullptr)
				newStudent = nullptr;

			if (res) {
				Helper::gotoxy(35, 23);
				SetConsoleTextAttribute(hM, 0 | BACKGROUND_GREEN);
				cout << "Account is created\n";
				SetConsoleTextAttribute(hM, 15);
			}
			else {
				Helper::gotoxy(35, 23);
				SetConsoleTextAttribute(hM, 0 | BACKGROUND_RED);
				cout << "Fail to create Account\n";
				SetConsoleTextAttribute(hM, 15);
			}
		}
	}
	else if (choice == '2' || choice == '4') {

		//diaplay teachers or students
		if(choice == '2')
			printEntity(i, 't');
		else
			printEntity(i, 's');
		
		int id;
		SetConsoleTextAttribute(hM, 0 | BACKGROUND_BLUE);
		Helper::gotoxy(10, 12);
		cout << "Enter ID";
		SetConsoleTextAttribute(hM, 15);
		cout << ": ";
		Helper::gotoxy(23, 12);
		cin.get();
		Helper::gotoxy(23, 12);
		cin.ignore(cin.rdbuf()->in_avail());
		Helper::gotoxy(23, 12);
		cin >> id;
		Helper::gotoxy(23, 12);
		cin.ignore(cin.rdbuf()->in_avail());

		if (choice == '2') {
			bool res = listOfDepartments[i]->deleteTeacherAccount(id);
			if (res) {
				Helper::gotoxy(35, 23);
				SetConsoleTextAttribute(hM, 0 | BACKGROUND_GREEN);
				cout << "Account is deleted\n";
				SetConsoleTextAttribute(hM, 15);
			}
			else {
				Helper::gotoxy(35, 23);
				SetConsoleTextAttribute(hM, 0 | BACKGROUND_RED);
				cout << "Fail to delete Account\n";
				SetConsoleTextAttribute(hM, 15);
			}
		}
		else {
			bool res = listOfDepartments[i]->deleteStudentAccount(id);
			if (res) {
				Helper::gotoxy(35, 23);
				SetConsoleTextAttribute(hM, 0 | BACKGROUND_GREEN);
				cout << "Account is deleted\n";
				SetConsoleTextAttribute(hM, 15);
			}
			else {
				Helper::gotoxy(35, 23);
				SetConsoleTextAttribute(hM, 0 | BACKGROUND_RED);
				cout << "Fail to delete Account\n";
				SetConsoleTextAttribute(hM, 15);
			}
		}
	}
	else if (choice == '5') {
		char ch = getChoice('7', 4) + 48;

		system("cls");
		Sleep(130);

		if (ch == '1' || ch == '3') {
			
			//diaplay teachers or students
			if (choice == '3')
				printEntity(i, 't');
			else
				printEntity(i, 's');
			
			int id;
			system("cls");
			SetConsoleTextAttribute(hM, 0 | BACKGROUND_BLUE);
			Helper::gotoxy(10, 12);
			cout << "Enter ID";
			SetConsoleTextAttribute(hM, 15);
			cout << ": ";
			Helper::gotoxy(20, 12);
			cin.get();
			Helper::gotoxy(20, 12);
			cin.get();
			Helper::gotoxy(20, 12);
			cin.ignore(cin.rdbuf()->in_avail());
			Helper::gotoxy(20, 12);
			cin >> id;
			Helper::gotoxy(20, 12);
			cin.ignore(cin.rdbuf()->in_avail());

		
			char uN[50];
			SetConsoleTextAttribute(hM, 0 | BACKGROUND_BLUE);
			Helper::gotoxy(10, 14);
			cout << "Enter New Username";
			SetConsoleTextAttribute(hM, 15);
			cout << ": ";
			Helper::gotoxy(30, 14);
			cin >> uN;
			Helper::gotoxy(30, 14);
			cin.ignore(cin.rdbuf()->in_avail());


			if (ch == '1') {
				bool res = listOfDepartments[i]->changeStudentUserName(id, uN);
				if (res) {
					Helper::gotoxy(35, 23);
					SetConsoleTextAttribute(hM, 0 | BACKGROUND_GREEN);
					cout << "Username Is Changed\n";
					SetConsoleTextAttribute(hM, 15);
				}
				else {
					Helper::gotoxy(35, 23);
					SetConsoleTextAttribute(hM, 0 | BACKGROUND_RED);
					cout << "Fail to Change Username\n";
					SetConsoleTextAttribute(hM, 15);
				}
			}
			else {
				bool res = listOfDepartments[i]->changeTeacherUserName(id, uN);
				if (res) {
					Helper::gotoxy(35, 23);
					SetConsoleTextAttribute(hM, 0 | BACKGROUND_GREEN);
					cout << "Username Is Changed\n";
					SetConsoleTextAttribute(hM, 15);
				}
				else {
					Helper::gotoxy(35, 23);
					SetConsoleTextAttribute(hM, 0 | BACKGROUND_RED);
					cout << "Fail to Change Username\n";
					SetConsoleTextAttribute(hM, 15);
				}
			}
		}
		else if (ch == '2' || ch == '4') {
			
			//diaplay teachers or students
			if (choice == '4')
				printEntity(i, 't');
			else
				printEntity(i, 's');
			
			int id;
			SetConsoleTextAttribute(hM, 0 | BACKGROUND_BLUE);
			Helper::gotoxy(10, 12);
			cout << "Enter ID";
			SetConsoleTextAttribute(hM, 15);
			cout << ": ";
			Helper::gotoxy(20, 12);
			cin.get();
			Helper::gotoxy(20, 12);
			cin.get();
			Helper::gotoxy(20, 12);
			cin.ignore(cin.rdbuf()->in_avail());
			Helper::gotoxy(20, 12);
			cin.ignore(cin.rdbuf()->in_avail());
			Helper::gotoxy(20, 12);
			cin >> id;
			Helper::gotoxy(20, 12);
			cin.ignore(cin.rdbuf()->in_avail());


			char pw[50];
			SetConsoleTextAttribute(hM, 0 | BACKGROUND_BLUE);
			Helper::gotoxy(10, 14);
			cout << "Enter New Password";
			SetConsoleTextAttribute(hM, 15);
			cout << ": ";
			Helper::gotoxy(30, 14);
			cin >> pw;
			Helper::gotoxy(30, 14);
			cin.ignore(cin.rdbuf()->in_avail());

			if (ch == '2') {
				bool res = listOfDepartments[i]->changeStudentPassword(id, pw);
				if (res)
				{
					Helper::gotoxy(35, 23);
					SetConsoleTextAttribute(hM, 0 | BACKGROUND_GREEN);
					cout << "Password Is Changed\n";
					SetConsoleTextAttribute(hM, 15);
				}
				else
				{
					Helper::gotoxy(35, 23);
					SetConsoleTextAttribute(hM, 0 | BACKGROUND_RED);
					cout << "Fail to Change Password\n";
					SetConsoleTextAttribute(hM, 15);
				}
			}
			else {
				bool res = listOfDepartments[i]->changeTeacherPassword(id, pw);
				if (res)
				{
					Helper::gotoxy(35, 23);
					SetConsoleTextAttribute(hM, 0 | BACKGROUND_GREEN);
					cout << "Password Is Changed\n";
					SetConsoleTextAttribute(hM, 15);
				}
				else
				{
					Helper::gotoxy(35, 23);
					SetConsoleTextAttribute(hM, 0 | BACKGROUND_RED);
					cout << "Fail to Change Password\n";
					SetConsoleTextAttribute(hM, 15);
				}
			}
		}
		else {
			Helper::gotoxy(35, 23);
			SetConsoleTextAttribute(hM, 0 | BACKGROUND_RED);
			cout << "Invalid Choice !!!\n";
			SetConsoleTextAttribute(hM, 15);
		}
	}
	else if (choice == '6') {
		system("CLS");
		listOfDepartments[i]->displayStudents();
	}

	else if (choice == '7') {
		system("CLS");
		listOfDepartments[i]->displayTeachers();
	}

	else if (choice == '8') {
		system("CLS");
		listOfDepartments[i]->displayCourses();
	}

	else if (choice == '9') {
		Sleep(150);
		return 6;
	}

	system("pause");
	Sleep(100);
	itManagerLogin(dep, i);
}
int University::teacherLogin(int i, const char* username, const char* _password) {
	system("CLS");
	char choice = getChoice('3', 7) + 48;
	char courseCode[20] = { 0 };
	system("CLS");
	Sleep(100);
	if (choice == '1' || choice == '6') {

		//diaplay students
		printEntity(i, 's');

		int id;
		SetConsoleTextAttribute(hM, 0 | BACKGROUND_BLUE);
		Helper::gotoxy(10, 10);
		cout << "Enter Student ID";
		SetConsoleTextAttribute(hM, 15);
		cout << ": ";
		Helper::gotoxy(29, 10);
		cin.get();
		Helper::gotoxy(29, 10);
		cin.ignore(cin.rdbuf()->in_avail());
		Helper::gotoxy(29, 10);
		cin >> id;
		Helper::gotoxy(29, 10);
		cin.ignore(cin.rdbuf()->in_avail());

		system("cls");

		//print available courses details
		int teacher_id = listOfDepartments[i]->getIDOfTeacher(username, _password);
		if (listOfDepartments[i]->checkHODAccount(username, _password))
			printCourses(i, '3', teacher_id);
		else
			printCourses(i, '2', teacher_id);

		SetConsoleTextAttribute(hM, 0 | BACKGROUND_BLUE);
		Helper::gotoxy(10, 12);
		char courseCode[20];
		cout << "Enter Course Code";
		SetConsoleTextAttribute(hM, 15);
		cout << ": ";
		Helper::gotoxy(29, 12);
		cin >> courseCode;
		Helper::gotoxy(29, 12);
		cin.ignore(cin.rdbuf()->in_avail());

		if (choice == '1') {
			float attPer;
			SetConsoleTextAttribute(hM, 0 | BACKGROUND_BLUE);
			Helper::gotoxy(10, 14);
			cout << "Enter Student Attendance Percentage";
			SetConsoleTextAttribute(hM, 15);
			cout << ": ";
			Helper::gotoxy(49, 14);
			cin >> attPer;
			Helper::gotoxy(49, 14);
			cin.ignore(cin.rdbuf()->in_avail());

			bool res = listOfDepartments[i]->manageAttendancePer(username, id, attPer, courseCode);
			if (res) {
				Helper::gotoxy(35, 23);
				SetConsoleTextAttribute(hM, 0 | BACKGROUND_GREEN);
				cout << "Attendance Is Updated\n";
				SetConsoleTextAttribute(hM, 15);
			}

			else {
				Helper::gotoxy(35, 23);
				SetConsoleTextAttribute(hM, 0 | BACKGROUND_RED);
				cout << "Fail to Update Attendance\n";
				SetConsoleTextAttribute(hM, 15);
			}
		}
		else {
			bool res = listOfDepartments[i]->changeTA(username, id, courseCode);
			if (res) {
				Helper::gotoxy(35, 23);
				SetConsoleTextAttribute(hM, 0 | BACKGROUND_GREEN);
				cout << "TA Is Changed Successfully\n";
				SetConsoleTextAttribute(hM, 15);
			}

			else {
				Helper::gotoxy(35, 23);
				SetConsoleTextAttribute(hM, 0 | BACKGROUND_RED);
				cout << "Fail to Change TA\n";
				SetConsoleTextAttribute(hM, 15);
			}
		}
	}
	else if (choice == '2') {
		//print available courses details
		int teacher_id = listOfDepartments[i]->getIDOfTeacher(username, _password);
		if (listOfDepartments[i]->checkHODAccount(username, _password))
			printCourses(i, '3', teacher_id);
		else
			printCourses(i, '2', teacher_id);

		SetConsoleTextAttribute(hM, 0 | BACKGROUND_BLUE);
		Helper::gotoxy(10, 10);
		char courseCode[20];
		cout << "Enter Course Code";
		SetConsoleTextAttribute(hM, 15);
		cout << ": ";
		Helper::gotoxy(29, 10);
		cin.get();
		Helper::gotoxy(29, 10);
		cin.ignore(cin.rdbuf()->in_avail());
		Helper::gotoxy(29, 10);
		cin >> courseCode;
		Helper::gotoxy(29, 10);
		cin.ignore(cin.rdbuf()->in_avail());

		listOfDepartments[i]->viewAttendanceOfAllStudent(username, courseCode);
	}
	else if (choice == '3') {

		//diaplay students
		printEntity(i, 's');

		int id;
		SetConsoleTextAttribute(hM, 0 | BACKGROUND_BLUE);
		Helper::gotoxy(10, 10);
		cout << "Enter Student ID";
		SetConsoleTextAttribute(hM, 15);
		cout << ": ";
		Helper::gotoxy(29, 10);
		cin.get();
		Helper::gotoxy(29, 10);
		cin.ignore(cin.rdbuf()->in_avail());
		Helper::gotoxy(29, 10);
		cin >> id;
		Helper::gotoxy(29, 10);
		cin.ignore(cin.rdbuf()->in_avail());

		system("cls");

		//print available courses details
		int teacher_id = listOfDepartments[i]->getIDOfTeacher(username, _password);
		if (listOfDepartments[i]->checkHODAccount(username, _password))
			printCourses(i, '3', teacher_id);
		else
			printCourses(i, '2', teacher_id);

		SetConsoleTextAttribute(hM, 0 | BACKGROUND_BLUE);
		Helper::gotoxy(10, 12);
		char courseCode[20];
		cout << "Enter Course Code";
		SetConsoleTextAttribute(hM, 15);
		cout << ": ";
		Helper::gotoxy(29, 12);
		cin >> courseCode;
		Helper::gotoxy(29, 12);
		cin.ignore(cin.rdbuf()->in_avail());

		float gpa;
		SetConsoleTextAttribute(hM, 0 | BACKGROUND_BLUE);
		Helper::gotoxy(10, 14);
		cout << "Enter Student GPA";
		SetConsoleTextAttribute(hM, 15);
		cout << ": ";
		Helper::gotoxy(30, 14);
		cin >> gpa;
		Helper::gotoxy(30, 14);
		cin.ignore(cin.rdbuf()->in_avail());

		float gt;
		SetConsoleTextAttribute(hM, 0 | BACKGROUND_BLUE);
		Helper::gotoxy(10, 16);
		cout << "Enter Student GT";
		SetConsoleTextAttribute(hM, 15);
		cout << ": ";
		Helper::gotoxy(30, 16);
		cin >> gt;
		Helper::gotoxy(30, 16);
		cin.ignore(cin.rdbuf()->in_avail());

		bool res = listOfDepartments[i]->manageEvaluationOfAStudent(username, id, gpa, gt, courseCode);
		if (res) {
			Helper::gotoxy(35, 23);
			SetConsoleTextAttribute(hM, 0 | BACKGROUND_GREEN);
			cout << "MarkSheet Is Updated\n";
			SetConsoleTextAttribute(hM, 15);
		}

		else {
			Helper::gotoxy(35, 23);
			SetConsoleTextAttribute(hM, 0 | BACKGROUND_RED);
			cout << "Fail to Update MarkSheet\n";
			SetConsoleTextAttribute(hM, 15);
		}
	}
	else if (choice == '4') {

		//print available courses details
		int teacher_id = listOfDepartments[i]->getIDOfTeacher(username, _password);
		if (listOfDepartments[i]->checkHODAccount(username, _password))
			printCourses(i, '3', teacher_id);
		else
			printCourses(i, '2', teacher_id);

		SetConsoleTextAttribute(hM, 0 | BACKGROUND_BLUE);
		Helper::gotoxy(10, 10);
		char courseCode[20];
		cout << "Enter Course Code";
		SetConsoleTextAttribute(hM, 15);
		cout << ": ";
		Helper::gotoxy(29, 10);
		cin.get();
		Helper::gotoxy(29, 10);
		cin.ignore(cin.rdbuf()->in_avail());
		Helper::gotoxy(29, 10);
		cin >> courseCode;
		Helper::gotoxy(29, 10);
		cin.ignore(cin.rdbuf()->in_avail());


		listOfDepartments[i]->viewEvaluationOfAllStudents(username, courseCode);
	}
	else if (choice == '5') {
		//diaplay students
		printEntity(i, 's');

		int id;
		SetConsoleTextAttribute(hM, 0 | BACKGROUND_BLUE);
		Helper::gotoxy(10, 10);
		cout << "Enter Student ID";
		SetConsoleTextAttribute(hM, 15);
		cout << ": ";
		Helper::gotoxy(29, 10);
		cin.get();
		Helper::gotoxy(29, 10);
		cin.ignore(cin.rdbuf()->in_avail());
		Helper::gotoxy(29, 10);
		cin >> id;
		Helper::gotoxy(29, 10);
		cin.ignore(cin.rdbuf()->in_avail());

		system("cls");

		//print available courses details
		int teacher_id = listOfDepartments[i]->getIDOfTeacher(username, _password);
		if (listOfDepartments[i]->checkHODAccount(username, _password))
			printCourses(i, '3', teacher_id);
		else
			printCourses(i, '2', teacher_id);

		SetConsoleTextAttribute(hM, 0 | BACKGROUND_BLUE);
		Helper::gotoxy(10, 12);
		char courseCode[20];
		cout << "Enter Course Code";
		SetConsoleTextAttribute(hM, 15);
		cout << ": ";
		Helper::gotoxy(29, 12);
		cin >> courseCode;
		Helper::gotoxy(29, 12);
		cin.ignore(cin.rdbuf()->in_avail());

		char grade;
		SetConsoleTextAttribute(hM, 0 | BACKGROUND_BLUE);
		Helper::gotoxy(10, 14);
		cout << "Enter Student Grade";
		SetConsoleTextAttribute(hM, 15);
		cout << ": ";
		Helper::gotoxy(31, 14);
		cin >> grade;
		Helper::gotoxy(31, 14);
		cin.ignore(cin.rdbuf()->in_avail());

		bool res = listOfDepartments[i]->assignGradeToStudent(username, id, grade, courseCode);

		if (res) {
			Helper::gotoxy(35, 23);
			SetConsoleTextAttribute(hM, 0 | BACKGROUND_GREEN);
			cout << "Grade Is Assigned Successfully\n";
			SetConsoleTextAttribute(hM, 15);
		}

		else {
			Helper::gotoxy(35, 23);
			SetConsoleTextAttribute(hM, 0 | BACKGROUND_RED);
			cout << "Fail to Assign Course\n";
			SetConsoleTextAttribute(hM, 15);
		}
	}
	else {
		Sleep(100);
		return 6;
	}

	system("pause");
	Sleep(100);
	teacherLogin(i, username, _password);
}
int University::studentLogin(int i, const char* username, int std_ID) {
	system("CLS");
	char choice = getChoice('4',7)+48;
	system("CLS");
	Sleep(100);
	if (choice == '1' || choice == '2' || choice == '3' || choice == '5') {
		char courseCode[20];

		//print available courses details
		if (choice == '1')
			printNonRegCourses(i,'s', std_ID);
		else
			printCourses(i,'1',std_ID);

		SetConsoleTextAttribute(hM, 0 | BACKGROUND_BLUE);
		Helper::gotoxy(10, 10);
		cout << "Enter Course Code";
		SetConsoleTextAttribute(hM, 15);
		cout << ": ";
		Helper::gotoxy(29, 10);
		cin.get();
		Helper::gotoxy(29, 10);
		cin.ignore(cin.rdbuf()->in_avail());
		Helper::gotoxy(29, 10);
		cin >> courseCode;
		Helper::gotoxy(29, 10);
		cin.ignore(cin.rdbuf()->in_avail());

		if (choice == '1') {
			bool res = listOfDepartments[i]->registerCourse(username, courseCode);
			if (res) {
				Helper::gotoxy(35, 23);
				SetConsoleTextAttribute(hM, 0 | BACKGROUND_GREEN);
				cout << "Course is registered Successfully\n";
				SetConsoleTextAttribute(hM, 15);
			}

			else {
				Helper::gotoxy(35, 23);
				SetConsoleTextAttribute(hM, 0 | BACKGROUND_RED);
				cout << "Fail to Register Course\n";
				SetConsoleTextAttribute(hM, 15);
			}
		}
		else if (choice == '2' || choice == '3') {
			bool res = listOfDepartments[i]->unRegisterCourse(username, courseCode , choice);
			if (res) {
				Helper::gotoxy(35, 23);
				SetConsoleTextAttribute(hM, 0 | BACKGROUND_GREEN);
				if(choice=='2')
					cout << "Course Is Unregistered Successfully\n";
				else
					cout << "Course Is Withdraw Successfully\n";
				SetConsoleTextAttribute(hM, 15);
			}

			else {
				Helper::gotoxy(35, 23);
				SetConsoleTextAttribute(hM, 0 | BACKGROUND_RED);
				if(choice=='2')
					cout << "Fail to UnRegister Course\n";
				else
					cout << "Fail to Withdraw Course\n";
				SetConsoleTextAttribute(hM, 15);
			}
		}
		else
			listOfDepartments[i]->viewAttendance(username, courseCode);
	}
	else if (choice == '4') {
		//print available courses details
		printCourses(i,'1', std_ID);

		char courseCode[20];
		SetConsoleTextAttribute(hM, 0 | BACKGROUND_BLUE);
		Helper::gotoxy(10, 10);
		cout << "Enter Course Code";
		SetConsoleTextAttribute(hM, 15);
		cout << ": ";
		Helper::gotoxy(29, 10);
		cin.get();
		Helper::gotoxy(29, 10);
		cin.ignore(cin.rdbuf()->in_avail());
		Helper::gotoxy(29, 10);
		cin >> courseCode;
		Helper::gotoxy(29, 10);
		cin.ignore(cin.rdbuf()->in_avail());

		listOfDepartments[i]->viewMarkSheet(username, courseCode);
	}
	else if (choice == '6') {
		char pw[50];
		SetConsoleTextAttribute(hM, 0 | BACKGROUND_BLUE);
		Helper::gotoxy(10, 12);
		cout << "Enter New Password";
		SetConsoleTextAttribute(hM, 15);
		cout << ": ";
		Helper::gotoxy(29, 12);
		cin.get();
		Helper::gotoxy(29, 12);
		cin.ignore(cin.rdbuf()->in_avail());
		Helper::gotoxy(29, 12);
		cin >> pw;
		Helper::gotoxy(29, 12);
		cin.ignore(cin.rdbuf()->in_avail());

		bool res = listOfDepartments[i]->changePassword(username, pw);
		if (res) {
			Helper::gotoxy(35, 23);
			SetConsoleTextAttribute(hM, 0 | BACKGROUND_GREEN);
			cout << "Password Is Changed\n";
			SetConsoleTextAttribute(hM, 15);
		}

		else {
			Helper::gotoxy(35, 23);
			SetConsoleTextAttribute(hM, 0 | BACKGROUND_RED);
			cout << "Fail to Change Password\n";
			SetConsoleTextAttribute(hM, 15);
		}	
	}
	else {
		Sleep(100);
		return 6;
	}

	system("pause");
	Sleep(100);
	studentLogin(i, username, std_ID);
}
int University::taLogin(int i, const char* username, const char* _courseCode){
	system("CLS");
	char choice = getChoice('5', 5)+48;
	system("CLS");
	Sleep(100);
	if (choice == '1') {
		
		//diaplay students
		printEntity(i, 's');
		
		int id;
		SetConsoleTextAttribute(hM, 0 | BACKGROUND_BLUE);
		Helper::gotoxy(10, 10);
		cout << "Enter Student ID: ";
		SetConsoleTextAttribute(hM, 15);
		cout << ": ";
		Helper::gotoxy(31, 10);
		cin.get();
		Helper::gotoxy(31, 10);
		cin.ignore(cin.rdbuf()->in_avail());
		Helper::gotoxy(31, 10);
		cin >> id;
		Helper::gotoxy(31, 10);
		cin.ignore(cin.rdbuf()->in_avail());

		if (choice == '1') {
			float attPer;
			SetConsoleTextAttribute(hM, 0 | BACKGROUND_BLUE);
			Helper::gotoxy(10, 12);
			cout << "Enter Student Attendance Percentage";
			SetConsoleTextAttribute(hM, 15);
			cout << ": ";
			Helper::gotoxy(50, 12);
			cin >> attPer;
			Helper::gotoxy(50, 12);
			cin.ignore(cin.rdbuf()->in_avail());

			bool res = listOfDepartments[i]->taManageAttendancePer(id, attPer, _courseCode);
			if (res) {
				Helper::gotoxy(35, 23);
				SetConsoleTextAttribute(hM, 0 | BACKGROUND_GREEN);
				cout << "Attendance Is Updated\n";
				SetConsoleTextAttribute(hM, 15);
			}
			else {
				Helper::gotoxy(35, 23);
				SetConsoleTextAttribute(hM, 0 | BACKGROUND_RED);
				cout << "Fail to Update Attendance\n";
				SetConsoleTextAttribute(hM, 15);
			}
		}
	}
	else if (choice == '2') {
		listOfDepartments[i]->taViewAttendanceOfAStudent(_courseCode);
	}
	else if (choice == '3') {
		
		//diaplay students
		printEntity(i, 's');
		
		int id;
		SetConsoleTextAttribute(hM, 0 | BACKGROUND_BLUE);
		Helper::gotoxy(10, 10);
		cout << "Enter Student ID: ";
		SetConsoleTextAttribute(hM, 15);
		cout << ": ";
		Helper::gotoxy(29, 10);
		cin.get();
		Helper::gotoxy(29, 10);
		cin.ignore(cin.rdbuf()->in_avail());
		Helper::gotoxy(29, 10);
		cin >> id;
		Helper::gotoxy(29, 10);
		cin.ignore(cin.rdbuf()->in_avail());
		
		float gpa;
		SetConsoleTextAttribute(hM, 0 | BACKGROUND_BLUE);
		Helper::gotoxy(10, 12);
		cout << "Enter Student GPA";
		SetConsoleTextAttribute(hM, 15);
		cout << ": ";
		Helper::gotoxy(30, 12);
		cin >> gpa;
		Helper::gotoxy(30, 12);
		cin.ignore(cin.rdbuf()->in_avail());

		float gt;
		SetConsoleTextAttribute(hM, 0 | BACKGROUND_BLUE);
		Helper::gotoxy(10, 14);
		cout << "Enter Student GT";
		SetConsoleTextAttribute(hM, 15);
		cout << ": ";
		Helper::gotoxy(30, 14);
		cin >> gt;
		Helper::gotoxy(30, 14);
		cin.ignore(cin.rdbuf()->in_avail());

		bool res = listOfDepartments[i]->taManageEvaluationOfAStudent(id, gpa, gt, _courseCode);
		if (res) {
			Helper::gotoxy(35, 23);
			SetConsoleTextAttribute(hM, 0 | BACKGROUND_GREEN);
			cout << "MarkSheet Is Updated\n";
			SetConsoleTextAttribute(hM, 15);
		}

		else {
			Helper::gotoxy(35, 23);
			SetConsoleTextAttribute(hM, 0 | BACKGROUND_RED);
			cout << "Fail to Update MarkSheet\n";
			SetConsoleTextAttribute(hM, 15);
		}
	}
	else if (choice == '4') {
		listOfDepartments[i]->taViewEvaluationOfAllStudents(_courseCode);
	}
	else{
		Sleep(100);
		return 6;
	}

	system("pause");
	Sleep(100);
	taLogin(i, username, _courseCode);
}

//print Instructions
void University::printInstructions() {
	SetConsoleTextAttribute(hM, 0 | BACKGROUND_GREEN | BACKGROUND_RED);
	Helper::gotoxy(90, 14);
	cout << "Instructions: ";
	SetConsoleTextAttribute(hM, 0 | BACKGROUND_GREEN | BACKGROUND_RED);
	Helper::gotoxy(94, 16);
	cout << "Use \"arrow up\" Key To Go UP";
	SetConsoleTextAttribute(hM, 0 | BACKGROUND_GREEN | BACKGROUND_RED);
	Helper::gotoxy(94, 18);
	cout << "Use \"arrow down\" Key To Go Down";
	SetConsoleTextAttribute(hM, 0 | BACKGROUND_GREEN | BACKGROUND_RED);
	Helper::gotoxy(94, 20);
	cout << "Use \"enter\" Key For Selection\n\n\n\n";
	SetConsoleTextAttribute(hM, 15);
}

//print menu bar
void University::printDepartmentName() {
	printInstructions();

	SetConsoleTextAttribute(hM, 0 | BACKGROUND_BLUE | BACKGROUND_RED | BACKGROUND_INTENSITY);
	Helper::gotoxy(63, 2);
	cout << setw(40) << "";
	Helper::gotoxy(63, 3);
	cout <<setw(7)<< " " << " Departments In University"<<setw(7)<<" ";
	Helper::gotoxy(63, 4);
	cout << setw(40) << "";
	SetConsoleTextAttribute(hM, 15);	
	
	for (int i = 0; i < currentDepartment; i++) {
		SetConsoleTextAttribute(hM, 0 | BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED | BACKGROUND_INTENSITY);
		Helper::gotoxy(10, 10+(4*i));
		cout << setw(35) << "";
		Helper::gotoxy(10, 11 + (4 * i));
		cout << "       " << listOfDepartments[i]->getName();
		int wx = Helper::wherex();

		for (int j = wx; j < 45; j++){
			SetConsoleTextAttribute(hM, 0 | BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED | BACKGROUND_INTENSITY);
			Helper::gotoxy(j, 11 + (4 * i));
			cout <<setw(1)<<" ";
		}
		
		Helper::gotoxy(10, 12+4*i);
		cout << setw(35) << "";
		SetConsoleTextAttribute(hM, 15);
	}
}
void University::printChoice() {
	printInstructions();
	SetConsoleTextAttribute(hM, 0 | BACKGROUND_BLUE | BACKGROUND_RED | BACKGROUND_INTENSITY);
	Helper::gotoxy(63, 2);
	cout << setw(40) << "";
	Helper::gotoxy(63, 3);
	cout << setw(12) << " " << " Different Modes" << setw(12) << " ";
	Helper::gotoxy(63, 4);
	cout << setw(40) << "";
	SetConsoleTextAttribute(hM, 15);
	
	SetConsoleTextAttribute(hM, 0 | BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED | BACKGROUND_INTENSITY);
	Helper::gotoxy(10, 10);
	cout << setw(22) << "";
	Helper::gotoxy(10, 11);
	cout <<"     "<<setw(10)<< "HOD Mode "<<setw(5)<<"       ";
	Helper::gotoxy(10, 12);
	cout << setw(22)<<"";

	Helper::gotoxy(10, 14);
	cout << setw(22) << "";
	Helper::gotoxy(10, 15);
	cout << "  "<< setw(5) << "IT Manager Mode" << setw(5) << "  ";
	Helper::gotoxy(10, 16);
	cout << setw(22) << "";


	Helper::gotoxy(10, 18);
	cout << setw(22) << "";
	Helper::gotoxy(10, 19);
	cout <<  "     " << setw(5) << "Teacher Mode" << setw(5) << "     ";
	Helper::gotoxy(10, 20);
	cout << setw(22) << "";

	Helper::gotoxy(10, 22);
	cout << setw(22) << "";
	Helper::gotoxy(10, 23);
	cout <<  "     " << setw(5) << "Student Mode" << setw(5) << "     ";
	Helper::gotoxy(10, 24);
	cout << setw(22) << "";

	Helper::gotoxy(10, 26);
	cout << setw(22) << "";
	Helper::gotoxy(10, 27);
	cout <<  "        " << setw(5) << "TA Mode" << setw(5) << "       ";
	Helper::gotoxy(10, 28);
	cout << setw(22) << "";

	Helper::gotoxy(10, 30);
	cout << setw(22) << "";
	Helper::gotoxy(10, 31);
	cout << "       " <<setw(5)<< "To Exit" << setw(5) << "        ";
	Helper::gotoxy(10, 32);
	cout << setw(22) << "";

	SetConsoleTextAttribute(hM, 15);
}
void University::printHODChoice() {
	printInstructions(); 
	SetConsoleTextAttribute(hM, 0 | BACKGROUND_BLUE | BACKGROUND_RED | BACKGROUND_INTENSITY);
	Helper::gotoxy(63, 2);
	cout << setw(30) << "";
	Helper::gotoxy(63, 3);
	cout << setw(11) << " " << "HOD MODE" << setw(11) << " ";
	Helper::gotoxy(63, 4);
	cout << setw(30) << "";
	SetConsoleTextAttribute(hM, 15);

	SetConsoleTextAttribute(hM, 0 | BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED | BACKGROUND_INTENSITY);
	Helper::gotoxy(10, 10);
	cout << setw(44) << "";
	Helper::gotoxy(10, 11);
	cout << "        " << setw(10) << "Assign Course To Teacher" << setw(5) << "            ";
	Helper::gotoxy(10, 12);
	cout << setw(44) << "";

	Helper::gotoxy(10, 14);
	cout << setw(44) << "";
	Helper::gotoxy(10, 15);
	cout << "     " << setw(10) << "Register Course For A Student" << setw(5) << "          ";
	Helper::gotoxy(10, 16);
	cout << setw(44) << "";

	Helper::gotoxy(10, 18);
	cout << setw(44) << "";
	Helper::gotoxy(10, 19);
	cout << "     " << setw(10) << "Unregister Course For A Student" << setw(5) << "        ";
	Helper::gotoxy(10, 20);
	cout << setw(44) << "";

	Helper::gotoxy(10, 22);
	cout << setw(44) << "";
	Helper::gotoxy(10, 23);
	cout << "     " << setw(10) << "View grades of a specific course" << setw(5) << "       ";
	Helper::gotoxy(10, 24);
	cout << setw(44) << "";

	Helper::gotoxy(10, 26);
	cout << setw(44) << "";
	Helper::gotoxy(10, 27);
	cout << "     " << setw(10) << "Display List Of Students" << setw(5) << "               ";
	Helper::gotoxy(10, 28);
	cout << setw(44) << "";

	Helper::gotoxy(10, 30);
	cout << setw(44) << "";
	Helper::gotoxy(10, 31);
	cout << "     " << setw(10) << "Display List Of Teachers" << setw(5) << "               ";
	Helper::gotoxy(10, 32);
	cout << setw(44) << "";

	Helper::gotoxy(10, 34);
	cout << setw(44) << "";
	Helper::gotoxy(10, 35);
	cout << "     " << setw(10) << "Display List Of Courses" << setw(5) << "                ";
	Helper::gotoxy(10, 36);
	cout << setw(44) << "";


	Helper::gotoxy(10, 38);
	cout << setw(44) << "";
	Helper::gotoxy(10, 39);
	cout << "               " << setw(10) << "To Go Back" << setw(5) << "                   ";
	Helper::gotoxy(10, 40);
	cout << setw(44) << "";
}
void University::printITManagerChoice() {
	printInstructions(); 
	SetConsoleTextAttribute(hM, 0 | BACKGROUND_BLUE | BACKGROUND_RED | BACKGROUND_INTENSITY);
	Helper::gotoxy(63, 2);
	cout << setw(32) << "";
	Helper::gotoxy(63, 3);
	cout << setw(9) << " " << "IT MANAGER MODE" << setw(8) << " ";
	Helper::gotoxy(63, 4);
	cout << setw(32) << "";
	SetConsoleTextAttribute(hM, 15);

	SetConsoleTextAttribute(hM, 0 | BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED | BACKGROUND_INTENSITY);
	Helper::gotoxy(10, 10);
	cout << setw(44) << "";
	Helper::gotoxy(10, 11);
	cout << "     " << setw(10) << "Create account of faculty members"<< setw(5) << "      ";
	Helper::gotoxy(10, 12);
	cout << setw(44) << "";

	Helper::gotoxy(10, 14);
	cout << setw(44) << "";
	Helper::gotoxy(10, 15);
	cout << "     " << setw(10) << "Delete account of faculty members" << setw(5) << "      ";
	Helper::gotoxy(10, 16);
	cout << setw(44) << "";

	Helper::gotoxy(10, 18);
	cout << setw(44) << "";
	Helper::gotoxy(10, 19);
	cout << "     " << setw(10) << "Create account of students" << setw(5) << "             ";
	Helper::gotoxy(10, 20);
	cout << setw(44) << "";

	Helper::gotoxy(10, 22);
	cout << setw(44) << "";
	Helper::gotoxy(10, 23);
	cout << "     " << setw(10) << "Delete accounts of students" << setw(5) << "            ";
	Helper::gotoxy(10, 24);
	cout << setw(44) << "";

	Helper::gotoxy(10, 26);
	cout << setw(44) << "";
	Helper::gotoxy(10, 27);
	cout << "     " << setw(10) << "Maintain accounts" << setw(5) << "                      ";
	Helper::gotoxy(10, 28);
	cout << setw(44) << "";

	Helper::gotoxy(10, 30);
	cout << setw(44) << "";
	Helper::gotoxy(10, 31);
	cout << "     " << setw(10) << "Display List Of Students" << setw(5) << "               ";
	Helper::gotoxy(10, 32);
	cout << setw(44) << "";

	Helper::gotoxy(10, 34);
	cout << setw(44) << "";
	Helper::gotoxy(10, 35);
	cout << "     " << setw(10) << "Display List Of Teachers" << setw(5) << "               ";
	Helper::gotoxy(10, 36);
	cout << setw(44) << "";

	Helper::gotoxy(10, 38);
	cout << setw(44) << "";
	Helper::gotoxy(10, 39);
	cout << "     " << setw(10) << "Display List Of Courses" << setw(5) << "                ";
	Helper::gotoxy(10, 40);
	cout << setw(44) << "";

	Helper::gotoxy(10, 42);
	cout << setw(44) << "";
	Helper::gotoxy(10, 43);
	cout << "               " << setw(10) << "To Go Back" << setw(5) << "                   ";
	Helper::gotoxy(10, 44);
	cout << setw(44) << "";
}
void University::printIT_SubChoice() {
	printInstructions();
	SetConsoleTextAttribute(hM, 0 | BACKGROUND_BLUE | BACKGROUND_RED | BACKGROUND_INTENSITY);
	Helper::gotoxy(63, 2);
	cout << setw(40) << "";
	Helper::gotoxy(63, 3);
	cout << setw(11) << " " << " MAINTAIN ACCOUNTS" << setw(11) << " ";
	Helper::gotoxy(63, 4);
	cout << setw(40) << "";
	SetConsoleTextAttribute(hM, 15);

	SetConsoleTextAttribute(hM, 0 | BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED | BACKGROUND_INTENSITY);
	Helper::gotoxy(10, 10);
	cout << setw(34) << "";
	Helper::gotoxy(10, 11);
	cout << "     " << setw(10) << "Change Student Username" << setw(5) << "      ";
	Helper::gotoxy(10, 12);
	cout << setw(34) << "";
		
	Helper::gotoxy(10, 14);
	cout << setw(34) << "";
	Helper::gotoxy(10, 15);
	cout << "     " << setw(10) << "Change Student Password" << setw(5) << "      ";
	Helper::gotoxy(10, 16);
	cout << setw(34) << "";
	
	Helper::gotoxy(10, 18);
	cout << setw(34) << "";
	Helper::gotoxy(10, 19);
	cout << "     " << setw(10) << "Change Teacher Username" << setw(5) << "      ";
	Helper::gotoxy(10, 20);
	cout << setw(34) << "";
	
	Helper::gotoxy(10, 22);
	cout << setw(34) << "";
	Helper::gotoxy(10, 23);
	cout << "     " << setw(10) << "Change Teacher Password" << setw(5) << "      ";
	Helper::gotoxy(10, 24);
	cout << setw(34) << "";
}
void University::printTeacherChoice() {
	printInstructions(); 
	SetConsoleTextAttribute(hM, 0 | BACKGROUND_BLUE | BACKGROUND_RED | BACKGROUND_INTENSITY);
	Helper::gotoxy(63, 2);
	cout << setw(35) << "";
	Helper::gotoxy(63, 3);
	cout << setw(11) << " " << " TEACHER MODE" << setw(11) << " ";
	Helper::gotoxy(63, 4);
	cout << setw(35) << "";
	SetConsoleTextAttribute(hM, 15);

	SetConsoleTextAttribute(hM, 0 | BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED | BACKGROUND_INTENSITY);
	Helper::gotoxy(10, 10);
	cout << setw(50) << "";
	Helper::gotoxy(10, 11);
	cout << "     " << setw(10) << "Manage Attendance Of Students" << setw(5) << "                ";
	Helper::gotoxy(10, 12);
	cout << setw(50) << "";

	Helper::gotoxy(10, 14);
	cout << setw(50) << "";
	Helper::gotoxy(10, 15);
	cout << "     " << setw(10) << "View Attendance Of All Students" << setw(5) << "              ";
	Helper::gotoxy(10, 16);
	cout << setw(50) << "";

	Helper::gotoxy(10, 18);
	cout << setw(50) << "";
	Helper::gotoxy(10, 19);
	cout << "     " << setw(10) << "Manage Evaluations Of Students" << setw(5) << "               ";
	Helper::gotoxy(10, 20);
	cout << setw(50) << "";

	Helper::gotoxy(10, 22);
	cout << setw(50) << "";
	Helper::gotoxy(10, 23);
	cout << "     " << setw(10) << "View Evaluation Report Of A Course" << setw(5) << "           ";
	Helper::gotoxy(10, 24);
	cout << setw(50) << "";

	Helper::gotoxy(10, 26);
	cout << setw(50) << "";
	Helper::gotoxy(10, 27);
	cout << "     " << setw(10) << "Assign Grades To Students" << setw(5) << "                    ";
	Helper::gotoxy(10, 28);
	cout << setw(50) << "";

	Helper::gotoxy(10, 30);
	cout << setw(50) << "";
	Helper::gotoxy(10, 31);
	cout << "     " << setw(10) << "Change TA Of A Specific Course" << setw(5) << "               ";
	Helper::gotoxy(10, 32);
	cout << setw(50) << "";

	Helper::gotoxy(10, 34);
	cout << setw(50) << "";
	Helper::gotoxy(10, 35);
	cout << "                    " << setw(10) << "To Go Back" << setw(5) << "                    ";
	Helper::gotoxy(10, 36);
	cout << setw(50) << "";
}
void University::printStudentChoice() {
	printInstructions(); 
	SetConsoleTextAttribute(hM, 0 | BACKGROUND_BLUE | BACKGROUND_RED | BACKGROUND_INTENSITY);
	Helper::gotoxy(63, 2);
	cout << setw(35) << "";
	Helper::gotoxy(63, 3);
	cout << setw(11) << " " << " STUDENT MODE" << setw(11) << " ";
	Helper::gotoxy(63, 4);
	cout << setw(35) << "";
	SetConsoleTextAttribute(hM, 15);

	SetConsoleTextAttribute(hM, 0 | BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED | BACKGROUND_INTENSITY);
	Helper::gotoxy(10, 10);
	cout << setw(44) << "";
	Helper::gotoxy(10, 11);
	cout << "     " << setw(10) << "Register A Course" << setw(5) << "                      ";
	Helper::gotoxy(10, 12);
	cout << setw(44) << "";

	Helper::gotoxy(10, 14);
	cout << setw(44) << "";
	Helper::gotoxy(10, 15);
	cout << "     " << setw(20) << "Unregister A Course" << setw(19) << "";
	Helper::gotoxy(10, 16);
	cout << setw(44) << "";

	Helper::gotoxy(10, 18);
	cout << setw(44) << "";
	Helper::gotoxy(10, 19);
	cout << "     " << setw(19) << "Withdraw A Course" << setw(20) << "";
	Helper::gotoxy(10, 20);
	cout << setw(44) << "";

	Helper::gotoxy(10, 22);
	cout << setw(44) << "";
	Helper::gotoxy(10, 23);
	cout << "     " << setw(10) << "View Mark-Sheet Of A Course" << setw(5) << "            ";
	Helper::gotoxy(10, 24);
	cout << setw(44) << "";

	Helper::gotoxy(10, 26);
	cout << setw(44) << "";
	Helper::gotoxy(10, 27);
	cout << "     " << setw(10) << "View attendance Of A Course" << setw(5) << "            ";
	Helper::gotoxy(10, 28);
	cout << setw(44) << "";

	Helper::gotoxy(10, 30);
	cout << setw(44) << "";
	Helper::gotoxy(10, 31);
	cout << "     " << setw(10) << "Change Password" << setw(5) << "                        ";
	Helper::gotoxy(10, 32);
	cout << setw(44) << "";

	Helper::gotoxy(10, 34);
	cout << setw(44) << "";
	Helper::gotoxy(10, 35);
	cout << "               " << setw(10) << "To Go Back" << setw(5) << "                   ";
	Helper::gotoxy(10, 36);
	cout << setw(44) << "";
}
void University::printTAChoice() {
	printInstructions(); 
	SetConsoleTextAttribute(hM, 0 | BACKGROUND_BLUE | BACKGROUND_RED | BACKGROUND_INTENSITY);
	Helper::gotoxy(63, 2);
	cout << setw(35) << "";
	Helper::gotoxy(63, 3);
	cout << setw(6) << " " << "TEACHING ASSISTANT MODE" << setw(6) << " ";
	Helper::gotoxy(63, 4);
	cout << setw(35) << "";
	SetConsoleTextAttribute(hM, 15);
	
	SetConsoleTextAttribute(hM, 0 | BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED | BACKGROUND_INTENSITY);
	Helper::gotoxy(10, 10);
	cout << setw(50) << "";
	Helper::gotoxy(10, 11);
	cout << "     " << setw(10) << "Manage Attendance Of Students" << setw(5) << "                ";
	Helper::gotoxy(10, 12);
	cout << setw(50) << "";


	Helper::gotoxy(10, 14);
	cout << setw(50) << "";
	Helper::gotoxy(10, 15);
	cout << "     " << setw(10) << "View Attendance Of All Students" << setw(5) << "              ";
	Helper::gotoxy(10, 16);
	cout << setw(50) << "";

	Helper::gotoxy(10, 18);
	cout << setw(50) << "";
	Helper::gotoxy(10, 19);
	cout << "     " << setw(10) << "Manage Evaluations Of Students" << setw(5) << "               ";
	Helper::gotoxy(10, 20);
	cout << setw(50) << "";

	Helper::gotoxy(10, 22);
	cout << setw(50) << "";
	Helper::gotoxy(10, 23);
	cout << "     " << setw(10) << "View Evaluation Report Of A Course" << setw(5) << "           ";
	Helper::gotoxy(10, 24);
	cout << setw(50) << "";

	Helper::gotoxy(10, 26);
	cout << setw(50) << "";
	Helper::gotoxy(10, 27);
	cout << "                  " << setw(10) << "To Go Back" << setw(5) << "                      ";
	Helper::gotoxy(10, 28);
	cout << setw(50) << "";
}

//print non register courses
void University::printNonRegCourses(int index, char choice, int ID) {
	try {
		if (index < 0)
			throw "Index is negative";
		else if (index >= currentDepartment)
			throw "Index is out of bound";

		SetConsoleTextAttribute(hM, 0 | BACKGROUND_BLUE | BACKGROUND_RED);
		Helper::gotoxy(90, 7);
		cout << setw(35) << "";
		Helper::gotoxy(90, 8);
		cout << setw(9) << "" << "Available Courses" << setw(9) << " ";
		Helper::gotoxy(90, 9);
		cout << setw(35) << "";
		SetConsoleTextAttribute(hM, 15);

		int size = 0;
		size = listOfDepartments[index]->getCurrentCourses();

		//Display name of courses available in a department
		for (int m = 0, i=0; m < size; m++) {
			SetConsoleTextAttribute(hM, 0 | BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED | BACKGROUND_INTENSITY);
			bool res = true;

			if (choice == 's')
				res = !listOfDepartments[index]->getStudent(ID)->isCourseExist(listOfDepartments[index]->getCourseCode(m));
			else
				res = !listOfDepartments[index]->getTeacher(ID)->isCourseExist(listOfDepartments[index]->getCourseCode(m));
			if (res) {
				Helper::gotoxy(100, 13 + (4 * i));
				cout << setw(47) << "";
				Helper::gotoxy(100, 14 + (4 * i));


				cout << setw(6) << "" << listOfDepartments[index]->getCourseName(m) << "(" <<
					listOfDepartments[index]->getCourseCode(m) << ")" << setw(6) << " ";

				int wx = Helper::wherex();

				for (int j = wx; j < 147; j++) {
					SetConsoleTextAttribute(hM, 0 | BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED | BACKGROUND_INTENSITY);
					Helper::gotoxy(j, 14 + (4 * i));
					cout << setw(1) << " ";
				}

				Helper::gotoxy(100, 15 + (4 * i));
				cout << setw(47) << "";
				SetConsoleTextAttribute(hM, 15);

				++i;
			}
		}
	}

	catch (const char* message) {
		cout << "Exception throw: " << message << endl;
	}
}

//print detail of available courses
void University::printCourses(int index, char choice, int ID) {
	try {
		if (index < 0)
			throw "Index is negative";
		else if (index >= currentDepartment)
			throw "Index is out of bound";

		SetConsoleTextAttribute(hM, 0 | BACKGROUND_BLUE | BACKGROUND_RED);
		Helper::gotoxy(90, 7);
		cout << setw(35) << "";
		Helper::gotoxy(90, 8);
		cout << setw(9) << "" << "Available Courses" << setw(9) << " ";
		Helper::gotoxy(90, 9);
		cout << setw(35) << "";
		SetConsoleTextAttribute(hM, 15);

		int size = 0;
		if (choice == '0')
			size = listOfDepartments[index]->getCurrentCourses();
		else if (choice == '1')
			size = listOfDepartments[index]->getStudent(ID)->getCurrentNoOfReg();
		else if (choice == '2')
			size = listOfDepartments[index]->getTeacher(ID)->getCurrentNumOfCourses();
		else if (choice == '3')
			size = listOfDepartments[index]->getHod(ID)->getCurrentNumOfCourses();
		//Display name of courses available in a department
		for (int i = 0; i < size; i++) {
			SetConsoleTextAttribute(hM, 0 | BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED | BACKGROUND_INTENSITY);

			Helper::gotoxy(100, 13 + (4 * i));
			cout << setw(47) << "";
			Helper::gotoxy(100, 14 + (4 * i));

			if (choice == '0') {
				cout << setw(6) << "" << listOfDepartments[index]->getCourseName(i) << "(" <<
					listOfDepartments[index]->getCourseCode(i) << ")" << setw(6) << " ";
			}
			else if (choice == '1') {
				cout << setw(6) << "" << listOfDepartments[index]->getStudent(ID)->getCourseName(i) << "(" <<
					listOfDepartments[index]->getStudent(ID)->getCourseCode(i) << ")" << setw(6) << " ";
			}
			else if (choice == '2') {
				cout << setw(6) << "" << listOfDepartments[index]->getTeacher(ID)->getCourseName(i) << "(" <<
					listOfDepartments[index]->getTeacher(ID)->getCourseCode(i) << ")" << setw(6) << " ";
			}
			else if (choice == '3') {
				cout << setw(6) << "" << listOfDepartments[index]->getHod(ID)->getCourseName(i) << "(" <<
					listOfDepartments[index]->getHod(ID)->getCourseCode(i) << ")" << setw(6) << " ";
			}


			int wx = Helper::wherex();

			for (int j = wx; j < 147; j++) {
				SetConsoleTextAttribute(hM, 0 | BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED | BACKGROUND_INTENSITY);
				Helper::gotoxy(j, 14 + (4 * i));
				cout << setw(1) << " ";
			}

			Helper::gotoxy(100, 15 + (4 * i));
			cout << setw(47) << "";
			SetConsoleTextAttribute(hM, 15);
		}
	}

	catch (const char* message) {
		cout << "Exception throw: " << message << endl;
	}
}

//get user choice
int University::getChoice(char mode, int total_buttons) {
	system("cls");
	int option = 1;
	int storeOpt = 1;

	while (true) {
		Sleep(130);
		if (GetAsyncKeyState(VK_DOWN) & 0x28000) {
			Sleep(100);
			system("cls");
			storeOpt = option;
			if (option == total_buttons)
				option = 1;
			else
				option++;
		}
		else if (GetAsyncKeyState(VK_UP) & 0x26000) {
			Sleep(100);
			storeOpt = option;
			if (option == 1)
				option = total_buttons;
			else
				option--;
		}
		else if (GetAsyncKeyState(VK_RETURN) & 0x0D000) {
			Sleep(100);
			return option;
		}

		if (mode == '0') 
			printChoice();
		else if (mode == '1')
			printHODChoice();
		else if (mode == '2')
			printITManagerChoice();
		else if (mode == '3')
			printTeacherChoice();
		else if (mode == '4')
			printStudentChoice();
		else if (mode == '5')
			printTAChoice();
		else if (mode == '7')
			printIT_SubChoice();
		else if (mode == '8')
			printDepartmentName();

		if (storeOpt != option) {
			SetConsoleTextAttribute(hM, 0);
			Helper::gotoxy(7, 3 + ((storeOpt+1)* 4));
			cout << "-> ";
		}
		SetConsoleTextAttribute(hM, 15);
		Helper::gotoxy(7, 3 + ((option+1) * 4));
		cout << "-> ";
	}
	Sleep(150);
	Helper::gotoxy(0, 0);
	cin.get();
	cin.get();
	cin.get();
}

//input username & password
void loginEntry(char* username, char* password) {

	SetConsoleTextAttribute(hM, 0 | BACKGROUND_BLUE);
	Helper::gotoxy(10, 10);
	cout << "Enter Username";
	SetConsoleTextAttribute(hM, 15);
	cout << ": ";
	Helper::gotoxy(27, 10);
	cin.get();
	Helper::gotoxy(27, 10);
	cin.ignore(cin.rdbuf()->in_avail());
	Helper::gotoxy(27, 10);
	cin >> username;
	Helper::gotoxy(27, 10);
	cin.ignore(cin.rdbuf()->in_avail());

	SetConsoleTextAttribute(hM, 0 | BACKGROUND_BLUE);
	Helper::gotoxy(10, 13);
	cout << "Enter Password";
	SetConsoleTextAttribute(hM, 15);
	cout << ": ";
	Helper::gotoxy(27, 13);
	cin.ignore(cin.rdbuf()->in_avail());
	//cin.clear('\n');
	Helper::gotoxy(27, 13);
	cin >> password;
	Helper::gotoxy(27, 13);
	cin.ignore(cin.rdbuf()->in_avail());
}

//login system
int University::loginMode(const char* dep, int i) {
	system("CLS");
	
	char mode = 0;
	mode = getChoice('0',6) + 48;
	system("cls");
	Sleep(150);
	char username[50] = {0};
	char password[50] = {0};

	//HOD MODE
	if (mode == '1') {
		system("CLS");
		cout << endl;
		SetConsoleTextAttribute(hM, 0 | BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED | BACKGROUND_INTENSITY);
		cout << "\t\t\t\t\t*******************************************************************\n";
		cout << "\t\t\t\t\t|                        " << setw(10) << "WELCOME TO HOD MODE" << setw(10) << "                      |\n";
		cout << "\t\t\t\t\t*******************************************************************\n\n\n";
		SetConsoleTextAttribute(hM, 15);
		cout << endl;

		//input username & password
		loginEntry(username, password);
	
		//if user enter correct username and password
		if (listOfDepartments[i]->checkHODAccount(username, password)) {
			SetConsoleTextAttribute(hM, 15 | BACKGROUND_GREEN);
			Helper::gotoxy(65, 23);
			cout << " Login Successfully \n\n";
			SetConsoleTextAttribute(hM, 15);
			Helper::gotoxy(60, 25);
			cout << "Please wait for 2 seconds......\n";
			Sleep(2000);
			HODLogin(i);
		}
		else {
			Helper::gotoxy(61, 15);
			SetConsoleTextAttribute(hM, 0 | BACKGROUND_RED);
			cout << "Invalid Username & Password\n\n";
			SetConsoleTextAttribute(hM, 15);
		}
	}
	//IT_MANAGER MODE
	else if (mode == '2') {
		system("CLS");
		cout << endl;
		SetConsoleTextAttribute(hM, 0 | BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED | BACKGROUND_INTENSITY);
		cout << "\t\t\t\t\t*******************************************************************\n";
		cout << "\t\t\t\t\t|                 "<<setw(10)<< "WELCOME TO IT_MANAGER MODE" << setw(10) << "                      |\n";
		cout << "\t\t\t\t\t*******************************************************************\n\n\n";

		//input username & password
		loginEntry(username, password);

		if (listOfDepartments[i]->checkItManagerAccount(username, password)) {
			SetConsoleTextAttribute(hM, 15 | BACKGROUND_GREEN);
			Helper::gotoxy(65, 23);
			cout << " Login Successfully \n\n";
			SetConsoleTextAttribute(hM, 15);
			Helper::gotoxy(60, 25);
			cout << "Please wait for 2 seconds......\n";
			Sleep(2000);
			itManagerLogin(dep,i);
		}
		else
		{
			Helper::gotoxy(61, 15);
			SetConsoleTextAttribute(hM, 0 | BACKGROUND_RED);
			cout << "Invalid Username & Password\n\n";
			SetConsoleTextAttribute(hM, 15);
		}
	}
	//Teacher
	else if (mode == '3') {
		system("CLS");
		cout << endl;
		SetConsoleTextAttribute(hM, 0 | BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED | BACKGROUND_INTENSITY);
		cout << "\t\t\t\t\t*******************************************************************\n";
		cout << "\t\t\t\t\t|                    " << setw(10) << "WELCOME TO TEACHER MODE" << setw(10) << "                      |\n";
		cout << "\t\t\t\t\t*******************************************************************\n\n\n";

		SetConsoleTextAttribute(hM, 15);
		cout << endl;

		//input username & password
		loginEntry(username, password);

		if (listOfDepartments[i]->checkTeacherAccount(username, password)) {
			SetConsoleTextAttribute(hM, 15 | BACKGROUND_GREEN);
			Helper::gotoxy(65, 23);
			cout << " Login Successfully \n\n";
			SetConsoleTextAttribute(hM, 15);
			Helper::gotoxy(60, 25);
			cout << "Please wait for 2 seconds......\n";
			Sleep(2000);

			teacherLogin(i, username, password);
		}
		else{
			Helper::gotoxy(61, 15);
			SetConsoleTextAttribute(hM, 0 | BACKGROUND_RED);
			cout << "Invalid Username & Password\n\n";
			SetConsoleTextAttribute(hM, 15);
		}
	}
	//Student
	else if (mode == '4') {
		system("CLS");
		cout << endl;
		SetConsoleTextAttribute(hM, 0 | BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED | BACKGROUND_INTENSITY);
		cout << "\t\t\t\t\t*******************************************************************\n";
		cout << "\t\t\t\t\t|                    " << setw(10) << "WELCOME TO STUDENT MODE" << setw(10) << "                      |\n";
		cout << "\t\t\t\t\t*******************************************************************\n\n\n";

		SetConsoleTextAttribute(hM, 15);
		cout << endl;

		//input username & password
		loginEntry(username, password);


		if (listOfDepartments[i]->checkStudentAccount(username, password)) {
			int rollNum = listOfDepartments[i]->getIDOfStudent(username, password);
			
			SetConsoleTextAttribute(hM, 15 | BACKGROUND_GREEN);
			Helper::gotoxy(65, 23);
			cout << " Login Successfully \n\n";
			SetConsoleTextAttribute(hM, 15);
			Helper::gotoxy(60, 25);
			cout << "Please wait for 2 seconds......\n"; Sleep(2000);

			studentLogin(i, username, rollNum);
		}
		else{
			Helper::gotoxy(61, 15);
			SetConsoleTextAttribute(hM, 0 | BACKGROUND_RED);
			cout << "Invalid Username & Password\n\n";
			SetConsoleTextAttribute(hM, 15);
		}
	}
	//TA MODE
	else if (mode == '5') {
		system("CLS");
		cout << endl;
		SetConsoleTextAttribute(hM, 0 | BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED | BACKGROUND_INTENSITY);
		cout << "\t\t\t\t\t*******************************************************************\n";
		cout << "\t\t\t\t\t|                 " << setw(10) << "WELCOME TO Teaching Assistant MODE              |\n";
		cout << "\t\t\t\t\t*******************************************************************\n\n\n";

		SetConsoleTextAttribute(hM, 15);
		cout << endl;

		//input username & password
		loginEntry(username, password);

		if (listOfDepartments[i]->checkTAAccount(username, password)) {
			char* _courseCode = new char[20];
			strcpy_s(_courseCode,20 ,listOfDepartments[i]->getCourseCodeThroghTA(username, password));
			SetConsoleTextAttribute(hM, 15 | BACKGROUND_GREEN);
			Helper::gotoxy(65, 23);
			cout << " Login Successfully \n\n";
			SetConsoleTextAttribute(hM, 15);
			Helper::gotoxy(60, 25);
			cout << "Please wait for 2 seconds......\n"; Sleep(2000);
			taLogin(i,username,_courseCode);
			if (_courseCode != nullptr)
				delete[] _courseCode;
		}
		else{
			Helper::gotoxy(61, 15);
			SetConsoleTextAttribute(hM, 0 | BACKGROUND_RED);
			cout << "Invalid Username & Password\n\n";
			SetConsoleTextAttribute(hM, 15);
		}
	}
	//Exit
	else if (mode == '6'){
		Helper::gotoxy(71, 14);
		SetConsoleTextAttribute(hM, 0 | BACKGROUND_RED);
		cout << "Exit Succeeded\n\n\n";
		SetConsoleTextAttribute(hM, 15);
		return 6;
	}
	
	system("pause");
	Sleep(110);
}
void University::LoginControl() {
	system("CLS");
	int index = getChoice('8', currentDepartment) - 1;
	char* dep = new char[60];
	strcpy_s(dep, strlen(listOfDepartments[index]->getName()) + 1, listOfDepartments[index]->getName());
	system("CLS");
	cout << endl;
	SetConsoleTextAttribute(hM, 0 | BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED | BACKGROUND_INTENSITY);
	cout << "\t\t\t\t\t*******************************************************************\n";
	cout << "\t\t\t\t\t|" << setw(40) << listOfDepartments[index]->getName() << setw(27) << "|\n";
	cout << "\t\t\t\t\t*******************************************************************\n\n\n";


	SetConsoleTextAttribute(hM, 0 | BACKGROUND_RED | BACKGROUND_BLUE | BACKGROUND_INTENSITY);
	Helper::gotoxy(50, 6);
	cout << "Welcome To The " << listOfDepartments[index]->getName() << " Department\n";

	SetConsoleTextAttribute(hM, 0 | BACKGROUND_GREEN | BACKGROUND_RED);
	Helper::gotoxy(50, 10);
	cout << "Instructions: ";
	SetConsoleTextAttribute(hM, 0 | BACKGROUND_GREEN | BACKGROUND_RED);
	Helper::gotoxy(54, 12);
	cout << "Use \"arrow up\" Key To Go UP";
	SetConsoleTextAttribute(hM, 0 | BACKGROUND_GREEN | BACKGROUND_RED);
	Helper::gotoxy(54, 14);
	cout << "Use \"arrow down\" Key To Go Down";
	SetConsoleTextAttribute(hM, 0 | BACKGROUND_GREEN | BACKGROUND_RED);
	Helper::gotoxy(54, 16);
	cout << "Use \"enter\" Key For Selection\n\n\n\n";
	SetConsoleTextAttribute(hM, 15);

	system("pause");
	SetConsoleTextAttribute(hM, 15);
	int res = 0;
	while (res != 6)
		res = loginMode(dep, index);

	if (dep != nullptr)
		delete[] dep;
}

//loads data from a file
void University::loadData() {
	
	//reading from a file
	ifstream iFile;
	iFile.open("data.txt", ios::in);
	if (iFile.fail())
		cout << "Fail To Open File\n";
	else {

		//read university name
		char universityName[100];
		iFile.getline(universityName, 100);
		name = new char[strlen(universityName) + 1];
		strcpy_s(name, strlen(universityName) + 1, universityName);

		//read number of departments
		iFile >> currentDepartment;
		iFile.ignore();

		//loop to initialize data in list of departments
		for (int i = 0; i < currentDepartment; i++) {
			listOfDepartments[i] = new Department();
			char nameOfDepartment[100];
			iFile.getline(nameOfDepartment, 100);
			listOfDepartments[i]->setName(nameOfDepartment);

			int numOfCourses;
			iFile >> numOfCourses;
			iFile.ignore();

			//store code of all course
			char** allCoursesCode = new char* [numOfCourses];
			int* ta_existArr = new int[numOfCourses];
			for (int j = 0; j < numOfCourses; j++) {
				char courseCode[20];
				char courseName[50];

				iFile.getline(courseCode, 20, ',');
				//to store code of all courses
				allCoursesCode[j] = new char[strlen(courseCode) + 1];
				strcpy_s(allCoursesCode[j], strlen(courseCode) + 1, courseCode);

				iFile.ignore();
				iFile.getline(courseName, 50, ',');
				courseName[strlen(courseName) + 1];
				iFile.ignore();
				int is_TA_exist;
				iFile >> is_TA_exist;
				ta_existArr[j] = is_TA_exist;
				iFile.ignore();
				int ta_teacher_id;
				int ta_std_id;
				if (is_TA_exist==1) {
					iFile >> ta_teacher_id;
					iFile.ignore();
					iFile.ignore();
					iFile >> ta_std_id;
					iFile.ignore();
				}
				TA* ta = nullptr;
				if (is_TA_exist==1) {
					ta = new TA();
					ta->setRollNum(ta_std_id);
					ta->setEmployeeId(ta_teacher_id);
				}	
				listOfDepartments[i]->addCourse(courseCode, courseName, ta);

				if (ta != nullptr)
					ta = nullptr;
			}

			//general data
			char password[20];
			char userName[20];
			char fName[50];
			char lName[50];
			int age;

			//IT Manager Data
			int manager_id;
			iFile.getline(userName, 100, ',');
			iFile.ignore();
			iFile.getline(password, 100, ',');
			iFile.ignore();
			iFile >> manager_id;
			iFile.ignore();
			iFile.ignore();
			iFile.getline(fName, 50, ' ');
			iFile.getline(lName, 50, ',');
			iFile.ignore();
			iFile >> age;
			iFile.ignore();
			IT_Manager* it_man = new IT_Manager(fName, lName, manager_id, age, userName, password);
			listOfDepartments[i]->setItManager(it_man);

			if (it_man != nullptr)
				it_man = nullptr;



			//Teacher
			int numOfTeachers;
			iFile >> numOfTeachers;
			iFile.ignore();
			for (int j = 0; j < numOfTeachers; j++) {
				iFile.getline(userName, 100, ',');
				iFile.ignore();
				iFile.getline(password, 100, ',');
				iFile.ignore();
				int teacher_id;
				iFile >> teacher_id;
				iFile.ignore();
				iFile.ignore();
				iFile.getline(fName, 50, ' ');
				iFile.getline(lName, 50, ',');
				iFile.ignore();
				iFile >> age;
				iFile.ignore();
				int max_Courses;
				int noOfCourse;
				iFile >> max_Courses;
				iFile.ignore();
				iFile >> noOfCourse;
				iFile.ignore();


				if (j == 0) {
					HOD* h = new HOD(fName, lName, teacher_id, age, max_Courses, userName, password);
					listOfDepartments[i]->setHOD(h);

					if (h != nullptr)
						h = nullptr;
				}
				else {
					Teacher* t = new Teacher(fName, lName, teacher_id, age, max_Courses, userName, password);
					listOfDepartments[i]->createTeacherAccount(t);

					if (t != nullptr)
						t = nullptr;
				}

				for (int k = 0; k < noOfCourse; k++) {
					char courseCode[10];
					iFile.getline(courseCode, 10);
					listOfDepartments[i]->assignCourse(teacher_id, courseCode);
				}
			}


			//students
			int numOfStudents;
			iFile >> numOfStudents;
			iFile.ignore();

			for (int j = 0; j < numOfStudents; j++) {
				iFile.getline(userName, 100, ',');
				iFile.ignore();
				iFile.getline(password, 100, ',');
				iFile.ignore();
				int student_id;
				iFile >> student_id;
				iFile.ignore();
				iFile.ignore();
				iFile.getline(fName, 50, ' ');
				iFile.getline(lName, 50, ',');
				iFile.ignore();
				iFile >> age;
				iFile.ignore();
				int max_Reg;
				int noOfReg;
				iFile >> max_Reg;
				iFile.ignore();
				iFile >> noOfReg;
				iFile.ignore();

				Student* std = new Student(fName, lName, student_id, age, userName, password);
				for (int k = 0; k < noOfReg; k++) {
					int reg_id;
					char courseName[50];

					iFile >> reg_id;
					iFile.ignore();
					iFile.ignore();
					iFile.getline(courseName, 50, ',');

					float gt, gpa, attendance;
					gt = gpa = attendance = 0.0;

					char grade = 0;
					iFile.ignore();
					iFile >> gpa;
					iFile.ignore();
					iFile >> grade;
					iFile.ignore();
					iFile.ignore();
					iFile >> gt;
					iFile.ignore();
					iFile.ignore();
					iFile >> attendance;
					iFile.ignore();

					int day, month, year;

					iFile >> year;
					iFile.ignore();
					iFile >> month;
					iFile.ignore();
					iFile >> day;
					iFile.ignore();
					
					Course* sub = listOfDepartments[i]->getCourse(courseName);
					Registeration* r = new Registeration(reg_id, std, sub, year, month, day);
					r->setGPA(gpa);
					r->setGrade(grade);
					r->setGT(gt);
					r->setAttendance(attendance);
					std->registerCourse(r);
					sub->setRegisteration(r);
					if (sub != nullptr) 
						sub = nullptr;

					if (r != nullptr)
						r = nullptr;
				}
				listOfDepartments[i]->createStudentAccount(std);
				if (std != nullptr)
					std = nullptr;
			}


			for (int m = 0; m < numOfCourses; m++) {
				if (ta_existArr != nullptr && ta_existArr[m] == 1) {
					int teacher_id = listOfDepartments[i]->getTAEmployeeId(allCoursesCode[m]);
					Teacher* emp = listOfDepartments[i]->getTeacher(teacher_id);

					int std_id = listOfDepartments[i]->getTAStudentId(allCoursesCode[m]);
					Student* s = listOfDepartments[i]->getStudent(std_id);

					if (s != nullptr && emp != nullptr) {
						TA* ta = listOfDepartments[i]->getTAOfACourse(allCoursesCode[m]);
						ta->setFirstName(emp->getFirstName());
						ta->setLastName(emp->getLastName());
						ta->setAge(emp->getAge());


						//set username & password
						ta->changeUserName(emp->getUserName());
						ta->changePassword(emp->getPassword());

						for (int k = 0; k < s->getCurrentNoOfReg(); k++) {
							Registeration* newReg = s->getRegisteraion(k);
							ta->registerCourse(newReg);
							newReg->setStudent(ta);

							if (newReg != nullptr)
								newReg = nullptr;
						}

						for (int k = 0; k < emp->getCurrentNumOfCourses(); k++) {
							Course* c = listOfDepartments[i]->getCourse(emp->getCourseCode(k));
							ta->setCourse(c);

							if (c != nullptr)
								c = nullptr;
						}

						listOfDepartments[i]->deleteStudentAccount(std_id);
						listOfDepartments[i]->deleteTeacherAccount(teacher_id);
						listOfDepartments[i]->createStudentAccount(ta);
						//free memory
						if (emp != nullptr)
							emp = nullptr;
						if (s != nullptr)
							s = nullptr;
						if (ta != nullptr)
							ta = nullptr;
					}
				}
				else
					listOfDepartments[i]->getCourse(allCoursesCode[m])->setTA();
			}
				if (ta_existArr != nullptr)
					delete[] ta_existArr;


			for (int m = 0; m < numOfCourses; m++)
				if (allCoursesCode[m] != nullptr)
					delete[] allCoursesCode[m];

			if (allCoursesCode != nullptr)
				delete[] allCoursesCode;
		}
	}
}
