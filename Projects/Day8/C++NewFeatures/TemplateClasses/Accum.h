#pragma once
#include "Person.h"

template<typename T>
class Accum
{
private:
	T total;
public:
	// constructor with a starting value
	Accum(T start) : total{start}
	{}
	
	T getTotal() { return total; }

	T operator+=(const T& t)
	{
		return total = total + t;
	}

};

// template specification
template<>
class Accum<Person>
{
private:
	int total;
public:
	Accum(int start) : total{ start }
	{}

	int getTotal() { return total; }

	int operator+=(Person& t)
	{
		return total = total + t.getNumber();
	}

};
