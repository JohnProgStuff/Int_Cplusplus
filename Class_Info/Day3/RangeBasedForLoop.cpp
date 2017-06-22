// RangeBasedForLoop.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <vector>
#include <iostream>
#include <list>

using namespace std;

// example of a user-defined type 
// which can be used in a range-based for loop
class MyContainer
{
private:
	list<int> _values;// { 111, 222, 333 };
public:
	MyContainer()
	{
		_values.push_back(111);
		_values.push_back(222);
		_values.push_back(333);
	}
	friend list<int>::iterator begin(MyContainer&);
	friend list<int>::iterator end(MyContainer&);
	//.......
};

list<int>::iterator begin(MyContainer& c)
{
	return c._values.begin();
}

list<int>::iterator end(MyContainer& c)
{
	return c._values.end();
}


int _tmain(int argc, _TCHAR* argv[])
{
	vector<int> v { 1, 2, 3, 4, 5 };
	// allows loop variable to be defined in different ways
	for (auto elem : v)
	{
		cout << elem << endl;
	}
	for (auto& elem : v)
	{
		elem *= 2;
	}
	// using regular for loop
	for (vector<int>::iterator iter = v.begin(), iter2 = v.end();
		iter != iter2;
		++iter)
	{
		cout << *iter << endl;
	}

	for (int i = 0; i < 10; i++)
	{
		cout << i << endl;
	}

	cout << "------------------------" << endl;
	for (int elem : v)
	{
		cout << elem << endl;
	}

	cout << "------------------------" << endl;
	// allows iteration over arrays
	int arr[] = { 10, 20, 30, 40 };
	for (auto elem : arr)
	{
		cout << elem << endl;
	}

	cout << "------------------------" << endl;
	// allows iterations over initializer_list instances
	auto list = { 100, 200, 300 };
	for (auto elem : list)
	{
		cout << elem << endl;
	}

	cout << "------------------------" << endl;
	// allows interation over user defined type
	MyContainer cont;
	for (auto& elem : cont)
	{
		cout << elem << endl;
		elem = 200;
	}

	for (auto& elem : cont)
	{
		cout << elem << endl;
	}

	cout << "------------------------" << endl;

	return 0;
}

