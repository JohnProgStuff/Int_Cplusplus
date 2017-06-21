#include <iostream>		// iostream.h
#include <vector>		// vector.h
#include <string>		// string.h

using namespace std;

class Person
{
private:
	string first;
	string last;
	int ID;

public:
	//Constructor
	Person() : ID{ -1 } //initialize only the id in constructor
	{}//Body of constructor

	Person(string f, string l, int id) : first{ f }, last{ l }, ID{ id }
	{
		print_name();
	}//Body of overloaded constructor

	Person(initializer_list<string> init) : ID{ -2 } 
	{
		auto n = begin(init);
		first = *n;
		n = end(init);
		n--;
		if (n != begin(init))
		{
			last = *n;
		}
	}//Body of constructor

	void print_name()
	{
		cout << first << " " << last << " " << ID << endl;
	}

};


int main()
{
	// 4 different ways to initialize variable.
	int a1 = 2;
	int a2(2);
	int a3;
	a3 = 2;
	int a4 = { 2 };   // This is the uniform initialization method.

	cout << "a1:" << a1 << ", a2:" << a2 << ", a3:" << a3 << ", a4:" << a4 << endl;

	Person person1("Kate", "Smith", 1);
	Person person2("Someone", "Else", 2);
	Person person3;		// person3 has been created but nothing initialized.
	Person person4();   // this is just a function declaration
	Person person5 = { "David", "Smith", 3 };

	// we can use a uniform initialization by using curly brackets.
	// like we did with a4 and person5.
	Person person6 = {};
	Person person7 = person5;
	Person person75 = { person5 };
	Person &person8 = person5;
	Person person9 = person5;
	person5 = person6;
	Person person85{ person6 };

	vector<int> v1 = { 1,2,3,4,5,6 };
	vector<int> v2{ 11,22,33,44,55,66 };
	vector<Person> v3 = { person1, person2, person3 };
	vector<Person> v4 = { person6, {"Jack", "Smith", 4}, person5 };
	// INITIALIZER_LIST's contain 0 or more strings
	// {1, 2, 3, 4}
	// {"JOHN", "JACOB", "JINGLE", "Himer", "SMITH"}


	Person person10 = { "Still", "Another", 5 };
	Person person11 = { "OnlyFirstName"};
	Person person12 = { "FirstN", "LastN", "afdsasf", };





} // end main