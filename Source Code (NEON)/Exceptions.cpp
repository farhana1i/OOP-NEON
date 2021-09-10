#include "Exceptions.h"

//size of new array is smaller than original array
const char* SizeIsSmaller::what() {
	return "New Size Is Less Than Original Size";
}

//size of new array is greater than original array
const char* SizeIsGreater::what() {
	return "New Size Is Greater Than Original Size";
}

//size of new array is negative
const char* SizeIsNegative::what() {
	return "New Size Is Negative\n";
}