#include <iostream>
#include <tuple>
#include <string>
#include <vector>
#include <algorithm>
//#include 
#include <fstream>		// ofstream to file
#include <array>		// template array

using namespace std;

int main()
{
	tuple<int, string, double> entry1{};
	tuple<int, string, double> entry2{ 1, "Zach", 100.0 };

	// type safe feature
	//tuple<int, string, double> entry3{ "Notgood", 2, 200.0 }; // won't work because it is safe
	tuple<string, string> var{ "Hello", "World!" };
	tuple<tuple<string, string>, int, double>
		entry4{ var, 3, 300.0 };
	tuple<string, double, string, int>
		entry5{ "abc", 400.0, "xyz", 5 };
	vector<tuple<int, string, double>> people
	{
		make_tuple(2, "Brian", 101.1),
		make_tuple(3, "Beth", 202.2),
		make_tuple(4, "Kevin", 303.3)
	};
}