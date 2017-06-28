// FunctionTemplates.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <string>
#include "BankAccount.h"
#include <vector>
#include <algorithm> // max_element
#include <functional> // greater operator


using namespace std;


// template function
template < typename T >  // we can use class or typename keyword on this line.
T mymax(const T& t1, const T&  t2) // we only use this const Template function because we use 22,33 constant ints.
{
	return t1 < t2 ? t2 : t1;
}

// template function
template < typename T >  // we can use class or typename keyword on this line.
T mymax(T& t1, T&  t2) // most of the time we use this because we use variables and not constant ints.
{
	return t1 < t2 ? t2 : t1;
}

// template function with default arguments
template<typename T, int N = 1>
T& increment(T& i)
{
	//i += N;
	return (i += N);
}

// template function with default types
template<typename T, typename C = less<T>> 
T findExtreme(vector<T>& v, C c = C())
{
	return *max_element(begin(v), end(v), c);
}


int main()
{
	std::cout << "max of 22 and 33 is " << mymax<int>(22,33) << std::endl;
	std::cout << "max of 24.12 and 24.13 is " << mymax(24.12, 24.13) << std::endl;
	std::string s1 = "hello";
	std::string s2 = "world";
	std::cout << "max of " << s1 << " and " << s2 << " is " << mymax<std::string>(s1, s2) << std::endl;
	
	BankAccount account1("Jane", 1000);
	BankAccount account2("Steve", 800);
	cout << "max of strings: " << account1.getHolderName() << " and " << account2.getHolderName() << " is "
		<< mymax<BankAccount>(account1, account2).getHolderName() << endl;

	vector<int> nums = { 6, 2, 3, 5, 4, 1 };
	for (int& a : nums) 
	{
		a = increment<int>(a); // increments by 1 from default N=1
		cout << a << " ";
	}
	cout << endl;
	// now undo last increment
	for (int& a : nums)
	{
		a = increment<int, -1>(a); // increments by 1 from default N=1
		cout << a << " ";
	}
	cout << endl;
	// now add three to each value.
	for (int& a : nums)
	{
		a = increment<int, 3>(a); // change the default N to N=3
		cout << a << " ";
	}
	cout << endl;

	int max = findExtreme(nums);

	int min = findExtreme<int, greater<int>>(nums);



    return 0;
}

