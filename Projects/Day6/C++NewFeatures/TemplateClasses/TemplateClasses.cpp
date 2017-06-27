#include <string>
#include <iostream>
#include "Accum.h"
#include "Person.h"

using namespace std;

int main()
{
	// use Accum with int
	Accum<int> integers{ 0 };
	integers += 3;
	integers += 7;

	cout << integers.getTotal() << endl;

	// use Accum with string
	Accum<string> strings{ "" };
	strings += "Hello ";
	strings += "World!";

	cout << strings.getTotal() << endl;

	string str{ "fasfas;dlfkasjdfasf" };
	strings += str;
	cout << strings.getTotal() << endl;

	// use Accum with user defined type
	Person start{ "","",0 };
	//Accum<Person> people{start};
	Accum<Person> people{ 0 };
	Person p1("John", "Peterson", 20);
	Person p2("Jon", "Smith", 55);
	people += p1;
	people += p2;

	// get combined age of p1 and p2
	cout << people.getTotal() << endl;

}