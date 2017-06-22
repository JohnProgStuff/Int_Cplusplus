// LambdaExpressions.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <vector>
#include <algorithm>
#include <iostream>
#include <iterator>

using namespace std;


int _tmain(int argc, _TCHAR* argv[])
{
	vector<int> v;
	for (int i = 0; i < 10; i++)
	{
		v.push_back(i);
	}

	for_each(v.begin(), v.end(), [](int n){ cout << n << " "; });
	cout << endl;

	cout << "---------------------------" << endl;

	for_each(
		v.begin(), 
		v.end(), 
		[](int n)
	{ 
		cout << n << " "; 
	}
	);
	cout << endl;

	cout << "---------------------------" << endl;
	// multiple statements in a lambda expression
	for_each(v.begin(), v.end(), 
		[](int n)
		{
			cout << n;
			if (n % 2 == 0)
			{
				cout << " even " << endl;
			}
			else
			{
				cout << " odd " << endl;
			}

		});

	cout << "---------------------------" << endl;
	// deducing the return type from the code
	vector<int> v2;
	transform(v.begin(), 
		v.end(), 
		back_inserter(v2), 
		[](int n){ return n*n*n; });

	for_each(v2.begin(),
		v2.end(),
		[](int n){cout << n << " "; });
	cout << endl;

	cout << "---------------------------" << endl;
	// explicitly specifying the return type
	vector<double> dv;
	transform(v.begin(),
		v.end(),
		back_inserter(dv),
		[](int n) -> double
		{
		if (n % 2 == 0)
		{
			return n*n*n;
		}
		else
		{
			return n / 2.0;
		}
	
		});
	for_each(dv.begin(),
		dv.end(),
		[](double x){cout << x << " "; });
	cout << endl;

	cout << "---------------------------" << endl;
	// capturing by value explicitly
	int x = 3, y = 7;
	cout << "printing elements between "
		<< x
		<< " and "
		<< y
		<< " inclusive"
		<< endl;
	
	for_each(v.begin(),
		v.end(),
		[x, y](int n)
		{
			if (n >= x && n <= y)
			{
				cout << n << " ";
			}
		});
	cout << endl;

	cout << "---------------------------" << endl;
	// capture by value implicitly [=]
	x = 2, y = 9;
	cout << "printing elements between "
		<< x
		<< " and "
		<< y
		<< " inclusive"
		<< endl;
	for_each(v.begin(), v.end(), [=](int n)
	{
		if (n >= x && n <= y)
		{
			cout << n << " ";
		}
	}
	);
	cout << endl;

	cout << "---------------------------" << endl;
	// capturing by value and changing locally
	x = 1, y = 1;
	for_each(v.begin(), v.end(), [=](int& r) mutable
	{
		int old = r;
		r *= 2;
		x = y;
		y = old;
	}
	);
	cout << "doubling" << endl;
	for_each(v.begin(), v.end(),
		[](int n){cout << n << " "; });
	cout << endl;
	cout << "x, y: " << x << ", " << y << endl;

	cout << "---------------------------" << endl;
	// capturing by reference
	v.clear();
	for (int i = 0; i < 10; i++)
	{
		v.push_back(i);
	}
	for_each(v.begin(), v.end(), [&x, &y](int& r)
	{
		int old = r;
		r *= 2;
		x = y;
		y = old;
	}
	);
	cout << "doubling" << endl;
	for_each(v.begin(), v.end(),
		[](int n){cout << n << " "; });
	cout << endl;
	cout << "x, y: " << x << ", " << y << endl;

	cout << "---------------------------" << endl;
	// capturing whole stack by reference
	v.clear();
	int i = 0;
	generate_n(back_inserter(v), 10,
		[&]()
	{
		return i++; 
	}
	);
	cout << "Initialzing" << endl;
	for_each(v.begin(), v.end(),
		[](int n){cout << n << " "; });
	cout << endl;
	cout << "i: " << i << endl;
	// [=, &i], [&, i] is possible

	cout << "---------------------------" << endl;
	// initialize a constant variable
	// mission impossible without lambda exmpression
	int a = 1;
	//const int const_val = 0;
	//if (a < 10)
	//{
	//	const_val = a*a;
	//}
	//else
	//{
	//	const_val = 1000;
	//}
	const auto const_val = [&]()
	{
		auto const_val2 = 0;
		if (a < 10)
		{
			const_val2 = a*a;
		}
		else
		{
			const_val2 = 1000;
		}
		return const_val2;

	}(); // lambda expression is invoked immediately

	cout << "---------------------------" << endl;
	// store a lambda expression
	auto f = [](int i){return i > 10; };
	cout << f(5) << endl;
	cout << typeid(decltype(f)).name() << endl;

	cout << "---------------------------" << endl;

	return 0;
}

