#include<iostream>
#include"University.h"
#include"Department.h"
#include"Course.h"
#include"TA.h"
#include"Helper.h"

using namespace std;

int main() {
	

	//to adjust window's size
	Helper::adjustWindowSize();
	
	Helper::printNEON('*', 5, 30, 7);
	system("cls");
	
	//create an object of university
	University u1;
	
	//Load data from a file
	u1.loadData();

	//to perform different functionalities
	u1.LoginControl();
	
	system("pause");
	return 0;
}
