#pragma once
#include <string>
#include "Noise.h"

using namespace std;

class Person
{
private:
	string _name;
	int _ID;
public:
	Person(string n, int id) : _name{ n }, _ID{ id }
	{
		Noise np{ n + " Speaking" };
		if (_ID == 0)
		{
			throw invalid_argument("ID cannot be zero.");
		}
	}
	~Person()
	{

	}
};