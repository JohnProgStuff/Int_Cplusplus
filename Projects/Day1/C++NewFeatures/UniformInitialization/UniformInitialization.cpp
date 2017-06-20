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
	Person() : ID(-1) //initialize only the id in structor
	{}//Body of constructor

	Person(string f, string l, int id) : first{ f }, last{ l }, ID{ id }
	{
		print_name();
	}//Body of overloaded constructor

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


	


} // end main