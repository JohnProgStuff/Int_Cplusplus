// NullPtr.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>

using namespace std;

bool ambiguous(int arg)
{
	return false;
}

bool ambiguous(int* ptr)
{
	return true;
}

int _tmain(int argc, _TCHAR* argv[])
{
	// allows nullptr to be used instead of 0 or NULL
	int* p1 = NULL;
	int* p2 = 0;
	int* p3 = nullptr;
	//p1 == p3;
	//p2 == p3;

	// after this call, p3 is nullptr
	delete p3; 

	// cannot conver nullptr to int
	//cout << int(nullptr) << endl;

	// example of NULL creating ambiguity 
	// and nullptr resolving it.
	cout << ambiguous(NULL) << endl;
	cout << ambiguous(nullptr) << endl;

	int* p{};

	return 0;
}

