#pragma once
#include <string>
using namespace std;

class Person
{
private:
	string firstname;
	string lastname;
	int arbitrary;
public:
	// 3-arg constructor
	Person(string, string, int);
	~Person();

	int getNumber();
	void setNumber(int);
	string getName();

};