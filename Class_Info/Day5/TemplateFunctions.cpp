// TemplateFunctions.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <string>
#include <algorithm>
#include "BankAccount.h"
#include <vector>
#include <functional>	// greater

using namespace std;

template <typename T>
T mymax(T& t1, T& t2)
{
	return t1 < t2 ? t2 : t1;
}

template <typename T>
T mymax(const T& t1, const T& t2)
{
	return t1 < t2 ? t2 : t1;
}

// template function default arguments
template <typename T, int N=1>
T& increment(T& i)
{
	i += N;
	return i;
}

template <typename T, typename C = less<T>>
T findExtreme(vector<T>& v, C c = C())
{
	return *max_element(begin(v), end(v), c);
}


int _tmain(int argc, _TCHAR* argv[])
{
	// mymax works with built-in type
	int a = 22, b = 33;
	cout << "max of 22 and 33 is " << mymax(a, b) << endl;
	cout << "max of 22 and 33 is " << mymax(a, 33) << endl;

	// mymax works with constants
	cout << "max of 22 and 33 is " << mymax(22, 33) << endl;

	// mymax works with strings
	string s1 = "hello";
	string s2 = "world";
	cout << "max of " << s1 << " and " << s2
		<< " is " << mymax(s1, s2) << endl;

	// mymax works with user defiend type
	BankAccount b1(1000, "Jake");
	BankAccount b2(2000, "Jacob");
	cout << "max of " << b1.getOwnerName()
		<< " and " << b2.getOwnerName()
		<< " is " << mymax(b1, b2).getOwnerName() << endl;

	vector<int> nums { 6, 2, 4, 7, 1, 5 };
	for (int& i : nums)
	{
		i = increment<int>(i);	// type of T is int
	}
	for (int& i : nums)
	{
		// in order to pass in a specified value for N,
		// we have to specify T first
		i = increment<int, 2>(i);
	}

	int max = findExtreme(nums);
	int min = findExtreme<int, greater<int>>(nums);

	return 0;
}

