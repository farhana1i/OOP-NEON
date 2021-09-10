#ifndef EXCEPTION_H
#define EXCEPTION_H

//size of new array is smaller than original array
class SizeIsSmaller{
public:
	const char* what();
};

//size of new array is greater than original array
class SizeIsGreater {
public:
	const char* what();
};

//size of new array is negative
class SizeIsNegative{
public:
	const char* what();
};

#endif // !EXCEPTION_H