// UniformInitialization.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <string>
#include <vector>
#include <initializer_list>

using namespace std;

class Person
{
private:
	string first;
	string last;
	int arbitrary;
public:
	Person() : arbitrary(-1)
	{}
	Person(string firstname, string lastname, int arbitrarynumber)
		: first(firstname), last(lastname), arbitrary(arbitrarynumber)
	{}
	Person(initializer_list<string> init) : arbitrary(-2)
	{
		auto n = begin(init);
		first = *n;
		n = end(init);
		n--;
		if (n != begin(init))
		{
			last = *n;
		}
	}


};

int _tmain(int argc, _TCHAR* argv[])
{
	// many ways to initialize built in types
	int a = 2;
	int b(2);
	int c = { 2 };
	int d{ 2 };

	// C-style arrays
	int list[4] = { 2, 3, 4, 5 };
	int table[3][2] = { { 2, 3 }, { 3, 1 }, { 4, 9 } };

	// objects of user defined types
	Person p("David", "Smith", 32);
	Person q("Someone", "Else", 33);
	Person r;
	//Person s();	// not an object, but a function named s
	Person t{};
	Person u = r;
	Person v(u);

	Person w{ "Still", "Another", 34 };
	Person x{ "first", "middle", "last" };
	Person y{ "onlyfirst" };


	vector<int> vv{ 1, 2, 3, 4 };
	vector<Person> people
	{p, q, r, t, {"Jane", "Doe", 45}, u, v, {} };

	class Point
	{
	public:
		int _x, _y;
		Point(int x, int y) : _x(x), _y(y)
		{}
	};
	Point p1 = { 1, 2 };
	Point p2{ 20, 40 };
	int values[] = { 2, 3, 5 };
	int another[]{2, 3, 5};
	int* ptr = new int[3]{5, 6, 7};
	delete[] ptr;

	class Hexagon
	{
	private:
		int _points[6];
	public:
		Hexagon() : _points{ 1, 2, 3, 4, 5, 6 }
		{}
	};


	return 0;
}

