#include <iostream>
#include "Person.h"
using namespace std;

// 3-arg constructor
Person::Person(string first, string last, int arb) 
	: firstname{first}, lastname{last}, arbitrary{arb}
{}


Person::~Person()
{}


int Person::getNumber()
{
	return arbitrary;
}

void Person::setNumber(int num)
{
	arbitrary = num;
}

string Person::getName()
{
	return firstname + " " + lastname;
}

