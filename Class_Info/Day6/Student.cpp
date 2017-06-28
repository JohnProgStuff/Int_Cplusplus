#include "stdafx.h"
#include "Student.h"
#include <iostream>

using namespace std;

Student::Student(string first, string last, double d)
   : firstname(first), lastname(last), gpa(d)
{
}

Student::~Student()
{
}

string Student::getName()
{
	return firstname + " " + lastname;
}

Student Student::operator+(const Student& s)
{
	return Student(firstname, lastname, gpa + s.gpa);
}