#pragma once
#include"Exceptions.h"
#include<iostream>
using namespace std;

template<class Type>
class Template
{
public:

	//grow size of a 1D array
	static Type* growSize(Type* array, int& size, int newSize = size+10);
	
	//grow size of a 2D array
	static Type** growSize(Type** array, int& size, int newSize = size+10);

	//shrink size of a 1D array
	static Type* shrinkSize(Type* array, int& size, int newSize);
	
	//shrink size of a 2D array
	static Type** shrinkSize(Type** array, int& size, int newSize);
};

//To grow size of a 2D array
template <class Type>
Type** Template<Type>::growSize(Type** array, int& size, int newSize) {
	try {
		if (newSize < 0)
			throw SizeIsNegative();
		else if (newSize < size)
			throw SizeIsSmaller();

		Type** tempArray = new Type * [newSize];
		for (int i = 0; i < size; i++)
			tempArray[i] = array[i];
		for (int i = size; i < newSize; i++)
			tempArray[i] = nullptr;

		if (array != nullptr)
			delete[] array;

		size = newSize;
		return tempArray;
	}
	catch (SizeIsNegative neg) {
		cout << "Exception throw: " << neg.what() << endl;
	}
	catch (SizeIsSmaller lessOrg) {
		cout << "Exception throw: " << lessOrg.what() << endl;
	}
	return array;
}

//To grow size of a 1D array
template <class Type>
Type* Template<Type>::growSize(Type* array, int& size, int newSize) {
	try {
		if (newSize < 0)
			throw SizeIsNegative();
		else if (newSize < size && newSize >= 0)
			throw SizeIsSmaller();

		Type* tempArray = new Type[newSize];
		for (int i = 0; i < size; i++)
			tempArray[i] = array[i];
		delete[] array;

		size = newSize;
		return tempArray;
	}
	catch (SizeIsNegative neg) {
		cout << "Exception throw: " << neg.what();
	}
	catch (SizeIsSmaller lessOrg) {
		cout << "Exception throw: " << lessOrg.what();
	}
	return array;
}

//To shrink size of a 2D array
template <class Type>
Type** Template<Type>::shrinkSize(Type** array, int& size, int newSize) {
	try {
		if (newSize < 0)
			throw SizeIsNegative();
		else if (newSize > size)
			throw SizeIsGreater();

		Type** tempArray = new Type * [newSize];
		for (int i = 0; i < newSize; i++)
			tempArray[i] = array[i];

		if (array != nullptr)
			delete[] array;

		size = newSize;
		return tempArray;
	}
	catch (SizeIsNegative neg) {
		cout << "Exception throw: " << neg.what() << endl;
	}
	catch (SizeIsGreater greater) {
		cout << "Exception throw: " << greater.what() << endl;
	}
	return array;
}

//To shrink size of a 1D array
template <class Type>
Type* Template<Type>::shrinkSize(Type* array, int& size, int newSize) {
	try {
		if (newSize < 0)
			throw SizeIsNegative();
		else if (newSize > size)
			throw SizeIsGreater();

		Type* tempArray = new Type[newSize];
		for (int i = 0; i < newSize; i++)
			tempArray[i] = array[i];
		delete[] array;

		size = newSize;
		return tempArray;
	}
	catch (SizeIsNegative neg) {
		cout << "Exception throw: " << neg.what();
	}
	catch (SizeIsGreater lessOrg) {
		cout << "Exception throw: " << lessOrg.what();
	}
	return array;
}

