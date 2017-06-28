// TemplateClasses.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Accum.h"
#include <iostream>
#include <string>
#include "Student.h"

using namespace std;

int _tmain(int argc, _TCHAR* argv[])
{
	Accum<int> integers(0);
	integers += 3;
	integers += 7;
	cout << integers.getTotal() << endl;

	Accum<string> strings("");
	strings += "hello";
	strings += " world";
	strings += "!";
	cout << strings.getTotal() << endl;
	// fix2: overload + operator in Student class 
	//Accum<Student> students(Student("Alice", "Smith", 3.5));
	Student s1("David", "Ferro", 3.3);
	Student s2("Larry", "Zeng", 3.8);
	//students += s1;
	//students += s2;
	//cout << students.getTotal().getGPA() << endl;

	// fix3:
	Accum<Student> students(0.0);
	students += s1;
	students += s2;
	cout << students.getTotal() << endl;

	// fix1: no access to source code for Student class
	Accum<double> doubles(0.0);
	doubles += s1.getGPA();
	doubles += s2.getGPA();
	cout << doubles.getTotal() << endl;

	return 0;
}

