#include <vector>
#include <iostream>
#include "Noise.h"
#include "Person.h"

using namespace std;

int main()
{
	Noise n1{ "beep 1" };
	try {
		vector<int> v;
		v.push_back(1);
		//int val = v.at(99); // throws exception
		Noise n2{ "bloop 2" };
		Person p1{ "John", 1 };
		Person p2{ "Jack", 0 };

	}
	catch (out_of_range& e)
	{
		cout << "catch exception: " << e.what() << endl;
	}
	catch (exception& e)
	{
		cout << "exception: " << e.what() << endl;
	}
}